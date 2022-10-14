using System.Text.Json;

namespace DynamicNode;

public class Node
{
    public string name { get; set; }
    public string text { get; set; }
    public dynamic value { get; set; }

    public Node()
    {
    }

    public Node(Node node)
    {
        name = node.name;
        text = node.text;
        value = node.value;
    }

    public static Node? ToNode(string json)
    {
        return JsonSerializer.Deserialize<Node>(json);
    }

    public static string ToJson(Node node)
    {
        return JsonSerializer.Serialize(node);
    }

    public async void SaveNodeToFileAsync(string path)
    {
        string title = "/" + this.name + ".node.json";
        string json = Node.ToJson(this);

        await File.WriteAllTextAsync(path + title, json);
    }
}