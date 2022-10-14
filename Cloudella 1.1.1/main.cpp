#include "Node.h"
#include "Vault.h"

#include <iostream>


int main()
{
    Vault vault;
    vault.loadNodesFromDirectory("/Users/aptem/Desktop/own_github/bunch_of_nodes");

    for (const Node& node: vault)
    {
        std::cout << node.name << ' ' << node.text << '\n';
    }

    vault.uploadNodesToDirectory("/Users/aptem/Desktop");
}