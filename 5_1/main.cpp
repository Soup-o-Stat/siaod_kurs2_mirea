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
    vector <int> numbers={};
    for (int i=0;i<8;i++) {
        int number_to_push=0;
        cout<<"Enter number: "<<endl;
        cin>>number_to_push;
        numbers.push_back(number_to_push);
    }
    for (int i=0;i<numbers.size();i++) {
        cout<<numbers[i];
    }
    cout<<endl;
    unsigned int binnum=0;
    for (int i=0;i<8;i++) {
        binnum|=(1<<numbers[i]);
        cout<<binnum<<endl;
    }


}

int main() {
    // task1_a();
    // task1_b();
    // task1_c();

    task2_a();

    return 0;
}
