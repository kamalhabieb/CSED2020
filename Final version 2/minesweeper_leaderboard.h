#ifndef MINESWEEPER_LEADERBOARD_H_INCLUDED
#define MINESWEEPER_LEADERBOARD_H_INCLUDED


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


                    ///**leader board Code*///////

void set_board (char board[][10])
{
    int i,j;

    for (i=0;i<10;i++) {
        board[i][0]='E';

        for (j=1;j<10;j++){

            board[i][j]='\0';
        }

    }

}

void read_board (char board[][10],char name[] , int score [],int playerScore)
{
    int i,j;

    for (i=0;i<10;i++){ //i represent rows

        //if score is higher then delete player 10 and store new player's name and score
        if (playerScore > score [i]){

            for (j=9;j>i;j--){

                strcpy(board[j],board[j-1]);

                score [j] =score[j-1];
           }

            clear_row (board,i);

            strcpy(board[i],name);

            score [i] = playerScore;

            break;
        }
    }
}

void read_name (char name[])
{
    int i=0;
    char ch;

    while ( ((ch=getchar())) && i!= 10 ){

            if (ch!='\n'){
                if ( (ch>='a'&&ch<='z' ) || (ch<'A'||ch>'Z') || ((ch ==' ') && i!=0) ){

                    name [i++] = ch;

                }

                else if (ch>='A' && ch <='Z'){

                name [i++] = ch+32 ;

                }
            }
            else if (ch=='\n'&&i!=0){
                break;
            }
    }

    name[i]='\0';
}

void print_board (char board [][10],int score[])
{
    int i,j;

    for (i=0;i<10;i++){

        printf("\t\t\t\t%d- ",i+1);

        for (j=0;j<10 ;j++){

            if (board[i][j]!='E' ){

                printf ("%c",board[i][j]);
            }

        }

        if (score[i]==0)
             printf("\t\t");

        else
            printf ("   \t");

        printf("\t%d",score[i]);

        printf("\n");
    }
}


void get_and_compare (char board[][10],int score [],int playerScore)
{
    int i,j,k,found=0;

    char name [10];


    found=0;

    printf("\n\t\t\t***Enter your name  (*Max Length = 10 the rest is ignored*) :  ");

    read_name (name);

    for (i=0;i<10;i++){

        if (strncmp (board[i],name,10) ==0){

            if (playerScore>score[i]){

                score[i]=playerScore;

                for (j=0;j<i;j++){

                    if (playerScore>score[j]){

                        for (k=i;k>j;k--){

                            clear_row (board,k);
                            strcpy(board[k],board[k-1]);
                            score [k] =score[k-1];
                        }

                        clear_row (board,j);
                        strcpy(board[j],name);
                        score [j] = playerScore;
                        break;
                    }
                }
            }

            found =1;
            break;

        }
    }

    if (i==10 && found ==0)
    {
        read_board (board,name,score,playerScore);
    }

    printf("\n");

    print_board (board,score);

}

void clear_row (char board[][10],int i)
{
    int j;

    for (j=0;j<10;j++){

        board[i][j]=' ';
    }
}

void load_board (char loadNames[][10], int loadScore[]) // send board array and score array as parameters
{
    FILE *rd = fopen ("board.txt","r");

    fread (loadNames,sizeof(char),100,rd);
    fread (loadScore,sizeof(int),10,rd);

    fclose(rd);
}

void save_board (char board[][10],char score []) // send board array and score array as parameters
{
    FILE *ptr = fopen("board.txt","w");

    fwrite(board,sizeof(char),100,ptr);
    fwrite(score,sizeof(int),10,ptr);

    fclose(ptr);
}
/**leader Board code ended*/


#endif // MINESWEEPER_LEADERBOARD_H_INCLUDED
