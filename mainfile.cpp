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


        //ask user if they to play another round
        if (nextRoundCheck() == false)
        {
            stillPlay = false;
        }
    }


    return 0;
}
