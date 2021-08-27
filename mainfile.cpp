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
    dictTable.printTable();

    //create hash table for alphabet
    hashTable oneCharacterTable;
    filename = "oneCharacter.txt";
    ifstream file(filename);

    if (file.is_open())
    {
        while (file >> word)
        {
            oneCharacterTable.insert(word);
        }
    }
    file.close();

    //create hash table for combinations of two letters in alphabet
    hashTable twoCharacterTable;
    filename = "twoCharacters.txt";
    ifstream file(filename);

    if (file.is_open())
    {
        while (file >> word)
        {
            twoCharacterTable.insert(word);
        }
    }
    file.close();

//----------------------------------------------------------------------------

    int numberOfPlayers = 0;
    cout << "Welcome to Letter Rush! How many people will be playing?: " << endl;

    //need to save the user input in a variable.
    cin >> numberOfPlayers;
    //array containing all of the players. deallocate afterwards.
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

    //Start initial round, and repeat (with same players, new scores, and reset lives)
    //if user still wants to play.
    bool stillPlay = true;
    while (stillPlay)
    {
        //Note: check string with .lower()
        cout << "The round will now start!" << endl;

        //should be a for loop to traverse through the players here:
        //also check if total (game) time is more than a minute, to up difficulty.
        string character = oneCharacterTable.chooseRandom();
        cout << "You have 5 seconds to type in a word with: " << character << endl;
        string userInput;
        cin >> userInput;

        //ask user if they to play another round
        if (nextRoundCheck() == false)
        {
            stillPlay = false;
        }
    }


    return 0;
}
