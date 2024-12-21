#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 256
#define MAX 1<<30

char tab[BIG_N][BIG_N];
int n=0, m, ex, ey, costs[BIG_N][BIG_N];

int turns[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} };

void count_path(int x, int y){
    for (int i=0; i<4; i++) {
        int x2 = x + turns[i][0];
        int y2 = y + turns[i][1];

        if(x2 >= 0 && y2 >= 0 && x2 < m && y2 < n && tab[y2][x2] != '#' && costs[y][x] + 1 < costs[y2][x2]){
            costs[y2][x2] = costs[y][x] + 1;
            count_path(x2, y2);
        }
    }
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    int sx,sy;

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

    int x=sx, y=sy, next_x,next_y;

    int sum=0;
    while(x!=ex || y!=ey){
        for (int i=0; i<4; i++) {
            int x2 = x + turns[i][0];
            int y2 = y + turns[i][1];

            if(x2 >= 0 && y2 >= 0 && x2 < m && y2 < n){
                if(costs[y][x] + 1 == costs[y2][x2]){
                    next_x=x2;
                    next_y=y2;
                } else if(tab[y2][x2] == '#'){
                    for (int j=0; j<4; j++) {
                        int x3 = x2 + turns[j][0];
                        int y3 = y2 + turns[j][1];
                        if(x3 >= 0 && y3 >= 0 && x3 < m && y3 < n && tab[y3][x3] != '#' && costs[y3][x3] - costs[y][x] - 2 >= 100){
                            sum++;
                        }
                    }
                }

            }
        }
        x=next_x;
        y=next_y;
    }

    printf("%d\n", sum);

    return 0;
}
