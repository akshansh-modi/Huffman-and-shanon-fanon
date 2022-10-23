#include <iostream>
using namespace std;
#include <unordered_map>
#include <queue>
unordered_map<char, int> counter;
class chbit
{
public:
    bool *code;
    int size;
};
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
void assign(tree *root, int len, bool *value);
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

unordered_map<char, chbit *> bitcode;

int main()
{
    string text;
    cout << "Enter string : ";
    getline(cin, text);
    tree *root = buildtree(text);
    printtree(root);
    // vector<bool> p;
    // p.push_back(1);
    // p.push_back(0);
    // cout << sizeof(p[1]);
    // bool tb[2] = {1, 0};
    // chbit t(2, tb);
    // cout << "\n"
    //      << sizeof(t);
    assign(root, 0, NULL);
    for (auto i : bitcode)
    {

        cout << i.first << ":";
        for (int j = 0; j < i.second->size; j++)
        {
            cout << i.second->code[j];
            /* code */
        }
        cout << "\n";
    }

    return 0;
}

void assign(tree *root, int len, bool *value)
{
    if (root == NULL)
    {
        return;
    }

    if (root->ch != NULL)
    {
bitcode[root->ch];
chbit * temp= new chbit;
temp->size= len;
temp->code=value;
        bitcode[root->ch]=temp;
        return;
    }
    bool *valueright = new bool(len + 1);
    bool *valueleft = new bool(len + 1);
    for (int i = 0; i < len; i++)
    {
        valueright[i] = value[i];
        valueleft[i] = value[i];
    }
    valueright[len] = 1;
    valueleft[len] = 0;

    assign(root->left, len + 1, valueleft);
    assign(root->right, len + 1, valueright);

    delete[] value;

    return;
}