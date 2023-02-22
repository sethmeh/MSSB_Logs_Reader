/* To use:
* Copy and paste the entire stars off/on logs spreadsheet into an input text file
* Run the main.cpp file
* enter the input text file, output text file, and the name of the player you want stats on
* Output will be sent to the specified output text file
*/


#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Game.h"

using namespace std;

const int MAX_ARRAY_SIZE = 200; //must be greater than the number of distinct opponents you've played against

void readFile(ifstream &inputFile, double myWins[], string opNames[], double opWins[], string playerName, int& opponentCount, vector <Game*> games[], double& totalGameCount) {
  string line;
  getline(inputFile, line);

  opponentCount = 0;
  int opIndex;

  while (getline(inputFile, line)) {
    opIndex = -1;
    totalGameCount++;
    
    string winnerID = line.substr(0, line.find("\t"));
    line = line.substr(line.find("\t") + 1);
    string winnerName = line.substr(0, line.find("\t"));
    line = line.substr(line.find("\t") + 1);
    string winnerScore = line.substr(0, line.find("\t"));
    line = line.substr(line.find("\t") + 1);
    string winnerElo = line.substr(0, line.find("\t"));
    line = line.substr(line.find("\t") + 1);
    string winnerRD = line.substr(0, line.find("\t"));
    line = line.substr(line.find("\t") + 1);
    string loserID = line.substr(0, line.find("\t"));
    line = line.substr(line.find("\t") + 1);
    string loserName = line.substr(0, line.find("\t"));
    line = line.substr(line.find("\t") + 1);
    string loserScore = line.substr(0, line.find("\t"));
    line = line.substr(line.find("\t") + 1);
    string loserElo = line.substr(0, line.find("\t"));
    line = line.substr(line.find("\t") + 1);
    string loserRD = line.substr(0, line.find("\t"));
    line = line.substr(line.find("\t") + 1);
    string timestamp = line.substr(0, line.find("\t"));
    line = line.substr(line.find("\t") + 1);
    string index = line;

    if(index.length() >= 5){
      index = index.substr(0,1) + index.substr(2);
    }
    if (winnerName == playerName) {
      for (int i = 0; i < opponentCount; i++){
        if (loserName == opNames[i]){
          opIndex = i;
          myWins[i]++;
          Game* newGame = new Game(stoi(winnerScore), stoi(loserScore), stod(winnerElo), stod(loserElo), timestamp, stoi(index));
          games[i].push_back(newGame);
        }
      }
      if (opIndex == -1){
        opNames[opponentCount] = loserName;
        myWins[opponentCount]++;
        Game* newGame = new Game(stoi(winnerScore), stoi(loserScore), stod(winnerElo), stod(loserElo), timestamp, stoi(index));
        games[opponentCount].push_back(newGame);
        opponentCount++;
      }
    } else if(loserName == playerName){
      for (int i = 0; i < opponentCount; i++){
        if (winnerName == opNames[i]){
          opIndex = i;
          opWins[i]++;
          Game* newGame = new Game(stoi(loserScore), stoi(winnerScore), stod(loserElo), stod(winnerElo), timestamp, stoi(index));
          games[i].push_back(newGame);
        }
      }
      if (opIndex == -1){
        opNames[opponentCount] = winnerName;
        opWins[opponentCount]++;
        Game* newGame = new Game(stoi(loserScore), stoi(winnerScore), stod(loserElo), stod(winnerElo), timestamp, stoi(index));
        games[opponentCount].push_back(newGame);
        opponentCount++;
      }
    }
  }
  return;
}

void writeInfo(ofstream& outputFile, double myWins[], string opNames[], double opWins[], string playerName, int& opponentCount, vector <Game*> games[], double& totalGameCount){


  outputFile << "The following shows the stats for inputted player '" << playerName << "' against all their opponents. ";
  outputFile << "\"Average game index\" approximates how late into the season two players have played. A higher index corresponds to more recently played games. ";
  outputFile << "The elo used is the raw elo from the spreadsheet, not the elo from the leaderboards. A positive elo differential means " << playerName << " had the higher average elo when playing against their opponent. A negative elo differential would mean the opposite. ";
  outputFile << "The same is true for total run differential. ";
  outputFile << endl << endl << endl;

  outputFile << "The current average index is " << totalGameCount/2 << endl << endl;

  outputFile << "Player " << playerName << " has played " << opponentCount << " different opponents.\n\n";
  
  for (int i = 0; i < opponentCount; i++){
    outputFile << playerName << " has played " << opNames[i] << " " << myWins[i] + opWins[i] << " times and has won " << setprecision(4) << 100 * myWins[i] / (myWins[i] + opWins[i]) << "% (" << myWins[i] << " out of " << myWins[i] + opWins[i] << ")\n";

    double totalPlayerRuns = 0;
    double totalOpRuns = 0;
    double totalPlayerElo = 0;
    double totalOpElo = 0;
    double totalEloDiff = 0;
    string firstDate = games[i].at(0)->getDate();
    string lastDate = games[i].at(games[i].size()-1)->getDate();
    double totalIndex = 0;
    for (int j = 0; j < games[i].size(); j++){
      totalPlayerRuns += games[i].at(j)->getplayerScore();
      totalOpRuns += games[i].at(j)->getOpScore();
      totalPlayerElo += games[i].at(j)->getPlayerElo();
      totalOpElo += games[i].at(j)->getOpElo();
      totalEloDiff += games[i].at(j)->getPlayerElo() - games[i].at(j)->getOpElo();
      totalIndex += games[i].at(j)->getIndex();
    }
    double playerRunAverage = totalPlayerRuns / games[i].size();
    double opRunAverage = totalOpRuns / games[i].size();
    double playerEloAverage = totalPlayerElo / games[i].size();
    double opEloAverage = totalOpElo / games[i].size();
    double eloDiffAverage = totalEloDiff / games[i].size();
    double indexAverage = totalIndex / games[i].size();

    outputFile << playerName << "'s first match against " << opNames[i] << " was on " << firstDate << " and their most recent game was on " << lastDate << endl;
    outputFile << "The average game index is: " << setprecision(6) << indexAverage << endl;
    outputFile << playerName << "'s average elo when playing " << opNames[i] << ": " << playerEloAverage << endl;
    outputFile << opNames[i] << "'s average elo when playing " << playerName << ": " << opEloAverage << endl;
    outputFile << "Average Elo Differential: " << eloDiffAverage << endl;
    
    outputFile << playerName << " averages " << setprecision(4) << playerRunAverage << " runs per game (" << totalPlayerRuns << " total)\n";
    outputFile << opNames[i] << " averages " << opRunAverage << " runs per game (" << totalOpRuns << " total)\n";
    outputFile << "Total Run Differential: " << totalPlayerRuns - totalOpRuns << endl << endl;
  }
}


int main() {
  std::string filename;
  ifstream inputFile;
  ofstream outputFile;
  
  double myWins[MAX_ARRAY_SIZE] = {0};
  string opNames[MAX_ARRAY_SIZE];
  double opWins[MAX_ARRAY_SIZE] = {0};
  vector <Game*> games[MAX_ARRAY_SIZE];
  int numOpponents = 0;
  string playerName;
  double totalGameCount = 0;
  

  std::cout << "Enter input File Name: ";
  std::cin >> filename;
  inputFile.open(filename);

  std::cout << "Enter output File Name: ";
  std::cin >> filename;
  outputFile.open(filename);

  std::cout << "Enter Player Name: ";
  std::cin >> playerName;

  readFile(inputFile, myWins, opNames, opWins, playerName, numOpponents, games, totalGameCount);
  writeInfo(outputFile, myWins, opNames, opWins, playerName, numOpponents, games, totalGameCount);
}
