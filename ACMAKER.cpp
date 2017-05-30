#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <set>
using namespace std;

typedef vector<string>::iterator vsit;


//n is the insignifcant words
//total_chars are the number of chars (not white spaces) of the sentence
int n, total_chars ;
vector<string> sent;
set<string> ins;
string special;  //abbreviation word
string sentence;  //sentence of the problem

//given the position of the i-th  char, current[i] is the word
int current[155];

//memoization matrix
int memo[155][155];

/*
 * get_current(i) is the word of the i-th char
 * @param x: x-th char
 * @return index of the word corresponding to x-th char in sentence
 */
int get_current(int x) {
    int chars = 0, i = 0;
    while (chars <= x) chars += sent[i++].length();
    return i; 
}

/*
 * auxiliar function to fill current
 */
void init() {
    for (int i = 0; i < total_chars; i++) 
        current[i] = get_current(i);
}


/**
  * try with all possibilities
  * @param i: i-th char of special word
  * @param a: a-th char of sentence
  * @param word: j-th word of sentence 
  * @return the number of ways of abbreviation (special word) 
  */
int backtrack(int i, int a, int word) {
    //i-th char of special word
    if (i == special.length()) {  
        
        if (word > sent.size()) 
            return 1;
        return 0;
    }

    if (special.length() - i < sent.size() - word + 1) return 0;

    if (memo[i][a] != -1) return memo[i][a];

    int all = 0;
    for (int x = a; x < total_chars; x++) {
        if (word < current[x]) return memo[i][a] = all;
        if (special[i] == sentence[x]) {
            if (current[x] == word) all += backtrack(i + 1, x + 1, word + 1);
            else all += backtrack(i + 1, x + 1, word);
        }
    }
    return memo[i][a] = all;
}

int main(void) {
    while (cin >> n, n != 0) {
        ins.clear();
        for (int i = 0; i < n; i++) { 
            string str;
            cin >> str;
            ins.insert(str);
        }
        cin.ignore();
        while (1) {
            //initializing some variables
            sent.clear();
            memset(memo, -1, sizeof(memo));
            memset(current, -1, sizeof(current));
            total_chars = 0;
            sentence = "";

            //reading line and breaking it
            string line;
            getline(cin, line);
            istringstream iss(line);
            istream_iterator<string> it(iss), end;
            sent.assign(it, end);
            if (sent.size() >= 2 && sent[0] == "LAST" && sent[1] == "CASE") 
                break;
            special = sent[0];
            sent.erase(sent.begin());
            for (vsit it = sent.begin(); it != sent.end(); it++) {
                if (ins.find(*it) != ins.end()) {
                    sent.erase(it);
                    it--;
                } else {
                    total_chars += it->length();
                    sentence += *it;
                }
            }
            string copy = special;   //backing up special abbreviation
            for (int  i = 0; i < special.length(); i++) 
                special[i] = 'a' - 'A' + special[i];
            init();

            //number of ways
            int x = backtrack(0, 0, 1); 
            if (x == 0) 
                cout << copy << " is not a valid abbreviation" << endl;
            else 
                cout << copy << " can be formed in " << x << " ways" << endl;
        }
    }
    return 0;
}
