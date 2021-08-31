// Letter Rush, a personal project by Daniel Nguyen
// https://github.com/danielvnguyen/LetterRush

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm> // for count
#include <stdlib.h> // for rand, srand
#include <time.h> // for sleep
#include <unistd.h> // for difftime
using namespace std;

// hashTable class to hold all of the valid words/strings:
class hashTable
{
    private:
    // dynamic string array to hold the dictionary
    string* stringArray;
    // max size of the underlying array
    int arraySize;
    // current size of the underlying array
    int currentSize;
    /*
    We are using a double hashing method for open
    addressing and dealing with collisions. this
    value will be used in the second hash function.
    */
    int hashTwoValue;

    // Helper functions:

    /*
    PARAM: value - an integer number
    POST: returns true if the given value is a prime number, false otherwise.
    */
    bool isPrime(int value);

    /*
    PARAM: value - an integer number
    POST: returns the next prime number greater than the given value
    */
    int findGreaterPrime(int value);

    /*
    PARAM:
    inputstring - a <string> object representing a word/characters
    value - an integer number
    POST: returns a value corresponding to the input string. Uses
    Horner's Method and the modulo operator to avoid overflow.
    */
    int hornerMethod(string inputString, int value);

    /*
    PARAM: inputString - a <string> object representing a word/characters
    POST: returns string value of the input string as an integer
    */
    int hashFunctionOne(string inputString);

    /*
    PARAM: inputString - a <string> object representing a word/characters
    POST: returns an integer used to deal with collisions in the hash table
    */
    int hashFunctionTwo(string inputString);

    /*
    PARAM: inputString - a <string> object representing a word/characters
    POST: a function that helps insert the input string into the correct position in the array
    */
    void insertHelper(string inputString);

    public:
    
    /*
    PARAM: N/A
    POST: initializes all of the attributes for a hash table object
    */
    hashTable();

    /*
    PARAM: size - an integer number
    POST: initializes all of the attributes for a hash table object, with a specific size
    */
    hashTable(int size);

    /*
    PARAM: N/A
    POST: deallocates the space for the underlying array attribute
    */
    ~hashTable();

    /*
    PARAM: inputstring - a <string> object representing a word/characters
    POST: inserts the given string into the correct position in the underlying array
    of the calling object. If the load factor is above 0.50, the size will be
    doubled and every current string will be repositioned.
    */
    void insert(string inputString);

    /*
    PARAM: inputstring - a <string> object representing a word/characters
    POST: returns true if the given string is found in the hash table, false otherwise.
    */
    bool find(string inputString);

    /*
    PARAM: N/A
    POST: returns load factor of the hash table
    */
    double loadFactor();

    /*
    PARAM: N/A
    POST: prints every element in the hash table, along with the index position
    */
    void printTable();

    /*
    PARAM: N/A
    POST: returns a random element within the hash table
    */
    string chooseRandom();
};

// Player class
class Player
{
    private:

    public:
    int lives;
    int score;
    string nickname;

    /*
    PARAM: N/A
    POST: initializes the attributes for the player object
    */
    Player();   

    /*
    PARAM: playerName - a <string> object representing the player's nickname
    POST: initializes the attributes for the player object, along with a nickname
    */
    Player(string playerName);

};

// Game helper functions:

/*
PARAM: 
usedWords - a string vector reference object 
inputstring - a <string> object representing a word/characters
POST: checks if the given input string is already in the vector object
*/
bool duplicateCheck(vector<string> & usedWords, string inputString);

/*
PARAM: N/A
POST: returns true if the player would like to continue to another round, false otherwise.
*/
bool nextRoundCheck();

/*
PARAM: 
list - a pointer to a Player object
size - an integer number
POST: returns true if theres sufficient players remaining, false otherwise.
*/
bool checkPlayers(Player* list, int size);

/*
PARAM: 
inputstring - a <string> object representing a word/characters
character - a <string> object representing a word/characters
POST: checks if the input string contains the given character(s)
*/
bool characterCheck(string inputString, string character);