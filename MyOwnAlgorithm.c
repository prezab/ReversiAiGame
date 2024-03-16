/**
 * @file reversi.c
 * @author <-- Your name here-->
 * @brief This file is used for APS105 Lab 8. 2023W version
 * @date 2023-03-14
 * 
 */

// DO NOT REMOVE THE FOLLOWING LINE
#if !defined(TESTER_P1) && !defined(TESTER_P2)
// DO NOT REMOVE THE ABOVE LINE
#include "reversi.h"
// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE

void printBoard(char board[][26], int n) {
    printf("  ");
    for (int col = 0; col < n; col++) {
            printf("%c", 'a'+ col);
        }
    printf("\n");
    
    for (int row = 0; row < n; row++) {
        printf("%c ", 'a' + row);
        
        for (int col = 0; col < n; col++) {
            printf("%c", board[row][col]);
        }
        printf("\n");
    }
}

bool positionInBounds(int n, int row, int col) {
    if (row >= n || col >= n ||row < 0 ||col < 0){
            return false;
    }
    else{
        return true;
    }
}

bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
    if(board[row][col] != 'U'|| board[row][col] == colour){
        return false;
    }
    if (deltaRow == 0 && deltaCol == 0){
        return false;
    }
    char checker = NULL;
    bool opps = false;
    do{
        row += deltaRow; 
        col += deltaCol;
        if (!positionInBounds(n,row,col)){
            return false;
        }
        checker = board[row][col];
        if (checker != 'U' && checker != 'W' && checker != 'B'){
            return false;
        }
        if (checker != 'U' && checker != colour){
            opps = true;
        }
        else if (checker == colour && opps == true){
            return true;
        }
        else{
            return false;
        }
    }
    while(positionInBounds(n,row,col));

}

int changecolour(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
    if(board[row][col] != 'U'){
        return false;
    }
    if (deltaRow == 0 && deltaCol == 0){
        return false;
    }
    char checker = NULL;
    do{
        row += deltaRow; 
        col += deltaCol;
        if (!positionInBounds(n,row,col)){
            return 0;
        }
        checker = board[row][col];
        if (checker != 'U' && checker != colour){
            board[row][col] = colour;
        }
        else{
            return 0;
        }
    }
    while(positionInBounds(n,row,col));

}

bool cango(char board[][26], int n, char colour){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            for(int a = -1; a <= 1; a++){
                for (int b = -1; b <= 1; b++){
                    if (checkLegalInDirection(board, n, i, j, colour, a, b)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void copyboard(char copiedboard[][26], char originalboard[][26]) {
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            copiedboard[i][j] = originalboard[i][j];
        }
    }
}

bool legalmove(char board[][26], int n, int i, int j, char color) {
    if (board[i][j] != 'U') {
        return false; 
    }
    else{
        for (int a = -1; a <= 1; a++) {
            for (int b = -1; b <= 1; b++) {
                if (checkLegalInDirection(board, n, i, j, color, a, b)) {
                    return true; 
                }
            }
        }
    }
    return false; 
}

int boardscore(char board[][26], char compcolour, int n){
    int score = 0;
    int boardvalues[][26] = {
    {95, -20,  20,   5,   5,  20, -20, 95},
    {-20, -50,  -2,  -2,  -2,  -2, -50, -20},
    { 20,  -1,   1,   1,   1,   1,  -1,  20},
    {  7,  -1,   1,   1,   1,   1,  -1,   7},
    {  7,  -1,   1,   1,   1,   1,  -1,   7},
    { 20,  -1,   1,   1,   1,   1,  -1,  20},
    {-20, -50,  -2,  -2,  -2,  -2, -50, -20},
    {95, -20,  20,   5,   5,  20, -20, 95}
    };

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            for(int a = -1; a <= 1; a++){
                for (int b = -1; b <= 1; b++){
                    if (checkLegalInDirection(board, n, i, j, compcolour, a, b)){
                            score += 10;
                        }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (n == 8){
                if (board[i][j] == compcolour) {
                    score += boardvalues[i][j];
                }
                else if (board[i][j] != compcolour && board[i][j] != 'U'){
                    score -= boardvalues[i][j]+10;
                }

            }
            else{
            if (board[i][j] == compcolour) {
                score += 10;
                if ((i == 0 && j ==0 )|| (i == n-1 && j == 0) || (i == 0 && j == n-1) || (i == n-1 && j == 0)) {
                    score += 95;
                }
                else if ((i == 1 && j == n-2) || (i == 1 && j == 1) || (i == n-2 && j == 1) || (i == n-2 && j == n-2)) {
                    score -= 50;
                }
            }
            else if (board[i][j] != compcolour && board[i][j] != 'U') {
                if ((i == 0 && j ==0 )|| (i == n-1 && j == 0) || (i == 0 && j == n-1) || (i == n-1 && j == 0)) {
                    score -= 95;
                }
                else if ((i == 1 && j == n-2) || (i == 1 && j == 1) || (i == n-2 && j == 1) || (i == n-2 && j == n-2)) {
                    score += 50;
                }
            }
            if(n>4){
                if (board[i][j] == compcolour) {
                    if ((i == 0 || i == n-1) && (j == 2 || j == n-3)) {
                        score += 20;
                    }
                }
                }
            }
        }
    }

    return score;
}

int getcomputerscore(char board[][26], int n, int row, int col, char compcolour, char playercolour, int depth) {
    char newboard[26][26];
    copyboard(newboard, board);
    bool cango = false;
    
    for (int a = -1; a <= 1; a++) {
        for (int b = -1; b <= 1; b++) {
            if (checkLegalInDirection(newboard, n, row, col, compcolour, a, b)) {
                changecolour(newboard, n, row, col, compcolour, a, b);
                cango = true;
            }
        }
    } 
    if (depth == 0) {
        return boardscore(newboard, compcolour, n);
    }
    if (!cango) {
        return -getcomputerscore(board, n, row, col, playercolour, compcolour, depth);
    }
    
    int bestscore = -1000000;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (legalmove(newboard, n, i, j, playercolour)) {
                int playerscore = -getcomputerscore(newboard, n, i, j, playercolour, compcolour, depth-1);
                if (playerscore >= bestscore) {
                    bestscore = playerscore;
                }
            }
        }
    }
    return bestscore;
}

char getopponent(char compcolour){
    if (compcolour == 'W'){
        return 'B';
    }
    else if (compcolour == 'B'){
        return 'W';
    }
}

int makeMove(char board[26][26], int n, char turn, int *row, int *col){
    int finalrow = 0;
    int finalcol = 0;
    int computermovescore = 0;
    int computermovefinalscore = -100000000;
    int computerscore = 0;
    bool cancheck = false;
    char opp = getopponent(turn);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (legalmove(board, n, i, j, turn)){
                cancheck = true;
                computermovescore += getcomputerscore(board, n, i, j, turn,opp,3);
            }
            if (computermovescore > computermovefinalscore && cancheck){
                computermovefinalscore = computermovescore;
                finalrow = i;
                finalcol = j;
                cancheck = false;
            }

        }
    }
    
    *row = finalrow;
    *col = finalcol;

    return 0;
}





//*******************************************************
// Note: Please only put your main function below
// DO NOT REMOVE THE FOLLOWING LINE
#ifndef TESTER_P2
// DO NOT REMOVE THE ABOVE LINE

int main(void) {
    char reversiboard[26][26];
    int boarddim = 0;
    printf("Enter the board dimension: ");
    scanf("%d", &boarddim);
    for (int i = 0; i < boarddim; i++){
        for (int j = 0; j < boarddim; j++){
            if ((i == (boarddim/2 -1) && j == (boarddim/2-1)) || (i == (boarddim/2) && j == (boarddim/2))){
                reversiboard [i][j] = 'W';
            }
            else if ((i == (boarddim/2-1) && j == (boarddim/2)) || (i == (boarddim/2) && j == (boarddim/2-1))){
                reversiboard [i][j] = 'B';
            }
            else{
                reversiboard [i][j] = 'U';
            }
        }
    }
    printf("Computer plays (B/W): ");
    char computercolour;
    char playercolour;
    bool playerturn;
    scanf(" %c", &computercolour);

    if (computercolour == 'B'){
        playerturn = false;
        playercolour = 'W';
    }
    else if (computercolour == 'W'){
        playerturn = true;
        playercolour = 'B';
    }
    else{
        return 0;
    }
    printBoard(reversiboard,boarddim);
    
    char playermove[2];
    bool playermovevalid = false;
    bool game = true;
    char computermove[2];
    int playerscore = 0;
    int computerscore = 0;
    bool cancheck = false;
    int comprow = 0;
    int compcol = 0;


    while (game){
        if (playerturn && cango(reversiboard,boarddim,playercolour)){
                printf("Enter move for colour %c (RowCol): ", playercolour);
                scanf("%s", playermove);
                for(int a = -1; a <= 1; a++){
                    for (int b = -1; b <= 1; b++){
                        if (checkLegalInDirection(reversiboard, boarddim, playermove[0] - 'a', playermove[1] - 'a', playercolour, a, b)){
                            playermovevalid = true;
                            changecolour(reversiboard, boarddim, playermove[0] - 'a', playermove[1] - 'a', playercolour, a, b);
                            playerscore++;
                        }
                    }
                }

                if (playermovevalid){
                    reversiboard[playermove[0] - 'a'][playermove[1]- 'a'] = playercolour;
                    playerscore++;
                }
                else {
                    printf("Invalid move.\n");
                    printf("%c player wins.", computercolour);
                    return 0;
                    game = false;
                }
                printBoard(reversiboard,boarddim);
                playermovevalid = false;
                playerturn = false;
        }
        else if(!playerturn && cango(reversiboard,boarddim,computercolour)){
            makeMove(reversiboard,boarddim,computercolour,&comprow,&compcol);

            computermove[0] = 'a' + comprow;
            computermove[1] = 'a' + compcol;

            for(int a = -1; a <= 1; a++){
                for (int b = -1; b <= 1; b++){
                    if (checkLegalInDirection(reversiboard, boarddim, computermove[0] - 'a', computermove[1] - 'a', computercolour, a, b)){
                        changecolour(reversiboard, boarddim, computermove[0] - 'a', computermove[1] - 'a', computercolour, a, b);
                        computerscore++;
                    }
                }
            }
            printf("Computer places %c at %c%c.", computercolour, computermove[0], computermove[1]);
            reversiboard[computermove[0] - 'a'][computermove[1]- 'a'] = computercolour;
            computerscore++;
            printf("\n");
            printBoard(reversiboard,boarddim);
            playerturn = true;
            cancheck = false;
        }
        else{
            if (!cango(reversiboard,boarddim,playercolour) && !cango(reversiboard,boarddim,computercolour)){
                game = false;
            }
            else if (!cango(reversiboard,boarddim,playercolour) && playerturn){
                printf("%c player has no valid move.\n", playercolour);
                playerturn = false;
            }
            else if (!cango(reversiboard,boarddim,computercolour) && !playerturn){
                printf("%c player has no valid move.\n", computercolour);
                playerturn = true;
            }
            else{
                game = false;
            }
        }
    
    }
    if (playerscore > computerscore){
        printf("%c player wins.", playercolour);
    }
    else if(playerscore == computerscore){
        printf("Draw!");
    }
    else{
        printf("%c player wins.", computercolour);
    }




    

    return 0;
}

// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE
//*******************************************************
