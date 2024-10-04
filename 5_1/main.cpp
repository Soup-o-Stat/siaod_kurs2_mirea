#include <iostream>

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
    cout<<"The initial maska: "<<maska<<endl;
    cout<<"Result: "<<endl;
    for(int i=0;i<=n;i++) {
        cout<<((x&maska)>>(n-i));
        maska=maska>>1;
    }
    cout<<endl;
}

int main() {
    task1_a();
    task1_b();

    return 0;
}
