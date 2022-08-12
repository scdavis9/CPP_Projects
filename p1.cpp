#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

int removeDuplicates(string arr[], int n)
{
    //int j = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {

            if (arr[i] == arr[j] || arr[i] == "")
            {
                n--;
                for (int k = i; k < n; k++)
                {
                    arr[k] = arr[k + 1];
                }
                i--;
            }
        }
    }

    return n;
}

int main(int argc, char *argv[])
{
    string source[3000];
    string destination[3000];
    int bandwith[3000];
    int final[2000];
    string temp[30000];
    string origsource[3000];
    string origdestination[3000];

    ifstream inFS;
    int done = 0;

    string line;
    int row = 0;
    int index = 0;
    int col = 0;
    string total[20000];
    int num = 0;
    int leaving = 0;
    int to = 0;

    inFS.open(argv[1]);

    while (!inFS.eof())
    {
        getline(inFS, line);
        stringstream ss(line);
        ss >> source[row] >> destination[row] >> bandwith[row]; //read in values and put in three diff arrays
        total[col] = source[row];
        col++;
        total[col] = destination[row];
        col++;

        row++;
        index++;
        ss.clear();
    }
    inFS.close();


    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < total[i].length(); j++)
        {
            total[i][j] = toupper(total[i][j]);
        }
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < source[i].length(); j++)
        {
            source[i][j] = toupper(source[i][j]);
        } // convert source to uppercase
        origsource[i] = source[i];
        for (int j = 0; j < destination[i].length(); j++)
        { // keep copy of original source and destination (with repeats)
            destination[i][j] = toupper(destination[i][j]);
        }
        origdestination[i] = destination[i];
    }

    int origColumn = col;
    int origRow = row;
    int origIndex = index;

    col = removeDuplicates(total, col); // remove duplicates
    row = removeDuplicates(source, row);
    index = removeDuplicates(destination, index);

    int size = 0;
    if (row > col)
    { // find which list has more and use
        size = row;
    }
    else if (col >= row)
    {
        size = row;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < index; j++)
        {
            if (source[i] == destination[j])
            { //find all non-leaf identifiers
                temp[num] = source[i];
                //cout << temp[num] << endl;
                num++;
            }
        }
    }
    int order = 0;
    string ordered[10000];
    num = removeDuplicates(temp, num);
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < num; j++)
        { //order 2nd half to first
            if (total[i] == temp[j])
            {
                //cout << total[i];
                ordered[order] = total[i];
                //cout << total[i] << endl;
                order++;
            }
        }
    }

    ofstream outPut;
    outPut.open("output.txt");

    for (int i = 0; i < col; i++)
    {
        outPut << total[i] << endl; //print out top half
    }
    outPut << endl;

    for (int i = 0; i <= order; i++)
    {
        if (ordered[i] == "")
        {
            break;
        }
        for (int j = 0; j < origRow; j++)
        {
            if (ordered[i] == origsource[j])
            {                           // FIX ME, adding up to/from values, copying to array. Need to copy outside of for loop, but not working?
                leaving += bandwith[j]; // need reset before i increments
            }
            if (ordered[i] == origdestination[j])
            {
                to += bandwith[j];
                // cout << "&" << to;
            }
        }

        final[done] = leaving;
        done++;

        outPut << ordered[i] << " " << leaving << " " << to << " " << fixed << setprecision(2) << (double(to) / leaving) << endl;
        to = 0;
        leaving = 0;
    }

    //for(int i=0; i<order; i++) {                               // print out bottom (REMEMBER PRINT TO FILE NOT SCREEN)
    //    cout << ordered[i] << " " << final[i]<<  endl;
    //}

    return 0;
}