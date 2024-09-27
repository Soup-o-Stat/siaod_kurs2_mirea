#include <iostream>
#include <fstream>

using namespace std;

void create_file() {
    ifstream file("common_file.txt");
    int num_of_strings=0;
    cout<<"Enter number of phone numbers: "<<endl;
    cin>>num_of_strings;
    cout<<endl;
    for (int i = 0; i < num_of_strings; i++) {
        
    }
    file.close();
}

int main() {
    create_file();
    return 0;
}