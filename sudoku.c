#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

uint8_t field[9][9];

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

void input(){
  bool validInput[3] = {false,false,false};

  do {
    draw();
    printf("Eingabe: ");
    char input[6] = "      ";
    const char allowed[] = {'1','2', '3','4','5','6','7','8','9','0'};
    // write input to input via pointer
    scanf("%5s,", &input[0]);

    // list of valid characters for input
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
    }
  } while (validInput[0] == false || validInput[1] == false || validInput[2] == false);
}


int main() {
// fill field with zeroes to avoid errors
  for (uint8_t y = 0; y < 9; y++) {
    for (uint8_t x = 0; x < 9; x++) {
      field[x][y] = 0;
    }
  }
  input();


  return 0;
}
