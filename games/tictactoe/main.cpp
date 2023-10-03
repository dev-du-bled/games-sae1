#include <iostream>
#include "../../libs/termkit.cpp"

class Player {
  public:
    std::string name;
    unsigned char symbol;
    int score;

    void player(std::string name, unsigned char symbol) {
      this->name = name;
      this->symbol = symbol;
      this->score = 0;
    }

    void addScore() {
      this->score++;
    }

    void resetScore() {
      this->score = 0;
    }
};

class Board {
  public:
    int size = 3;
    unsigned char grid[3][3];

    void createBoard(int size) {
      this->size = size;
      this->grid[size][size];
    }

    void resetBoard() {
      for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
          this->grid[i][j] = ' ';
        }
      }
    }

    bool isFull() {
      for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
          if (this->grid[i][j] == ' ') {
            return false;
          }
        }
      }

      return true;
    }
};

int main() {
  return 0;
}