#pragma once

#include <memory>
#include <string>
#include <vector>
#include <ostream>

namespace red
{
namespace xml
{
class Exception : public std::runtime_error
{
public:
    explicit Exception(const char* msg) : std::runtime_error(msg) {}
};

struct Token
{
    enum class Type
    {
        OpeningTagStart,
        ClosingTagStart,
        TagEnd,
        TagName,
        TagContent,
    };

    std::string content;
    Type type;
};

class Value
{
public:
    Value() = default;
    explicit Value(std::string value) : m_value(std::move(value)) {}

    std::string ToString() const { return m_value; }
    int ToInt() const { return std::stoi(m_value); }

private:
    std::string m_value;
};

class Tag
{
public:
    Tag() : Tag("") {}
    explicit Tag(std::string name) : Tag(std::move(name), {}) {}
    Tag(std::string name, Value value);

    Tag* GetParent() const { return m_parent; }
    std::string GetName() const { return m_name; }
    const Value& GetValue() const { return m_value; }
    const std::vector<std::shared_ptr<Tag>>& GetChildren() const { return m_children; }
    void SetName(std::string name);
    void SetValue(Value value) { m_value = std::move(value); }
    Tag* AddChild(std::shared_ptr<Tag> tag);
    Tag* AddChild(std::string tagName);
    Tag* AddChild(std::string tagName, Value value);
    const Tag* GetFirstChild() const;
    Tag* GetFirstChild();
    const Tag* GetFirstChild(const std::string& name) const;
    Tag* GetFirstChild(const std::string& name);
    std::vector<Tag*> GetChildren(const std::string& name) const;

private:
    std::string m_name;
    Value m_value;
    Tag* m_parent;
    std::vector<std::shared_ptr<Tag>> m_children;
};

inline Tag* Tag::GetFirstChild()
{
    return const_cast<Tag*>(static_cast<const Tag*>(this)->GetFirstChild());
}

inline Tag* Tag::GetFirstChild(const std::string& name)
{
    return const_cast<Tag*>(static_cast<const Tag*>(this)->GetFirstChild(name));
}

class Document
{
public:
    Document() = default;
    explicit Document(const std::string& contents);

    const Tag& GetRoot() const { return m_root; }
    Tag& GetRoot() { return m_root; }
    const std::vector<Token>& GetTokens() const { return m_tokens; }
    void OutputAllData(std::ostream& os) const { OutData(os, m_root); }

    Tag* AddRoot(std::string name);

private:
    enum class State
    {
        InsideTag,
        OutsideTag,
    };

    void Lexical(const std::string& contents);
    void AddToken(std::string& text, Token::Type type);
    void Parse();

    static void OutData(std::ostream& os, const Tag& tag, std::size_t depth = 0);

    Tag m_root;
    std::vector<Token> m_tokens;
};

class File
{
public:
    static Document Read(const std::string& path);
    static void Write(const std::string& path, const Document& document);
};
} // namespace xml
} // namespace red
