#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define STDIN 0
#define STDOUT 1
#define BUFFER_SIZE 512
#define ROW_SIZE 3
#define BOARD_SIZE ROW_SIZE*ROW_SIZE

void clear_board(char *board){
  for (int i = 0; i < BOARD_SIZE; i++){
    board[i] = '0';
  }
}

void print_board(char *board){
  for (int i = 0; i < BOARD_SIZE; i++){
    write(STDOUT, &board[i], 1);
    if (i > 0 && (i + 1) % ROW_SIZE == 0)
      write(STDOUT, "\n", 2);
  }
}

void process_input(char *board, int input, int *player){
  char playerChar = 'X';
  if (input > BOARD_SIZE)
    write(STDOUT, "INPUT ERROR\n", 12);
  else if (board[input] != '0')
    write(STDOUT, "INVALID MOVE\n", 13);
  else {
    if (*player == 1)
      playerChar = 'O';
    board[input] = playerChar;
    *player = !(*player);
  }
  print_board(board);
}

int game(){
  char buffer[BUFFER_SIZE];
  char board[BOARD_SIZE];
  int userInput;
  int stop = 0;
  int player = 0;

  clear_board(&board);
  print_board(&board);
  while (read(STDIN, buffer, BUFFER_SIZE) && !stop){
    userInput = atoi(buffer);
    process_input(&board, userInput, &player);
  }
}

int main(int argc, char **argv){
  int result = game();
}
