#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
class Game{
  private:

    int playerScore;
    int opScore;
    double playerElo;
    double opElo;
    string date;
    int index;

  public:
Game(){playerScore = 0; opScore = 0; playerElo = 0; opElo = 0; date = ""; index = 0;}
Game(int ws, int ls, double pe, double oe, string d, int i){playerScore = ws; opScore = ls; playerElo = pe; opElo = oe; date = d; index = i;}

int getplayerScore(){
  return playerScore;
}
int getOpScore(){
  return opScore;
}
double getPlayerElo(){
  return playerElo;
}
double getOpElo(){
  return opElo;
}
string getDate(){
  return date;
}
int getIndex(){
  return index;
}

void setplayerScore(int ws){
  playerScore = ws;
}
void setOpScore(int ls){
  opScore = ls;
}
void setPlayerElo(double pe){
  playerElo = pe;
}
void setOpElo(double oe){
  opElo = oe;
}
void setDate(string d){
  date = d;
}
void setIndex(int i){
  index = i;
}

};







#endif