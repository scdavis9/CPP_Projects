#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <cstring>

using namespace std;

void remove_duplicates(int* arr, int& n) {

// temporary list to store all the unique elements
string temp[1000]="0";
    int size=0;
// iterate each element of arr[]
for (int i = 0; i < n; ++i) {

// checking if there exist an element arr[j] ( j < i )
// that is equal to arr[i]
int flag = 1;
for (int j = 0; j < i; ++j) {
if (arr[j] == arr[i]) {
flag = 0;
break;
}
}

// flag == 0 means arr[i] is repeated
// flag == 1 means that no element that appears
// on left side of arr[i] is equal to arr[i]
// therefore, we push arr[i] to temp
if (flag)
   for(int k=0; k<size; k++) {
       if (temp[k]=="0") {
           temp[k]= arr[i];
           size++;
           break;
       }
   }
   
// temp.push_back(arr[i]);

}


int main(int argc, char*argv[]) {
istringstream inSS;
int index = 0;
string line;
string source[30000];
string destination[30000];
int bandwith[30000];
string wordArray[3000];



ifstream input;
input.open(argv[1]);

while(!input.eof()) {
	getline(input, wordArray[index]);
	index++;
}
for (int i = 0; i < index; i++) {
		for (int j = 0; j < index; j++) {
			toupper(source[i][j]);
		}
	}
return 0;

}