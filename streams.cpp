#include <iostream>
#include <fstream>

using namespace std;

int main() {
    char data[100];

    ofstream outfile;
    outfile.open("apple.dat");

    cout <<"Writing to a file: " << endl;
    cout << "Enter your name: " << endl;
    cin.getline(data, 100);

    outfile << data << endl;
    return 0;
}