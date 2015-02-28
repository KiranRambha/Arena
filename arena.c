#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10 //Total of 10 rows in the arena
#define COLS 20 //Total of 20 columns in the arena 

/**
 * Author: Kiran Rambha
 */
char arena[ROWS][COLS];
char tresure = '#'; //Variable to store the tresure character
char player = '@'; //Variable to store the player character 
char monster = 'M'; //Variable to store the monster character
FILE *file; //The file variable.
int play = 1; //Variable to keep the game running until an change is observed.

/**
 * Initializing the arena and arena's borders.
 */
void initializeArena() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1) {
				arena[i][j] = '0';
			} else {
				arena[i][j] = '.';
			}
		}
	}
}

/**
 * Printing the state of the game onto the screen.
 */
void printArena() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			putchar(arena[i][j]);
			putchar(' ');
		}
		printf("\n");
	}
}

/**
 * Structure of a Node for linked list
 * type: stores the type of character in the game.
 * row: stores the row number occupied by the character.
 * column: stores the column occupied by the character.
 * next: a pointer to the next node.
 */
struct node {
	char type; //stores the type of character in the game
	unsigned row; //x-Axis
	unsigned column; //y-Axis
	struct node *next; //The head of the linked list
};

/**
 * Creates the List of objects and the places where they need to be added.
 * This method takes a list of nodes and then creates a new node and sets it as the 
 * head of this list and returns it.
 */
struct node *addObject(struct node *head, unsigned row, unsigned column, char type) {
	struct node *curr = NULL;
	curr = malloc(sizeof(*curr));
	curr -> row = row;
	curr -> column = column;
	curr -> type = type;
	curr -> next = head;
	head = curr;
	return head;
}

/**
 * Monster top and left movement stimulator.
 * loops through the arena and detects the monsters and moves them in
 * the randomly selected top or left direction.
 */
 int monsterTopAndLeftMovement(int xaxis ,int yaxis) {
 	int xAxis = xaxis;
 	int yAxis = yaxis;
 	int direction = rand() % 2;
 	int stepper = 4; 
 	if (direction == 0) {
 		if (xAxis > 1) {
 			if (arena[xAxis - 1][yAxis] != monster && arena[xAxis - 1][yAxis] != tresure) {
 				if (arena[xAxis - 1][yAxis] == player) {
 					arena[xAxis - 1][yAxis] = monster;
 					arena[xAxis][yAxis] = '.';
 					play = 0;
 				} else {
 					arena[xAxis - 1][yAxis] = monster;
 					arena[xAxis][yAxis] = '.';
 				}
 				stepper = 0;
 			}
 		}
 	} else {
 		if (yAxis > 1) {
 			if (arena[xAxis][yAxis - 1] != monster && arena[xAxis][yAxis - 1] != tresure) {
 				if (arena[xAxis][yAxis - 1] == player) {
 					arena[xAxis][yAxis - 1] = monster;
 					arena[xAxis][yAxis] = '.';
 					play = 0;
 				} else {
 					arena[xAxis][yAxis - 1] = monster;
 					arena[xAxis][yAxis] = '.';
 				}
 				stepper = 1;
 			}
 		}
 	}
 	return stepper;
 }

 /**
 * Monster top and left movement stimulator.
 * loops through the arena and detects the monsters and moves them in
 * the randomly selected bottom or right direction.
 */
int monsterBottomAndRightMovement(int xaxis ,int yaxis) {
 	int xAxis = xaxis;
 	int yAxis = yaxis;
 	int stepper = 4;
 	int direction = rand() % 2;
 	if (direction == 0) {
 		if (xAxis < ROWS - 2) {
 			if (arena[xAxis + 1][yAxis] != monster && arena[xAxis + 1][yAxis] != tresure) {
 				if (arena[xAxis + 1][yAxis] == player) {
 					arena[xAxis + 1][yAxis] = monster;
 					arena[xAxis][yAxis] = '.';
 					play = 0;
 				} else {
  					arena[xAxis + 1][yAxis] = monster;
 					arena[xAxis][yAxis] = '.';
 				}
 				stepper = 2;
 			}
 		}
 	} else {
 		if (yAxis < COLS - 2) {
 			if (arena[xAxis][yAxis + 1] != monster && arena[xAxis][yAxis + 1] != tresure) {
 				if (arena[xAxis][yAxis + 1] == player) {
	 				arena[xAxis][yAxis + 1] = monster;
 					arena[xAxis][yAxis] = '.';
 					play = 0; 					
 				} else {
 					arena[xAxis][yAxis + 1] = monster;
 					arena[xAxis][yAxis] = '.';
 				}
 				stepper = 3;
 			}
 		}
 	}
 	return stepper;
 }

/**
 * Returns the row number of the player.
 */
int getPlayerRowPosition() {
	int playerRowValue = 0;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (arena[i][j] == player) {
				playerRowValue = i;
			}
		}
	}
	return playerRowValue;
}

/**
 * Returns the column number of the player.
 */
int getPlayerColumnPosition() {
	int playerColumnValue = 0;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (arena[i][j] == player) {
				playerColumnValue = j;
			}
		}
	}
	return playerColumnValue;
}

/**
 * Random row generator for the position of new characters in the arena.
 */
 int rowGenerator() {
 	srand(time(NULL));
 	int rowNumber = rand() % 8;
 	rowNumber++;
 	return rowNumber;
 }

/**
 * Random column generator for the position of the new characters in the arena.
 */
 int columnGenerator() {
 	srand(time(NULL));
 	int columnNumber = rand() % 18;
 	columnNumber++;
 	return columnNumber;
 }

 /**
 * Method used to iterate through the list and insert it into the arena at the particular position.
 */
void iterList(struct node *curr) {
	initializeArena();
	struct node *iter = curr;
	while (iter != NULL) {
		arena[iter -> row][iter -> column] = iter -> type;
		iter = iter -> next;
	}
}

/**
 * This method updates the list with the position of the the player in the array
 * so that the data matches the values in the list after player movement.
 */
void updateList(struct node *curr) {
	struct node *list = curr;
	while (list != NULL) {
		if (list -> type == player) {
			list -> row = getPlayerRowPosition();
			list -> column = getPlayerColumnPosition();
		}
		list = list -> next;
	}
}

/**
 * Deletes all the nodes in the list and free's the memory recursively.
 */
void deletelist(struct node *n)
{
	if(n != NULL)
	{
		deletelist(n -> next);
	}
	free(n);
}

/**
 * This method is called everytime a move is made 
 * This method updates the list 
 * takes the list old positions and the direction of the movement and then loops through the list 
 * and if the current node is a player then updates its position and goes to the next position and if 
 * that has a monster then according to the direction it checks if the move posible or not and then moves
 * according to the direction given.
 */
 void replacingIterList(struct node *curr, int oldMonsterPositionX, int oldMonsterPositionY, int moveDirection) {
 	struct node *replacingiter = curr;
 	int MonsterX = oldMonsterPositionX;
 	int MonsterY = oldMonsterPositionY;
 	int step = moveDirection;
 	while (replacingiter != NULL) {
 		if (replacingiter -> type == player) {
 			replacingiter -> row = getPlayerRowPosition();
 			replacingiter -> column = getPlayerColumnPosition();
 		} else if (replacingiter -> type == monster) {
 			if (replacingiter -> row == MonsterX && replacingiter -> column == MonsterY) {
 				if (step == 0) {
 					replacingiter -> row = MonsterX - 1;
 					replacingiter -> column = MonsterY;
 				} else if (step == 1) {
 					replacingiter -> row = MonsterX;
 					replacingiter -> column = MonsterY - 1;
 				} else if (step == 2) {
 					replacingiter -> row = MonsterX + 1;
 					replacingiter -> column = MonsterY;
 				} else if (step == 3) {
 					replacingiter -> row = MonsterX;
 					replacingiter -> column = MonsterY + 1;
 				}
 			}
 		}
 		replacingiter = replacingiter -> next;
 	}
 }

/**
 * Loops through the arena to check if there is any tressure in the arena or not.
 */
int hasTressure() {
	int tressureVal = 0;
	for (int x = 0; x < ROWS; x++) {
		for (int y = 0; y < COLS; y++) {
			if (arena[x][y] == tresure) {
				tressureVal = 1;
			}
		}
	}
	return tressureVal;
}

/**
 * Method is used to move the player to a particular position.
 * This method takes the old row position and column positions and the new row and column positions and moves the player to the
 * new position and resets the values of the old position. 
 * After the movement the movement of the monsters take place by choosing the random directions in which they need to move.
 */
void movePlayer(unsigned oldRow, unsigned oldColumn, unsigned row, unsigned column, struct node *list) {
	srand(time(NULL));
	int monsterMovementSelector = rand() % 10; //Direction in which the monsters should move.
	struct node *curr = list;
	arena[oldRow][oldColumn] = '.'; //The old position of the player is set to default.
	int stepper = 4; //An integer to select the directioin in which the monsters should move.

	//if the new position of the player already has a monster then remove the player from the grid and end the game.
	if(arena[row][column] == monster) {
		play = 0;
		while (curr != NULL) {
			if (curr -> type == player) {
				curr -> type = monster;
				curr -> row = row;
				curr -> column = column;
				break;
			} else {
				curr = curr -> next;
			}
		}
	} 
	//else perform the following methods.
	else {
		/*
		 * If the position to which the player is moving has a tressure then
		 * loop through list until it finds the tresure at that particular position
		 * and replaces it with the player.
		 */
		if (arena[row][column] == tresure) {
			while (curr != NULL) {
				if (curr -> row == row && curr -> column == column) {
					curr -> type = player;
				}
				curr = curr -> next;
			}
		}
		arena[row][column] = player; //Moves the player to the new row and column.
		int tressureValue = hasTressure(); //Checking if there is any tressure left in the arena.
		//If the random number generated is less than or equal to 4 then perform these methods.
		if (monsterMovementSelector <= 4) {
			for (int m = 1; m < ROWS - 1; m++) {
				for (int n = 1; n < COLS - 1; n++) {
					if (arena[m][n] == monster) {
						stepper = monsterTopAndLeftMovement(m, n);
						replacingIterList(curr, m, n, stepper);
					}
				}
			}
		} 
		//If the random number generated is more than 4 then perform these methods.
		else if (monsterMovementSelector > 4) {
			for (int a = ROWS - 2; a > 0; a--) {
				for (int b = COLS - 2; b > 0; b--) {
					if (arena[a][b] == monster) {
						stepper = monsterBottomAndRightMovement(a, b);
						replacingIterList(curr, a, b, stepper);
					}
				}
			}
		}
		//If the number of tresures in the arena is 0 then player has won.
		if (tressureValue == 0) {
			play = 2;
		}
	}
}

/**
 * Getting the input from the user and making the move.
 */
struct node *makeMove(struct node *list) {
	char move = 'q'; //Variable to store the move of the player.
	char string[10], filedata[10];
	char *s;

	//This data is used in the loading file function: num1 - storing the row position, num2 - storing the column position and 
	//swap - when num1 and num2 are known telling the computer to create a node.
	int num1 = 0, num2 = 0, swap = 0; 
	int playerRowPosition = getPlayerRowPosition(); //Storing the player row position.
	int playerColumnPosition = getPlayerColumnPosition(); //Storing the player column position.
	srand(time(NULL));
	int randomTypeGenerator = rand() % 8;
	struct node *curr = list;
	scanf("%c", &move);
	//Player right movement.
	if(move == 'd') { 
		if (playerColumnPosition + 1 < COLS - 1) {
			playerColumnPosition++;
			movePlayer(playerRowPosition, playerColumnPosition - 1, playerRowPosition, playerColumnPosition, curr);
		}
	} 
	//Player up movement.
	else if (move == 'w') {
		if (playerRowPosition - 1 > 0) {
			playerRowPosition--;
			movePlayer(playerRowPosition + 1, playerColumnPosition, playerRowPosition, playerColumnPosition, curr);
		}
	} 
	//Player left movement.
	else if (move == 'a') {
		if (playerColumnPosition - 1 > 0) {
			playerColumnPosition--;
			movePlayer(playerRowPosition, playerColumnPosition + 1, playerRowPosition, playerColumnPosition, curr);
		}
	} 
	//Player down movement.
	else if (move == 's') {
		if (playerRowPosition + 1 < ROWS - 1) {
			playerRowPosition++;
			movePlayer(playerRowPosition - 1, playerColumnPosition, playerRowPosition, playerColumnPosition, curr);
		}
	} 
	//Producing a random character in the arena, only 1 in 8 times produces a treasure.
	else if (move == 't') {
		int loop = 1; //Loops until a character produced into the arena.
		while (loop == 1) {
			int randomRowGenerator = rowGenerator(); //Selecting a random row.
			int randomColumnGenerator = columnGenerator(); //Selecting a random column.
			//If the selected random position is not a monster and is not a player and is not a treasure then insert a random character at that position.
			if (arena[randomRowGenerator][randomColumnGenerator] != monster 
				&& arena[randomRowGenerator][randomColumnGenerator] != player 
				&& arena[randomRowGenerator][randomColumnGenerator] != tresure) {
				//Adding a monster at the selected position.
				if (randomTypeGenerator < 7) {
					curr = addObject(curr, randomRowGenerator, randomColumnGenerator, monster);
					break;
				} 
				//Adding a treasure at the selected position.
				else if (randomTypeGenerator == 7) {
					curr = addObject(curr, randomRowGenerator, randomColumnGenerator, tresure);
					break;
				}
				loop = 0;
			}
		}
	} 
	//Saving the data on the arena to a file called arena.sav.
	else if (move == 'k') {
		file = fopen("arena.sav", "w+");
		printf("Saving Your Game!\n"); 
		fprintf(file, "%d\n", ROWS); //Writing the number of rows to the file.
		fprintf(file, "%d\n", COLS); //Writing the number of columns to the file.
		//Loop through the list and write the data of the list to the file.
		while (curr != NULL) {
			sprintf(string, "%d %d %c", curr -> row, curr -> column, curr -> type);
			fprintf(file, "%s\n", string);
			curr = curr -> next;
		}
		fclose(file);
		printf("Game Saved!\n");
		curr = list;
	} 
	//Loading the data from the file
	else if (move == 'l') {
		//Load the data from the file.
		file = fopen("arena.sav", "r");
		printf("Trying to load the Game!\n");
		int count = 0;
		int arenaSize = 1; //This is used to check if the file has the correct values of the width and height of the arena.
		int loop = 0;
		deletelist(curr); //Clearing the list before loading the file to the list.
		initializeArena(); //Clearing the arena.
		curr = NULL;
		//Reading till the end of the file.
	    while (fscanf(file, "%s", string) != EOF) {
	    	/**
	    	 * Reading twice from the file to check if the width and height of the arena match.
	    	 * If it matches then it continues to read the file else it breaks the loop and ends the game.
	    	 */
	    	if (loop < 2) {
	    		if (strtol(string, &s, 10) != 0) {
	    			int arenaSize = strtol(string, &s, 10);
	    			if (loop == 0) {
	    				if (arenaSize == ROWS) {
		    				loop++;
		    			} else {
		    				printf("Load error! Check the file.\n");
		    				break;
		    			}
	    			} else if (loop == 1) {
	    				if (arenaSize == COLS) {
	    					loop++;
	    				} else {
	    					printf("Load error! Check the file.\n");
	    					break;
	    				}
	    			}
	    		}
	    	} 
	    	/**
	    	 * If the values of the size of the arena are valid then it starts reading the characters and its position in the arena from the file.
	    	 * It reads three times from the file before creating the node in the list with that read data.
	    	 */
	    	else if (loop >= 2) {
	    		//Reading the row and column values of the character from the file and convert the string to int.
	    		if (strtol(string, &s, 10) != 0) {
		    		if (swap == 0) {
			    			num1 = strtol(string, &s, 10);
			    			swap = 1;
			    		} else if (swap == 1) {
			    			num2 = strtol(string, &s, 10);
			    			swap = 0;
			    		}
			    		count++;
		    	} else {
		    		count++;
		    	}
		    	//After reading three times we create the node in the list.
		    	if (count == 3) {
		    		curr = addObject(curr, num1, num2, string[0]);
		    		count = 0;
		    	}
	    	}
	    }
	    fclose(file); //After the reading is complete the file is closed.
	    printf("Game Loaded!\n");
	    iterList(curr); //loading the list to the arena.
	}
	return curr;
}

//Main class
int main() {
	initializeArena(); //Initialising the arena.
	printArena(); //Printing the arena.
	printf("Initializing ...\n");
	struct node *curr = NULL; //Creating a node for the link list which stores all the character for the arena.
	srand(time(NULL));
	int xposition = (rand() % (ROWS - 2)); //Random x position for the player.
	int yposition = (rand() % (COLS - 2)); //Random y position for the player.
	int xTresurePosition = (rand() % (ROWS - 2)); //Random x position for the treasure. 
	int yTresurePosition = (rand() % (COLS - 2)); //Random y position for the treasure.
	int xMonsterPosition = (rand() % (ROWS - 2)); //Random x position for the monster.
	int yMonsterPosition = (rand() % (COLS - 2)); //Random y position for the mosnter.
	curr = addObject(curr, xposition + 1, yposition + 1, player);
	curr = addObject(curr, xTresurePosition + 1, yTresurePosition + 1, tresure);
	curr = addObject(curr, xMonsterPosition + 1, yMonsterPosition + 1, monster);
	iterList(curr);
	printArena();
	while(play == 1) {
		curr = makeMove(curr);
		updateList(curr);
		iterList(curr);
		printArena();
	}
	if (play == 0) {
		printf("You Lost!\n");
		deletelist(curr);
	} else if (play == 2) {
		printf("You Won!\n");
		deletelist(curr);
	}
}
