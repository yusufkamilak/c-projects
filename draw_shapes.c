/* Yusuf Kamil AK - 150116827 - HW1 Source Code
   This program lets user to draw several shapes according to data received.
   Inspired by love, made with passion.

   @ykamilak

*/
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#define GRAPH_SIZE 30

// Global Declarations
enum ShapeType { LINE,PARABOLA,CIRCLE };
typedef enum ShapeType ShapeType;

// Declarations of functions which are used by whole the program.
void menuHandling();
void draw(ShapeType type,char arrayOfPositions[GRAPH_SIZE][GRAPH_SIZE]);
int *getRequiredParameters(ShapeType type);
void printOutGraph(char array[GRAPH_SIZE][GRAPH_SIZE]);

// Main body method.
int main(void) {
  menuHandling();
  return 0;
}

// Utility functions
void menuHandling() {
  int choice = 0;
  char arrayOfPositions[GRAPH_SIZE][GRAPH_SIZE];
  do {
    printf("What kind of process would you like to make?\n \
            1 --> Draw a line\n \
            2 --> Draw a parabola\n \
            3 --> Draw a circle\n \
            4 --> Shut down the program.\n""");
    scanf("%d",&choice);
    switch (choice) {
      case 1:
        draw(LINE,arrayOfPositions);
        printOutGraph(arrayOfPositions);
        break;
      case 2:
        draw(PARABOLA,arrayOfPositions);
        printOutGraph(arrayOfPositions);
        break;
      case 3:
        draw(CIRCLE,arrayOfPositions);
        printOutGraph(arrayOfPositions);
        break;
      case 4:
        printf("\nMay we meet again...\n\n");
        break;
      default:
        printf("\nLooks like you've inserted an invalid number. Try again.\n\n");
        continue;
    }
  }while (choice != 4);
}

void printOutGraph(char array[GRAPH_SIZE][GRAPH_SIZE]) {
  for (int i = 0; i <= GRAPH_SIZE + 1; i++) {
    for (int j = 0; j <= GRAPH_SIZE + 1; j++) {
      if (i == 0 && j == GRAPH_SIZE / 2) {
        printf("y");
      }else if (j == GRAPH_SIZE + 1 && i == (GRAPH_SIZE + 2) / 2) {
        printf("x");
      }else if (i == GRAPH_SIZE + 1 || j == GRAPH_SIZE + 1){
        printf(" ");
      }else if (i == 0) {
        printf(" ");
      }else {
        printf("%c",array[i - 1][j]);
      }
    }
    printf("\n");
  }
}

void draw(ShapeType type,char arrayOfPositions[GRAPH_SIZE][GRAPH_SIZE]) {
  int *parameters;
  ShapeType shape = LINE;
  switch (type) {
    case LINE:
      shape = LINE;
      break;
    case PARABOLA:
      shape = PARABOLA;
      break;
    default:
      shape = CIRCLE;
      break;
  }
  parameters = getRequiredParameters(shape);
  //Printing out parameters.
  printf("\n\n\nHere's your parameters: ");
  for (int i = 0; i < (type == LINE ? 2 : 3) ; i++) {
    printf("%d ",*(parameters + i));
  }
  printf("\n");
  //Here's where the magic starts.
  for (int i = 0; i <= GRAPH_SIZE; i++) {
    for (int j = 0; j <= GRAPH_SIZE; j++) {
      int xPosition = (j - (GRAPH_SIZE / 2));
      int formulaResult = 0;
      switch (type) {
        case LINE:
          formulaResult = ((*parameters) * xPosition) + *(parameters + 1);
          break;
        case PARABOLA:
          formulaResult = (*parameters) * (xPosition * xPosition) + (*(parameters + 1) * xPosition) + *(parameters + 2);
          break;
        case CIRCLE:
          formulaResult = *(parameters + 1) + sqrt((*(parameters + 2) * *(parameters + 2)) - ((xPosition - *(parameters)) * (xPosition - *(parameters))));
          break;
        default:
          break;
      }
      int yPosition = (GRAPH_SIZE + 1) - i;
      int points = (GRAPH_SIZE / 2) - formulaResult;
      if (i == points) {
        arrayOfPositions[i][j] = 'X';
      }
      else if (type == CIRCLE && i == (GRAPH_SIZE / 2) + formulaResult) {
        arrayOfPositions[i][j] = 'X';
      }
      else if (i == GRAPH_SIZE / 2) {
        arrayOfPositions[i][j] = '-';
      }
      else if (j == GRAPH_SIZE / 2) {
        arrayOfPositions[i][j] = '|';
      }
      else {
        arrayOfPositions[i][j] = ' ';
      }
    }
  }
}

/* returns array of parameters required for drawing according to type. */
int *getRequiredParameters(ShapeType type) {
  /* making local variable static since C does not advocate
  to return the address of the local variable. */
  static int parameters[3];
  int values[] = {0,0,0};
  char valueNames[] = {'a','b','c'};
  int parameterNumber = 0;
  switch (type) {
    case LINE:
      printf("Line Formula: y = ax + b\n");
      parameterNumber = 2;
      break;
    case PARABOLA:
      printf("Parabola Formula: y = ax^2 + bx + c\n");
      parameterNumber = 3;
      break;
    case CIRCLE:
      parameterNumber = 3;
      printf("Parabola Formula: (x-a)^2 + (x-b)^2 = c^2\n");
      break;
    default: break;
  }
  for (int i = 0; i < parameterNumber; i++) {
    printf("Your '%c' value: ",valueNames[i]);
    scanf("%d",&values[i]);
    parameters[i] = values[i];
  }
  return parameters;
}
