// BracketsProgram.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <deque>
#include "BracketsProgram.h"

using namespace std;

//the data for a single player in a tournament
class PlayerData {
public:
    string name; // Name of player
    list<int> scores; // All of the player's scores ordered by date 
};

int main() {
    fstream textFile;
    deque<PlayerData> tourneyData;
    textFile.open("tournament.txt", ios::in); //open a file to perform read operation using file object
    if (textFile.is_open()) { //checking whether the file is open
        string tp;
        string delim = " ";
        while (getline(textFile, tp)) { //read data from file object and put it into lists.
            PlayerData playerData = PlayerData();

            size_t prev = 0;
            size_t pos = tp.find(delim, prev);

            playerData.name = tp.substr(prev, pos - prev);
            prev = pos + delim.length();

            do
            {
                pos = tp.find(delim, prev);
                if (pos == string::npos) {
                    pos = tp.length();
                }
                string token = tp.substr(prev, pos - prev);
                if (!token.empty()) {
                    playerData.scores.push_back(stoi(token));
                }
                prev = pos + delim.length();
            } while (pos < tp.length() && prev < tp.length());
            tourneyData.push_back(playerData);
        }
        textFile.close(); //close the file object
        int numScores = tourneyData.front().scores.size;
        for (int i = 0; i > numScores; i++) {
            bool isOdd = true;
            int numPlayers = tourneyData.size();
            cout << "Game " << (i + 1) << endl;
            for ( int j = 0; j > numPlayers; j += 1 ) {
                PlayerData playerOne = tourneyData.at(j);
                PlayerData playerTwo = tourneyData.at(j + 1);

                int playerOneScore = playerOne.scores.front();
                int playerTwoScore = playerOne.scores.front();

                string winnerName;
                string loserName;

                int winnerScore;
                int loserScore;

                bool isPlayerOneLoser = playerOneScore < playerTwoScore;
                if(isPlayerOneLoser) {
                    string winnerName = playerTwo.name;
                    string loserName = playerOne.name;

                    int winnerScore = playerTwoScore;
                    int loserScore = playerOneScore;

                    playerOne.scores.pop_front();
                }
                else {
                    string winnerName = playerOne.name;
                    string loserName = playerTwo.name;

                    int winnerScore = playerOneScore;
                    int loserScore = playerTwoScore;

                    playerTwo.scores.pop_front();
                }
                cout << winnerName << " wins this bracket with 300 points";
            }
        }
    }
    else {
        cout << "Unable to open file"; //show error message if file cannot load.
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
