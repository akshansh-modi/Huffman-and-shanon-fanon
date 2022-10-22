#include <iostream>
using namespace std;
#include <unordered_map>
#include <queue>
class chbit;
unordered_map<char, int> counter;

void freqcount(string text)
{

    for (int i = 0; i < text.length(); i++)
    {
        counter[text[i]]++;
    }
    return;
}
class tree
{
public:
    char ch;
    int freq;
    tree *right;
    tree *left;

    tree(char ch, int freq, tree *left = NULL, tree *right = NULL)
    {
        this->ch = ch;
        this->freq = freq;
        this->left = left;
        this->right = right;
    }
    bool compare(tree *other)
    {
        return this->freq < other->freq;
    }
};
// priority queue -->minimum
// max or min heap??
class comparenode
{
public:
    bool operator()(tree *l, tree *r)

    {
        return (l->freq > r->freq);
    }
};

priority_queue<tree *, vector<tree *>, comparenode> minheap;
tree *buildtree(string text)
{
    freqcount(text);
    for (auto i : counter)
    {

        tree *t = new tree(i.first, i.second);
        minheap.push(t);
    }

    while (minheap.size() != 1)
    {
        tree *smallleft = minheap.top();
        minheap.pop();
        tree *smallright = minheap.top();
        minheap.pop();
        int parentfreq = smallleft->freq + smallright->freq;
        tree *parent = new tree(NULL, parentfreq, smallleft, smallright);
        minheap.push(parent);
    }

    return minheap.top();
}
void printtree(tree *root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->ch != NULL)
    {
        cout << root->ch << ":" << root->freq;
    }
    else
    {
        cout << ":" << root->freq;
    }
    cout << "\n";
    cout << " L:";
    printtree(root->left);
    cout << " R:";
    printtree(root->right);
    cout << "\n";

    return;
}

int main()
{
    string text;
    cout << "Enter string : ";
    getline(cin, text);
    tree *root = buildtree(text);
    printtree(root);
    return 0;
}

class chbit
{
    bool *bitcode;
    int size;
    char ch;

    chbit(char ch, int size, bool *bitcode)
    {
        this->ch = ch;
        this->size = size;
        this->bitcode = bitcode;
    }
};