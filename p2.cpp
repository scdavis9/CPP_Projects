#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
#include <vector>

using namespace std;

int compare(int a, int b, vector<int> &sorts) {
    for(int i = 0; i < sorts.size(); i++) {
        if(sorts[i] < 0) {
            sorts[i] = 0;
        }
        int aDigit = (a/pow(10, sorts[i]));
        int bDigit = (b/pow(10, sorts[i]));
        aDigit = aDigit % 10;
        bDigit = bDigit % 10;
        if (aDigit < bDigit) {
            return -1;
        }
        else if (aDigit > bDigit) {
            return 1;
        }
    }
    return 0;
}

int compares(string a, string b, vector<int> &sorts) {
    for(int i = 0; i < sorts.size(); i++) {
        if(sorts[i] < 0) {
            sorts[i] = 0;
        }
        char Achar = a[sorts[i]];
        char Bchar = b[sorts[i]];
        if (Achar < Bchar) {
            return -1;
        }
        else if (Achar > Bchar) {
            return 1;
        }
    }
    return 0;
}


void merge(int left, int right, int middle, vector<int> &ints, vector<int> &sorts) {
    vector<int> leftarr;
    vector<int> rightarr;
    for(int i = left; i <= middle; i++) {
        leftarr.push_back(ints[i]);
    }
    for (int i = middle +  1; i <= right; i++) {
        rightarr.push_back(ints[i]);
    }
    int i = 0;
    int j = 0;
    int k = left;
    while( i < leftarr.size() && j < rightarr.size()) {
           if (compare(leftarr[i], rightarr[j], sorts) <= 0) {
               ints[k] = leftarr[i];
                i++;
                k++;
           }
           else {
               ints[k] = rightarr[j];
               j++;
               k++;
           }
    }
    while(i < leftarr.size()) {
        ints[k] = leftarr[i];
        i++;
        k++;
    }
    while(j < rightarr.size()) {
        ints[k] = rightarr[j];
        j++;
        k++;
    }
}

void mergesort(int left, int right, vector<int> &ints, vector<int> &sorts) {
    int middle = (left + right) / 2;
    if (right > left) {
        mergesort(left, middle, ints, sorts);
        mergesort (middle + 1, right, ints, sorts);

        merge(left, right, middle, ints, sorts);
    
    }
}

void merges(int left, int right, int middle, vector<string> &strings, vector<int> sorts) {
    vector<string> leftarr;
    vector<string> rightarr;
    for(int i = left; i <= middle; i++) {
        leftarr.push_back(strings[i]);
    }
    for (int i = middle +  1; i <= right; i++) {
        rightarr.push_back(strings[i]);
    }
    int i = 0;
    int j = 0;
    int k = left;
    while( i < leftarr.size() && j < rightarr.size()) {
           if(compares(leftarr[i], rightarr[j], sorts) <= 0) {
               strings[k] = leftarr[i];
                i++;
                k++;
           }
           else {
               strings[k] = rightarr[j];
               j++;
               k++;
           }
    }
    while(i < leftarr.size()) {
        strings[k] = leftarr[i];
        i++;
        k++;
    }
    while(j < rightarr.size()) {
        strings[k] = rightarr[j];
        j++;
        k++;
    }
}

void mergesorts(int left, int right, vector<string> &strings, vector<int> &sorts) {
    int middle = (left + right) / 2;
    if (right > left) {
        mergesorts(left, middle, strings, sorts);
        mergesorts (middle + 1, right, strings, sorts);

        merges(left, right, middle, strings, sorts);
    
    }
}


int main(int argc, char *argv[]) {
if(argc != 5) {
    cout << "Usage: ./a.out i|s sort_filename input_filename output_filename" << endl;
    return 0;
}
if(argv[1][0] != 'i' && argv[1][0] != 's') {
    cout << "Invalid datatype \"" << argv[1] << "\" (must be \"i\" or \"s\")" << endl;
    return 0;
}

ifstream input;

input.open(argv[2]);
vector<int> sorts;
if(!input.good()) {
    cout <<  "Unable to open sort file" << endl;
    return 0;
}

while(true) { // just reading in sorts
    int tmp;
    input >> tmp;
    if(input.eof()) break;
    sorts.push_back(tmp); // just push elements into a vector from the back
}

if (argv[1] == 'i') { // reads from input integer file
input.close();
input.clear();
input.open(argv[3]);
if(!input.good()) {
    cout << "Unable to open input file" << endl;
    return 0;
}
vector<int> ints;
    while(true) { //infinite loop created for the purpose
        int tmp2;
        input >> tmp2;
        if(input.eof()) break;
        ints.push_back(tmp2);
    }
    ofstream outPut;
    outPut.open(argv[4]);
    if(!outPut.good()) {
    cout << "Unable to open output file" << endl;
    return 0;
}
    if (argv[1][0] == 'i') {
        mergesort(0, ints.size() - 1, ints, sorts);
        for(int i = 0; i < ints.size(); i++) {
            outPut << right << setw(10) << ints[i] << endl;
        }
    }


}
else if(argv[1][0] == 's') { //reads from input string file
input.close();
input.clear();
input.open(argv[3]);
if(!input.good()) {
    cout << "Unable to open input file" << endl;
    return 0;
}
vector<string> strings;      // vector of type 
    while(true) {
        string tmp3;
        input >> tmp3;
        if(input.eof()) break;
        strings.push_back(tmp3);
    }
    ofstream outPut;
    outPut.open(argv[4]);
    if(!outPut.good()) {
    cout << "Unable to open output file" << endl;
    return 0;
}
    if (argv[1][0] == 's') {
        mergesorts(0, strings.size() - 1, strings, sorts);
        for(int i = 0; i < strings.size(); i++) {
            outPut <<  strings[i] << endl;
        }
    }



}

 return 0;
}


