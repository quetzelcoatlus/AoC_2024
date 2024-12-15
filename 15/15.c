#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 1024

char tab[BIG_N][BIG_N];
int n=-1,m=0,x,y;

void move(char c){
    int vecx,vecy;
    switch(c){
        case '<': vecx = -1; vecy =  0; break;
        case '^': vecx =  0; vecy = -1; break;
        case '>': vecx =  1; vecy =  0; break;
        case 'v': vecx =  0; vecy =  1; break;
    }

    int tmpy = y+vecy, tmpx = x+vecx;
    while(tab[tmpy][tmpx] == 'O'){
        tmpy+=vecy;
        tmpx+=vecx;
    }

    if(tab[tmpy][tmpx] == '#') return;

    while(tmpy != y || tmpx != x){
        tab[tmpy][tmpx] = tab[tmpy-vecy][tmpx-vecx];
        tmpy=tmpy-vecy;
        tmpx=tmpx-vecx;
    }
    y+=vecy;
    x+=vecx;
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    int sum=0;

    char *p;
    while(fscanf(fp,"%s",tab[m]) == 1){
        if((p=strchr(tab[m], '@'))){
            x=p-tab[m];
            y=m;
        }
        if(strchr(tab[m], '<') && n == -1)
            n=m;

        m++;
    }
    fclose(fp);

    for(int i=n;i<m;i++)
        for(int j=0;j<(int)strlen(tab[i]);j++)
            move(tab[i][j]);

    for(int i=0;i<n;i++)
        for(int j=0;j<(int)strlen(tab[i]);j++)
            if(tab[i][j] == 'O') sum+=100*i+j;

    printf("%d\n",sum);

    return 0;
}
