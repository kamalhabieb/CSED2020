#ifndef MINESWEEPER_NEWGAME_H_INCLUDED
#define MINESWEEPER_NEWGAME_H_INCLUDED


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


void new_game(void)
{
   char c,d;                   // these variables are for avoiding getting characters instead of numbers
   int row,col,scan;           // scan : keeping track of the user's input (numbers or not)
   do{                         // preventing user from entering characters
    printf("\n\n\nEnter The Dimensions Of The Grid : ");
    scan = scanf("%d%c%d%c",&row,&c,&col,&d);
    fflush(stdin);
    }
    while(row<2 || row > 100 || col<2 || col>100 || scan!=4 || (c!='\n'&&c!=' ') || d!='\n');

    int flagsNum = 0;
    int qMarksNum = 0;
    int movesNum = 0;
    int openFirst = 0; // a flag to distribute mines
    time_t loadTime =0;
    time_t firstTime = time(NULL);
    int B[row][col];
    char A[row][col];
    set_A(row,col,A);
    set_B(row,col,B);
    game_play(row,col,openFirst,movesNum,flagsNum,qMarksNum,A,B,loadTime,firstTime);
}

void set_A (int row , int col , char A[][col])
{
    int i,j;

    for (i=0;i<row;i++){

        for (j=0;j<col;j++) {

            A[i][j]='X';
        }
    }
}

void set_B (int row , int col , int B[][col])
{
    int i,j;

    for (i=0;i<row;i++){

        for (j=0;j<col;j++){

            B[i][j]=88; //88 represent an empty B element
        }
    }
}


#endif // MINESWEEPER_NEWGAME_H_INCLUDED
