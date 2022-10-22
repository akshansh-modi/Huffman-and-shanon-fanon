#include <iostream>
using namespace std;
#include <unordered_map>
#include <queue>

unordered_map<char, int> counter;
// priority_queue<tree> pq;
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


