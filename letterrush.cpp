#include "letterrush.h"

//Prviate function implementations:
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

//Public function implementations:
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

hashTable::~hashTable()
{
    //deallocate memory associated with array attribute
    delete[] stringArray;
}

//robustness
void hashTable::insert(string inputString)
{
    //Check if the string is already in the hash table or not
    if (find(inputString) == false)
    {
        //Make insertion helper method or use recursion for robustness
    }
    else
    {
        cout << "The string already exists in the hash table" << endl;
    } 
}

bool hashTable::find(string inputString)
{

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

//Dictionary functions:
/*
- reading dictionary into a hashTable object
- checking if word is in said dictionary.
- if so, insert into result vector
- printing hashtable + positions, as well as result vector.
*/