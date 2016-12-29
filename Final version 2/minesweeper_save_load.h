#ifndef MINESWEEPER_SAVE_LOAD_H_INCLUDED
#define MINESWEEPER_SAVE_LOAD_H_INCLUDED


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



void load_game (void)
{

    if(!fopen("game.txt","r"))
        {
            printf("\n\n\n\n\n\n\t\t\t\t\t\t ERROR OCCURED\n\n\n\t\t\t\tTHERE IS NO SAVED GAME TO BE LOADED");
            return;
        }
    FILE * ptrLoad = fopen("game.txt","r");

    int arrayInfo [6];

    fread(arrayInfo,sizeof (int),6,ptrLoad);

    int row = arrayInfo [0];
    int col = arrayInfo [1];
    int openFirst = arrayInfo [2];
    int movesNum =arrayInfo [3];
    int flagsNum = arrayInfo [4];
    int qMarksNum = arrayInfo [5];

    if(row>100 || col >100 || row<0 || col<0)
    {
        printf("\n\n\n\n\n\n\t\t\t\t\t\t ERROR OCCURED\n\n\n\t\t\t\tTHERE IS NO SAVED GAME TO BE LOADED");
        return;
    }

    char A [row][col];
    int B [row][col];
    time_t  loadTime;

    time_t timeStart = time(NULL);

    fread(A,sizeof (char),row*col,ptrLoad);
    fread(B,sizeof (int),row*col,ptrLoad);
    fscanf(ptrLoad,"%lld",&loadTime);

    game_play(row,col,openFirst,movesNum,flagsNum,qMarksNum,A,B,loadTime,timeStart);

}

void save_game (int row,int col,int openFirst,int movesNum,int flagsNum,int qMarksNum,long long startGame , char A[][col],int B[][col])
{
    int arrayInfo [6];
    arrayInfo [0] = row;
    arrayInfo [1] = col;
    arrayInfo [2] = openFirst;
    arrayInfo [3] = movesNum;
    arrayInfo [4] = flagsNum;
    arrayInfo [5] = qMarksNum;

    //save game file pointer
    FILE * ptrSave=fopen("game.txt","w");

    fwrite(arrayInfo,sizeof (int),6,ptrSave); // save info

    fwrite(A,sizeof (char),row*col,ptrSave); //save array A

    fwrite(B,sizeof (int),row*col,ptrSave); //save array B*/

    fprintf(ptrSave,"%lld",startGame); // save time

    fclose(ptrSave);
}


#endif // MINESWEEPER_SAVE_LOAD_H_INCLUDED
