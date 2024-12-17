#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 1024
#define MAX 1<<30

char tab[BIG_N][BIG_N], bool[BIG_N][BIG_N] = {0};
int n=0,m, costs[BIG_N][BIG_N][4],sx,sy;

int turns[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} };
int turn_cost[4] = {0 , 1000, 2000, 1000};

void count_path(int x, int y, int turn, int cost){
    for (int i = 0; i < 4; i++) {
        if (i == 2) continue;

        int tx_x = turns[(turn + i) % 4][0];
        int tx_y = turns[(turn + i) % 4][1];

        if(tab[y + tx_y][x + tx_x] == '.'){
            int new_cost = cost + 1 + turn_cost[i];
            if (new_cost < costs[y + tx_y][x + tx_x][(turn + i) % 4]) {
                costs[y + tx_y][x + tx_x][(turn + i) % 4] = new_cost;
                count_path(x + tx_x, y + tx_y, (turn + i) % 4, new_cost);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    int ex,ey;

    while(fscanf(fp,"%s",tab[n]) == 1) n++;
    m=strlen(tab[0]);
    fclose(fp);

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int k=0;k<4;k++) costs[i][j][k]=MAX;
            if(tab[i][j] == 'S'){ sx=j; sy=i; tab[i][j] = '.'; }
            if(tab[i][j] == 'E'){ ex=j; ey=i; tab[i][j] = '.'; }
        }
    }

    count_path(sx,sy,2,0);

    int min = MAX;
    for (int i=0; i<4; i++)
        if (costs[ey][ex][i] < min)
            min = costs[ey][ex][i];

    printf("%d\n",min);

    return 0;
}
