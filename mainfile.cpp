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
    if (numberOfPlayers <= 1)
    {
        cout << endl << "Sorry, you need at least 2 players." << endl;
        exit(0);
    }
    //array containing all of the players. deallocate afterwards.
    Player* listOfPlayers = new Player[numberOfPlayers];

    //obtain nicknames and initalize the player objects
    string playerName;
    for (int i = 0; i < numberOfPlayers; i++)
    {
        cout << endl << "Player " << i+1 << "!" << " What is your nickname?: (enter at least 1 character)" << endl;
        cin >> playerName;
        Player currentPlayer(playerName);
        listOfPlayers[i] = currentPlayer;
    }

    //word bank to keep track of words that have been used
    vector<string> usedWords;

    bool stillPlay = true;
    bool stillPlayersLeft = true;
    //While the user still wants to play
    while (stillPlay)
    {
        sleep(1);
        cout << endl << "The round will now start!" << endl;

        usedWords.clear();

        stillPlayersLeft = true;
        int sec = 5;
        int setTime = 60;
        bool difficultyUp = false;
        time_t roundTime = time(NULL);

        //While there are still players left
        while (stillPlayersLeft)
        {
            for (int i = 0; i < numberOfPlayers; i++)
            {
                //check if there's at least 2 players with lives left
                if (checkPlayers(listOfPlayers, numberOfPlayers) == false)
                {
                    stillPlayersLeft = false;
                    break;
                }

                //Checking for players that have been eliminated
                if (listOfPlayers[i].lives == 0)
                {
                    continue;
                }

                //Check if round time has gone over a minute, if so, increase difficulty:
                if (difftime(time(NULL), roundTime) >= setTime)
                {
                    cout << endl << "...Difficulty is increasing!" << endl;
                    difficultyUp = true;
                }

                sleep(1);
                cout << endl << listOfPlayers[i].nickname << ", it is your turn!" << endl;

                string character;
                if (difficultyUp == true)
                {
                    sec = 3;
                    character = twoCharacterTable.chooseRandom();
                }
                else
                {
                    character = oneCharacterTable.chooseRandom();
                }

                sleep(1);
                cout << endl << "You have " << sec << " seconds to type in a valid word with the letter: " << character << endl;

                bool validWord = false;
                string userInput;
                time_t start = time(NULL);

                //Keep checking if user has input a valid otherwise, otherwise, time will run out.
                while (!validWord)
                {
                    //obtain user input
                    cin >> userInput;
                    
                    //if time runs out
                    if (difftime(time(NULL), start) >= sec)
                    {
                        cout << endl << "Didn't enter in " << sec << " seconds! You lose a life :(" << endl;
                        listOfPlayers[i].lives -= 1;
                        if (listOfPlayers[i].lives == 0)
                        {
                            cout << endl << listOfPlayers[i].nickname << " is out!" << endl;
                        }
                        break;
                    }
                    //go through word validity cases
                    else if (dictTable.find(userInput) == false)
                    {
                        cout << endl << "That word does not exist! Try again:" << endl;
                        continue;
                    }
                    else if (duplicateCheck(usedWords, userInput) == true)
                    {
                        cout << endl << "That word has already been used! Try again:" << endl;
                        continue;
                    }
                    else if (characterCheck(userInput, character) == false)
                    {
                        cout << endl << "That word doesn't contain the given letter! Try again:" << endl;
                        continue;
                    }
                    //if user input passes all of the cases
                    else
                    {
                        cout << endl << "That word is valid!" << endl;
                        usedWords.push_back(userInput);
                        validWord = true;
                        continue;
                    }
                }
            }
        }
        
        //Announce winner of that round, and award them with +1 to their score.
        for (int i = 0; i < numberOfPlayers; i++)
        {
            if (listOfPlayers[i].lives != 0)
            {
                cout << endl << listOfPlayers[i].nickname << " won this round!" << endl;
                listOfPlayers[i].score += 1;
            }
            //reset lives for next round
            listOfPlayers[i].lives = 3;
        }

        //print scores of all of the players
        cout << endl << "Here are the current scores: " << endl;
        for (int i = 0; i < numberOfPlayers; i++)
        {
            cout << endl;
            cout << listOfPlayers[i].nickname << " - Wins: " << listOfPlayers[i].score << endl;
        }

        //ask user if they to play another round
        if (nextRoundCheck() == false)
        {
            stillPlay = false;
        }
    }

    cout << endl << "Thanks for playing Letter Rush by Daniel Nguyen!" << endl;
    delete[] listOfPlayers;
    return 0;
}
