#include "Vault.h"

void Vault::addNode(const Node& node)
{
    storage.insert(node);
}

std::set<Node, compareNodes>::iterator Vault::findNode(const std::string& nodeName)
{
    return storage.find(Node{nodeName, ""});
}

std::set<Node, compareNodes>::iterator Vault::begin()
{
    return storage.begin();
}

std::set<Node, compareNodes>::iterator Vault::end()
{
    return storage.end();
}

bool isPrefixAndExtensionCorrect(const std::string& path)
{
    std::string extension;
    std::string prefix;

    try
    {
        extension = path.substr(path.rfind('.'));
        prefix = path.substr(0, path.rfind('.')).substr(path.substr(0, path.rfind('.')).rfind('.'));
    } catch (...)
    {
        return false;
    }

    if (extension == ".json" && prefix == ".node")
    {
        return true;
    }

    return false;
}

void Vault::loadNodesFromDirectory(const std::string& path)
{
    DIR* directory = opendir(path.c_str());

    if (directory != nullptr)
    {
        struct dirent* diread = readdir(directory);

        while (diread != nullptr)
        {
            std::filesystem::path fullFilePath = path + '/' + diread->d_name;

            if (isPrefixAndExtensionCorrect(fullFilePath.string()))
            {
                std::ifstream ifstr(fullFilePath);
                json tempJSON = json::parse(ifstr);

                storage.insert(Node(tempJSON));
            }
            diread = readdir(directory);
        }
        closedir(directory);
    } else
    {
        perror("Directory not opened");
    }
}

void Vault::uploadNodesToDirectory(const std::string& path)
{
    DIR* directory = opendir(path.c_str());

    if (directory != nullptr)
    {
        for (const Node& node: storage)
        {
            node.addNodeToDir(path);
        }
        closedir(directory);
    } else
    {
        perror("Directory not opened");
    }
}