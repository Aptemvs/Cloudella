#include "Node.h"

json Node::toJSON() const
{
    json jNode{};
    jNode["name"] = this->name;
    jNode["text"] = this->text;
    return jNode;
}

void Node::addNodeToDir(const std::string& path) const
{
    std::string filename(this->name + ".node" + ".json");
    std::string filepath = (path + "/" + filename);

    std::fstream output_fstream;
    output_fstream.open(filepath, std::ios_base::out);

    json tempJSON = this->toJSON();
    output_fstream << tempJSON << '\n';
}

