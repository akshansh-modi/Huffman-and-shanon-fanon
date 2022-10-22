

// #include "Huffmantree.h"
#include <vector>
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
// // priority queue -->minimum
// // max or min heap??



class comparenode {
public:
	bool operator()(tree* l, tree* r)

	{
		return (l->freq > r->freq);
	}
};




int main(){
priority_queue<tree*, vector<tree*>,comparenode> minheap ;
string text;
cout<<"Enter string :";
getline(cin,text);
freqcount(text);
for(auto i:counter){

    tree* t=new tree(i.first,i.second);
 minheap.push(t);
}

while(minheap.empty()!=1){
    cout<<"\n"<<minheap.top()->ch<<": ";
cout<<minheap.top()->freq;
minheap.pop();
}



// minheap working properly
    return 0;
}
