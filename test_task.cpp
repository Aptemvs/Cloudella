#include "dirent.h"
#include "json.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <set>

using json = nlohmann::json;

std::string randomString(size_t strSize)
{
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string result;

    for (size_t i = 0; i < strSize; i++)
    {
        result += alphabet[rand() % i];
    }

    return result;
}

struct Node
{
    std::string name;
    std::string text;

    Node()
    {}

    Node(const Node& node)
            : name(node.name), text(node.text)
    {}

    Node(const std::string& nodeName, const std::string& nodeText)
            : name(nodeName), text(nodeText)
    {}
};

json NodeToJSON(const Node& node)
{
    json jNode{};
    jNode["name"] = node.name;
    jNode["text"] = node.text;
    return jNode;
}

Node JSONtoNode(const json& JNode)
{
    std::string JNodeString = JNode.dump();
    json JNodeStringParsed = json::parse(JNodeString);
    return Node(JNodeStringParsed["name"], JNodeStringParsed["text"]);
}

Node createRandomNode()
{
    return Node{randomString(8), randomString(30)};
}

struct compareNodes
{
    inline bool operator()(const Node& lhs, const Node& rhs)
    {
        return lhs.name < rhs.name;
    }
};

struct Vault
{
    void addNode(const Node& node)
    {
        storage.insert(node);
    }

    std::multiset<Node, compareNodes>::iterator findNode(const std::string& nodeName)
    {
        return storage.find(Node{nodeName, ""});
    }

    std::multiset<Node, compareNodes>::iterator begin()
    {
        return storage.begin();
    }

    std::multiset<Node, compareNodes>::iterator end()
    {
        return storage.end();
    }

    void loadNodesFromDirectory(const std::string& path)
    {
        DIR* directory;
        struct dirent* diread;

        const char* cpath = path.c_str();

        if ((directory = opendir(cpath)) != nullptr)
        {
            while ((diread = readdir(directory)) != nullptr)
            {
                std::string prefix;
                std::string fileName;

                std::filesystem::path filePath = diread->d_name;
                std::filesystem::path fullFilePath = path + '/' + diread->d_name;

                std::string filePathStringStem = filePath.stem().string();

                if (std::count(filePathStringStem.begin(), filePathStringStem.end(), '.') > 0)
                {
                    prefix = filePathStringStem.substr(filePathStringStem.rfind("."));
                    fileName = filePathStringStem.substr(0, filePathStringStem.rfind("."));
                }

                if (filePath.extension() == ".json" && prefix == ".node")
                {
                    std::ifstream ifstr(fullFilePath.string());
                    json tempJSON = json::parse(ifstr);
                    Node tempNode = JSONtoNode(tempJSON);

                    storage.insert(tempNode);
                }
            }
            closedir(directory);
        } else
        {
            perror("File not opened");
        }
    }

    void uploadNodesToDirectory(const std::string& path)
    {
        DIR* directory;

        const char* cpath = path.c_str();

        if ((directory = opendir(cpath)) != nullptr)
        {
            for (const Node& node: storage)
            {
                std::string filename(node.name + ".node" + ".json");
                std::string filepath = (path + "/" + filename);

                std::fstream output_fstream;
                output_fstream.open(filepath, std::ios_base::out);

                json tempJSON = NodeToJSON(node);
                output_fstream << tempJSON << '\n';
            }
            closedir(directory);
        } else
        {
            perror("Directory not opened");
        }
    }

private:
    std::multiset<Node, compareNodes> storage;
};

int main()
{
    Vault vault;

    Node test1{"abc", "123"};
    Node test2{"cde", "321"};
    Node test3{"dfg", "2135"};

    vault.addNode(test1);
    vault.addNode(test2);
    vault.addNode(test3);

    vault.uploadNodesToDirectory("/Users/aptem/Desktop/abc");
}