#include <iostream>
using namespace std;
#include <fstream>
#define HEADER_TEXT_SEPERATOR char(132)
#define SPACE char(129)
#include <unordered_map>
#include <queue>

unordered_map<char, int> counter;

void freqcount(string text) // assign frequency of occurance to
{
    int length = text.length();
    for (int i = 0; i < length; i++)
    {
        if (text[i] == '\n')
        {
            counter['\n']++;
        }
        else
        {
            counter[text[i]]++;
        }
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
};

void assign(tree *root, string value);
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
/*
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
}*/
//
unordered_map<char, string> bitcode;
unordered_map<string, char> charac;
void encode()
{

    string line;
    ofstream fout;
    fout.open("encode.txt", ios::app);
    ifstream fin;
    fin.open("sample.txt");
    while (getline(fin, line))
    {
        freqcount(line);
    }
    tree *root = buildtree();

    assign(root, "");
    fin.close();

    fin.open("sample.txt");
    char cr;
    string code;

    for (auto i : bitcode)
    {
        cr = i.first;
        code = i.second;
        if (cr == ' ')
        {
            fout << SPACE << "\t" << code << "\t";
        }

        else
        {
            fout << cr << "\t" << code << "\t";
        }
    }
    fout << "\n"
         << HEADER_TEXT_SEPERATOR;
    fout << "\n";
    int bufcount = 0;
    char buff = '\0';
    while (getline(fin, line))
    {
        int lengthf = line.size();
        for (int f = 0; f < lengthf; f++)
        {

            string temp = bitcode[line[f]];
            int lengthi = temp.size();
            for (int i = 0; i < lengthi; i++)
            {
                if (temp[i] == '1')
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
    }

    fin.close();
    fout.close();
}

void decode()
{
    string line;
    ofstream fout;
    ifstream fin;
    fout.open("sample2.txt", ios::app);
    fin.open("encode.txt");
    bool found = 0;
    char cr;
    string code;
    fin >> cr;
    while (cr != HEADER_TEXT_SEPERATOR)
    {
        fin >> code;
        if (cr == SPACE)
        {
            bitcode[' '] = code;
        }

        else
        {
            bitcode[cr] = code;
        }
        fin >> cr;
    }

    for (auto i : bitcode)
    {
        charac[i.second] = i.first;
    }

    string br = "";
    string lined;
    while (getline(fin, lined))
    {
        int lengthd = lined.length();
        for (int f = 0; f < lengthd; f++)
        {

            for (int i = 0; i < 8; i++)
            {
                if ((lined[f] >> (7 - i)) & 1)
                {
                    br += "1";
                }
                else
                {
                    br += "0";
                }
                if (charac.count(br))
                {

                    fout << charac[br];
                    br = "";
                }
            }
        }
    }

    fin.close();
    fout.close();
}

int main()
{
    // encode();
    decode();

    return 0;
}

void assign(tree *root, string value) // to assign bitcode to all char in tree
{
    if (root == NULL)
    {
        return;
    }

    if (root->ch != '\0')
    {
        bitcode[root->ch];

        bitcode[root->ch] = value;
        return;
    }

    string valueright = value + "1";
    string valueleft = value + "0";

    assign(root->left, valueleft);
    assign(root->right, valueright);

    return;
}