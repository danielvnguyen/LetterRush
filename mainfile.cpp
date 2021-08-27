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

    //create hash table for alphabet
    hashTable oneCharacterTable(60);
    string filenameTwo = "oneCharacter.txt";
    ifstream fileTwo(filenameTwo);

    if (fileTwo.is_open())
    {
        while (fileTwo >> word)
        {
            oneCharacterTable.insert(word);
        }
    }
    fileTwo.close();

    //create hash table for combinations of two letters in alphabet
    hashTable twoCharacterTable(1400);
    string filenameThree = "twoCharacters.txt";
    ifstream fileThree(filenameThree);

    if (fileThree.is_open())
    {
        while (fileThree >> word)
        {
            twoCharacterTable.insert(word);
        }
    }
    fileThree.close();

//----------------------------------------------------------------------------

    int numberOfPlayers = 0;
    cout << "Welcome to Letter Rush! How many people will be playing?: (must have at least 2 players)" << endl;

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

    //word bank to keep track of words that have been used
    vector<string> usedWords;

    //Start initial round, and repeat (with same players, new scores, and reset lives)
    //if user still wants to play.
    bool stillPlay = true;
    while (stillPlay)
    {
        //Note: check string with .lower()
        sleep(2);
        cout << "The round will now start!" << endl;

        usedWords.clear();

        bool stillPlayersLeft = true;
        while (stillPlayersLeft)
        {
            for (int i = 0; i < numberOfPlayers; i++)
            {
                //Checking for players that have been eliminated
                if (listOfPlayers[i].lives == 0)
                {
                    continue;
                }

                cout << listOfPlayers[i].nickname << ", it is your turn!" << endl;
                string character = oneCharacterTable.chooseRandom();
                cout << "You have 5 seconds to type in a word with: " << character << endl;
                string userInput;
                cin >> userInput;

                //Check if input word is a valid word, and if it's been used already:
                //Valid = characters in word, word in dictionary, word not a duplicate.
                if (dictTable.find(userInput) == true && duplicateCheck(usedWords, userInput) == false 
                && characterCheck(userInput, character) == true)
                {
                    cout << "That word is valid!" << endl;
                    usedWords.push_back(userInput);
                }
                else
                {
                    cout << "That word is not valid!" << endl;
                    listOfPlayers[i].lives -= 1;
                    if (listOfPlayers[i].lives == 0)
                    {
                        cout << listOfPlayers[i].nickname << " is out!" << endl;
                    }
                }
            }

            //check if there's at least 2 players with lives left
            if (checkPlayers(listOfPlayers, numberOfPlayers) == false)
            {
                stillPlayersLeft = false;
            }
        }
        
        //Anounce winner of that round, and award them with +1 to their score.

        //ask user if they to play another round
        if (nextRoundCheck() == false)
        {
            stillPlay = false;
        }
    }

    cout << "Thanks for playing Letter Rush!" << endl;
    return 0;
}
