#include "letterrush.h"

int main()
{
    hashTable dictTable;
    string filename = "dictionary.txt", word;
    ifstream file(filename);

    if (file.is_open())
    {
        while (file >> word)
        {
            dictTable.insert(word);
        }
    }
    file.close();


    return 0;
}
