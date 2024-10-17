#include <string>
#include <sstream>
#include <queue>
#include <iostream>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec
{
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        if (!root)
            return "null";

        ostringstream out;
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();

            if (node)
            {
                out << node->val << " ";
                q.push(node->left);
                q.push(node->right);
            }
            else
            {
                out << "null ";
            }
        }

        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        if (data == "null")
            return nullptr;

        // "in" is a stream class to operate on strings. It internally maintains a pointer to the current reading position.
        istringstream in(data);
        string val;
        in >> val;
        TreeNode *root = new TreeNode(stoi(val));
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();

            if (in >> val && val != "null")
            {
                node->left = new TreeNode(stoi(val));
                q.push(node->left);
            }

            if (in >> val && val != "null")
            {
                node->right = new TreeNode(stoi(val));
                q.push(node->right);
            }
        }

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

int main()
{
    Codec ser, deser;
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    string serialized = ser.serialize(root);
    cout << "Serialized: " << serialized << endl;

    TreeNode *deserialized = deser.deserialize(serialized);
    string reserialized = ser.serialize(deserialized);
    cout << "Reserialized: " << reserialized << endl;

    return 0;
}
