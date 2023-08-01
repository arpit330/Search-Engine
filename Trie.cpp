#include <bits/stdc++.h>
using namespace std;

class TrieNode
{
public:
    unordered_map<char, TrieNode *> links;
    bool isEndOfWord;

    TrieNode()
    {
        isEndOfWord = false;
    }

    bool containsKey(char ch)
    {
        return (links.find(ch) != links.end());
    }

    void put(char ch)
    {
        links.insert(make_pair(ch, new TrieNode()));
    }

    TrieNode *get(char ch)
    {
        return links[ch];
    }

    void markEnd()
    {
        isEndOfWord = true;
    }

    bool isEnd()
    {
        return isEndOfWord == true;
    }
};

class Trie
{
public:
    TrieNode *root;
    Trie()
    {
        root = new TrieNode();
    }

    void Insert(string &word)
    {
        int len = word.length();
        TrieNode *curr = root;
        for (int i = 0; i < len; i++)
        {
            if (!curr->containsKey(word[i]))
            {
                curr->put(word[i]);
            }
            curr = curr->get(word[i]);
        }
        curr->markEnd();
    }

    void get_all_searches(vector<string> &result, TrieNode *node, string prefix)
    {
        if (node == NULL)
            return;
        if (node->isEnd())
        {
            result.push_back(prefix);
            return;
        }
        for (auto nxt : node->links)
        {
            prefix += nxt.first;
            get_all_searches(result, nxt.second, prefix);
        }
    }

    vector<string> prefix_search(string prefix)
    {
        int len = prefix.length();
        TrieNode *curr = root;
        vector<string> result;
        for (int i = 0; i < len; i++)
        {
            if (!curr->containsKey(prefix[i]))
            {
                return result;
            }
            curr = curr->get(prefix[i]);
        }
        get_all_searches(result, curr, prefix);
        return result;
    }

    bool exact_search(string target)
    {
        int len = target.length();
        TrieNode *curr = root;

        for (int i = 0; i < len; i++)
        {
            if (!curr->containsKey(target[i]))
            {
                return false;
            }
            curr = curr->get(target[i]);
        }

        return curr->isEnd();
    }
};

// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(string pat, int M, int *lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else 
        {
            
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(string pat, string txt)
{
    int M = pat.length();
    int N = txt.length();

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while ((N - i) >= (M - j))
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            return i - j;
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return -1;
}

vector<string> Patter_search(vector<string> &data, string pattern)
{
    vector<string> results;
    for (auto str : data)
    {
        if (KMPSearch(pattern, str) != -1)
            results.push_back(str);
    }
    return results;
}