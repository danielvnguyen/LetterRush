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

int hashTable::hornerMethod(string inputString, int value)
{

}

int hashTable::hashFunctionOne(string inputString)
{

}

int hashTable::hashFunctionTwo(string inputString)
{

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

}

void hashTable::insert(string inputString)
{

}

bool hashTable::find(string inputString)
{

}

int hashTable::size()
{

}

int hashTable::maxSize()
{

}

double hashTable::loadFactor()
{

}