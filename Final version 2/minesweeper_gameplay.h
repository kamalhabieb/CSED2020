#ifndef MINESWEEPER_GAMEPLAY_H_INCLUDED
#define MINESWEEPER_GAMEPLAY_H_INCLUDED

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

                                       /**game play function */
time_t calc_time (time_t loadTime,time_t start)
{

    time_t end = time(NULL);

    double timeDisplay =  difftime(end,start)+loadTime;

    double min=0 ,sec=timeDisplay;

    if (timeDisplay>=60){

        while (sec >= 60){

            sec -= 60;
            min ++;
        }
        printf ("\t\t\t\t\t\ttime : %g minutes %g seconds\n\n",min,sec);
    }

    else {

        printf ("\t\t\t\t\t\ttime : 0 minutes %g seconds\n\n",sec);
    }

    return timeDisplay ;

}

void game_play(int row,int col,int openFirst,int movesNum,int flagsNum,int qMarksNum,char A[][col],int B[][col],time_t loadTime,time_t firstTime)
{
    char board [10][10] ;
    set_board(board);
    int score [10] = {0};

    int state,switchFlag,cou,scan,scan_1,scan_2; // scans : keeping track of the user's input (numbers or not)
    char c,d;          // these variables are for avoiding getting a character after a number
    switchFlag = 0;
    int x,y;
        cou = 0;
        x = y = -5;
        print_grid(row,col,A,B);
        while(cou == 0){
            system("cls");
            printf("\n\n\n");
            calc_time(loadTime,firstTime);
            printf("\n\nmoves = %d\t\t",movesNum);
            printf("flags = %d\t\t",flagsNum);
            printf("question marks = %d\t",qMarksNum);
            printf("** To save enter (0)\t To quit to main menu enter (101)\t To Exit enter(102) **\n\n\n");
            printf("\n\n");
            print_grid(row,col,A,B);

            /*** threads ***/
        time_t start = time(NULL);
        /** declaring threads (giving them ID's) **/
        pthread_t alarm_th;
        ///  this is the thread function :-

        void*  idle_user()
            {
                pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
                while(1)
                    {
                        pthread_testcancel();

                        time_t end = time(NULL);

                        double timeDisplay =  difftime(end,start);

                    if (timeDisplay>59)  // 1 second delay
                        {
                            system("cls");
                            printf("\n\n What Is Taking You So Long !!!!!!!!??????? \n\n");
                            calc_time(loadTime,firstTime);
                            printf("\n\nmoves = %d\t\t",movesNum);
                            printf("flags = %d\t\t",flagsNum);
                            printf("question marks = %d\n\n",qMarksNum);
                            printf("\n\n");
                            print_grid(row,col,A,B);
                            printf("\n\n");
                            printf("\n\n\nEnter Row : \n");
                            state = x = y = 0; /// if the user is idle for a minute but entered an input this input is turned into zero (to avoid bugs)
                            start = time(NULL);
                        }
                    }
                pthread_exit(0);
            }
            /// that was the thread function

            /// creating thread
            pthread_create(&alarm_th, NULL,idle_user, NULL);

            /*** threads ***/
            printf("\n\n\nEnter Row : \n");
            scan_1 = scanf("%d%c",&x,&c);
            fflush(stdin);
            if(x==0)   // choosing to save the game
            {
                x = 102; // main issue
                save_game(row,col,openFirst,movesNum,flagsNum,qMarksNum,calc_time(loadTime,firstTime),A,B);
                pthread_cancel(alarm_th);
                char dummy_1; // for avoiding any bugy inputs
                int state_2,scan_3;
                int switchFlag_2 = 0;
                do{
                do{
                system("cls");
                printf("\n\n\n\n\t\t ENTER (1) TO CONTINUE \n\n\t\t (101) TO QUIT TO MAIN MENU \n\n\t\t (102) TO EXIT \n\n");
                scan_3 = scanf("%d%c",&state_2,&dummy_1);
                fflush(stdin);
                }
                while(!(scan_3==2 && dummy_1=='\n'));
                switch(state_2)
                {
                    case 1:  switchFlag_2 = 1;
                             system("cls");
                             printf("\n\n\n");
                             calc_time(loadTime,firstTime);
                             printf("\n\nmoves = %d\t\t",movesNum);
                             printf("flags = %d\t\t",flagsNum);
                             printf("question marks = %d\t",qMarksNum);
                             printf("** To save enter (0)\t To quit to main menu enter (101)\t To Exit enter(102) **\n\n\n");
                             printf("\n\n");
                             print_grid(row,col,A,B);
                             printf("\n\n\nEnter Row : \n");
                             scan_1 = scanf("%d%c",&x,&c);
                             fflush(stdin);
                             break;

                    case 101:  switchFlag_2 = 1;
                             main();
                             break;

                    case 102:  switchFlag_2 = 1;
                             return;
                             break;

                    default: system("cls");
                             printf("\n\n\n\n\t\t ENTER : \n\n\t\t(1) TO CONTINUE \n\n\t\t (101) TO QUIT TO MAIN MENU \n\n\t\t (102) TO EXIT \n\n\t\t");

                }
                }
                while(switchFlag_2 == 0);
            }
            if(x==101)
            {
                pthread_cancel(alarm_th);
                main();

            }
            if(x==102)
            {
                pthread_cancel(alarm_th);
                return ;
            }
            if(x == 101 ) // main issue
            {
                pthread_cancel(alarm_th);
                return ;
            }
            printf("\nEnter col : \n");
            scan_2 = scanf("%d%c",&y,&d);
            fflush(stdin);
            x = x-1;
            y = y-1;
            switchFlag=0; // reinitializing switch flag
            while(x<0 || x>=row || y<0 || y>=col || scan_1!=2 || scan_2!=2 || c!='\n' || d!='\n'){
                system("cls");
                printf("\n\n\n");
                calc_time(loadTime,firstTime);
                printf("\n\nmoves = %d\t\t",movesNum);
                printf("flags = %d\t\t",flagsNum);
                printf("question marks = %d\t\t",qMarksNum);
                printf("** To save enter (0)\t To quit to main menu enter (101)\t To Exit enter(102) **\n\n\n");

                printf("\n\n");
                print_grid(row,col,A,B);
                printf("\n\nInvalid Input\n");
                printf("\n\n\nEnter Row : \n");
                scan_1 = scanf("%d%c",&x,&c);
                fflush(stdin);
                if(x==0)
                {
                    save_game(row,col,openFirst,movesNum,flagsNum,qMarksNum,calc_time(loadTime,firstTime),A,B);
                    pthread_cancel(alarm_th);
                    char dummy_1;
                    int scan_3;
                    int state_2;
                    int switchFlag_2 = 0;
                    do{
                        do{
                            system("cls");
                            printf("\n\n\n\n\t\t ENTER (1) TO CONTINUE \n\n\t\t (2) TO QUIT TO MAIN MENU \n\n\t\t (3) TO EXIT \n\n");
                            scan_3 = scanf("%d%c",&state_2,&dummy_1);
                            fflush(stdin);
                        }
                while(!(scan_3==2 && dummy_1=='\n'));
                    switch(state_2)
                    {
                        case 1:  switchFlag_2 = 1;
                                system("cls");
                                 calc_time(loadTime,firstTime);
                                 printf("\n\nmoves = %d\t\t",movesNum);
                                 printf("flags = %d\t\t",flagsNum);
                                 printf("question marks = %d\t",qMarksNum);
                                 printf("** To save enter (0)\t To quit to main menu enter (101)\t To Exit enter(102) **\n\n\n");
                                 printf("\n\n");
                                 print_grid(row,col,A,B);
                                 printf("\n\n\nEnter Row : \n");
                                 scan_1 = scanf("%d%c",&x,&c);
                                 fflush(stdin);
                                 break;

                        case 2:  switchFlag_2 = 1;
                                 main();
                                 break;

                        case 3:  switchFlag_2 = 1;
                                 return;
                                 break;

                        default: system("cls");
                                 printf("\n\n\n\n\t\t ENTER : \n\n\t\t(1) TO CONTINUE \n\n\t\t (2) TO QUIT TO MAIN MENU \n\n\t\t (3) TO EXIT \n\n\t\t");
                                 break;
                    }
                }
                while(switchFlag_2 == 0);
            }
            if(x == 101)
            {
                pthread_cancel(alarm_th);
                main();

            }
            if(x == 102)
            {
                pthread_cancel(alarm_th);
                return ;
            }
                printf("\nEnter col : \n");
                scan_2 = scanf("%d%c",&y,&d);
                fflush(stdin);
                x = x-1;
                y = y-1;
            }
            while(switchFlag == 0){
            do{
            system("cls");
            printf("\n\n");
            calc_time(loadTime,firstTime);
            printf("\n\nmoves = %d\t\t",movesNum);
            printf("flags = %d\t\t",flagsNum);
            printf("question marks = %d\n\n",qMarksNum);
            printf("\n\n");
            print_grid(row,col,A,B);
            printf("\n\n\nChoose State Number :\n\n1-Open\t\t2-Flag\t\t3-Question Mark\t\t4-remove flag\t\t5-remove question mark\n\n");

            scan = scanf("%d%c",&state,&c);
            fflush(stdin);
            }
            while (c!='\n' ||scan!=2);
            /// thread's condition checking
            if(scan)
                {
                    pthread_cancel(alarm_th);
                }
                pthread_join(alarm_th,NULL);
 /****************************************************/
            switch(state){
                case 1 : movesNum++;
                         openFirst++;
                         cou = open_cell(row,col,A,B,x,y,&openFirst);
                         switchFlag = 1;
                         break;
                case 2 : movesNum++;
                         flagsNum += flag_cell(row,col,A,x,y);
                         switchFlag = 1;
                         break;
                case 3 : movesNum++;
                         qMarksNum += q_markCell(row,col,A,x,y);
                         switchFlag = 1;
                         break;
                case 4 : movesNum++;
                         flagsNum += remove_flag(row,col,A,x,y);
                         switchFlag = 1;
                         break;
                case 5 : movesNum++;
                         qMarksNum += removeq_mark(row,col,A,x,y);
                         switchFlag = 1;
                         break;
                default :
                         system("cls");
                         printf("\n\n");
                         calc_time(loadTime,firstTime);
                         printf("\n\nmoves = %d\t\t",movesNum);
                         printf("flags = %d\t\t",flagsNum);
                         printf("question marks = %d\n\n",qMarksNum);
                         printf("\n\n");
                         print_grid(row,col,A,B);
                         printf("Invalid state\n");
            }


            }
        if (cou == 1)
        {
            system("cls");
            printf("\n\n\n\n\t\t\t\tGAME OVER !!! YOU LOST\n\n\n\n");
            system("color CE");
            printf("\n\n");
            calc_time(loadTime,firstTime);
            printf("\n\nmoves = %d\t\t",movesNum);
            printf("flags = %d\t\t",flagsNum);
            printf("question marks = %d\n\n",qMarksNum);
            printf("\n\n");
            open_all_lose(row,col,A,B,x,y);
            printf("\n\n");
        }
        else if(cou == 2)
        {
            int playerScore = ( ( (row*row*row*row)*(col*col*col*col) ) / (calc_time(loadTime,firstTime) *movesNum) );
            system("cls");
            system("color A1");
            printf("\n\n\n\n\t\t\t\t**CONGRATULATIONS !!! YOU WON**\n\n\n\n");
            printf("\n\n");
            calc_time(loadTime,firstTime);
            printf("\n\n\n\t\t\t\tYour score : %d",playerScore);
            printf("\n\nmoves = %d\t\t",movesNum);
            printf("flags = %d\t\t",flagsNum);
            printf("question marks = %d\n\n",qMarksNum);
            printf("\n\n");
            open_all_win(row,col,A,B,x,y);

            //leader board
            load_board (board,score);
            get_and_compare (board,score,playerScore);
            save_board (board,score);

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
        }
    }

}

#endif // MINESWEEPER_GAMEPLAY_H_INCLUDED
