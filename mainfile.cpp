#include "letterrush.h"

int main()
{
    //create hash table object for dictionary
    hashTable dictTable;
    string filename = "dictionary.txt", word;
    ifstream file(filename);

    //read the dictionary text file into the hash table object
    if (file.is_open())
    {
        while (file >> word)
        {
            dictTable.insert(word);
        }
    }
    file.close();

    cout << "Welcome to Letter Rush! How many people will be playing?: " << endl;
    //need to save the user input in a variable.


    return 0;
}
