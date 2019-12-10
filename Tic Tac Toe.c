//Kevin Anderson
//COP 3502H
//Made in Code::Blocks

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define PLAYER1 0
#define AI 1

//X = player 1 input, O = player 2 input, N = neither
typedef enum  {X,O,N}inputs;


void printTable(inputs table[3][3]);
//tp==turn player
void gameInput(inputs table[3][3], int tp);
bool checkWin(inputs table[3][3]);
//helper functions to print a new line
void newLine();
void dnewLine();

int main()
{
    int i,j;
    int turn = PLAYER1;
    bool gameOver=false;
    char YN;
    inputs table[3][3];

    srand(time(NULL));

    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            table[i][j]=N;
    printTable(table);

    while(true){

        printf("\nIt is %s's turn.\n", turn==PLAYER1 ? "Player 1" : "AI Player");
        printf("%s, select an empty space to mark an %c: ", turn==PLAYER1 ? "Player 1" : "Player 2",turn==PLAYER1 ? 'X' : 'O');
        gameInput(table,turn);
        newLine();
        printTable(table);
        gameOver = checkWin(table);
        //Since turn is either 1 or 0, 1-turn will always get the other value.
        turn = 1-turn;
        //If the game is over, prompt the user to play again.
        if(gameOver){
            printf("\nDo you want to play again (Y/N)? ");
            scanf(" %c",&YN);
            if (tolower(YN)=='y'){
                newLine();
                for(i=0;i<3;i++)
                    for(j=0;j<3;j++)
                        table[i][j]=N;
                printTable(table);
                turn=PLAYER1;
            }
            else
                return 0;
        }
    }
    return 0;
}

void printTable(inputs table[3][3]){
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(j==2)
                if(table[i][j]==N)
                    printf(" %d ",i*3+j+1);
                else
                    printf(" %s ",table[i][j]==X ? "X" : table[i][j]==O ? "O" : "");
            else
                if(table[i][j]==N)
                    printf(" %d |",i*3+j+1);
                else
                    printf(" %s |",table[i][j]==X ? "X" : table[i][j]==O ? "O" : "");
        }
        if(i!=2)
            printf("\n-----------\n");
    }
    newLine();
}

void gameInput(inputs table[3][3], int tp){
    int in,i;
    int mod,div;

    if (tp==PLAYER1){
        while(true){
            scanf("%d",&in);
            in--;
            mod=in%3;
            div=in/3;

            if(table[div][mod]!=N){
                printf("Please enter a valid input.\n");
                continue;
            }
            table[div][mod] = tp==PLAYER1 ? X : O;
            break;
        }
    }
    //The tic tac toe AI is really long, but it basically says "If there is a win, take/prevent it. Otherwise,
    //take the smartest move. If that's not programmed, choose a random space.
    else{
        while(true){
            if(table[1][1]==N){
                table[1][1] = tp==PLAYER1 ? X : O;
                printf("5\n");
                return;
            }
            //If there is a possible horizontal or vertical win, place a piece to win
            for(i=0;i<3;i++){
                if(table[0][i]==table[1][i] && table[0][i]==O && table[2][i]==N){
                    table[2][i] = tp==PLAYER1 ? X : O;
                    printf("%d\n", 1+i+2*3);
                    return;
                }
                else if(table[1][i]==table[2][i] && table[1][i]==O && table[0][i]==N){
                    table[0][i] = tp==PLAYER1 ? X : O;
                    printf("%d\n", 1+i+0*3);
                    return;
                }
                else if(table[0][i]==table[2][i] && table[0][i]==O && table[1][i]==N){
                    table[1][i] = tp==PLAYER1 ? X : O;
                    printf("%d\n", 1+i+1*3);
                    return;
                }
                else if(table[i][0]==table[i][1] && table[i][0]==O && table[i][2]==N){
                    table[i][2] = tp==PLAYER1 ? X : O;
                    printf("%d\n", 1+2+i*3);
                    return;
                }
                else if(table[i][1]==table[i][2] && table[i][1]==O && table[i][0]==N){
                    table[i][0] = tp==PLAYER1 ? X : O;
                    printf("%d\n", 1+0+i*3);
                    return;
                }
                else if(table[i][0]==table[i][2] && table[i][0]==O && table[i][1]==N){
                    table[i][1] = tp==PLAYER1 ? X : O;
                    printf("%d\n", 1+1+i*3);
                    return;
                }
            }
            //If there is a possibly diagonal win, take it.
            if(table[0][0]==O && table[1][1]==O && table[2][2]==N){
                table[2][2] = tp==PLAYER1 ? X : O;
                printf("%d\n", 9);
                return;
            }
            else if(table[2][2]==O && table[1][1]==O && table[0][0]==N){
                table[0][0] = tp==PLAYER1 ? X : O;
                printf("%d\n", 9);
                return;
            }
            else if(table[0][0]==O && table[2][2]==O && table[1][1]==N){
                table[1][1] = tp==PLAYER1 ? X : O;
                printf("%d\n", 5);
                return;
            }
            else if(table[0][2]==O && table[1][1]==O && table[2][0]==N){
                table[2][0] = tp==PLAYER1 ? X : O;
                printf("%d\n", 7);
                return;
            }
            else if(table[2][0]==O && table[1][1]==O && table[0][2]==N){
                table[0][2] = tp==PLAYER1 ? X : O;
                printf("%d\n", 7);
                return;
            }
            else if(table[0][2]==O && table[2][0]==O && table[1][1]==N){
                table[1][1] = tp==PLAYER1 ? X : O;
                printf("%d\n", 5);
                return;
            }
            //If the opponent could possibly win horiz. or vert, place a piece to block it.
            for(i=0;i<3;i++){
                if(table[0][i]==table[1][i] && table[0][i]!=N && table[2][i]==N){
                    table[2][i] = tp==PLAYER1 ? X : O;
                    printf("%d\n", 1+i+2*3);
                    return;
                }
                else if(table[1][i]==table[2][i] && table[1][i]!=N && table[0][i]==N){
                    table[0][i] = tp==PLAYER1 ? X : O;
                    printf("%d\n", 1+i+0*3);
                    return;
                }
                else if(table[0][i]==table[2][i] && table[0][i]!=N && table[1][i]==N){
                    table[1][i] = tp==PLAYER1 ? X : O;
                    printf("%d\n", 1+i+1*3);
                    return;
                }
                else if(table[i][0]==table[i][1] && table[i][0]!=N && table[i][2]==N){
                    table[i][2] = tp==PLAYER1 ? X : O;
                    printf("%d\n", 1+2+i*3);
                    return;
                }
                else if(table[i][1]==table[i][2] && table[i][1]!=N && table[i][0]==N){
                    table[i][0] = tp==PLAYER1 ? X : O;
                    printf("%d\n", 1+0+i*3);
                    return;
                }
                else if(table[i][0]==table[i][2] && table[i][0]!=N && table[i][1]==N){
                    table[i][1] = tp==PLAYER1 ? X : O;
                    printf("%d\n", 1+1+i*3);
                    return;
                }
            }
            //If there is a spot taken on the corner, take an edge spot.
            if (((table[0][0] == table[2][2] && table[2][2]==X) || (table[2][0]==table[0][2] && table[0][2]==X))
                    && (table[0][1]==N || table[2][1]==N || table[1][0] || table[1][2])){
                if(table[0][1]==N){
                    table[0][1] = tp==PLAYER1 ? X : O;
                    printf("2\n");
                    return;
                }
                else if(table[2][1]==N){
                    table[2][1] = tp==PLAYER1 ? X : O;
                    printf("8\n");
                    return;
                }
                else if(table[1][0]==N){
                    table[1][0] = tp==PLAYER1 ? X : O;
                    printf("4\n");
                    return;
                }
                else if(table[1][2]==N){
                    table[1][2] = tp==PLAYER1 ? X : O;
                    printf("6\n");
                    return;
                }
            }
            //If possible, take the spot opposite X (I re-worked the AI, so I actually don't think this part
            //will ever be called if the opponent is good enough,
            //because the AI should spend all of its moves blocking the opponent)
            else if(table[0][0]==X && table[2][2]==N){
                div=2;
                mod=2;
            }
            else if(table[2][2]==X && table[0][0]==N){
                div=0;
                mod=0;
            }
            else if(table[0][2]==X && table[2][0]==N){
                div=2;
                mod=0;
            }
            else if(table[2][0]==X && table[0][2]==N){
                div=0;
                mod=2;
            }
            //else, choose a random corner, because corners are generally the smartest choices in tic tac toe
            else if(table[0][2]==N || table[0][0]==N || table[2][0]==N || table[2][2]==N){
                //If there are two Xs on the edges, place an O such that an X can't connect them.
                if(table[0][1]==table[1][0] && table[0][1]==X && table[0][0]==N){
                    table[0][0] = tp==PLAYER1 ? X : O;
                    printf("1\n");
                    return;
                }
                else if(table[2][1]==table[1][0] && table[0][1]==X && table[2][0]==N){
                    table[2][0] = tp==PLAYER1 ? X : O;
                    printf("1\n");
                    return;
                }
                else if(table[0][1]==table[1][2] && table[0][1]==X && table[0][2]==N){
                    table[0][2] = tp==PLAYER1 ? X : O;
                    printf("1\n");
                    return;
                }
                else if(table[1][2]==table[2][1] && table[2][1]==X && table[2][2]==N){
                    table[2][2] = tp==PLAYER1 ? X : O;
                    printf("1\n");
                    return;
                }
                mod = rand()%2;
                div = rand()%2;
                //This chooses a corner, because if mod/div is 0, it will stay 0.
                //If it is 1, it will become 2.
                mod*=2;
                div*=2;
            }
            //else, choose a random open spot
            else{
                mod = rand()%3;
                div = rand()%3;
            }
            if(table[div][mod]!=N){
                continue;
            }
            printf("%d\n",mod+div*3+1);
            table[div][mod] = tp==PLAYER1 ? X : O;
            break;
        }
    }
    return;
}
bool checkWin(inputs table[3][3]){
    int i,j;
    if (table[0][0]==table[0][1] && table[0][1]==table[0][2] && table[0][1]!=N){
        printf("\n%s wins!!\n\n", table[0][0]==X ? "Player 1": "AI Player");
        return true;;
    }
    else if (table[1][0]==table[1][1] && table[1][1]==table[1][2]&& table[1][1]!=N){
        printf("\n%s wins!!\n\n", table[1][0]==X ? "Player 1": "AI Player");
        return true;;
    }
    else if (table[2][0]==table[2][1] && table[2][1]==table[2][2]&& table[2][1]!=N){
        printf("\n%s wins!!\n\n", table[2][0]==X ? "Player 1": "AI Player");
        return true;;
    }
    else if (table[0][0]==table[1][1] && table[1][1]==table[2][2]&& table[1][1]!=N){
        printf("\n%s wins!!\n\n", table[0][0]==X ? "Player 1": "AI Player");
        return true;;
    }
    else if (table[0][2]==table[1][1]&& table[1][1]==table[2][0]&& table[1][1]!=N){
        printf("\n%s wins!!\n\n", table[0][2]==X ? "Player 1": "AI Player");
        return true;;
    }
    else if (table[0][0]==table[1][0]&& table[1][0]==table[2][0]&& table[1][0]!=N){
        printf("\n%s wins!!\n\n", table[0][0]==X ? "Player 1": "AI Player");
        return true;;
    }
    else if (table[0][1]==table[1][1]&& table[1][1]==table[2][1]&& table[1][1]!=N){
        printf("\n%s wins!!\n\n", table[0][1]==X ? "Player 1": "AI Player");
        return true;;
    }
    else if (table[0][2]==table[1][2]&& table[1][2]==table[2][2]&& table[1][2]!=N){
        printf("\n%s wins!!\n\n", table[0][2]==X ? "Player 1": "AI Player");
        return true;;
    }
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(table[i][j]==N)
                return false;
        }
    }
    printf("\nThe game has ended in a draw!");
    return true;;
}

void newLine(){
printf("\n");
}
void dnewLine(){
printf("\n\n");
}
