#include "letterrush.h"

//Private function implementations:
bool hashTable::isPrime(int value)
{
    //Corner cases (if value is 1 or below, return false)
    if (value <= 1)
    {
        return false;
    }
    //if value is 2 or 3, return true
    if (value <= 3)
    {
        return true;
    }
    //if value mod 2 or 3 is not 0, return false
    if (value % 2 == 0 || value % 3 == 0)
    {
        return false;
    }
    //otherwise, verify if the value is a prime or not
    for (int i = 5; i*i<=value; i = i+6)
    {
        if (value%i == 0 || value%(i+2) == 0)
        {
            return false;
        }
    }
    //return true if so
    return true;
}

int hashTable::findGreaterPrime(int value)
{
    //Corner case
    if (value <= 1)
    {
        return 2;
    }
    
    int prime = value;
    bool found = false;

    //while prime hasn't been found
    while (!found)
    {   
        //increment prime
        prime++;
        //verify if number is a prime
        if (isPrime(prime))
        {
            found = true;
        }
    }
    return prime;
}

//Helper method to avoid overflow when generating string values
int hashTable::hornerMethod(string inputString, int value)
{
    //get size of input string
    int stringSize = inputString.length();
    int lastHashValue = 0;

    //for each character in the input string
    for (int i = 0; i < stringSize; i++)
    {   
        //perform a multiplication by 32 and a modulo by the input value
        lastHashValue = (32 * lastHashValue) + (inputString[i] - 96);
        lastHashValue = lastHashValue % value;
    }
    
    return lastHashValue;
}

int hashTable::hashFunctionOne(string inputString)
{
    return (hornerMethod(inputString, arraySize));
}

int hashTable::hashFunctionTwo(string inputString)
{
    return (hashTwoValue - (hornerMethod(inputString, hashTwoValue)));
}

void hashTable::insertHelper(string inputString)
{
    //obtain position to insert the given string 
    int j = 0;
    int index = hashFunctionOne(inputString) + (j*hashFunctionTwo(inputString));

    //if the current position is open
    if (stringArray[index] == "")
    {
        //insert string and increment current size
        stringArray[index] = inputString;
        currentSize++;
    }
    else
    {
        //otherwise, use double hashing to look for the next open position
        while (stringArray[index] != "")
        {
            //increment the index to insert at with second hash function
            j++;
            index = hashFunctionOne(inputString) + (j*hashFunctionTwo(inputString));
            index %= arraySize;
        }
        stringArray[index] = inputString;
        currentSize++;
    }
}

//Public function implementations:---------------------------------------------------------
hashTable::hashTable()
{
    arraySize = 700000;
    stringArray = new string[arraySize];
    for (int i = 0; i < arraySize; i++)
    {
        stringArray[i] = "";
    }
    currentSize = 0;
    hashTwoValue = findGreaterPrime(arraySize/2);
}

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

hashTable::~hashTable()
{
    //deallocate memory associated with array attribute
    delete[] stringArray;
}

void hashTable::insert(string inputString)
{
    //check if the string is already in the hash table or not
    if (find(inputString) == false)
    {
        insertHelper(inputString);

        //check if the load factor > 0.5 after insertion. If so, resize and rehash.
        if (loadFactor() > 0.50)
        {   
            //create variables to hold the old array contents
            int oldSize = arraySize;
            string* oldArray = stringArray;

            //obtain new size for the new array and allocate memory
            int newSize = findGreaterPrime(arraySize*2);
            string* newArray = new string[newSize];
            //update attributes
            arraySize = newSize;
            hashTwoValue = findGreaterPrime(arraySize/2);
            currentSize = 0;

            //go through old array to find strings to insert
            for (int i = 0; i < oldSize; i++)
            {
                if (oldArray[i] != "")
                {
                    insertHelper(oldArray[i]);
                }
            }
        }
    }
    else
    {
        cout << "The string has already been inserted." << endl;
    } 
}

bool hashTable::find(string inputString)
{
    //obtain position to insert the given string 
    int j = 0;
    int index = hashFunctionOne(inputString) + (j*hashFunctionTwo(inputString));

    //if current position matches with the given string, return true
    if (stringArray[index] == inputString)
    {
        return true;
    }
    //otherwise, if empty, return false
    else if (stringArray[index] == "")
    {
        return false;
    }
    //otherwise, if not empty but does not match, go to the next position.
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

int hashTable::size()
{
    return currentSize;
}

int hashTable::maxSize()
{
    return arraySize;
}

double hashTable::loadFactor()
{
    return ((double)currentSize/arraySize);
}

void hashTable::printTable()
{
    for (int i = 0; i < arraySize; i++)
    {
        cout << "String: " << stringArray[i] << ", " << "Position: " << i << endl;
    }
}

string hashTable::chooseRandom()
{
    bool trueValue = false;
    while(!trueValue)
    {
        //seed to generate pseudo-random letters
        srand(time(NULL));
        int randPosition = rand() % arraySize + 1;
        if (stringArray[randPosition] != "")
        {
            trueValue = true;
            return stringArray[randPosition];
        }
    }
}

//Player function implementations:----------------------------------------

Player::Player()
{
    lives = 3;
    score = 0;
}

Player::Player(string playerName)
{
    lives = 3;
    score = 0;
    nickname = playerName;
}

//Dictionary functions:

//for printing result vector
void printVector(vector<string> usedWords)
{
    for (auto i = usedWords.begin(); i != usedWords.end(); ++i)
    {
        cout << *i << endl;
    }
}

//checking for duplicate input strings
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

bool nextRoundCheck()
{
    bool validResponse = false;
    while(!validResponse)
    {
        string userInput;
        cout << "Would you like to move onto the next round?: [yes/no]" << endl;
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
            cout << "Sorry, please enter a valid response." << endl;
        }
    }
}

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