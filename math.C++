#include <iostream>
#include <string>

using namespace std;


int main() {
    string userName;
    int userAge;
    string avatarName;

    cout << "Hi, what's your name?\n";
    cin >> userName;
    cout << "How old are you?\n";
    cin >> userAge;

    switch(userAge) {
        case 3:
        cout << "Please get a parent!\n";
        break;

        case 8:
        cout << "Please get a parent!\n";
        break;

        default:
        cout << "Please enter a username!\n";
        cin >> avatarName;
        cout << avatarName << endl;
        break;
    }




    return 0;
}