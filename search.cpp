
#include "search.h"
SearchEngine::SearchEngine()
{
    v.resize(100003);
    for (int i = 0; i < v.size(); i++)
    {
        v[i].sentence1 = "-1";
    }
    book_code = 0;
    page = 0;
    paragraph = 0;
    sentence_no = 0;
}

SearchEngine::~SearchEngine()
{
   
}
int SearchEngine::hash_sentence(string s)
{
    int hash = 0;
    for (int i = 0; i < s.length(); i++)
    {
        hash = (hash * 31 + s[i]) % v.size();
    }
    return hash;
}

void SearchEngine::insert1(string d)
{
    // cout<<d<<endl;
    for (char &ch : d)
    {
        // cout<<"hi"<<endl;
        if (ch >= 'A' && ch <= 'Z')
        {
            ch += 'a' - 'A';
        }
    }
    int x = hash_sentence(d);
    long long initial_position = x;
    long long j = 1;
    while (v[x].sentence1 != "-1")
    {
        x = (initial_position + j) % v.size();
        j++;
        if (x == initial_position)
        {
            return; 
        }
    }
   

    v[x].sentence1 = d;
}
bool SearchEngine::is_punct(char d)
{
    char arr[14] = {'.', ',', '-', ':', '!', '"', '\'', '(', ')', '?', '[', ']', ';', '@'};
    for (int i = 0; i < 14; i++)
    {
        if (d == arr[i])
        {
            return true;
        }
    }
    return false;
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    for (char &ch : sentence)
    {
        // cout<<"hi"<<endl;

        if (ch >= 'A' && ch <= 'Z')
        {
            ch += 'a' - 'A';
        }
    }

    int x = hash_sentence(sentence);

    v[x].book_code = book_code;
    v[x].page = page;
    v[x].paragraph = paragraph;

    v[x].sentence_no = sentence_no;
    long long initial_position = x;
    long long j = 1;

    while (v[x].sentence1 != "-1")
    {
        x = (initial_position + j) % v.size();
        j++;
        if (x == initial_position)
        {
            return; // Avoid infinite loops
        }
    }
  

    v[x].sentence1 = sentence;
}
int SearchEngine::power(int b, int exp)
{
    if (exp < 0)
    {
        
        return 0;
    }
    long long res = 1;
    for (int i = 0; i < exp; i++)
    {
        res *= b;
    }
    return res;
}

int SearchEngine::findd(const string &sentence, const string &pattern)
{
    int sentenceLength = sentence.length();
    int patternLength = pattern.length();
    int sentenceHash = 0;
    int patternHash = 0;
    // int prime = 101;  // You can choose any prime number

    // Calculate the hash of the pattern
    for (int i = 0; i < patternLength; i++)
    {
        patternHash = (patternHash * 13 + pattern[i]);    //% prime;
        sentenceHash = (sentenceHash * 13 + sentence[i]); //% prime;
    }

    for (int i = 0; i <= sentenceLength - patternLength; i++)
    {
        // Check if the hashes match
        if (sentenceHash == patternHash)
        {
            // If the hashes match, do a character-by-character comparison
            int j;
            for (j = 0; j < patternLength; j++)
            {
                if (sentence[i + j] != pattern[j])
                {
                    break;
                }
            }
            if (j == patternLength)
            {

                return i;
            }
        }

        if (i < sentenceLength - patternLength)
        {
            sentenceHash = (13 * (sentenceHash - sentence[i] * power(13, patternLength - 1)) + sentence[i + patternLength]); 
        }
    }

    return -1;
}

Node *SearchEngine::search(string pattern, int &n_matches)
{
    Node *result_head = nullptr;
    Node *result_tail = nullptr;

    for (char &ch : pattern)
    {
        // cout<<"hi"<<endl;
        if (ch >= 'A' && ch <= 'Z')
        {
            ch += 'a' - 'A';
        }
    }

    int pattern_hash = hash_sentence(pattern);
    n_matches = 0;

    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].sentence1 != "-1")
        {

            if (findd(v[i].sentence1, pattern) != -1)
            {

                int offset = findd(v[i].sentence1, pattern);
                n_matches++;
                if (result_tail)
                {
                    result_tail->right = new Node(v[i].book_code, v[i].page, v[i].paragraph, v[i].sentence_no, offset);
                    result_tail = result_tail->right;
                }
                else
                {
                    result_head = new Node(v[i].book_code, v[i].page, v[i].paragraph, v[i].sentence_no, offset);
                    result_tail = result_head;
                }
            }
        }
    }

    return result_head;
}
