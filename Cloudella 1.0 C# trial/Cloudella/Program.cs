using DynamicNode;
using DynamicVault;

internal class Program
{
    private static void Main()
    {
        Vault vault1 = new Vault();
        Vault vault2 = new Vault();

        Node node1 = new Node
        {
            name = "node1Name",
            text = "node1Text",
            value = "node1Value"
        };
        Node node2 = new Node
        {
            name = "node2Name",
            text = "node2Text",
            value = 2222222
        };
        Node node3 = new Node
        {
            name = "node3Name",
            text = "node3Text",
            value = new List<int> { 3, 3, 3, 3 }
        };

        //vault1.AddNode(node1);
        //vault1.AddNode(node2);
        //vault1.AddNode(node3);

        vault1.UploadNodesToDirectory("/Users/aptem/Desktop/nodes");

        vault2.LoadNodesFromDirectory("/Users/aptem/Desktop/nodes");

        vault2.PrintStorage();
    }
}