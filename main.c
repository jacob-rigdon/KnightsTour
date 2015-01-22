#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int visited[SIZE][SIZE];
int maxMoves;
int size;

int coordinateToIndex(int x, int y)
{
    return x*5 + y + 1;
}

int findTours(int x, int y, int move, int stack[maxMoves])
{
    int i;
    if( (x < 0) || (x >= size) || (y < 0) || (y >= size) )
        return 0;        //coordinate out of bounds

    if( visited[x][y] == 1)
        return 0;       //node already visited

    if(move == maxMoves)
    {
        //successful solution
        visited[x][y] = 1;  //mark node
        stack[move] = coordinateToIndex(x, y);  //add last to stack

        for(i = 0; i < maxMoves; i++){
            printf("%3d", stack[i]);    //print stack
        }
        printf("\n");
        return 1;
    }

    else
    {
        int result = 0;
        visited[x][y] = 1;
        //valid move, but no solution yet
        int i;
        int next[8][2] = { {2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2} };

        for(i = 0; i < 8; i++){
            result |= findTours( x+next[i][0], y+next[i][1], move+1, stack);
            result |= findTours( x+next[(i+1)%8][0], y+next[(i+1)%8][1], move+1, stack);
            result |= findTours( x+next[(i+2)%8][0], y+next[(i+2)%8][1], move+1, stack);
            result |= findTours( x+next[(i+3)%8][0], y+next[(i+3)%8][1], move+1, stack);
            result |= findTours( x+next[(i+4)%8][0], y+next[(i+4)%8][1], move+1, stack);
            result |= findTours( x+next[(i+5)%8][0], y+next[(i+5)%8][1], move+1, stack);
            result |= findTours( x+next[(i+6)%8][0], y+next[(i+6)%8][1], move+1, stack);
            result |= findTours( x+next[(i+7)%8][0], y+next[(i+7)%8][1], move+1, stack);

            if(result == 1)
            {
                stack[move] = coordinateToIndex(x,y);
                return 1;
            }

            else
            {
                visited[x][y] = 0;
                return 0;
            }
        }

        return 0;
    }
}

int main(int argc, char** argv)
{
    int i, j;
    int k, l;
    size = 5;
    maxMoves = size*size-1;
    int solutionStack[maxMoves];

    for(i = 0; i < maxMoves; i++)
    {
        solutionStack[i] = 0;   //initialize stack
    }

    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){


            findTours(i, j, 0, solutionStack);

            //reset visited matrix
            for(k = 0; k < size; k ++){
                for(l = 0; l < size; l++){
                    visited[k][l] = 0;
                }
            }

        }
    }

    return 0;
}
