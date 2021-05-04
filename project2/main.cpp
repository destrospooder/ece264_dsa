// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2021

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
    string lastName;
    string firstName;
    string ssn;
};


// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

    ifstream input(filename);
    if (!input) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    // The first line indicates the size
    string line;
    getline(input, line);
    stringstream ss(line);
    int size;
    ss >> size;

    // Load the data
    for (int i = 0; i < size; i++) {
        getline(input, line);
        stringstream ss2(line);
        Data *pData = new Data();
        ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
        l.push_back(pData);
    }

    input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

    ofstream output(filename);
    if (!output) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    // Write the size first
    int size = l.size();
    output << size << "\n";

    // Write the data
    for (auto pData:l) {
        output << pData->lastName << " "
               << pData->firstName << " "
               << pData->ssn << "\n";
    }

    output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
    string filename;
    cout << "Enter name of input file: ";
    cin >> filename;
    list<Data *> theList;
    loadDataList(theList, filename);

    cout << "Data loaded.\n";

    cout << "Executing sort...\n";
    clock_t t1 = clock();
    sortDataList(theList);
    clock_t t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

    cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

    cout << "Enter name of output file: ";
    cin >> filename;
    writeDataList(theList, filename);

    return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class definitions here if you wish.

//ECE264 - Data Structures and Algorithms I
//Benjamin Aziel
//Due May 4, 2021
//Prof. Carl Sable

//Function definitions are fine
//For the array, you need to define outside with ~1*10^6



inline bool easySort(Data* index1, Data* index2) {
    if (index1 -> lastName > index2 -> lastName)
        return false;
    if (index1 -> lastName < index2 -> lastName)
        return true;
    if (index1 -> firstName > index2 -> firstName)
        return false;
    if (index1 -> firstName < index2 -> firstName)
        return true;
    if (index1 -> ssn >= index2 -> ssn)
        return false;
    else
        return true;
}

int bigArr[1010000];
int postArr[1010000];

int maxVal(const int randomArr[], int m){
    int max = randomArr[0];
    for(int i = 1; i < m; i++){
        if(randomArr[i] > max){
            max = randomArr[i];
        }
    }
    return max;
}

void countSort(int rawArr[], int size, int digit){
    int bucket[10] = {0};
    for(int x = 0; x < size; x++){
        bucket[(rawArr[x] / digit)%10]++;
    }
    for(int indicator = 1; indicator < 10; indicator++){
        bucket[indicator] += bucket[indicator - 1];
    }
    for(int y = size - 1; y >=0; y--){
        bigArr[bucket[(rawArr[y] / digit)%10] - 1] = rawArr[y];
        bucket[(rawArr[y] / digit)%10]--;
    }
    for(int z = 0; z < size; z++){
        rawArr[z] = bigArr[z];
    }
}

void radix4(int rawArr[], int size){
    int max = maxVal(rawArr, size);
    for(int digit = 1; max / digit > 0; digit *= 10){
        countSort(rawArr, size, digit);
    }
}

inline bool easySort4(Data* index1, Data* index2) {
    if (index1 -> ssn >= index2 -> ssn)
        return false;
    return true;
}

void sortDataList(list<Data *> &l) {
    string firstName = l.front()->firstName;
    int count = 0;
    int index = 0;
    int index2 = 0;
    string temp;
    for (auto it:l){
        if (count++ == 1000) {
//          l.sort(easySort4);
            for(auto inc:l){
                postArr[index] = stoi(inc -> ssn.substr(0,3) + inc -> ssn.substr(4,2) + inc -> ssn.substr(7,4));
                index++;
            }
            radix4(postArr, l.size());
            for(auto inc2:l){
                temp = to_string(postArr[index2++]);
                while(temp.length() != 9){
                    temp = "0" + temp;
                }
                temp.insert(3, "-");
                temp.insert(6, "-");
                inc2 -> ssn = temp;
            }
            return;
        }
        if (it->firstName != firstName) {
            l.sort(easySort);
            return;
        }
    }
}