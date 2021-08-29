//Function Definitions:

//Will probably need more libraries for timer, etc.
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
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

    void insertHelper(string inputString);

    public:
    
    hashTable();

    hashTable(int size);

    ~hashTable();

    void insert(string inputString);

    bool find(string inputString);

    double loadFactor();

    void printTable();

    string chooseRandom();
};

//Player class
class Player
{
    private:

    public:
    int lives;
    int score;
    string nickname;

    /*
    - constructors, destructor, what other functions?
    */

    Player();   

    Player(string playerName);

};

//Miscellaneous functions to help with the game:

//checking for duplicate input strings
bool duplicateCheck(vector<string> & usedWords, string inputString);

bool nextRoundCheck();

bool checkPlayers(Player* list, int size);

//checking if the given character is inside of the input word
bool characterCheck(string inputString, string character);