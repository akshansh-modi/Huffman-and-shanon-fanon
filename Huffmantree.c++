#include <iostream>
using namespace std;
#include <fstream>

#include <unordered_map>
#include <queue>
unordered_map<char, int> counter;
class chbit // will be used to assign bitcode to characters
{
public:
    bool *code;
    int size;
};
void freqcount(string text) // assign frequency of occurance to
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
class comparenode // for making of minimum priority queue
{
public:
    bool operator()(tree *l, tree *r)

    {
        return (l->freq >= r->freq);
    }
};

priority_queue<tree *, vector<tree *>, comparenode> minheap;
tree *buildtree() // to build tree
{
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
        tree *parent = new tree('\0', parentfreq, smallleft, smallright);
        minheap.push(parent);
    }

    return minheap.top();
}
void printtree(tree *root) // to check tree made
{
    if (root == NULL)
    {
        return;
    }
    if (root->ch != '\0')
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

void encode()
{

    /*
    string text;
    cout << "Enter string : ";
    getline(cin, text);
    tree *root = buildtree(text);
    printtree(root);

    assign(root, 0, NULL);
    for (auto i : bitcode)
    {

        cout << i.first << ":";
        for (int j = 0; j < i.second->size; j++)
        {
            cout << i.second->code[j];

        }
        cout << "\n";
    }
    */
    //--------------------------------------------------------------------------------------------------------------
    // encoding part
    string line;
    ofstream fout;
    fout.open("encode.txt", ios::app);
    ifstream fin;
    fin.open("sample.txt");
    while (getline(fin, line))
    {
        // cout << line << endl;
        freqcount(line);
    }
    tree *root = buildtree();
    // printtree(root);

    assign(root, 0, NULL);
    /*  for (auto i : bitcode)
       {

           cout << i.first << ":";
           for (int j = 0; j < i.second->size; j++)
           {
               cout << i.second->code[j];
              // code
           }
           cout << "\n";
       }
       */
    fin.close();

    fin.open("sample.txt");
    char cr;
    int freq;

    for (auto i : counter)
    {
        cr = i.first;
        freq = i.second;
        fout << cr << "\t" << freq << "\t";
    }
    fout << "\n"
         << "==lol==";
    fout << "\n";
    int bufcount = 0;
    char buff = '\0';
    while (getline(fin, line))
    {

        for (int f = 0; f < line.length(); f++)
        {

            chbit *temp = bitcode[line[f]];
            for (int i = 0; i < temp->size; i++)
            {
                if (temp->code[i])
                {
                    buff |= 1 << (7 - bufcount);
                }
                bufcount++;
                if (bufcount == 8)
                {
                    fout << buff;
                    bufcount = 0;
                    buff = '\0';
                }
            }
        }
        /*char k = 'l';
           for (int i = 0; i < 8; i++)
           {
               if ((k >> (7 - i)) & 1)
               {
                   buff |= 1 << (7 - i);// writing bit
               }
           }

            for (int i = 0; i < 8; i++)
           {
               int tmp = (buff >> (7-i)) & 0x1;// getting bit
               cout << tmp;
           }


       */
    }

    // fout.write((char *)&obj, sizeof(obj));

    fin.close();
    fout.close();

    //----------------------------------------------------------------------------------------------------------------
}

int main()
{
    encode();

    /*
    string text;
    cout << "Enter string : ";
    getline(cin, text);
    tree *root = buildtree(text);
    printtree(root);

    assign(root, 0, NULL);
    for (auto i : bitcode)
    {

        cout << i.first << ":";
        for (int j = 0; j < i.second->size; j++)
        {
            cout << i.second->code[j];

        }
        cout << "\n";
    }
    */
    //--------------------------------------------------------------------------------------------------------------
    // encoding part
    string line;
    ofstream fout;
    ifstream fin;
    fout.open("sample2.txt", ios::app);
    fin.open("encode.txt");
    bool found = 0;
    char cr;
    int freq;

    fin >> cr >> freq;
    counter[cr] = freq;
    fin.close();
    fout.close();

    //----------------------------------------------------------------------------------------------------------------

    return 0;
}

void assign(tree *root, int len, bool *value) // to assign bitcode to all char in tree
{
    if (root == NULL)
    {
        return;
    }

    if (root->ch != '\0')
    {
        bitcode[root->ch];
        chbit *temp = new chbit;
        temp->size = len;
        temp->code = value;
        bitcode[root->ch] = temp;
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