#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <bitset>
#include <vector>
#include <ctime>
#include <set>
#include <unordered_set>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

void task1_a() {
    unsigned int x;
    cout<<"Enter x: "<<endl;
    cin>>x;
    unsigned char maska=1;
    x=x&(~(maska<<4));
    cout<<x<<endl;
}

void task1_b() {
    unsigned int x;
    cout<<"Enter x: "<<endl;
    cin>>x;
    unsigned char maska=1;
    x=x|((maska<<6));
    cout<<x<<endl;
}

void task1_c() {

    unsigned int x=25;
    const int n=sizeof(int)*8;
    unsigned maska=(1<<n-1);
    cout<<"The initial maska: "<<bitset<n>(maska)<<endl;
    cout<<"Result: "<<endl;
    for(int i=1;i<=n;i++) {
        cout<<((x&maska)>>(n-i));
        maska=maska>>1;
    }
    cout<<endl;
}


void task2_a() {
    vector<int> numbers = {};
    unsigned char bit_array = 0;

    for (int i = 0; i < 8; i++) {
        int number_to_push = 0;
        cout << "Enter number between 0 and 7: " << endl;
        cin >> number_to_push;
        if (number_to_push < 0 || number_to_push > 7) {
            cout << "Invalid number! Must be between 0 and 7." << endl;
            i--;
        }
        else {
            numbers.push_back(number_to_push);
            bit_array |= (1 << number_to_push);
        }
    }
    cout << "Input numbers: ";
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    cout << "Sorted numbers: ";
    for (int i = 0; i < 8; i++) {
        if (bit_array & (1 << i)) {
            cout << i << " ";
        }
    }
    cout << endl;
}

void task2_b() {
    vector<int> numbers;
    unsigned long long bit_array = 0;
    srand(static_cast<unsigned int>(time(0)));
    while (numbers.size() < 64) {
        int number_to_push = rand() % 64;
        if (!(bit_array & (1ULL << number_to_push))) {
            numbers.push_back(number_to_push);
            bit_array |= (1ULL << number_to_push);
        }
    }
    cout << "Input numbers: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Sorted numbers: ";
    for (int i = 0; i < 64; i++) {
        if (bit_array & (1ULL << i)) {
            cout << i << " ";
        }
    }
    cout << endl;
}

void task2_c() {
    vector<int> numbers;
    unsigned char bit_array[8] = {0};
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 64; ) {
        int number_to_push = rand() % 64;
        int byte_index = number_to_push / 8;
        int bit_index = number_to_push % 8;
        if (!(bit_array[byte_index] & (1 << bit_index))) {
            numbers.push_back(number_to_push);
            bit_array[byte_index] |= (1 << bit_index);
            i++;
        }
    }
    cout << "Input numbers: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Sorted numbers: ";
    for (int i = 0; i < 64; i++) {
        int byte_index = i / 8;
        int bit_index = i % 8;
        if (bit_array[byte_index] & (1 << bit_index)) {
            cout << i << " ";
        }
    }
    cout << endl;
}

void task3() {
    ofstream file_for_input("input.txt");
    int max_num = 10000000;
    vector<int> numbers(max_num);
    for (int i = 0; i < max_num; ++i) {
        numbers[i] = i;
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(numbers.begin(), numbers.end(), g);
    for (const int& num : numbers) {
        file_for_input << num << endl;
    }
    file_for_input.close();
    cout << "File has been created"<< endl;
    auto start_time = high_resolution_clock::now();
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<int> bit_array(max_num, 0);
    int num;
    while (input_file >> num) {
        if (num>=0 && num<max_num) {
            bit_array[num] = 1;
        }
    }
    input_file.close();
    for (int i = 0; i < max_num; ++i) {
        if (bit_array[i]) {
            output_file<<i<<endl;
        }
    }
    output_file.close();
    auto end_time = high_resolution_clock::now();
    duration<double> duration = end_time - start_time;
    cout<<"File has been created! Data has been sorted! Time: "<<duration.count()<<endl;
    size_t memory_usage = bit_array.size() / 8;
    cout << "Memory used by bit array: " << memory_usage << " bytes" << endl;
}

int main() {
    task1_a();
    task1_b();
    task1_c();

    task2_a();
    task2_b();
    task2_c();

    task3();

    return 0;
}