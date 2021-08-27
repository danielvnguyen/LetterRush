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

    int numberOfPlayers = 0;
    cout << "Welcome to Letter Rush! How many people will be playing?: " << endl;

    //need to save the user input in a variable.
    cin >> numberOfPlayers;
    //array containing all of the players
    Player* listOfPlayers = new Player[numberOfPlayers];

    //obtain nicknames and initalize the player objects
    string playerName;
    for (int i = 0; i < numberOfPlayers; i++)
    {
        cout << "Player " << i+1 << "!" << " What is your nickname?: " << endl;
        cin >> playerName;
        Player currentPlayer(playerName);
        listOfPlayers[i] = currentPlayer;
    }

    return 0;
}
