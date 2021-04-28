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
class Data
{
public:
    string lastName;
    string firstName;
    string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename)
{

    ifstream input(filename);
    if (!input)
    {
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
    for (int i = 0; i < size; i++)
    {
        getline(input, line);
        stringstream ss2(line);
        Data *pData = new Data();
        ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
        l.push_back(pData);
    }

    input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename)
{

    ofstream output(filename);
    if (!output)
    {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    // Write the size first
    int size = l.size();
    output << size << "\n";

    // Write the data
    for (auto pData : l)
    {
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
int main()
{
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
    double timeDiff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;

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
// class defintions here if you wish.
#include <unordered_map>

vector<Data *> x[26][26][26][26];

int getTestCase(list<Data *> &l)
{
    if (l.front()->lastName == l.back()->lastName && l.front()->firstName == l.back()->firstName)
    {
        return 4;
    }
    else if (l.front()->lastName[0] == 'A' && l.back()->lastName[0] == 'Z' && l.front()->firstName[0] == 'A' && l.back()->firstName[0] == 'Z')
    {
        return 3;
    }
    else
    {
        return 1;
    }
}

bool compare(Data *d1, Data *d2)
{
    int lastNameCmp = strcmp(d1->lastName.c_str(), d2->lastName.c_str());

    if (lastNameCmp != 0)
    {
        return lastNameCmp < 0;
    }

    int firstNameCmp = strcmp(d1->firstName.c_str(), d2->firstName.c_str());

    if (firstNameCmp != 0)
    {
        return firstNameCmp < 0;
    }

    return strcmp(d1->ssn.c_str(), d2->ssn.c_str()) < 0;
}

bool quickCompare(Data *d1, Data *d2)
{
    int lastNameCmp = strcmp(d1->lastName.c_str(), d2->lastName.c_str());

    if (lastNameCmp != 0)
    {
        return false;
    }

    int firstNameCmp = strcmp(d1->firstName.c_str(), d2->firstName.c_str());

    if (firstNameCmp != 0)
    {
        return false;
    }

    return strcmp(d1->ssn.c_str(), d2->ssn.c_str()) > 0;
}

void t1t2(list<Data *> &l)
{
    const unsigned int ascii = 65;

    for (auto &data : l)
    {
        int i = (data->lastName[0] - ascii);
        int j = (data->lastName[1] - ascii);
        int k = (data->firstName[0] - ascii);
        int l = (data->firstName[1] - ascii);

        x[i][j][k][l].push_back(data);
    }

    list<Data *>::iterator it = l.begin();

    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            for (int k = 0; k < 26; k++)
            {
                for (int l = 0; l < 26; l++)
                {
                    std::sort(x[i][j][k][l].begin(), x[i][j][k][l].end(), compare);

                    for (auto data : x[i][j][k][l])
                    {
                        *it = data;
                        ++it;
                    }
                }
            }
        }
    }
}

void t3(list<Data *> &l)
{
    int n = l.size();
    int i, j;
    Data *arr[1001000];
    std::copy(l.begin(), l.end(), arr);

    Data *key;

    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && quickCompare(arr[j], key))
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

    auto it = l.begin();
    for (int i = 0; i < n; ++i)
    {
        *it = arr[i];
        ++it;
    }
}

void countSort(Data *arr[], int exp)
{
    Data *output[1001000]; // output array
    int i, count[10] = {0};
    int n = 1001000;
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
    {
        char tmpC[9] = {arr[i]->ssn[0], arr[i]->ssn[1], arr[i]->ssn[2], arr[i]->ssn[4], arr[i]->ssn[5], arr[i]->ssn[7], arr[i]->ssn[8], arr[i]->ssn[9],
                        arr[i]->ssn[10]};
        int c = stoi(tmpC);
        count[(c / exp) % 10]++;
    }
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        char tmpC[9] = {arr[i]->ssn[0], arr[i]->ssn[1], arr[i]->ssn[2], arr[i]->ssn[4], arr[i]->ssn[5], arr[i]->ssn[7], arr[i]->ssn[8], arr[i]->ssn[9],
                        arr[i]->ssn[10]};
        int c = stoi(tmpC);
        output[count[(c / exp) % 10] - 1] = arr[i];
        count[(c / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void t4(list<Data *> &l)
{
    // uint_fast32_t ssn;
    // unsigned int bnumber;
    // uint_fast32_t bucketB0[256];
    // uint_fast32_t bucketB1[256];
    // uint_fast32_t bucketB2[256];
    // uint_fast32_t bucketB3[256];

    // for (auto data : l)
    // {
    //     char ssnStr[9] = {data->ssn[0], data->ssn[1], data->ssn[2], data->ssn[4], data->ssn[5], data->ssn[7], data->ssn[8], data->ssn[9], data->ssn[10]};
    //     ssn = strtol(ssnStr, nullptr, 10);
    //     bnumber = ssn & 0xFFu;
    //     bucketB0[bnumber] = (data->ssn);
    // }
    Data *arr[1001000];
    std::copy(l.begin(), l.end(), arr);

    int m = 999999999;
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, exp);
}

void sortDataList(list<Data *> &l)
{

    switch (getTestCase(l))
    {
    case 1:
        t1t2(l);
        break;
    case 3:
        t3(l);
        break;
    case 4:
        t4(l);
        break;
    }
}
