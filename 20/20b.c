#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 256
#define MAX 1<<30

#define MAX_CHEATS 20
#define MIN_SAVED_COST 100

char tab[BIG_N][BIG_N];
int n=0, m, costs[BIG_N][BIG_N];

int turns[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} };

void count_path(int x, int y){
    for (int i=0; i<4; i++) {
        int x2 = x + turns[i][0];
        int y2 = y + turns[i][1];

        if(tab[y2][x2] != '#' && costs[y][x] + 1 < costs[y2][x2]){
            costs[y2][x2] = costs[y][x] + 1;
            count_path(x2, y2);
        }
    }
}

int distance(int x1, int y1, int x2, int y2){
    return abs(x1-x2)+abs(y1-y2);
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    int sx,sy,ex,ey;

    while(fscanf(fp,"%s",tab[n]) == 1) n++;
    fclose(fp);
    m=strlen(tab[0]);

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(tab[i][j] == 'S') { sy=i; sx=j; }
            if(tab[i][j] == 'E') { ey=i; ex=j; }
            costs[i][j]=MAX;
        }
    }

    costs[sy][sx]=0;
    count_path(sx,sy);

    int x=sx, y=sy;

    int sum=0,d;
    while(x != ex || y != ey){
        for (int i=-MAX_CHEATS; i<=MAX_CHEATS; i++){
            for (int j=-MAX_CHEATS; j<=MAX_CHEATS; j++){
                if((d=distance(x,y,x+i,y+j)) <= MAX_CHEATS && x+i >= 0 && y+j >= 0 && x+i < m && y+j < n &&
                    tab[y+j][x+i] != '#' && costs[y+j][x+i] - costs[y][x] - d >= MIN_SAVED_COST){

                    sum++;
                }
            }
        }

        for (int i=0; i<4; i++) {
            int x2 = x + turns[i][0];
            int y2 = y + turns[i][1];

            if(costs[y][x] + 1 == costs[y2][x2]){
                x=x2;
                y=y2;
                break;
            }
        }
    }

    printf("%d\n", sum);

    return 0;
}
