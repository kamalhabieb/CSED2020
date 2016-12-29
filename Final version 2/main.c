#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/**
Header files
**/

#include "minesweeper_gameplay.h"
#include "minesweeper_opencell.h"
#include "minesweeper_leaderboard.h"
#include "minesweeper_save_load.h"
#include "minesweeper_newgame.h"

/**added functions for leader board*/
void set_board (char board[][10]);
void get_and_compare (char board[][10],int score [],int playerScore);
void read_board (char board[][10],char name[] , int score [],int playerScore);
void print_board (char board [][10],int score[]);
void load_board (char loadNames[10][10], int loadScore[10]);
void save_board (char board[][10],char score []);
void read_name (char name[]);
void clear_row (char board[][10],int i);

/**save and load*/
void load_game (void);
void save_game (int row,int col,int openFirst,int movesNum,int flagsNum,int qMarksNum,long long startGame , char A[][col],int B[][col]);


void game_play(int row,int col,int openFirst,int movesNum,int flagsNum,int qMarksNum,char A[][col],int B[][col],time_t loadTime,time_t firstTime);
time_t calc_time (time_t loadTime,time_t start);
void print_grid(int row ,int col ,char A[][col],int B[][col]);
void set_B (int row , int col , int B[][col]);
void set_A (int row , int col , char A[][col]);
int open_cell(int row , int col ,char A[][col],int B[][col],int x,int y,int* opebFirst);
int countXs (int i,int j,int row,int col ,char A[][col]);
void random_num (int row,int col,char A[][col],int B[][col],int *mines,int x,int y);
void mine_dis (int row,int col,int B[][col],int *mines);
int open_adj_cells(int row,int col,char A[][col],int B[][col],int x,int y,int openFirst);
int flag_cell(int row,int col,char A[][col],int x,int y);
int q_markCell(int row,int col,char A[][col],int x,int y);
int remove_flag(int row,int col,char A[][col],int x,int y);
int removeq_mark(int row,int col,char A[][col],int x,int y);
void count_mines (int i,int j,int row,int col ,int B[][col]);
int count_flags(int row,int col,char A[][col],int x,int y);
void new_game(void);
void open_all_lose(int row,int col,char A[][col],int B[][col],int x,int y);
void open_all_win(int row ,int col ,char A[][col],int B[][col],int x,int y);
int count_open(int row,int col,char A[][col]);
void find_mine(int row,int col,char A[][col],int B[][col],int x,int y);

int main()
{
    system("MODE 1000,1000");

    system("color 3F");

    int x,scan;
    char c;
    scan = 3; // initializing scan
    char board [10][10] ;
    int score [10] = {0};
    set_board (board);
    printf("\n\n\n\n\n\n\n");
    printf("\n\n\t\t\t\t\t\t************************************\n\t\t\t\t\t\t*\t\t\t\t   *\n\t\t\t\t\t\t*\t\t\t\t   *");
    printf("\n\t\t\t\t\t\t** Hello,Welcome To MINE SWEEPER! **\n\t\t\t\t\t\t*\t\t\t\t   *\n\t\t\t\t\t\t*\t\t\t\t   *");
    printf("\n\t\t\t\t\t\t************************************\n");
    printf("\n\n\n\n\t\t\t\t\t\t  1-Start a New Game\n\n\n\n\n\t\t\t\t\t\t  2-Load a previous Game\n\n\n\n\n\t\t\t\t\t\t  3-View LeaderBoard\n\n\n\n\n\t\t\t\t\t\t  4-Exit\n\n");
    do{
        if (scan != 3){
            system("cls");
            printf("\n\n\n\n\n\n\n");
            printf("\n\t\t\t\t\t\t  Invalid input \n\n");
            printf("\n\n\n\n\n\t\t\t\t\t\t  1-Start a New Game\n\n\n\n\n\t\t\t\t\t\t  2-Load a previous Game\n\n\n\n\n\t\t\t\t\t\t  3-View LeaderBoard\n\n\n\n\n\t\t\t\t\t\t  4-Exit\n\n");
            }
    scan = scanf("%d%c",&x,&c);
    fflush(stdin);
    if(c=='\n'){
        scan--;
    }
    }
    while(x<=0 || x>4 || scan!=1);
    switch(x)
    {
        case 1: system("cls");
                new_game();
                break;
        case 2: system("cls");
                load_game();
                break;
        case 3: system("cls");

                printf("\n\n\t\t\t\t\t\t**************");
                printf("\n\t\t\t\t\t\t*LEADER BOARD*\n");
                printf("\t\t\t\t\t\t**************\n\n");
                load_board (board,score);
                print_board (board,score);

                printf("\n\n\n\t TO RETURN TO MAIN MENU ENTER (0)\n\n\n\t TO EXIT ENTER (1)\n\n");
                int switchState = 0;
                int scan = 5; // initial value (meaningless value)
                int switchFlag = 0;
                char dummy; // preventing bugs
                do{
                    do{
                        scan = scanf("%d%c",&switchState,&dummy);
                        fflush(stdin);
                    }while(!(dummy == '\n' && scan == 2));

                    switch (switchState)
                    {
                        case 0  : switchFlag = 1;
                                main();
                                break;
                        case 1  : switchFlag = 1;
                                return;
                                break;
                        default : printf("\t\tCHOOSE A STATE FROM ABOVE\n\n");
                                break;
                    }
                }while(switchFlag == 0);

                break;

        case 4: break; // Option for user to exit the game
    }

    printf("\n");

    return 0;
}


int flag_cell(int row,int col,char A[][col],int x,int y)
{
    if(A[x][y]=='X' || A[x][y]=='?'){
        A[x][y]='F';
        return 1;
    }
    else if(A[x][y]=='F')
    {
        printf("\n\n\n \t\t\t THE CELL IS ALREADY FLAGED \n\n\n");
        system("pause");
        return 0;
    }
    else
    {
        printf("\n\n\n \t\t\t THE CELL IS ALREADY OPENED \n\n\n");
        system("pause");
    return 0;
    }
}
int remove_flag(int row,int col,char A[][col],int x,int y)
{
    if(A[x][y]=='F'){
        A[x][y]='X';
        return -1;
    }
    else
    {
        printf("\n\n\n \t\t\t THERE IS NO FLAG TO BE REMOVED \n\n\n");
        system("pause");
    return 0;
    }
}
int removeq_mark(int row,int col,char A[][col],int x,int y)
{
    if(A[x][y]=='?')
    {
    A[x][y]='X';
    return -1;
    }
    else
    {
        printf("\n\n\n \t\t\t THERE IS NO QUESTION MARK TO BE REMOVED \n\n\n");
        system("pause");
        return 0;
    }
}
int q_markCell(int row,int col,char A[][col],int x,int y)
{
    if(A[x][y]=='X' || A[x][y]=='F')
    {
        A[x][y]='?';
        return 1;
    }
    else if(A[x][y]=='?')
    {
        printf("\n\n\n \t\t\t THERE IS A QUESTION MARK ALREADY  \n\n\n");
        system("pause");
        return 0;
    }
    else
    {
        printf("\n\n\n \t\t\t THE CELL IS ALREADY OPENED \n\n\n");
        system("pause");
        return 0;
    }
}



void print_grid(int row ,int col ,char A[][col],int B[][col])
{
    int i,j;
    for (i=0;i<=row;i++){
            printf("\t\t\t");
        for (j=0;j<=col;j++){

            if (j!=0){
                if (i==0){
                    printf("\t%d",j);
                }
                else {
                    if (A[i-1][j-1] == 'O'){
                        if (B[i-1][j-1] == 0){
                            printf ("\t%c",B[i-1][j-1]);
                        }
                        else{
                            printf ("\t%d",B[i-1][j-1]);
                        }
                    }
                    else if(A[i-1][j-1] != 'O'){
                        printf ("\t%c",A[i-1][j-1]);
                    }
                }
            }
            if (j==0&&i!=0) {

                printf ("\n\n\n\t\t\t%d",i);

            }

        }
    }
     // printf("\n\t");
}

void open_all_lose(int row,int col,char A[][col],int B[][col],int x,int y)
{
    if(B[x][y]==10)
    {
        A[x][y]='!';
    }
    else if(B[x][y]!=10)
    {
        find_mine(row,col,A,B,x,y);
    }
    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if(A[i][j]=='F' && B[i][j]==10)
            {
                A[i][j]='*';
            }
            else if(A[i][j]=='X' && B[i][j]==10)
            {
                A[i][j]='M';
            }
            else if(A[i][j]=='F' && B[i][j]!=10)
            {
                A[i][j]='_';
            }
            else if(A[i][j]=='X' && B[i][j]!=10)
            {
                A[i][j]='O';
            }
        }
    }
    print_grid(row,col,A,B);
    printf("\n\n");
    system("pause");
}
void open_all_win(int row ,int col ,char A[][col],int B[][col],int x,int y)
{
    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if(i==x && j==y && j<col)
            {
                j++;
            }
            else if(j==col)
            {
                break;
            }
            if((A[i][j]=='X' || A[i][j]=='?')&& B[i][j]==10)
            {
                A[i][j]='F';
            }
        }
    }
    print_grid(row,col,A,B);
    printf("\n\n");
}
void find_mine(int row,int col,char A[][col],int B[][col],int x,int y)
{
    int i,j;
    for(i=(x-1);i<=(x+1);i++)
    {
        if(i == -1)
        {
            i++;
        }
        for(j=(y-1);j<=(y+1);j++)
        {
                if(j==-1)
                {
                    j++;
                }
                if(i==x && j==y)
                {
                    j++;
                }
                if(j>y && y+1==col)   // for not counting outside the array
                {
                    break;
                }
                if(A[i][j] == 'X' && B[i][j] == 10)
                {
                    A[i][j] = '!';
                }
                if(j>=y && y+1==col)
                {
                    break;
                }
        }
        if(i==x && x+1==row)
        {
            break;
        }
    }
}
