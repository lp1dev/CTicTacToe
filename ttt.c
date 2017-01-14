#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STDIN 0
#define STDOUT 1
#define BUFFER_SIZE 512
#define BOARD_SIZE 3

void clear_board(char *board[BOARD_SIZE][BOARD_SIZE]){
  for (char i = 0; i < BOARD_SIZE; i++){
    for (char j = 0; j < BOARD_SIZE; j++){
      &board[i][j] = '0';
    }
  }
}

void print_board(char *board[BOARD_SIZE][BOARD_SIZE]){
  for (char i = 0; i < BOARD_SIZE; i++){
    write(STDOUT, "|", 1);
    for (char j = 0; j < BOARD_SIZE; j++){
      write(STDOUT, board[i][j], 1);
      write(STDOUT, "|", 1);
    }
    write(STDOUT, "\n", 1);
  }
}

void process_input(char *board[BOARD_SIZE][BOARD_SIZE], int *input, int *player){
  print_board(*board);
}

int game(){
  char buffer[BUFFER_SIZE];
  char board[BOARD_SIZE][BOARD_SIZE];
  int userInput;
  int stop = 0;
  int player = 0;

  clear_board(&board);
  print_board(&board);
  while (read(STDIN, buffer, BUFFER_SIZE) && !stop){
    userInput = atoi(buffer);
    process_input(&board, &userInput, &player);
  }
}

int main(int argc, char **argv){
  int result = game();
}
