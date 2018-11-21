#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

uint8_t field[9][9];
char lastInput[] = {'0','0','0'};

void draw() {
  printf("  __          _     _             \n");
  printf(" (_    | |   | \\   / \\   |/    | |\n");
  printf(" __)   |_|   |_/   \\_/   |\\    |_|\n");
  // printf("\n");
  // printf("\n");
  // printf("\n");
  printf("    1  2  3   4  5  6   7  8  9\n");

  printf("  +−−−−−−−−−+−−−−−−−−−+−−−−−−−−−+\n");
  for (uint8_t y = 0; y < 9; y++) {
    printf("%d |",y+1);
    for (uint8_t x = 0; x < 9; x++) {
      if (field[x][y]!=0)
        printf(" %d ",field[x][y]);
      else
        printf(" . ");
      if ((x)==2 || (x)==5)
        printf("|");
    }
    printf("|\n");
    if (y==2 || y==5)
      printf("  +−−−−−−−−−+−−−−−−−−−+−−−−−−−−−+\n");
  }
  printf("  +−−−−−−−−−+−−−−−−−−−+−−−−−−−−−+\n");
}

void check()
{
  for (uint8_t i = 0; i < 100; i++) {
    if (i%5 == 0)
      printf("*");
  }
  printf("\nchecked\n");
}

void game(){
  // validity state of the input array
  bool validInput[3] = {false,false,false};
  bool isWon = false;

  char input[6] = "------";
  // game loop
  while(!isWon){
    draw();
    do {
      draw();
      printf("Eingabe: ");
      // fill input with spaces to avoid erros
      //input = "      ";
      // allowed characters for input
      const char allowed[] = {'1','2', '3','4','5','6','7','8','9','0'};
      // write input to input via pointer
      scanf("%5s,", &input[0]);
      printf("%c%c%c\n",input[0],input[2],input[4]);


      validInput[0] = validInput[1] = validInput[2] = false;

      for (uint8_t i=0; i<=9; i++) {
        if (input[0] == allowed[i]) {
          printf("1 true\n");
          validInput[0] = true;}
        if (input[2] == allowed[i]) {
          printf("2 true\n");
          validInput[1] = true;}
        if (input[4] == allowed[i]) {
          printf("3 true\n");
          validInput[2] = true;}
          if ((input[0]=='0' || input[2]=='0') && (input[0]!='0' || input[2]!='0' || input[4]!='0'))
            validInput[0] = validInput[1] = validInput[2] = false;

        if (input[0]=='c' && input[2]=='-' && input[4]=='-'){
          check();
          i = 10; //end for loop
        };
      }
      // if (input[0]=='0' && input[2]=='0' && input[4]=='0') {
      //   undo();
      // }

    } while (validInput[0] == false || validInput[1] == false || validInput[2] == false);
    // saving last value of input coordinates for undo function
    // idea: timeline for multiple undos
    lastInput[0] = input[0];
    lastInput[1] = input[2];
    lastInput[2] = field[input[0]-1][input[2]-1];
    field[atoi(&input[2])-1][atoi(&input[0])-1] = atoi(&input[4]);
  }

}// end of game loop

int main() {
// fill field with zeroes to avoid errors
  for (uint8_t y = 0; y < 9; y++) {
    for (uint8_t x = 0; x < 9; x++) {
      field[x][y] = 0;
    }
  }
  game();
  printf("GEWONNEN!\nGut gemacht!\n");


  return 0;
}
