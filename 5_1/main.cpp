#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <bitset>
#include <vector>

using namespace std;

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
    vector<int> numbers = {};
    unsigned long long bit_array = 0;

    for (int i = 0; i < 64; i++) {
        int number_to_push = 0;
        cout << "Enter number between 0 and 63: " << endl;
        cin >> number_to_push;
        if (number_to_push < 0 || number_to_push > 63) {
            cout << "Invalid number! Must be between 0 and 63." << endl;
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
    for (int i = 0; i < 64; i++) {
        if (bit_array & (1 << i)) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main() {
    // task1_a();
    // task1_b();
    // task1_c();

    //task2_a();
    task2_b();

    return 0;
}