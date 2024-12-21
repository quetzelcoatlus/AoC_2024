#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

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

        if(x2 >= 0 && y2 >= 0 && x2 < m && y2 < n && tab[y2][x2] != '#' && costs[y][x] + 1 < costs[y2][x2]){
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

    int sx,sy;

    while(fscanf(fp,"%s",tab[n]) == 1) n++;
    fclose(fp);
    m=strlen(tab[0]);

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(tab[i][j] == 'S') { sy=i; sx=j; }
            costs[i][j]=MAX;
        }
    }

    costs[sy][sx]=0;
    count_path(sx,sy);

    int d,sum=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(tab[i][j] != '#')
                for(int k=0;k<n;k++)
                    for(int l=0;l<m;l++)
                        if(tab[k][l] != '#' && (d=distance(i,j,k,l)) <= MAX_CHEATS && costs[k][l] - costs[i][j] - d >= MIN_SAVED_COST)
                            sum++;

    printf("%d\n",sum);

    return 0;
}
