#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cctype>

using namespace std;

typedef struct node {
    pair<long, long> range;
    struct node *next;
} node;

node *Build(ifstream &file);
void Free(node *start);
int Digits(long number);
vector<int> factor(int number);
vector<int> partition(int factor, long number, int digits);

int main() {
    ifstream inputFile("Day2Text.txt");
    
    node *start = Build(inputFile);

    long counter = 0;
    pair<long, long> compare;
    vector<int> factors;
    vector<int> partition;
    string token;

    for (node *it = start; it != 0; it = it->next) {
        for (long i = it->range.first; i <= it->range.second; i++) {
            //compare.first = i / (long) pow(10, Digits(i) / 2);
            //compare.second = (Digits(i) > 1) ? i % ((long) pow(10, Digits(i) / 2)) : 0;
            //cout << compare.first << ", " << compare.second << '\n';

            //make a for loop iterating through the factor vector to output vectors with components of partitioned sections
            vector<int> factors = factor(Digits(i));
            for(int j : factors) {
                
            }

            if (compare.first == compare.second) {
                counter += i;
            }
        }
    }
    cout << "Counter: " << counter << '\n';
    Free(start);
    return 0; 
}

vector<int> factor(int number) {
    vector<int> factors;
    for (int i = 2; i <= number; i++) {
        if (number % i == 0)
            factors.push_back(i);
    }
    return factors;
}

vector<int> partition(int factor, long number, int digits) {
    string buffer = to_string(number);
    string token;
    int charnum = 0;
    vector<int> partitions;
    for (int i : factors) {
        for (int j = 0; j < i; j++) {
            for (int )
        }
    }
}

node *Build(ifstream &file) {
    string token;
    node *tempnode = new node;
    node *start = tempnode;
    string text;

    // loops over the intervals, putting the full string of range into the string "text"
    while (getline(file, text, ',')) {
        for (char c : text) {
            if (isdigit(c)) {
                token += c;
            }
            else if (c == '-') {
                //cout << token << ',' << ' ';
                tempnode->range.first = (long) stol(token);
                token.clear();
            }
        }
        tempnode->range.second = (long) stol(token);
        tempnode->next = new node;
        printf("%li, %li\n", tempnode->range.first, tempnode->range.second);
        tempnode = tempnode->next;
        //cout << token << '\n';
        token.clear();
    }
    delete tempnode->next;
    tempnode->next = 0;
    return start;
}

int Digits(long number) {
    int value;
    if (number > 0) {
        value = (int) log10(number) + 1;
        return value;
    }
    else {
        return 1;
    }
}

void Free(node *start) {
    while (start != 0) {
        node *temp = start;
        start = start->next;
        delete temp;
    }
}

