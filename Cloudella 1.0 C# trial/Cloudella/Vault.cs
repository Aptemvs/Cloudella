using DynamicNode;

namespace DynamicVault;

public class Vault
{
    public void AddNode(Node node)
    {
        storage.Add(node);
    }

    //Object FindNode(string name)
    //{
    //}

    public void LoadNodesFromDirectory(string path)
    {
        foreach (string file in Directory.EnumerateFiles(path, "*.node.json"))
        {
            string json = File.ReadAllText(file);
            Node node = Node.ToNode(json);
            //Console.WriteLine(node.value.GetType());
            //storage.Add(Node.ToNode(json));
        }
    }

    public void UploadNodesToDirectory(string path)
    {
        foreach (Node node in storage)
        {
            node.SaveNodeToFileAsync(path);
        }
    }

    public void PrintStorage()
    {
        foreach (Node node in storage)
        {
            Console.WriteLine($"{node}");
        }
    }

    private List<Node> storage = new List<Node>();
}

