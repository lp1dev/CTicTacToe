#include <stdio.h>
#include <string.h>

#define STDIN 0
#define BUFFER_SIZE 512
#define BOARD_SIZE 3

int game(){
  char buffer[BUFFER_SIZE];
  int board[BOARD_SIZE][BOARD_SIZE];
  int userInput;
  int stop = 0;
  
  while (read(STDIN, buffer, BUFFER_SIZE) && !stop){
    userInput = atoi(buffer);
    printf("UserInput : %i\n", userInput);
  }
}

int main(int argc, char **argv){
  int result = game();
}
