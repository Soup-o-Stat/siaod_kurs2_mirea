#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

int global_num_of_phones=0;

void mega_converter(const string &ntext_file, const string &nbinary_file) {
    ifstream text_file(ntext_file);
    ofstream binary_file(nbinary_file);

    if (text_file.is_open() && binary_file.is_open()) {
        string line;
        while (getline(text_file, line)) {
            size_t len = line.length();
            for (int i = 0; i < len; i++) {
                if (line[i] == ' ') {
                    binary_file << endl;
                }
                else {
                    binary_file << line[i];
                }
            }
        }
        text_file.close();
        binary_file.close();
        cout<<"Converted file successfully!"<<endl;
    }
    else {
        cout<<"File could not be opened!"<<endl;
    }
};

void create_file(){
    vector<string> used_phonenumbers;
    srand(static_cast<unsigned int>(time(0)));
    ofstream file("common_file.txt");
    int num_of_strings=0;
    cout<<"Enter number of phone numbers: "<<endl;
    cin>>num_of_strings;
    global_num_of_phones = num_of_strings;
    cout<<endl;
    for (int i = 0; i < num_of_strings; i++) {
        int randomNumber1 = 10 + rand() % (99 - 10 + 1);
        int randomNumber2 = 100 + rand() % (999 - 100 + 1);
        int randomNumber3 = 1000 + rand() % (9000 - 10 + 1);
        string phonenumber="89"+to_string(randomNumber1)+to_string(randomNumber2)+to_string(randomNumber3);
        if (find(used_phonenumbers.begin(), used_phonenumbers.end(), phonenumber) == used_phonenumbers.end()) {
            used_phonenumbers.push_back(phonenumber);
        }
        else {
            cout<<phonenumber<<" has been used. DETERMINATE THIS!!!"<<endl;
            i--;
        }
    }
    sort(used_phonenumbers.begin(), used_phonenumbers.end());
    for (int i = 0; i < used_phonenumbers.size(); i++) {
        file<<used_phonenumbers[i]<<" "<<endl;
    }
    file.close();
}

int bin_file_search() {
    string key;
    cout<<"Binary search"<<endl;
    cout << "Enter phone number (key): " << endl;
    cin >> key;
    auto start_time = high_resolution_clock::now();
    ifstream file("common_file.bin");
    vector<string> phoneNumbers;
    string line;
    while (getline(file, line)) {
        phoneNumbers.push_back(line);
    }
    file.close();
    int left = 0;
    int right = phoneNumbers.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (phoneNumbers[mid] == key) {
            cout << "Phone number found!" << endl;
            cout << phoneNumbers[mid] << endl;
            auto end_time =high_resolution_clock::now();
            duration<double> elapsed = end_time - start_time;
            cout << "Sorting completed in: " << elapsed.count() << " seconds." << endl;
            return 0;
        }
        else if (phoneNumbers[mid] < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    cout << "Phone number not found!    (¬_¬)" << endl;
    auto end_time =high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    cout << "Sorting completed in: " << elapsed.count() << " seconds." << endl;
    return 0;
}

int lin_file_search() {
    string key;
    cout<<"Linear search"<<endl;
    cout << "Enter phone number (key): " << endl;
    cin >> key;
    auto start_time = high_resolution_clock::now();
    ifstream file("common_file.bin");
    for (int i = 0; i < global_num_of_phones; i++) {
        string line;
        getline(file, line);
        if (line == key) {
            cout << "Phone number found!" << endl;
            cout << line << endl;
            auto end_time =high_resolution_clock::now();
            duration<double> elapsed = end_time - start_time;
            cout << "Sorting completed in: " << elapsed.count() << " seconds." << endl;
            return 0;
        }
    }
    cout << "Phone number not found!" << endl;
    auto end_time =high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    cout << "Sorting completed in: " << elapsed.count() << " seconds." << endl;
    return 0;
}

int main() {
    string mode;
    create_file();
    mega_converter("common_file.txt", "common_file.bin");
    cout<<"Enter mode (Linear or Binary)"<<endl;
    cin>>mode;
    if (mode == "Linear") {
        lin_file_search();
    }
    if (mode == "Binary") {
        bin_file_search();
    }
    return 0;
}