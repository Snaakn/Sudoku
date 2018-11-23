#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

static uint8_t field[9][9];
static bool isProtected[9][9];
char lastInput[] = {'0','0','0','0'};

bool colorcheck(uint8_t,uint8_t,uint8_t);

void loadLevel() {
  uint8_t level1[9][9] = {{4,1,0,0,6,5,0,0,7},
                          {0,0,6,0,0,7,4,8,0},
                          {2,0,7,4,9,0,0,0,6},
                          {0,6,0,0,7,0,1,0,0},
                          {3,0,1,5,0,0,0,7,2},
                          {0,9,0,0,4,2,3,0,8},
                          {1,0,8,6,0,0,0,2,9},
                          {0,2,0,0,1,8,6,4,0},
                          {6,0,0,3,0,0,0,1,0}};
  for (uint8_t i = 0; i < 9; i++){
    for (uint8_t j = 0; j < 9; j++){
      field[i][j] = level1[j][i];
      if (field[i][j] != 0){
        isProtected[i][j] = true;
      } else
          isProtected[i][j] = false;
    }
  }
}


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
        if(isProtected[x][y]){
          if (!colorcheck(x,y,field[x][y]))
            printf("[\x1B[31m%d\x1B[0m]",field[x][y]);
          else
            printf("\x1B[0m[%d]",field[x][y]);
        }
        else
        if (!colorcheck(x,y,field[x][y]))
          printf(" \x1B[31m%d\x1B[0m ",field[x][y]);
        else
          printf(" \x1B[0m%d ",field[x][y]);
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

bool colorcheck(uint8_t x, uint8_t y, uint8_t num) {
  uint8_t y_check = 0;
  uint8_t x_check = 0;
  if (y >=0 && y <= 2)
    y_check = 0;
  else if (y >=3 && y <= 5 )
    y_check = 3;
  else if (y >= 6 && y <= 8 )
    y_check = 6;
  if (x >=0 && x <= 2)
    x_check = 0;
  else if (x >=3 && x <= 5 )
    x_check = 3;
  else if (x >=6 && x <= 8 )
    x_check = 6;

  for (uint8_t j = y_check; j < (y_check + 3); j++) {
    for (uint8_t i = x_check; i < (x_check + 3); i++) {
      if (field[i][j] == num && i != x && j != y) {
        return false;
      }
    }
  }
  for (uint8_t k = 0; k < 9; k++) {
    if ((field[k][y] == num && k != x) || (field[x][k] == num && k != y))
      return false;
  }
  return true;
}


bool check() {
  const uint32_t fac9 = 362880;
  for (uint8_t i = 0; i < 9; i++) {
    uint32_t xfac = 1;
    uint32_t yfac = 1;
    for (uint8_t j = 0; j < 9; j++) {
      xfac *= field[i][j];
      yfac *= field[j][i];
    }
    if (xfac != fac9 || yfac != fac9) {
      printf("%u %u\n",xfac,yfac);
      printf("\nchecked\n");
      return false;
    }
  }
  return true;
}

void game(){
  // validity state of the input array
  bool validInput[3] = {false,false,false};
  bool isWon = false;

  char input[6] = "0,0,0";
  // game loop
  while(!isWon){
    draw();
    isWon = check();
    do {
      draw();

      // only if real coordinates are used no zero should be saved
      if ((input[0] != '0' && input[0] != 'c') &&
          (input[2] != '0' && input[2] != 'c') &&
          (input[4] != '0' && input[4] != 'c')) {
        lastInput[0] = input[0];
        lastInput[1] = input[2];
        lastInput[2] = lastInput[3];
        lastInput[3] = input[4];

      }
      printf("Eingabe: ");
      // fill input with spaces to avoid erros
      //input = "      ";
      // allowed characters for input
      const char allowed[] = {'1','2', '3','4','5','6','7','8','9','0'};
      // write input to input via pointer
      scanf("%5s,", &input[0]);
      //printf("%c%c%c%c\n",input[0],input[2],input[4],lastInput[2]);


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
          if ((input[0]=='0' || input[2]=='0') && (input[4]!='0' || input[2]!='0' || input[4]!='0'))
            validInput[0] = validInput[1] = validInput[2] = false;
        }



    } while (/*(input[0]!='c') &&*/ ((validInput[0] == false) || (validInput[1] == false) || (validInput[2] == false)));
    // saving last value of input coordinates for undo function
    // idea: timeline for multiple undos
    // if (input[0]=='c'){
    //   isWon=check();
    // }
    // else{

        // Undo operation
      if (input[0] == '0' && input[2] == '0' && input[4] == '0') {
        input[0]=lastInput[0];
        input[2]=lastInput[1];
        input[4]=lastInput[2];
      }
        if(!isProtected[atoi(&input[2])-1][atoi(&input[0])-1])
          field[atoi(&input[2])-1][atoi(&input[0])-1] = atoi(&input[4]);
      //}
}

}// end of game loop

int main() {
// fill field with zeroes to avoid errors
  for (uint8_t y = 0; y < 9; y++) {
    for (uint8_t x = 0; x < 9; x++) {
      field[x][y] = 0;
    }
  }
  loadLevel();
  game();
  printf("GEWONNEN!\nGut gemacht!\n");


  return 0;
}
