#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 1024

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");

    char tab[BIG_N][BIG_N], bool[BIG_N][BIG_N]={0}, *tmp;
    int n=-1,sum=0,m,x,y;
    int vecx[]={0,1,0,-1},vecy[]={-1,0,1,0},veci=0;

    while(fscanf(f,"%s",(char *)&tab[++n]) > 0){
        if((tmp=strchr(tab[n], '^'))){
            y=n;
            x=tmp-tab[n];
        }
    }

    m=strlen(tab[0]);

    while(x>=0 && y>=0 && x<m && y<n){
        if(!bool[y][x]){
            bool[y][x]=1;
            sum++;
        }
        //if next square is blocked, turn right (change vector)
        if(tab[y+vecy[veci]][x+vecx[veci]] == '#') veci=(veci+1) % 4;
        x+=vecx[veci];
        y+=vecy[veci];
    }

    printf("%d\n",sum);

    fclose(f);
    return 0;
}
