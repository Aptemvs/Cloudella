#ifndef CLOUDELLA_NODE_H
#define CLOUDELLA_NODE_H

#include "json.hpp"
#include <string>
#include <fstream>
#include <utility>

using json = nlohmann::json;

struct Node
{
    std::string name;
    std::string text;

    Node()
    = default;

    Node(const json& JSON)
    {
        json JNodeStringParsed = json::parse(JSON.dump());

        this->name = JNodeStringParsed["name"];
        this->text = JNodeStringParsed["text"];
    }

    Node(const Node& node)
            : name(node.name), text(node.text)
    {}

    Node(std::string nodeName, std::string nodeText)
            : name(std::move(nodeName)), text(std::move(nodeText))
    {}

    json toJSON() const;

    void addNodeToDir(const std::string& path) const;
};

struct compareNodes
{
    inline bool operator()(const Node& lhs, const Node& rhs) const
    {
        return lhs.name < rhs.name;
    }
};

#endif //CLOUDELLA_NODE_H
