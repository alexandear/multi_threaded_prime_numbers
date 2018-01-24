#include "Xml.h"
#include "Utils.h"

#include <utility>
#include <cctype>

namespace red
{
namespace xml
{
Tag::Tag(std::string name, Value value)
    : m_name(std::move(name)), m_value(std::move(value)), m_parent(this)
{
}

void Tag::SetName(std::string name)
{
    if (m_name.empty())
        m_name = std::move(name);
}

Tag* Tag::AddChild(std::shared_ptr<Tag> tag)
{
    tag->m_parent = this;
    m_children.push_back(std::move(tag));
    return m_children.back().get();
}

const Tag* Tag::GetFirstChild() const
{
    if (m_children.empty())
        throw std::runtime_error("children are empty");

    return std::begin(m_children)->get();
}

const Tag* Tag::GetFirstChild(const std::string& name) const
{
    for (const auto& tag : m_children)
        if (tag->m_name == name)
            return tag.get();

    throw std::runtime_error("child is not found");
}

std::vector<Tag*> Tag::GetChildren(const std::string& name) const
{
    std::vector<Tag*> tags;

    for (const auto& tag : m_children)
        if (tag->m_name == name)
            tags.push_back(tag.get());

    return tags;
}

Document::Document(const std::string& contents)
{
    Lexical(contents);
    Parse();
}

void Document::Lexical(const std::string& contents)
{
    std::string token;
    State state = State::OutsideTag;

    for (auto it = std::cbegin(contents); it != std::cend(contents); ++it)
    {
        if (std::isspace(*it))
            continue;

        token += *it;

        switch (state)
        {
        case State::OutsideTag:
            if (token == "<")
            {
                if (*std::next(it, 1) == '/')
                    continue;

                AddToken(token, Token::Type::OpeningTagStart);
                state = State::InsideTag;
            }
            else if (token == "</")
            {
                AddToken(token, Token::Type::ClosingTagStart);
                state = State::InsideTag;
            }
            else if (*std::next(it, 1) == '<')
            {
                AddToken(token, Token::Type::TagContent);
            }
            break;
        case State::InsideTag:
            if (*std::next(it, 1) == '>' || *std::next(it, 1) == ' ')
            {
                AddToken(token, Token::Type::TagName);
            }
            if (token == ">")
            {
                AddToken(token, Token::Type::TagEnd);
                state = State::OutsideTag;
            }
            break;
        }
    }
}

void Document::AddToken(std::string& text, Token::Type type)
{
    m_tokens.push_back(Token{text, type});
    text.clear();
}

void Document::Parse()
{
    Tag* parentTag = &m_root;
    std::shared_ptr<Tag> currentTag;

    for (Token token : m_tokens)
    {
        switch (token.type)
        {
        case Token::Type::OpeningTagStart:
            currentTag = std::make_shared<Tag>();
            parentTag = parentTag->AddChild(currentTag);
            break;
        case Token::Type::ClosingTagStart:
            parentTag = parentTag->GetParent();
            break;
        case Token::Type::TagName:
            currentTag->SetName(token.content);
            break;
        case Token::Type::TagContent:
            currentTag->SetValue(Value(token.content));
            break;
        case Token::Type::TagEnd:
            break;
        }
    }
}

void Document::OutData(std::ostream& os, const Tag& tag, std::size_t depth /*= 0*/)
{
    if (tag.GetChildren().empty())
    {
        os << "<" << tag.GetName() << "/>";
        os << '\n';
        return;
    }

    std::string spacesBegin;
    for (std::size_t i = 0; i < depth; ++i)
        spacesBegin.append("  ");

    for (const auto& child : tag.GetChildren())
    {
        os << spacesBegin << "<" << child->GetName() << ">";
        std::string value = child->GetValue().ToString();
        if (!value.empty())
            os << value;
        else
            os << '\n';
        OutData(os, *child, depth + 1);
    }
    if (!tag.GetName().empty())
    {
        std::string spacesEnd;
        for (std::size_t i = 0; i < depth - 1; ++i)
            spacesEnd.append("  ");
        os << spacesEnd << "<" << tag.GetName() << "/>";
        os << '\n';
    }
}

Document File::Read(const std::string& path)
{
    Ifstream file(path);

    std::string contents;
    std::string line;
    while (std::getline(file, line))
    {
        line += '\n';
        contents += line;
    }

    if (file.bad())
        throw FstreamException("error while reading file");

    return Document(contents);
}

void File::Write(const std::string& path, const Document& document)
{
    Ofstream file(path);
    document.OutputAllData(file);
}
} // namespace xml
} // namespace red
