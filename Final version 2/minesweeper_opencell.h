#ifndef MINESWEEPER_OPENCELL_H_INCLUDED
#define MINESWEEPER_OPENCELL_H_INCLUDED


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


int open_cell(int row ,int col ,char A[][col],int B[][col],int x,int y,int* openFirst)
{
    /***
    minesNum : a variable used in winning function
    mines : a variable used in random function and mines distribution function
    open first : indicates the first time to open a cell
    game flag : indicates the current state
    ***/
    int i,j,mines,minesNum,gameFlag;
    gameFlag = 0;
    mines = 1+((row*col)/10);
    minesNum = 1+((row*col)/10);
    if(*openFirst == 1)   //distributing mines and numbers around them
    {
        random_num(row,col,A,B,&mines,x,y);
        mine_dis(row,col,B,&mines);

        for (i=0;i<row;i++){

            for (j=0;j<col;j++){

                if (B[i][j]!=10){

                    count_mines (i,j,row,col,B);
                }
            }
        }
    }
    if(B[x][y] == 0 && (A[x][y]=='X' || A[x][y]=='?'))
    {
        A[x][y]='O';

        open_adj_cells(row,col,A,B,x,y,&openFirst);


        if(minesNum == (row*col)-count_open(row,col,A)) // checking winning condition after opening a '0' cell and it's surroundings
        {
        return 2;
        }
        else{
        return 0;
        }
    }
    else if(B[x][y]!=0 && B[x][y]!=10 &&(A[x][y]=='X' || A[x][y]=='?'))
    {
        A[x][y]='O';

        if(minesNum == (row*col)-count_open(row,col,A)) // checking wining state after opening a single cell (directly)
        {
        return 2;
        }
        else
        {
        return 0;
        }
    }
    else if(A[x][y]=='O' && B[x][y]!=0 && B[x][y]!=10) // opening an open cell
    {
        int flagsNum;
        flagsNum = count_flags(row,col,A,x,y);  // checking the number of flags surrounding the cell
        if (flagsNum==B[x][y])
        {
            gameFlag = open_adj_cells(row,col,A,B,x,y,&openFirst);
            return gameFlag;
        }
        else
        {
            printf("\n\n\n\t\t FLAGS AROUND THE CELL ARE NOT EQUAL TO %d \n\n\n",B[x][y]);
            system("pause");
            return 0;
        }
    }
    else if((A[x][y] == 'X' || A[x][y] == '?')&& B[x][y]==10 ) //loosing condition
    {
        return 1;
    }
    else if(A[x][y] == 'F') //condition prevents opening a flagged cell
    {
        return 0;
    }
    if (A[x][y]=='O' && B[x][y] == 0) // condition prevents opening cells around an open '0' cell once more
    {
        printf("\n\n\n \t\t\t THE CELL IS ALREADY OPENED \n\n\n");
        system("pause");
        return 0;
    }
    if(count_open(row,col,A)== ((row*col)-minesNum)) // condition checks for the winning state every time we open a cell
    {
        return 2;
    }
}
void random_num (int row,int col,char A[][col],int B[][col],int *mines,int x,int y)
{
    int maxMines;

    maxMines = countXs(x,y,row,col,A); // maximum number of possible surrounding mines

    srand(time(NULL));

    if (*mines<=8 && *mines <= maxMines){

        B[x][y] = rand()%(*mines+1);
    }

    if (*mines>=8 || *mines >maxMines) {

        B[x][y] = rand()%(maxMines+1);
    }

    if (B[x][y]==0){

        if (countXs (x,y,row,col ,A) == (row*col -1)){

            B[x][y] =1;
        }
    }

    int mineSerround = B[x][y];

    *mines -= mineSerround ;

    do {

        int m,l;

        for (m=(x-1);m<=(x+1);m++){

            if (m==-1)
            {
                m++;
            }

            for (l=(y-1);l<=(y+1);l++){

                if (l==-1)
                {
                    l++;
                }

                if (m==x && l==y)
                {
                    l++;
                }

                if (l>y&&y==(col-1)){

                    break;
                }

                /* if not mine put 99 (for safety so no mines are placed later in this location)or the number picked in the first cell may become wrong*/

                if (B[m][l]!=10){

                    B[m][l]=99;

                }

                if (rand()%2 && B[m][l]!=10 && mineSerround!=0){

                    B[m][l] = 10; // mines are represented by the number 10

                    mineSerround-- ;
                }

                if (l>=y && y==(col-1)){

                    break;
                }

            }

            if (m>=x && x==(row-1) ){

                break;
            }
        }
    }
    while (mineSerround!=0);
}
void mine_dis (int row,int col,int B[][col],int *mines)
{
    int i , j;

    srand(time(NULL));

    while (*mines > 0)
    {

        for (i=0;i<row;i++){

            for (j=0;j<col;j++){

                int x = rand()%row;
                int y = rand()%col;

                if (B[x][y]==88){ //88 represent an empty B element

                    B[x][y] = 10; // mines are represented by the number 10

                    *mines -=1 ;


                }

                if (*mines==0){

                    break;

                }
            }

            if (*mines==0){

                        break;
                    }
        }
    }
}
/***

counting Xs to use them in the random function

***/
int countXs (int i,int j,int row,int col ,char A[][col])
{
    int k,l,count=0;

    for (k=(i-1);k<=(i+1);k++){

        if (k==-1)
        {
            k++;
        }

        for (l=(j-1);l<=(j+1);l++){

            if (l==-1)
            {
                l++;
            }

            if (k==i && l==j)
            {
                l++;
            }

            if (l>j&&j==(col-1)){

                break;
            }

            if (A[k][l]=='X'){

                count ++ ;
            }

            if (l>=j&&j==(col-1)){

                break;
            }

        }

        if (k>=i&&i==(row-1) ){

            break;
        }
    }

    return count;
}

int open_adj_cells(int row,int col,char A[][col],int B[][col],int x,int y,int openFirst)
{
    int i,j,gameFlag;//game flag  indicates the current state
    for(i=(x-1);i<=(x+1);i++)
    {
        if(i == -1)
        {
            i++;
        }
        if(i==row)
        {
            break;
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
                 if(j==col)
                {
                    break;
                }
                if(A[i][j] == 'X' || A[i][j] == '?')
                {
                    gameFlag = open_cell(row,col,A,B,i,j,&openFirst);
                    if( gameFlag == 1)
                    {
                        return 1;
                    }
                    else if( gameFlag == 2)
                    {
                        return 2;
                    }
                }
        }
    }
    return 0;
}
// count number of mine around a cell and put this number in it

void count_mines (int i,int j,int row,int col ,int B[][col])
{
    int k,l,count=0;

    for (k=(i-1);k<=(i+1);k++){

        if (k==-1)
        {
            k++;
        }

        for (l=(j-1);l<=(j+1);l++){

            if (l==-1)
            {
                l++;
            }

            if (k==i && l==j)
            {
                l++;
            }

            if (l>j&&j==(col-1)){

                break;
            }

            if (B[k][l]==10){

                count ++ ;
            }

            if (l>=j&&j==(col-1)){

                break;
            }

        }

        if (k>=i&&i==(row-1) ){

            break;
        }
    }

    B[i][j] = count;
}

int count_flags(int row,int col,char A[][col],int x,int y)
{
    int i,j,flagsNum;
    flagsNum = 0;
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
                if(A[i][j] == 'F')
                {
                    flagsNum++;
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
    return flagsNum;
}
int count_open(int row,int col,char A[][col])
{
    int i,j,openCell;
    openCell = 0;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
                if(A[i][j] == 'O' || A[i][j] == '?')
                {
                    openCell++;
                }
        }
    }
    return openCell;
}



#endif // MINESWEEPER_OPENCELL_H_INCLUDED
