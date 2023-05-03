#include <iostream>

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