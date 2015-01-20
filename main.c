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

int searchForMove(int x, int y, int move)
{
    if( (x < 0) || (x >= size) || (y < 0) || (y >= size) )
        return 0;        //coordinate out of bounds

    if( visited[x][y] == 1)
        return 0;       //node already visited

    if(move == maxMoves)
    {
        //successful solution
        visited[x][y] = 1;  //mark node
        printf("solution found\n");
        printf("%d, ", coordinateToIndex(x,y));
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
            result |= searchForMove( x+next[i][1], y+next[i][2], move+1);
            result |= searchForMove( x+next[(i+1)%8][1], y+next[(i+1)%8][2], move+1);
            result |= searchForMove( x+next[(i+2)%8][1], y+next[(i+2)%8][2], move+1);
            result |= searchForMove( x+next[(i+3)%8][1], y+next[(i+3)%8][2], move+1);
            result |= searchForMove( x+next[(i+4)%8][1], y+next[(i+4)%8][2], move+1);
            result |= searchForMove( x+next[(i+5)%8][1], y+next[(i+5)%8][2], move+1);
            result |= searchForMove( x+next[(i+6)%8][1], y+next[(i+6)%8][2], move+1);
            result |= searchForMove( x+next[(i+7)%8][1], y+next[(i+7)%8][2], move+1);

            if(result == 1)
            {
                printf("%d, ", coordinateToIndex(x,y));
                return 1;
            }
            else
            {
                visited[x][y] = 0;
                return 0;
            }
        }
    }
}

int main(int argc, char** argv)
{
    int i, j;
    int height, width;

    size = 5;
    maxMoves = size*size;

    if( argc == 3 && ( (height = atoi(argv[1])) > 0 ) && ( (width = atoi(argv[2])) > 0 ) )
    {
        for( i = 0; i < height; i++ )
        {
            for(j = 0; j < width; j++ )
            {
                printf("*----------------------------------*\n");
                printf("*----------      %d      ----------*\n", coordinateToIndex(i,j) );
                printf("*----------------------------------*\n");
                printf("\n\n");

                searchForMove(i,j,1);

                printf("Found %d Tours"/*, TODO*/,1);
                printf("\n\n");
            }
        }

    }

    else
    {   //sytax error
        printf("Syntax Error: Run - KnightsTour <positive integer board height> <positive integer board width>\n\n");
        return 1;
    }

    return 0;
}

