#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define STDIN 0
#define STDOUT 1
#define BUFFER_SIZE 8
#define ROW_SIZE 3
#define BOARD_SIZE ROW_SIZE*ROW_SIZE
#define true 1
#define false 0

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

int has_won(char *board, int *player){
  //Checking rows
  for (int i = 0; i < BOARD_SIZE; i += ROW_SIZE){
    for (int j = 0; j < ROW_SIZE; j++){
      if (board[(j + i)] != board[(j + i) + 1])
	continue;
      if (j + 2 == ROW_SIZE && board[(j + i)] != '0')
	return *player;
    }
  }
  //Checking lines
  for (int i = 0; i < ROW_SIZE; i++){
    for (int j = 0; j < BOARD_SIZE; j += ROW_SIZE){
      if (board[(j + i)] != board[(j + i) + ROW_SIZE])
	continue;
      if (((j + i) + ROW_SIZE) >= BOARD_SIZE - ROW_SIZE && board[(j + i)] != '0')
	return *player;
    }
  }
  //Checking diagonals
  int acc = ROW_SIZE + 1;
  //Right diagonal
  for (int i = 0; i < BOARD_SIZE; i += acc){
    if (board[i] != board[i + acc])
      continue;
    if ((i + acc) >= BOARD_SIZE - ROW_SIZE && board[i] != '0')
      return *player;
  }
  //Left diagonal
  acc = ROW_SIZE - 1;
  for (int i = (ROW_SIZE - 1); i < BOARD_SIZE; i += acc){
    if (board[i] != board[i + acc])
      continue;
    if ((i + acc) >= BOARD_SIZE - ROW_SIZE && board[i] != '0')
      return *player;
  }
  //Checking tie
  for (int i = 0; i < BOARD_SIZE; i++){
    if (board[i] == '0')
      break;
    if ((i + 1) == BOARD_SIZE)
      return -1;
  }
  return false;
}

int process_input(char *board, int input, int *player, int *winner){
  char playerChar = *player ? 'O' : 'X';

  if (input > BOARD_SIZE)
    write(STDOUT, "INPUT ERROR\n", 12);
  else if (board[input] != '0')
    write(STDOUT, "INVALID MOVE\n", 13);
  else {
    board[input] = playerChar;
    *player = !(*player);
    print_board(board);
    if (*winner = has_won(board, player)){
      return false;
    }
  }
  return true;
}

int game(){
  char buffer[BUFFER_SIZE];
  char board[BOARD_SIZE];
  int userInput;
  int winner = -1;
  int player = 0;

  clear_board(&board);
  print_board(&board);
  while (read(STDIN, buffer, BUFFER_SIZE)){
    userInput = atoi(buffer);
    if (!process_input(&board, userInput, &player, &winner))
      return winner;
  }
  return -1;
}

int main(int argc, char **argv){
  int result = game();
  if (result > 0)
    printf("Player %i won!\n", result);
  else
    printf("Tie!\n", result);
}
