#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

typedef struct {
     int height;
     int width;
     char **grid;
 } map;

double randNum(int lower, int upper){
    int num;
    srand(time(NULL));
    num = (rand() % (upper - lower + 1)) + lower;

    return num;
}

map* make_game(int a, int b){
    map *newGame = malloc(sizeof(map));
    int i, j;

    newGame->height = a;
    newGame->width = b;

    newGame->grid = malloc(sizeof(char *) * newGame->height);
    for(i = 0; i < newGame->height; i++){
        newGame->grid[i] = malloc(sizeof(char) * newGame->width);
    }

    for(j = 0; j < newGame->height; j++){
        for(i = 0; i < newGame->width; i++){
            newGame->grid[j][i] = '0';
        }
    }
    return newGame;
}

map* fill_game(map* game, int formation){
    if(formation == 1){
        game->grid[0][6] = '#';
        game->grid[1][6] = '#';
        game->grid[2][2] = '#';
        game->grid[2][3] = '#';
        game->grid[2][4] = '#';
        game->grid[3][0] = '#';
        game->grid[4][0] = '#';
        game->grid[5][0] = '#';
        game->grid[6][0] = '#';
        game->grid[7][0] = '#';
        game->grid[7][3] = '#';
        game->grid[7][4] = '#';
        game->grid[7][5] = '#';
        game->grid[8][1] = '#';
        game->grid[8][2] = '#';
        game->grid[8][3] = '#';
        game->grid[8][4] = '#';
    } else if(formation == 2){
        game->grid[0][0] = '#';
        game->grid[1][0] = '#';
        game->grid[2][0] = '#';
        game->grid[3][0] = '#';
        game->grid[4][1] = '#';
        game->grid[5][1] = '#';
        game->grid[3][5] = '#';
        game->grid[3][6] = '#';
        game->grid[3][7] = '#';
        game->grid[3][8] = '#';
        game->grid[3][9] = '#';
        game->grid[5][6] = '#';
        game->grid[6][6] = '#';
        game->grid[9][3] = '#';
        game->grid[9][4] = '#';
        game->grid[9][5] = '#';
        game->grid[9][6] = '#';
    } else if (formation == 3){
        game->grid[0][0] = '#';
        game->grid[0][1] = '#';
        game->grid[0][2] = '#';
        game->grid[0][3] = '#';
        game->grid[6][1] = '#';
        game->grid[6][2] = '#';
        game->grid[4][3] = '#';
        game->grid[5][3] = '#';
        game->grid[6][3] = '#';
        game->grid[8][5] = '#';
        game->grid[8][6] = '#';
        game->grid[8][7] = '#';
        game->grid[5][8] = '#';
        game->grid[6][8] = '#';
        game->grid[7][8] = '#';
        game->grid[8][8] = '#';
        game->grid[9][8] = '#';
    }
    return game;
}

void print_grid(map* game){
    int i, j;
    printf("    1 2 3 4 5 6 7 8 9 10\n");
    printf("  -");
    for(i = 0; i < game->width+1; i++){
        printf(" -");
    }
    printf("\n");
    for(j = 0; j < game->height; j++){
        printf("%c |", j+65);
        for(i = 0; i < game->width; i++){
            printf(" %c", game->grid[j][i]);
        }
        printf(" |");
        printf("\n");
    }
    printf("  -");
    for(i = 0; i < game->width+1; i++){
        printf(" -");
    }
    printf("\n");
}

int isHit(int row, int col, map* game){
    if(game->grid[row-1][col-1] == '#'){
        return TRUE;
    } else {
        return FALSE;
    }
}

int gameover(map* game){
    int i, j;
    int flag = 0;

    for(j = 0; j < game->height; j++){
        for(i = 0; i < game->width; i++){
            if(game->grid[j][i] == '#'){
                //printf("Game not over.\n");
                flag++;
            }
        }
    }
    if(flag == 0){ //no more ships left
        return FALSE;
    } else {
        return TRUE; //more ships left
    }
}
void print_turn(map* playerShips, map* playerShots){
    printf("Your grid for selecting targets:\n");
    print_grid(playerShots);
    printf("Your ship grid:\n");
    print_grid(playerShips);
}

int player_turn(map* playerShips, map* playerShots, map* enemyShips){
    int flag1 = 0;

    while(flag1 == 0){
        printf("Please enter a co-ordinate to fire at.\n");
        int col = 0;
        char rowChar = ' ';
        int row = 0;
        scanf("%c %d", &rowChar, &col);
        if(rowChar == 'Q'){
            printf("Quiting Game, thank you for playing!\n");
            return -1;
        } else {
            if(col < 1 || col > 10){
                //printf("Invalid column: %d.\n", col);
                //printf("\n");
            } else if(!((rowChar < 75 && rowChar > 64) || (rowChar < 107 && rowChar > 96))){
                if(row != 10){
                    //printf("Invalid row: %d\n", row);
                    //printf("\n");
                }
            } else { //inputs are within the parameters
                //printf("within the parameters\n");
                if(rowChar < 107 && rowChar > 96){
                    rowChar = toupper(rowChar);
                }
                row = rowChar-64;
                //printf("%d %d \n", row, col);
                if((enemyShips->grid[row-1][col-1] == 'x') || (enemyShips->grid[row-1][col-1] == 'X')){
                    printf("You have already fired there.\n");
                } else {
                    if(isHit(row, col, enemyShips)){
                        //printf("HIT!\n");
                        enemyShips->grid[row-1][col-1] = 'X';
                        playerShots->grid[row-1][col-1] = 'X';
                        return TRUE;
                    } else {
                        //printf("MISS!\n");
                        playerShots->grid[row-1][col-1] = 'x';
                        return FALSE;
                    }
                    flag1++;
                }
            }
        }
    }
}

int enemy_turn(map* playerShips){
    int flag1 = 0;

    while(flag1 == 0){
        int row;
        int rand1 = randNum(0, 99);
        int col = randNum(0, 9);
        row = rand1 / 10;
        //printf("Enemy shot: %d, %d\n", row, col);
        if((playerShips->grid[row][col] != 'x') && (playerShips->grid[row][col] != 'X')){ //valid shot
            if(playerShips->grid[row][col] == '#'){
                //printf("ENEMY HIT YOU!\n");
                flag1++;
                playerShips->grid[row][col] = 'X';
                return TRUE;
            } else {
                //printf("ENEMY MISSED YOU!\n");
                flag1++;
                playerShips->grid[row][col] = 'x';
                return FALSE;
            }
        }
    }
}

void place_ships(map* playerShips){
    int heady;
    int taily;
    int temp;
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    int shipLength[5] = {5, 4, 3, 3, 2};
    char shipName[5][12] = {
                                {'C', 'A', 'R', 'R', 'I', 'E', 'R', '\0'},
                                {'B', 'A', 'T', 'T', 'L', 'E', 'S', 'H', 'I', 'P', '\0'},
                                {'C', 'R', 'U', 'I', 'S', 'E', 'R', '\0'},
                                {'S', 'U', 'B', 'M', 'A', 'R', 'I', 'N', 'E', '\0'},
                                {'D', 'E', 'S', 'T', 'R', 'O', 'Y', 'E', 'R', '\0'}
                            };
    int curShipL;
    int i;
    int tracker;

    printf("Enter the location for the head of your ship in the following format:\n");
    printf("headrow(A-J) headcolumn(1-10) tailrow(A-J) tailcolumn(1-10)\n");
    printf("To print your current ships, enter: 'PPPP'\n");
    for(i = 0; i <= 4; i++){
        tracker = 0;
        flag1 = 0;
        flag2 = 0;
        flag3 = 0;
        curShipL = shipLength[i];
        printf("Please place your %s (length of %d cells).\n", shipName[i], curShipL);
        while(flag1 == 0){
            char headrow;
            char tailrow;
            int headcol;
            int tailcol;
            scanf("%c %d %c %d", &headrow, &headcol, &tailrow, &tailcol);
            if(headrow == 'P'){
                if(flag3 == 0){
                    print_grid(playerShips);
                    flag3++;
                }
            } else {
                if((headcol < 1 || headcol > 10) || (tailcol < 1 || tailcol > 10)){
                    //printf("Invalid column.\n");
                    //printf("\n");
                } else if(!(((headrow < 75 && headrow > 64) || (headrow < 107 && headrow > 96)) && ((tailrow < 75 && tailrow > 64) || (tailrow < 107 && tailrow > 96)))){
                    if(headrow != 10){
                        //printf("Invalid row.\n");
                        //printf("\n");
                    }
                } else { //inputs are within the parameters
                    if(headrow < 107 && headrow > 96){
                        headrow = toupper(headrow);
                    }
                    if(tailrow < 107 && tailrow > 96){
                        tailrow = toupper(tailrow);
                    }
                    heady = headrow-64;
                    taily = tailrow-64;
                    //printf("head: %d %d tail: %d %d\n", heady, headcol, taily, tailcol);
                    if(heady == taily){ //horizontal
                        //check if length is right
                        if(headcol < tailcol){
                            if((tailcol - headcol) == (curShipL-1)){
                                //printf("Correct length.\n");
                                flag2++;
                            } else {
                                printf("Incorrect length of placement.\n");
                                flag2 = 0;
                            }
                        } else {
                            if((headcol - tailcol) == (curShipL-1)){
                                //printf("Correct length.\n");
                                flag2++;
                            } else {
                                printf("Incorrect length of placement.\n");
                                flag2 = 0;
                            }
                        }
                    } else if(headcol == tailcol){ //vertical
                        //check if length is right
                        if(heady < taily){
                            if((taily - heady) == (curShipL - 1)){
                                //printf("Correct length.\n");
                                flag2++;
                            } else {
                                printf("Incorrect length of placement.\n");
                                flag2 = 0;
                            }
                        } else {
                            if((heady - taily) == (curShipL - 1)){
                                //printf("Correct length.\n");
                                flag2++;
                            } else {
                                printf("Incorrect length of placement.\n");
                                flag2 = 0;
                            }
                        }
                    } else {
                        //invalid, loop it
                        printf("Incorrect length of placement.\n");
                        flag2 = 0;
                    }

                    if(flag2 != 0){
                        //only let it get to here if the length is right
                        if(heady == taily){ //horizontal
                            if(headcol < tailcol){ //head is first
                                for(temp = headcol; temp <= tailcol; temp++){
                                    if(playerShips->grid[heady-1][temp-1] != '0'){
                                        printf("Cell already taken.\n");
                                        break;
                                    } else {
                                        playerShips->grid[heady-1][temp-1] = '#';
                                        tracker++;
                                        if(tracker == curShipL){ //end of ship
                                            flag1++;
                                        }
                                    }
                                }
                            } else if(headcol > tailcol){ //tail is first
                                for(temp = tailcol; temp <= headcol; temp++){
                                    if(playerShips->grid[heady-1][temp-1] != '0'){
                                        printf("Cell already taken.\n");
                                        break;
                                    } else {
                                        playerShips->grid[heady-1][temp-1] = '#';
                                        tracker++;
                                        if(tracker == curShipL){ //end of ship
                                            flag1++;
                                        }
                                    }
                                }
                            } else if(headcol == tailcol){ //invalid
                                printf("Invalid ship placement.\n");
                            }
                        } else if(headcol == tailcol){ //vertical
                            if(heady < taily){ //head is on top
                                for(temp = heady; temp <= taily; temp++){
                                    if(playerShips->grid[temp-1][headcol-1] != '0'){
                                        printf("Cell already taken.\n");
                                        break;
                                    } else {
                                        playerShips->grid[temp-1][headcol-1] = '#';
                                        tracker++;
                                        if(tracker == curShipL){ //end of ship
                                            flag1++;
                                        }
                                    }
                                }
                            } else if(heady > taily){ //tail is on top
                                for(temp = taily; temp <= heady; temp++){
                                    if(playerShips->grid[temp-1][headcol-1] != '0'){
                                        printf("Cell already taken.\n");
                                        break;
                                    } else {
                                        playerShips->grid[temp-1][headcol-1] = '#';
                                        tracker++;
                                        if(tracker == curShipL){ //end of ship
                                            flag1++;
                                        }
                                    }
                                }
                            } else if(heady == taily){ //invalid
                                printf("Invalid ship placement.\n");
                            }
                        } else { //invalid
                            printf("Invalid ship placement.\n");
                        }
                    }
                }
            }
        }
    }
}

void free_map(map* game){
    int i;

    for(i = 0; i < game->height; i++){
        free(game->grid[i]);
    }
    free(game->grid);
    free(game);
}

int main (int argc, char *argv[]){
    int flag = 0;
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    int flag4 = 0;


    while(flag3 == 0){
        map *playerShips = make_game(10, 10);
        map *enemyShips = make_game(10, 10);
        map *playerShots = make_game(10, 10);
        //place enemy ships
        int shipFormation = randNum(1, 3);
        //printf("formation: %d\n", shipFormation);
        fill_game(enemyShips, shipFormation);

        printf("\n");
        printf("Welcome to Battleship! Written in C, using the GCC compiler.\n");
        printf("The game will start by asking you to place all of your ships, in the specified format.\n");
        printf("The game will then go back and forth between you and the AI, each taking shots at eachothers ships.\n");
        printf("The first person to destroy all parts of all opposing ships will be crowned the winner!\n");
        printf("\n");
        //place player ships
        place_ships(playerShips);

        print_turn(playerShips, playerShots);

        printf("\n");
        printf("If you wish to quit at any time, enter 'QQ'.\n");
        //begin game functions
        while(flag == 0){
            flag1 = 0;
            flag2 = 0;
            flag1 = player_turn(playerShips, playerShots, enemyShips);
            if(flag1 == -1){
                flag++;
            } else {
                if(!(gameover(enemyShips))){
                    flag++;
                    printf("YOU WIN!\n");
                    printf("You have destroyed all enemy ships!\n");
                    break;
                }
                flag2 = enemy_turn(playerShips);
                if(!(gameover(playerShips))){
                    flag++;
                    printf("YOU LOSE!\n");
                    printf("All of your ships have been destroyed!\n");
                    break;
                }
                print_turn(playerShips, playerShots);
                if(flag1 != 0){
                    printf("YOU HIT THE ENEMY!\n");
                } else {
                    printf("YOU MISSED THE ENEMY!\n");
                }
                if(flag2 != 0){
                    printf("THE ENEMY HIT YOU!\n");
                } else {
                    printf("THE ENEMY MISSED YOU!\n");
                }
            }
        }
        char in;
        printf("Do you want to play again(Y/N)?\n");
        while(flag4 == 0){
            scanf("%c", &in);
            if(in == 'N'){
                printf("Thank you for playing!\n");
                free_map(playerShips);
                free_map(playerShots);
                free_map(enemyShips);
                flag3++;
                flag4++;
            } else if(in == 'Y'){
                printf("Let's play again!\n");
                free_map(playerShips);
                free_map(playerShots);
                free_map(enemyShips);
                flag4++;
                flag = 0;
            }
        }
    }

    return 0;
}
