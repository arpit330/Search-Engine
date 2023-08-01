#include <bits/stdc++.h>
#include "Trie.cpp"
using namespace std;

vector<string> get_array_from_file(string src)
{
    fstream file(src);

    string word;
    vector<string> words;

    if (!file)
    {
        cerr << "\nCan't Open File " << src << " Some Error Occurred.!\n";
        return words;
    }

    while (!file.eof())
    {
        getline(file, word);
        if (word.size())
            words.push_back(word);
        word = "\0";
    }

    return words;
}

int main(int argc, char **argv)
{

    string filename;
    Trie T;
    vector<string> data;

    int choice;
    do
    {

        do
        {
            cout << "------------------------\n";
            cout << "SEARCH FOR :" << endl;
            cout << "1. Movies" << endl;
            cout << "2. Music" << endl;
            char opt;
            cin >> opt;
            if (opt == '1')
            {
                filename = "movies";
                break;
            }
            else if (opt == '2')
            {
                filename = "music";
                break;
            }
            else
            {
                cout << "Error..." << endl;
                cout << "Choose a valid option." << endl;
                cout << endl;
            }
        } while (1);

        data = get_array_from_file(filename + ".txt");

        for (string word : data)
        {
            // cout << word << "\n";
            T.Insert(word);
        }

        cout << "------------------------\n";
        cout << "MENU\n";
        cout << "1. Exact Search.\n";
        cout << "2. Prefix Search.\n";
        cout << "3. Universal Search.\n";
        cout << "0. Exit.\n";

        cin >> choice;
        getchar();

        string pattern;

        if (choice)
        {
            cout << "Enter Search Text (leave empty to list all) : ";
            getline(cin, pattern);
        }

        int flag = 0;
        switch (choice)
        {
        case 1:
            cout << "\n";
            cout << "Results for Exact Search : \n\n";
            if (T.exact_search(pattern))
            {
                cout << filename << " Exists.\n ";
            }
            else
            {
                cout << "NOT Found.\n";
            }
            break;
        case 2:
            cout << "\n";
            cout << "Results for Prefix Search : \n\n";
            for (string w : T.prefix_search(pattern))
            {
                flag = 1;
                cout << w << "\n";
            }
            if (!flag)
            {
                cout << "NOT Found.\n";
            }
            break;

        case 3:
            cout << "\n";
            cout << "Results for Universal Search : \n\n";
            for (string w : Patter_search(data, pattern))
            {
                flag = 1;
                cout << w << "\n";
            }
            if (!flag)
            {
                cout << "NOT Found.\n";
            }
            break;

        default:
            break;
        }

        cout << "\n\npress any key to continue.";
        getchar();
        system("clear");

    } while (choice);

    return 0;
}
