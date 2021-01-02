#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include <cmath>
#include <climits>

#include "SkipBoGame.h"
#include "CommandLineError.h"

SkipBoGame::SkipBoGame() {}

SkipBoGame::SkipBoGame(std::ifstream* gameStream) {  
  // read command line arguments
  *gameStream >> shuffleOrNot >> nump >> curp;
  peep = new Player[nump];
  //read each player
  int idx;
  for (int i = 0; i < nump; i++) {
    idx = (curp + i) % nump;
    peep[idx].readIn(gameStream);
  }
  //read draw pile
  draw.readIn(gameStream);
  if (shuffleOrNot == "true") {
    draw.shuffle();
    draw.shuffled = shuffleOrNot;
  }
  //read build piles
  for (int i = 0; i < 4; i++) {
    build[i].readIn(gameStream);
  }
  gameStream->close();
}

SkipBoGame::~SkipBoGame() {
  delete[] peep;
}

void SkipBoGame::setUpDraw(std::istream& stream) {
  draw.DeckToDraw(stream);
}

void SkipBoGame::setUpPlayers(char **argv) {
  // initialize a random seed so that shuffle is random
  std::srand(time(0));
  nump = atoi(argv[2]);
  // determine if player turn should be shuffled and obtain random player
  int cmp = strcmp(argv[1], "true");
  curp = (cmp == 0) ? std::rand() % nump : 0;
  // update SkipBoGame to "shuffled" gamemode if indicated
  if (cmp == 0) {
    shuffleOrNot = "true";
    draw.shuffled = "true";
    draw.shuffle();
  } else {
    shuffleOrNot = "false";
  }
  // initialize players
  peep = new Player[nump];
  for (int i = 0; i < nump; i++) {
    peep[i].name = "Player" + std::to_string(i);
  }
  // deal player stock piles
  int stockSize = atoi(argv[3]);
  dealCards(stockSize);
}

void SkipBoGame::dealCards(int stockSize) {
  //deal cards to stockpile in round robin fashion
  for (int i = 0; i < stockSize; i++) {
    for (int j = 0; j < nump; j++) {
      Card c(draw.top().getValue());
      peep[j].stock.addCard(c);
      draw.popCard();
    }
  }
}

/* for live game play - must not change format!
drawPile  build_a  build_b  build_c  build_d
playerName  stock_0  
discards: discard_1 discard_2 discard_3 discard_4
hand: card_5 card_6 card_7 card_8 card_9
 */
void SkipBoGame::display() const {
  std::cout << "Draw: ";
  draw.display();
  std::cout << "  Build Piles: ";
  for (int j = 0; j < 4; j++) {
    build[j].display();
    std::cout << " ";
  }
  std::cout << std::endl;
  peep[curp].display();
}

/* for saving state - must not change format!
shuffle numplayers currplayer
PlayerCurp [display]
PlayerCurp+1 [display]
[etc for all players]
Draw [display]
Build_a [display]
Build_b [display]
Build_c [display]
Build_d [display]
*/
std::string SkipBoGame::toString() const {
  std::stringstream result;
  int idx;
  result << draw.getRand() << " " << nump << " " << curp << "\n";
  for (int i = 0; i < nump; ++i) {
    idx = (curp+i) % nump;
    result << peep[idx].toString();
  }
  result << "Draw " << draw.toString(); 
  for (int j = 0; j < 4; j++) {
    result << "Build_" << char('a'+j) << " ";
    result << build[j].toString();  
  }
  return result.str();
}

void SkipBoGame::play() {
  int t = turn;
  std::string userInput;
  char whatNow = '0';

  // execute game loop while there is no winner
  while (!GameOver()) {

    // prompt user for play, save, or quit action
    std::cout << " >> Player" << curp << " turn next" << std::endl;
    std::cout << "(p)lay, (s)ave, or (q)uit ? ";
    std::cin >> userInput;

    whatNow = userInput.at(0);
    // if player supplies bad input, output error and try again
    if ((whatNow != 'p') && (whatNow != 'q') && (whatNow != 's')) {
      std::cout << "illegal command, try again" << std::endl << std::endl;
    }
    else {
      // play action
      if (whatNow == 'p') {
        fillHand();
        while (t == turn) {
          playTurn();
          //check if game over
          if (turn == -1) {
            std::cout << "GAME OVER - Player" << curp << " wins!" << std::endl;
            return;
          }
       }
       t++;
      }
      //save action
      else if (whatNow == 's') {
        std::string filename;
        //prompt for filename to save to
        std::cout << "save filename: ";
        std::cin >> filename;

        saveGame(filename);
        return;
      }
      //quit action
      else if (whatNow == 'q') {
        std::cout << "thanks for playing" << std::endl;
        return;
      } 
    //update current player  
    curp = (curp + 1) % nump;
    }
  }

}

bool SkipBoGame::GameOver() {
  return peep[curp].stock.isEmpty() ? true : false;
}

void SkipBoGame::playTurn() {
  display();
  std::string i, f, t;
  char input, moveFrom, moveTo;

  std::cout << "(m)ove [start] [end] or (d)raw ? ";
  //read player action as string
  std::cin >> i;
  //read player action char
  input = i.at(0);
  //player move action
  if (input == 'm') {
    //read details of player action as strings
    std::cin >> f >> t;
    //read details of player action as chars
    moveFrom = f.at(0);
    moveTo = t.at(0);
    //check if player move is legal
    if(!legalMove(moveFrom, moveTo)) {
      std::cout << "illegal command, try again" << std::endl;
      std::cout << std::endl;
      return playTurn();
    }
    //if move is legal, make player move
    makeMove(moveFrom, moveTo);

    //set aside completed build piles
    for (int i = 0; i < 4; i++) {
      if (build[i].size() == 12) {
        //put aside
        setAside(i);
        std::cout << "build pile " << (char) (i + 97) << " full, set aside" << std::endl;
      }
    }
    std::cout << std::endl;
  
    //check if game over after making move
    if (GameOver()) {
      turn = -1;
      return;
    }
  }
  //player draw action
  else if (input == 'd') {
    //check if player hand is empty. if not, return error
    if (peep[curp].hand.isEmpty()) {
      fillHand();
      std::cout << std::endl;
    } else {
      //hand must be empty to draw!
      std::cout << "illegal command, try again" << std::endl << std::endl;
      return playTurn();
    }
  }
  //input must be m or d
  else {
    std::cout << "illegal command, try again" << std::endl;
    return playTurn();
  }
}

void SkipBoGame::setAside(int i) {
  //set aside completed build pile and clear completed pile from game
  aside.push_back(build[i]);
  for (int j = 0; j < 12; j++) {
    build[i].popCard();
  }
}

bool SkipBoGame::legalMove(char moveFrom, char moveTo) {
  Card cardToMove;
  //stock can only move to build
  if ((moveFrom == '0') && (moveTo >= 'a') && (moveTo <= 'd')) {
    cardToMove = peep[curp].stock.top();
    int diff = cardToMove.getValue() - build[moveTo - 'a'].size();
    if ((diff == 1) || (cardToMove.getValue() == 0)) {
      return true;
    }
  }
  //discard can move to build
  if ((moveFrom >= '1') && (moveFrom <= '4') && (moveTo >= 'a') && (moveTo <= 'd')) {
    //illegal if discard pile is empty
    if (peep[curp].discard[moveFrom - '1'].size() == 0) {
      return false;
    }
    cardToMove = peep[curp].discard[moveFrom - '1'].top();
    int diff = cardToMove.getValue() - build[moveTo - 'a'].size();
    if ((diff == 1) || (cardToMove.getValue() == 0)) {
      return true;
    }
  }
  //hand can move to discard or build
  if ((moveFrom >= '5') && (moveFrom <= '9')) {
    //move to build
    if ((moveTo >= 'a') && (moveTo <= 'd')) {
      cardToMove = peep[curp].hand.getCard((moveFrom - '0') % 5);
      int diff = cardToMove.getValue() - build[moveTo - 'a'].size();
      if ((diff == 1) || (cardToMove.getValue() == 0)) {
        return true;
      }
    }
    //move to discard
    if (((moveFrom - '0') % 5 < peep[curp].hand.size()) && (moveTo <= '4') && (moveTo >= '1')) {
      return true;
    }
  }
  return false;
}

//only called if move is valid
void SkipBoGame::makeMove(char moveFrom, char moveTo) {
  //move from curr player's stock pile to build pile.
  if (moveFrom == '0') {
    Card c(peep[curp].stock.top().getValue());
    build[moveTo - 'a'].addCard(c);
    peep[curp].stock.popCard();
  }
  //move from discard to build
  if ((moveFrom >= '1') && (moveFrom <= '4')) {
    int idx = (moveFrom - '1');
    Card c(peep[curp].discard[idx].top().getValue());
    build[moveTo - 'a'].addCard(c);
    peep[curp].discard[idx].popCard();
  }
  //move from hand to build
  if ((moveFrom >= '5') && (moveFrom <= '9') && (moveTo >= 'a') && (moveTo <= 'd')) {
    int idx = moveFrom - '5';
    Card c(peep[curp].hand.getCard(idx));
    build[moveTo - 'a'].addCard(c);
    peep[curp].hand.popCard(idx);
  }
  //move from hand to discard, which ends the turn
  if ((moveFrom >= '5') && (moveFrom <= '9') && (moveTo >= '1') && (moveTo <= '4')) {
    int idx = moveFrom - '5';
    Card c(peep[curp].hand.getCard(idx));
    peep[curp].discard[(moveTo - '1') % 5].addCard(c);
    peep[curp].hand.popCard(idx);
    turn++;

    std::cout << std::endl;
    display();
  }
}

void SkipBoGame::saveGame(std::string filename) {
  //check if game is in shuffle gamemode
  if (shuffleOrNot == "true") {
    draw.shuffle();
  }
  //now write to file
  std::ofstream savefile(filename);
  savefile << shuffleOrNot << " " << nump << " " << curp << std::endl;

  //write player data
  int idx;
  for (int i = 0; i < nump; i++) {
    idx = (curp + i) % nump;
    savefile << peep[idx].toString();
  }
  //check for completed build piles to add to draw
  if (!aside.empty()) {
    replenishDraw();
  }
  savefile << "Draw " << draw.toString();
  for (int i = 0; i < 4; i++) {
    savefile << "Build_" << (char) ('a' + i) << " " << build[i].toString();
  }
  savefile.close();
}


void SkipBoGame::fillHand() {
  //as long as the hand is not full, replenish draw until hand is full
  while (!peep[curp].hand.isFull()) {
    if (draw.isEmpty()) {
      replenishDraw();
    }
    Card c(draw.top().getValue());
    peep[curp].hand.addCard(c);
    draw.popCard();
  }
}

void SkipBoGame::replenishDraw() {
  // iterate backwards through "set aside" build piles to insert earliest completed build piles into draw
  for (std::vector<BuildPile>::reverse_iterator item = aside.rbegin(); item != aside.rend(); ++item) {
    //insert each card of completed build pile into bottom of draw
    while (!item->isEmpty()) {
        Card c(item->top().getValue());
        draw.insert(c);
        item->popCard();
      }
  }
  //clear "set aside" build piles
  while (!aside.empty()) {
    aside.pop_back();
  }
  if (shuffleOrNot == "true") {
      draw.shuffle();
  }
}
