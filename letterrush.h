//Function Definitions:

//Will probably need more libraries for timer, etc.
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

//hashTable class to hold all of the valid words/strings:
class hashTable
{
    private:
    //dynamic string array to hold the dictionary
    string* stringArray;
    int arraySize;
    int currentSize;
    /*
    we are using double hashing method for open
    addressing and dealing with collisions. this
    value will be used in the 2nd hash function.
    */
    int hashTwoValue;

    //Helper methods that shouldn't be visible will go here:
    bool isPrime(int value);

    int findGreaterPrime(int value);

    int hornerMethod(string inputString, int value);

    int hashFunctionOne(string inputString);

    int hashFunctionTwo(string inputString);

    public:
    
    hashTable();

    ~hashTable();

    void insert(string inputString);

    bool find(string inputString);

    int size();

    int maxSize();

    double loadFactor();

};

/*
- Functions regarding dictionary, printing, and result vector here:

*/