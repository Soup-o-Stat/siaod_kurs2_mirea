#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>

using namespace std;

void find_substring_in_words(string input_text, string input_substring) {
    string clean_text;
    vector<string> words;
    string word;
    for (char symbol1 : input_text) {
        if (!ispunct(symbol1)) {
            clean_text += symbol1;
        }
    }
    for (char symbol2 : clean_text) {
        if (symbol2 != ' ') {
            word += symbol2;
        } else {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    for (auto i = words.begin(); i != words.end();) {
        if (i->size() >= input_substring.size() && i->compare(i->size() - input_substring.size(), input_substring.size(), input_substring) == 0) {
            ++i;
        }
        else {
            i = words.erase(i);
        }
    }
    for (const auto& i : words) {
        cout << i << endl;
    }
}

void task1() {
    cout<<"task 1"<<endl;
    cin.get();
    cout<<endl;
    string text;
    string substring;
    cout<<"Enter text: "<<endl;
    getline(cin,text);
    cout<<"Your text: "<<text<<endl;
    cout<<"Enter substring:"<<endl;
    cin>>substring;
    cout<<"Your substring: "<<substring<<endl;
    find_substring_in_words(text,substring);
}

int karp(const string &pattern, const string &text) {
    int m = pattern.length();
    int n = text.length();

    const int base = 256;
    const int mod = 101;

    int patternHash = 0;
    int textHash = 0;
    int h = 1;

    for (int i = 0; i < m - 1; i++) {
        h = (h * base) % mod;
    }
    for (int i = 0; i < m; i++) {
        patternHash = (base * patternHash + pattern[i]) % mod;
        textHash = (base * textHash + text[i]) % mod;
    }
    int count = 0;

    for (int i = 0; i <= n - m; i++) {
        if (patternHash == textHash) {
            if (text.substr(i, m) == pattern) {
                count++;
            }
        }
        if (i < n - m) {
            textHash = (base * (textHash - text[i] * h) + text[i + m]) % mod;
            if (textHash < 0) {
                textHash += mod;
            }
        }
    }
    return count;
}

int task2() {
    cout<<"task 2"<<endl;
    cin.get();
    string pattern;
    string text;
    cout << "Enter pattern: "<<endl;
    getline(cin, pattern);

    if (pattern.length() > 17) {
        cout << "Error: The patern must contain no more than 17 characters" << endl;
        return 1;
    }
    cout << "Enter text: "<<endl;;
    getline(cin, text);
    ofstream outputFile("text.txt");
    if (outputFile.is_open()) {
        outputFile << pattern <<endl;
        outputFile << text <<endl;
        outputFile.close();
        cout << "The data has been successfully written to the file text.txt" << endl;
    }
    int occurrences = karp(pattern, text);
    cout << "Number of occurrences: " << occurrences << endl;
    return 0;
}

int main() {
    int task_choice = 0;
    cout<<"Enter the task: "<<endl;
    cin>>task_choice;
    if (task_choice == 1) {
        task1();
    }
    else if (task_choice == 2) {
        task2();
    }
    else {
        cout<<"Wrong task number"<<endl;
    }

    return 0;
}