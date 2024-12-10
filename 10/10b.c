#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 1024

char tab[BIG_N][BIG_N];
int n=-1,m;

int find_trails(int i, int j){
    if(tab[i][j] == '9')
        return 1;

    int sum=0;

    for(int x=-1; x<=1; x++)
        for(int y=-1; y<=1; y++)
            if(abs(x+y)==1)
                if(tab[i+x][j+y] == tab[i][j]+1 && i+x>=0 && j+y>=0 && i<n && j<m)
                    sum += find_trails(i+x,j+y);

    return sum;
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");

    int sum=0;

    while(fscanf(f,"%s",(char *)&tab[++n]) > 0);

    m=strlen(tab[0]);

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(tab[i][j] == '0')
                sum += find_trails(i,j);

    printf("%d\n",sum);

    fclose(f);
    return 0;
}
