#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 1024

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");

    char tab[BIG_N][BIG_N], loop[BIG_N][BIG_N], *tmp;
    int n=-1,sum=0,m,x,y;
    int vecx[]={0,1,0,-1},vecy[]={-1,0,1,0},veci=0;
    int tmpx, tmpy;

    while(fscanf(f,"%s",(char *)&tab[++n]) > 0){
        if((tmp=strchr(tab[n], '^'))){
            y=n;
            x=tmp-tab[n];
        }
    }

    m=strlen(tab[0]);
    tmpx=x;
    tmpy=y;

    // Just bruteforce - check every square where obstacle can be put and see if it loops ;/
    for(int xx=0; xx<m; xx++){
        for(int yy=0; yy<n; yy++){
            if(tab[yy][xx] == '#' || tab[yy][xx] == '^')
                continue;

            tab[yy][xx] = '#';
            memset(loop, 0, sizeof(loop));

            while(x>=0 && y>=0 && x<m && y<n){
                // Keep turning until you can move forward
                while(tab[y+vecy[veci]][x+vecx[veci]] == '#') veci=(veci+1) % 4;

                // Check if we were in this place with same movement vector - bit comparision trick
                if(loop[y][x] & (1<<veci)){
                    sum++;
                    break;
                } else {
                    loop[y][x] |= (1<<veci);
                }

                // Move
                x+=vecx[veci];
                y+=vecy[veci];

            }
            // Restore default state
            tab[yy][xx] = '.';
            x=tmpx;
            y=tmpy;
            veci=0;
        }
    }

    printf("%d\n",sum);

    fclose(f);
    return 0;
}
