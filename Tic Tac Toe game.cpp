#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <random>
#include <ctime>

using std::string;
using std::getline;
using namespace ::std;

const string winningCases[8] = {"123","456","789","147","258","369","159","357"};


void make_board(char grid[3][3]){
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            grid[i][j]= '-' ;
        }
    }
}

void print_board(char grid[3][3]){
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
    cout << '\n';
}

void player_enter_move(char grid[][3]){
    char humanMove;
    int num_humanMove;

    while(true){
        cout << "\nPlease enter the move >> " ;
        cin >> humanMove;

        // find index for a grid
        num_humanMove = static_cast<int>(humanMove) - 49;

        int row = num_humanMove / 3;
        int col = num_humanMove % 3;

        // check right input
        if(49 > static_cast<int>(humanMove) && static_cast<int>(humanMove) < 57){
            cout << "Not valid input. " << endl;

        }else if(grid[row][col] == 'X' || grid[row][col]== 'O'){
            cout << "It's taken. " << endl;

        }else{
            grid[row][col] = 'X';

//            print_board(*grid[3]);

            break;
        }
    }

}

int find_grid_space(char move){
    int gridSpace=0;

    int winningMove_int = static_cast<int>(move) - 48;
    gridSpace = winningMove_int - 1;

    return gridSpace;
}

bool check_for_win(char grid[3][3]){
    /* This function goes through the grid and check if there is a winner
     *
     * First, it will iterate the winningCases
     * Second, based on one of the winningCases move, it will check the board
     *
     * for example, if the winning case is {4,5,6},
     * it will check [1][0],[1][1],[1][2] and if they have same character(all 'X' or 'O')
     * it will return true(winner)
     * */

    bool winner = true;
    for (int i = 0; i < 8; i++) {   // iterate winningCases
        winner = true;
        char previousMove = '?';
        string winningMove = winningCases[i];   // ig. {456}

        for (int j = 0; j < 3; j++) {   // checking with the position of 4,5,6

            int gridSpace = find_grid_space(winningMove[j]);
            int row = gridSpace / 3;
            int col = gridSpace % 3;

            char gridChar = grid[row][col];


            // checking the location of 4,5,6
            if(previousMove == '?'){    // first iteration ig. [1][0] will be saved as previousMove
                previousMove = gridChar;
            }
            else if((previousMove!='-')&&(previousMove == gridChar)){   // if [1][0]==[1][1] and [1][1]==[1][2]
                                                                        // loop will continue and winner is still true
                continue;
            }
            else if (previousMove == '-' || previousMove == 'X' || previousMove == 'O'){ // no winner
                winner = false;
                break;
            }
        }
        if (winner){
            cout << "********** We got a winner! ************** \n";
            break;
        }
    }
    return winner;
}

void computer_second_best_move(char grid[][3]){
    int flag=0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if( (i==0 && (j==0 || j==1)) || (i==2 && (j==0 || j==1))){
                if (grid[i][j] != 'O' && grid[i][j]!='X'){
                    grid[i][j]='O';
                    flag++;
                    break;
                }
            }
            else if((i==0 && j==1) || (i==1 && (j==0 || j==2)) || (i==2 && j==1)){
                if (grid[i][j] != 'O' && grid[i][j]!='X'){
                    grid[i][j]='O';
                    flag++;
                    break;
                }
            }
            else{
                if (grid[i][j] == '-'){
                    grid[i][j]='O';
                    flag++;
                    break;
                }
            }
        }
        if(flag==1)
            break;
    }


}

void computer_after_first_move(char grid[][3]){
    int flag=0;

    for (int i = 0; i < 8; i++) {   // iterate winningCases
        char previousMove = '?';
        string winningMove = winningCases[i];   // ig. {456}

        for (int j = 0; j < 3; j++) {   // checking with the position of 4,5,6

            char winningMove_char = winningMove[j];

            // find the location in the grid

            int winningMove_int = static_cast<int>(winningMove_char) - 48;
            int gridSpace = winningMove_int - 1;

            int row = gridSpace / 3;
            int col = gridSpace % 3;

            char gridChar = grid[row][col];


            // checking the location of 4,5,6
            if (previousMove == '?') {    // first iteration ig. [1][0] will be saved as previousMove
                previousMove = gridChar;
            } else if ((previousMove != '-') && (previousMove == gridChar)) {   // if [1][0]==[1][1] and [1][1]==[1][2]
                winningMove_char = winningMove[j + 1];


                winningMove_int = static_cast<int>(winningMove_char) - 48;
                gridSpace = winningMove_int - 1;

                row = gridSpace / 3;
                col = gridSpace % 3;

                if(grid[row][col] == 'X' || grid[row][col] == 'O'){
                    break;
                }

                grid[row][col] = 'O';
                flag++;
                break;

            } else{
                break;
            }
        }
        if(flag==1)
            break;
        else if (i==7) {
            computer_second_best_move(grid);
            break;
        }
    }
}

void computer_enter_move(char grid[][3]){
    if (grid[1][1] == '-')
        grid [1][1] = 'O';
    else
        computer_after_first_move(grid);
}

char continue_play(){
    static char play;
    cout << "Would you like to play again? (Y/N) ";
    cin >> play;

    return play;
}

bool check_draw(char grid[3][3]){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == '-'){
                return false;
            }
        }
    }
    return true;
}


int main(int argc, char *argv[]){

    cout << "\nWelcome to 'Tic Tac Toe' game. \nWith this game, you will play against Computer. \n\nGood Luck!\n ";

    char grid[3][3];
    char play='y';
    const unsigned int seed = time(0);
    bool win, draw;

    int computerPlay = seed % 2;
//    computerPlay = rand()%2;

    if(computerPlay){
        cout << "\nFirst move goes to Computer!\n\n" ;
    }else{
        cout << "\nFirst move goes to Human player!\n\n" ;
    }


    while(play == 'y' || play == 'Y'){
        make_board(grid);
        win = true;

        while(win){

            if(!computerPlay){
                player_enter_move(grid);
                print_board(grid);
                win = !check_for_win(grid);
                draw = check_draw(grid);

                if(!win){
                    cout << "You've beat the computer! Great job :D  \n\n\n";
                    break;
                }
                if(draw){
                    cout << "Draw! Well done everyone :) \n\n";
                    break;
                }

                computerPlay = true;

            }else{
                cout << "\nComputer move \n";
                computer_enter_move(grid);
                print_board(grid);
                win = !check_for_win(grid);

                if(!win){
                    cout << "This dumb computer that I programmed has won. What's wrong with you? \n\n\n";
                    break;
                }
                if(draw){
                    cout << "Draw! Well done everyone :) \n\n";
                    break;
                }
                computerPlay = false;
            }
        }
        play = continue_play();
    }
    return 0;
}
