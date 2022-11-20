#include <iostream>
using namespace std;
#include <fstream>
#define INTERNAL_NODE_CHARACTER char(188)
#define PSEUDO_EOF char(129)
#define CHARACTER_CODE_SEPERATOR char(189)
#define HEADER_ENTRY_SEPERATOR char(190)
#define HEADER_TEXT_SEPERATOR char(191)
#include <unordered_map>
#include <queue>
#include <unistd.h>
#include <windows.h>
unordered_map<char, int> counter;

void freqcount(char text) // assign frequency of occurance to characters
{

    counter[text]++;
}
class tree
{
public:
    char ch;
    int freq;
    tree *right;
    tree *left;
    tree() {}
    tree(char ch, tree *left = NULL, tree *right = NULL)
    {
        this->ch = ch;
        this->left = left;
        this->right = right;
    }
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
        return (l->freq > r->freq);
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
        tree *parent = new tree(INTERNAL_NODE_CHARACTER, parentfreq, smallleft, smallright);
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
// tree *
void encode(string filename, string encodefile)
{

    ofstream fout;
    fout.open(encodefile, ios::app);
    ifstream fin;
    fin.open(filename);
    char c;
    while (fin.get(c))
    {
        freqcount(c);
    }
    counter[PSEUDO_EOF] = 1;

    tree *root = buildtree();
    assign(root, ""); // saare characters ko bitcode assign hon gayeeeee
    fin.close();
    /*
     for (auto i : counter)
     {
         cout << i.first << " : " << i.second << "\n";
     }
     cout << "\n\n";
     for (auto i : bitcode)
     {
         cout << i.first << " : " << i.second << "\n";
     }
 */
    fin.open(filename);
    char cr;
    string code;

    for (auto i : bitcode)
    {
        cr = i.first;
        code = i.second;

        fout << cr << CHARACTER_CODE_SEPERATOR << code << HEADER_ENTRY_SEPERATOR;
    }
    fout << HEADER_TEXT_SEPERATOR;

    int bufcount = 0;
    char buff = '\0';

    while (fin.get(c))
    {

        string temp = bitcode[c];
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
    string temp = bitcode[PSEUDO_EOF];
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
    if (buff != '\0')
    {
        fout << buff;
    }
    // fout << PSEUDO_EOF;
    fin.close();
    fout.flush();
    fout.close();
    // return root;
}

void decode(string encodefilename, string decodefilename)
{

    ofstream fout;
    ifstream fin;
    fout.open(decodefilename, ios::app);
    fin.open(encodefilename);
    char cr;
    char key;
    string code;
    cr = fin.get();
    key = cr;

    while (cr != HEADER_TEXT_SEPERATOR)
    {

        if (cr == CHARACTER_CODE_SEPERATOR)
        {

            fin.get(cr);
            while (cr != HEADER_ENTRY_SEPERATOR)
            {
                bitcode[key] += cr;
                fin.get(cr);
            }
        }

        else
        {
            key = cr;
            fin.get(cr);
        }
    }
    // for (auto i : bitcode)
    // {
    //     cout << i.first << " : " << i.second << "\n";
    // }
    for (auto i : bitcode)
    {
        charac[i.second] = i.first;
    }

    string br = "";
    char ct;

    while (fin.get(ct))
    {

        for (int i = 0; i < 8; i++)
        {
            if ((ct >> (7 - i)) & 1)
            {
                br += "1";
            }
            else
            {
                br += "0";
            }
            if (charac.count(br))
            {
                if (charac[br] == PSEUDO_EOF)
                {
                    break;
                }
                fout << charac[br];
                br = "";
            }
        }
        if (charac.count(br))
        {
            if (charac[br] == PSEUDO_EOF)
            {
                break;
            }
        }
    }

    fin.close();
    fout.close();
}

// void entry();

// void attach(tree *root, char c, string i.second)
// {

//     return;
// }
tree *decodetree(tree *root)
{

    tree *temp;
    for (auto i : bitcode)
    {
        tree *temp = root;
        string bits = i.second;
        int j = bits.size() - 1;

        for (int k = 0; k < bits.size(); k++)
        {

            if (bits[k] == '1')
            {
                if (k == j)
                {
                    temp->right = new tree(i.first);
                }
                else
                {

                    if (temp->right == NULL)
                    {
                        temp->right = new tree(INTERNAL_NODE_CHARACTER);
                    }
                    temp = temp->right;
                }
            }
            else
            {
              if (k == j)
                {
                    temp->left = new tree(i.first);
                }
                else
                {

                    if (temp->left == NULL)
                    {
                        temp->left = new tree(INTERNAL_NODE_CHARACTER);
                    }
                    temp = temp->left;
                }
            }
        }
    }
    return root;
}
void printdecode(tree *root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->ch != INTERNAL_NODE_CHARACTER)
    {
        cout << root->ch;
    }
    else
    {
        cout << ":";
    }
    cout << "\n";
    cout << " L:";
    printdecode(root->left);
    cout << " R:";
    printdecode(root->right);
    cout << "\n";

    return;
}
int main()
{
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    // entry();
    string filename;
    string encodefile;
    string decodefile;
    /*
     cout << "\n1. Encode\n2. Decode\n";
     int x;
     cin >> x;
     switch (x)
     {
     case 1:
         // cout << "enter filename: ";
         // cin >> filename;
         // cout << "enter encodefile: ";^
         // cin >> encodefile;
         // tree * root = encode(filename, encodefile);
         // tree * root =
         encode("sample.txt", "encode.txt");

         break;
     case 2:

         // cout << "enter encodefile: ";
         // cin >> encodefile;
         // cout << "enter decodefile: ";
         // cin >> decodefile;
         decode("encode.txt", "decode.txt");
         break;
     // case 3:
     //     copy();
     //     break;
     default:
         break;
     }
     */
    int ch1, ch2;
    cout << "Press" << endl
         << "\t 1. Encode " << endl
         << "\t 2. Decode " << endl;
    cin >> ch1;
    switch (ch1)
    {
    case 1:
        // cout << "enter filename: ";
        // cin >> filename;
        // cout << "enter encodefile: ";
        // cin >> encodefile;
        // encode(filename, encodefile);
        // tree *root =
        encode("sample2.txt", "encode2.txt");
        cout << "Encoded Successfully !!" << endl
             << endl;
        // cout<<"\t\t 1. Print Huffman Encode Tree \n\t\t 2. Print Binary Code"<<endl;
        // cin>>ch2;
        // switch(ch2){
        //     case 1:
        //         cout<<" Printing Tree "<<endl<<endl;
        //         printtree(root);
        //         break;
        //     case 2:
        //         cout<<" Printing Binary code "<<endl;
        //         for (auto i : bitcode)
        //          {
        //              cout << i.first << " : " << i.second<< "\n";
        //          }
        //         break;
        //     default:
        //         break;
        // }
        break;
    case 2:
        // cout << "Enter encodefile: ";
        // cin >> encodefile;
        // cout << "Enter decodefile: ";
        // cin >> decodefile;
        decode("encode2.txt", "decode2.txt");
        cout << "Decoded Successfully !!" << endl
             << endl;
        cout << "\t\t 1. Print Huffman Decode Tree \n\t\t 2. Print Binary Code" << endl;
        cin >> ch2;
        if (ch2 == 1)
        {
            cout << " Printing Tree " << endl;
            tree *root2 = new tree(INTERNAL_NODE_CHARACTER);

            decodetree(root2);
            printdecode(root2);
        }
        else if (ch2 == 2)
        {

            cout << " Printing Binary code " << endl;
            for (auto i : bitcode)
            {
                cout << i.first << " : " << i.second << "\n";
            }
        }

        break;
    default:
        break;
    }
    return 0;
}

void assign(tree *root, string value) // to assign bitcode to all char in tree
{
    if (root == NULL)
    {
        return;
    }

    if (root->right == NULL && root->left == NULL)
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

// void entry()
// {

//     string entry = "---------------WELCOME----------------";

//     string project = "DS LAB PBL";

//     string made = " MADE BY";
//     string name1 = "Akshansh Modi";
//     string name2 = "Saumya Bansal";
//     string name3 = "Armaan Sharma";
//     string name4 = "Arshika Porwal";

//     string end = "--------------------------------------";

//     cout << "\t\t\t\t";
//     for (int i = 0; i < entry.length(); i++)
//     {
//         cout << entry[i];
//         usleep(100000);
//     }
//     // for (int i = 0; i < sizesmall; i++)
//     //    {

//     //        smallstr[i] = output[i];
//     //    }
//     cout << "\n\t\t\t\t\t     ";
//     for (int i = 0; i < project.length(); i++)
//     {
//         cout << project[i];
//         usleep(100000);
//     }
//     cout << "\n\t\t\t\t\t      ";
//     for (int i = 0; i < made.length(); i++)
//     {
//         cout << made[i];
//         usleep(100000);
//     }
//     cout << "\n\t\t\t\t\t    ";
//     for (int i = 0; i < name1.length(); i++)
//     {
//         cout << name1[i];
//         usleep(100000);
//     }
//     cout << "\n\t\t\t\t\t    ";
//     for (int i = 0; i < name2.length(); i++)
//     {
//         cout << name2[i];
//         usleep(100000);
//     }
//     cout << "\n\t\t\t\t\t    ";
//     for (int i = 0; i < name3.length(); i++)
//     {
//         cout << name3[i];
//         usleep(100000);
//     }

//     cout << "\n\t\t\t\t\t    ";
//     for (int i = 0; i < name4.length(); i++)
//     {
//         cout << name4[i];
//         usleep(100000);
//     }
//     cout << "\n\t\t\t\t";

//     for (int i = 0; i < end.length(); i++)
//     {
//         cout << end[i];
//         usleep(100000);
//     }
// }