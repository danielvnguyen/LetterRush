#include "letterrush.h"

// Private function implementations:

/*
PARAM: value - an integer number
POST: returns true if the given value is a prime number, false otherwise.
*/
bool hashTable::isPrime(int value)
{
    // corner cases (if value is 1 or below, return false)
    if (value <= 1)
    {
        return false;
    }
    // if value is 2 or 3, return true
    if (value <= 3)
    {
        return true;
    }
    // if value mod 2 or 3 is not 0, return false
    if (value % 2 == 0 || value % 3 == 0)
    {
        return false;
    }
    // otherwise, verify if the value is a prime or not
    for (int i = 5; i*i<=value; i = i+6)
    {
        if (value%i == 0 || value%(i+2) == 0)
        {
            return false;
        }
    }
    // return true if given value is a prime number
    return true;
}

/*
PARAM: value - an integer number
POST: returns the next prime number greater than the given value
*/
int hashTable::findGreaterPrime(int value)
{
    // corner case
    if (value <= 1)
    {
        return 2;
    }
    
    int prime = value;
    bool found = false;

    // while prime hasn't been found
    while (!found)
    {   
        // increment prime
        prime++;
        // verify if number is a prime
        if (isPrime(prime))
        {
            found = true;
        }
    }
    return prime;
}

/*
PARAM:
inputstring - a <string> object representing a word/characters
value - an integer number
POST: returns a value corresponding to the input string. Uses
Horner's Method and the modulo operator to avoid overflow.
*/
int hashTable::hornerMethod(string inputString, int value)
{
    // get size of input string
    int stringSize = inputString.length();
    int lastHashValue = 0;

    // for each character in the input string
    for (int i = 0; i < stringSize; i++)
    {   
        // perform a multiplication by 32 and a modulo by the input value
        lastHashValue = (32 * lastHashValue) + (inputString[i] - 96);
        lastHashValue = lastHashValue % value;
    }
    
    return lastHashValue;
}

/*
PARAM: inputString - a <string> object representing a word/characters
POST: returns string value of the input string as an integer
*/
int hashTable::hashFunctionOne(string inputString)
{
    return (hornerMethod(inputString, arraySize));
}

/*
PARAM: inputString - a <string> object representing a word/characters
POST: returns an integer used to deal with collisions in the hash table
*/
int hashTable::hashFunctionTwo(string inputString)
{
    return (hashTwoValue - (hornerMethod(inputString, hashTwoValue)));
}

/*
PARAM: inputString - a <string> object representing a word/characters
POST: a function that helps insert the input string into the correct position in the array
*/
void hashTable::insertHelper(string inputString)
{
    // obtain position to insert the given string 
    int j = 0;
    int index = hashFunctionOne(inputString) + (j*hashFunctionTwo(inputString));

    // if the current position is open
    if (stringArray[index] == "")
    {
        // insert string and increment current size
        stringArray[index] = inputString;
        currentSize++;
    }
    else
    {
        // otherwise, use double hashing to look for the next open position
        while (stringArray[index] != "")
        {
            // increment the index to insert at with second hash function
            j++;
            index = hashFunctionOne(inputString) + (j*hashFunctionTwo(inputString));
            index %= arraySize;
        }
        stringArray[index] = inputString;
        // increment current number of strings
        currentSize++;
    }
}

// Public function implementations:-----------------------------------------

/*
PARAM: N/A
POST: initializes all of the attributes for a hash table object
*/
hashTable::hashTable()
{
    arraySize = 1000000;
    // allocate space for the underlying array
    stringArray = new string[arraySize];
    for (int i = 0; i < arraySize; i++)
    {
        // all positions are "" initially
        stringArray[i] = "";
    }
    currentSize = 0;
    hashTwoValue = findGreaterPrime(arraySize/2);
}

/*
PARAM: size - an integer number
POST: initializes all of the attributes for a hash table object, with a specific size
*/
hashTable::hashTable(int size)
{
    arraySize = size;
    stringArray = new string[arraySize];
    for (int i = 0; i < arraySize; i++)
    {
        stringArray[i] = "";
    }
    currentSize = 0;
    hashTwoValue = findGreaterPrime(arraySize/2);
}

/*
PARAM: N/A
POST: deallocates the space for the underlying array attribute
*/
hashTable::~hashTable()
{
    delete[] stringArray;
}

/*
PARAM: inputstring - a <string> object representing a word/characters
POST: inserts the given string into the correct position in the underlying array
of the calling object. If the load factor is above 0.50, the size will be
doubled and every current string will be repositioned.
*/
void hashTable::insert(string inputString)
{
    // check if the string is already in the hash table or not
    if (find(inputString) == false)
    {
        insertHelper(inputString);

        // check if the load factor > 0.5 after insertion. If so, resize and rehash.
        if (loadFactor() > 0.50)
        {   
            // create variables to hold the old array contents
            int oldSize = arraySize;
            string* oldArray = stringArray;

            // obtain new size for the new array and allocate memory
            int newSize = findGreaterPrime(arraySize*2);
            string* newArray = new string[newSize];
            // update attributes
            arraySize = newSize;
            hashTwoValue = findGreaterPrime(arraySize/2);
            currentSize = 0;

            // go through old array to find strings to insert
            for (int i = 0; i < oldSize; i++)
            {
                if (oldArray[i] != "")
                {
                    insertHelper(oldArray[i]);
                }
            }

            //deallocate old array, and update the attribute
            delete[] oldArray;
            stringArray = newArray;
        }
    }
    else
    {
        cout << "The string has already been inserted." << endl;
    } 
}

/*
PARAM: inputstring - a <string> object representing a word/characters
POST: returns true if the given string is found in the hash table, false otherwise.
*/
bool hashTable::find(string inputString)
{
    // obtain position to insert the given string 
    int j = 0;
    int index = hashFunctionOne(inputString) + (j*hashFunctionTwo(inputString));

    // if current position matches with the given string, return true
    if (stringArray[index] == inputString)
    {
        return true;
    }
    // otherwise, if empty, return false
    else if (stringArray[index] == "")
    {
        return false;
    }
    // otherwise, if not empty but does not match, go to the next position.
    else
    {
        while (stringArray[index] != inputString && stringArray[index] != "")
        {
            j++;
            index = hashFunctionOne(inputString) + (j*hashFunctionTwo(inputString));
            index %= arraySize;
        }
        if (stringArray[index] == inputString)
        {
            return true;
        }
        else if (stringArray[index] == "")
        {
            return false;
        }
    }
    return false;
}

/*
PARAM: N/A
POST: returns load factor of the hash table
*/
double hashTable::loadFactor()
{
    return ((double)currentSize/arraySize);
}

/*
PARAM: N/A
POST: prints every element in the hash table, along with the index position
*/
void hashTable::printTable()
{
    for (int i = 0; i < arraySize; i++)
    {
        cout << "String: " << stringArray[i] << ", " << "Position: " << i << endl;
    }
}

/*
PARAM: N/A
POST: returns a random element within the hash table
*/
string hashTable::chooseRandom()
{
    bool trueValue = false;
    while(!trueValue)
    {
        // seed to generate pseudo-random letters
        srand(time(NULL));
        int randPosition = rand() % arraySize;
        if (stringArray[randPosition] != "")
        {
            trueValue = true;
            return stringArray[randPosition];
        }
    }
    return 0;
}

// Player function implementations:----------------------------------------

/*
PARAM: N/A
POST: initializes the attributes for the player object
*/
Player::Player()
{
    lives = 3;
    score = 0;
}

/*
PARAM: playerName - a <string> object representing the player's nickname
POST: initializes the attributes for the player object, along with a nickname
*/
Player::Player(string playerName)
{
    lives = 3;
    score = 0;
    nickname = playerName;
}

// Game helper function implementations:------------------------------------

/*
PARAM: 
usedWords - a string vector reference object 
inputstring - a <string> object representing a word/characters
POST: checks if the given input string is already in the vector object
*/
bool duplicateCheck(vector<string> & usedWords, string inputString)
{
    if (count(usedWords.begin(), usedWords.end(), inputString) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
PARAM: N/A
POST: returns true if the player would like to continue to another round, false otherwise.
*/
bool nextRoundCheck()
{
    bool validResponse = false;
    while(!validResponse)
    {
        string userInput;
        cout << endl << "Would you like to move onto the next round?: [yes/no]" << endl;
        cin >> userInput;

        if (userInput == "yes")
        {
            validResponse = true;
            return true;
        }
        else if (userInput == "no")
        {
            validResponse = true;
            return false;
        }
        else
        {
            cout << endl << "Sorry, please enter a valid response." << endl;
        }
    }
    return false;
}

/*
PARAM: 
list - a pointer to a Player object
size - an integer number
POST: returns true if theres sufficient players remaining, false otherwise.
*/
bool checkPlayers(Player* list, int size)
{
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (list[i].lives != 0)
        {
            count++;
        }
    }

    if (count >= 2)
    {
        return true;
    }
    return false;

}

/*
PARAM: 
inputstring - a <string> object representing a word/characters
character - a <string> object representing a word/characters
POST: checks if the input string contains the given character(s)
*/
bool characterCheck(string inputString, string character)
{
    if (inputString.find(character) < inputString.length())
    {
        return true;
    }
    else
    {
        return false;
    }
}