#ifndef CLOUDELLA_VAULT_H
#define CLOUDELLA_VAULT_H

#include "dirent.h"
#include "Node.h"

#include <set>
#include <fstream>

struct Vault
{
    void addNode(const Node& node);

    std::multiset<Node, compareNodes>::iterator findNode(const std::string& nodeName);

    std::multiset<Node, compareNodes>::iterator begin();

    std::multiset<Node, compareNodes>::iterator end();

    void loadNodesFromDirectory(const std::string& path);

    void uploadNodesToDirectory(const std::string& path);

private:
    std::set<Node, compareNodes> storage;
};

#endif //CLOUDELLA_VAULT_H
