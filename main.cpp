#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
class Trie
{
public:
    class node
    {
    public:
        string word;
        int freq;
        vector<node *> next;
        node(string a, int b) : word(a), freq(b)
        {
            next.empty();
        }
        node()
        {
            next.clear();
        }
    };
    node *root;
    Trie()
    {
        root = new node();
    }
    void insert_sentence(string s);
    vector<string> predicted_text(string s);
    void print_elements(node *current, string space);
    void insert_article(string path);
    vector<string> suggest_four(vector<node *> current);
    int next_bucket_search(vector<node *> current, string word)
    {
        for (int i = 0; i < current.size(); i++)
        {
            if (word == current[i]->word)
            {
                return i;
            }
        }
        return -1;
    }
};
vector<string> Trie ::suggest_four(vector<node *> current)
{
    vector<string> suggest;
    for (int i = 0; i < 4; i++)
    {
        if (current.empty())
        {
            break;
        }
        int max = 0;
        for (int j = 0; j < current.size(); j++)
        {
            if (current[max]->freq < current[j]->freq)
            {
                max = j;
            }
        }
        suggest.push_back(current[max]->word);
        current.erase(current.begin() + max);
    }
    return suggest;
}
string lower(string upper)
{
    for (int i = 0; i < upper.length(); i++)
    {
        upper[i] = tolower(upper[i]);
    }
    return upper;
}
vector<string> words_split(const string &s)
{
    string word = "";
    vector<string> words;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ' || s[i] == ',')
        {
            if (!word.empty())
            {
                words.push_back(word);
                word.clear();
            }
        }
        else
        {
            word += s[i];
        }
    }
    // Check for trailing word after the loop
    if (!word.empty())
    {
        words.push_back(word);
    }
    return words;
}
void Trie ::insert_sentence(string s)
{
    s = lower(s);
    vector<string> words = words_split(s);
    node *current = root;
    for (int i = 0; i < words.size(); i++)
    {
        bool found = false;
        for (int j = 0; j < current->next.size(); j++)
        {
            if (words[i] == current->next[j]->word)
            {
                found = true;
                current->next[j]->freq++;
                current = current->next[j];
                break;
            }
        }
        if (!found)
        {
            node *newNode = new node(words[i], 1);
            current->next.push_back(newNode);
            current = newNode;
        }
    }
}
void Trie ::print_elements(node *current, string space = "")
{
    if (current == NULL || current->next.empty())
    {
        return;
    }
    for (int i = 0; i < current->next.size(); i++)
    {
        cout << space << current->next[i]->word << "(" << current->next[i]->freq << ")" << endl;
        print_elements(current->next[i], space + "\t|");
    }
}
vector<string> Trie::predicted_text(string s)
{
    s = lower(s);
    vector<string> words = words_split(s);
    node *current = root;
    bool loop = false;
    bool found;
    int index = 0;
    for (int i = 0; i < words.size(); i++)
    {
        found = false;
        for (int j = 0; j < current->next.size(); j++)
        {
            if (words[i] == current->next[j]->word)
            {
                found = true;
                index = i;
                break;
            }
        }
        if(found){
            break;
        }
    }
    int next_bucket;
    if (found)
    {
        for (int i = index; i < words.size(); i++)
        {
            while (true)
            {

                next_bucket = next_bucket_search(current->next, words[i]);
                if(next_bucket == -1){
                    break;
                }
                current = current->next[next_bucket];
            }
        }
    }
    return suggest_four(current->next);
}

void Trie ::insert_article(string path)
{
    ifstream file(path);
    int i, j;
    string sentence = "";
    while (!file.eof())
    {
        string ss;
        i = 0;
        getline(file, ss);
        while (i < ss.length())
        {
            if (ss[i] == '?' || ss[i] == '.' || ss[i] == '!')
            {
                insert_sentence(sentence);
                sentence = "";
            }
            else
            {
                sentence += ss[i];
            }
            i++;
        }
    }
}
int main()
{

    Trie *mytrie = new Trie();


    mytrie->insert_article("article.txt");
    mytrie->print_elements(mytrie->root);
    string str;
    string sentence="";
    bool flag = true;
    //If you want to see how the trie tree looks. Just run
    //mytrie->print_elements(mytrie->root);
    while (true) {
//        system("cls");
        cout << "Enter Sentence or Press Enter for suggestions: ";
        cout << sentence;

        string input;
        getline(cin, input);


        if(flag){
            sentence += input;
            flag = false;
        }else{
            sentence += " " + input;
        }

        vector<string> suggestions = mytrie->predicted_text(sentence);

        int i = 1;
        if(suggestions.empty()){
            cout<<"No Suggestions\n";
            break;
        }
        for (auto suggestion : suggestions) {
            cout << "\t" << i << ". " << suggestion << endl;
            ++i;
        }
        cout << "Select a suggestion (1-4): ";
        cin >> i;

        if(i>0 && i<5){
            sentence += " " + suggestions[i-1];
        }
        else{
            cout<<"Invalid Input";
        }
        cin.ignore();
    }
    cout << "Final Sentence: " << sentence << endl;
    delete mytrie;
    return 0;
}