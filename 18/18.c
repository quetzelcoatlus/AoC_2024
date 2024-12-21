#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 1024
#define MAX 1<<30

#define SIZE 71
char tab[SIZE][SIZE];
int costs[SIZE][SIZE];

int turns[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} };

void count_path(int x, int y){
    for (int i=0; i<4; i++) {

        int x2 = x + turns[i][0];
        int y2 = y + turns[i][1];

        if(x2 >= 0 && y2 >= 0 && x2 < SIZE && y2 < SIZE && tab[x2][y2] != '#' && costs[x][y] + 1 < costs[x2][y2]){
            costs[x2][y2] = costs[x][y] + 1;
            count_path(x2, y2);
        }
    }
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    int x,y,n=0;

    while(fscanf(fp,"%d,%d\n",&x,&y) == 2){
        if(n < LIMIT) tab[x][y]='#';
        n++;
    }
    fclose(fp);

    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            costs[i][j]=MAX;

    costs[0][0]=0;
    count_path(0,0);

    printf("%d\n",costs[SIZE-1][SIZE-1]);

    return 0;
}