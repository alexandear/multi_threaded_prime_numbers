#include "Xml.h"
#include "Utils.h"

#include <utility>
#include <cctype>
#include <algorithm>

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
    m_children.emplace_back(std::move(tag));
    return m_children.back().get();
}

Tag* Tag::AddChild(std::string tagName)
{
    return AddChild(std::make_shared<Tag>(std::move(tagName)));
}

Tag* Tag::AddChild(std::string tagName, Value value)
{
    return AddChild(std::make_shared<Tag>(std::move(tagName), std::move(value)));
}

const Tag* Tag::GetFirstChild() const
{
    if (m_children.empty())
        throw Exception("children are empty");

    return std::begin(m_children)->get();
}

const Tag* Tag::GetFirstChild(const std::string& name) const
{
    auto it = std::find_if(std::begin(m_children), std::end(m_children), [&name](const auto& tag) {
        return tag->m_name == name;
    });
    if (it == std::end(m_children))
        throw Exception("child is not found");

    return it->get();
}

std::vector<Tag*> Tag::GetChildren(const std::string& name) const
{
    std::vector<Tag*> tags;

    for (const auto& tag : m_children)
    {
        if (tag->m_name == name)
            tags.emplace_back(tag.get());
    }

    return tags;
}

Document::Document(const std::string& contents)
{
    Lexical(contents);
    Parse();
}

Tag* Document::AddRoot(std::string name)
{
    return m_root.AddChild(std::make_shared<Tag>(std::move(name)));
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
    m_tokens.emplace_back(Token{text, type});
    text.clear();
}

void Document::Parse()
{
    Tag* parentTag = &m_root;
    std::shared_ptr<Tag> currentTag;

    for (const auto& token : m_tokens)
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
            if (currentTag)
                currentTag->SetName(token.content);
            break;
        case Token::Type::TagContent:
            if (currentTag)
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
        os << "</" << tag.GetName() << ">";
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
        os << spacesEnd << "</" << tag.GetName() << ">";
        os << '\n';
    }
}

Document File::Read(const std::string& path)
{
    Ifstream file(path);

    std::string contents;
    std::string line;
    while (std::getline(file, line))
        contents += line + '\n';

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
