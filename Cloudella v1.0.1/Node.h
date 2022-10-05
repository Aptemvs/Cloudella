#ifndef CLOUDELLA_NODE_H
#define CLOUDELLA_NODE_H

#include "json.hpp"
#include <string>
#include <fstream>

using json = nlohmann::json;

struct Node
{
    std::string name;
    std::string text;

    Node()
    {}

    Node(const json& JSON)
    {
        json JNodeStringParsed = json::parse(JSON.dump());

        this->name = JNodeStringParsed["name"];
        this->text = JNodeStringParsed["text"];
    }

    Node(const Node& node)
            : name(node.name), text(node.text)
    {}

    Node(const std::string& nodeName, const std::string& nodeText)
            : name(nodeName), text(nodeText)
    {}

    json toJSON() const;

    void addNodeToDir(const std::string& path) const;
};

struct compareNodes
{
    inline bool operator()(const Node& lhs, const Node& rhs)
    {
        return lhs.name < rhs.name;
    }
};

#endif //CLOUDELLA_NODE_H
