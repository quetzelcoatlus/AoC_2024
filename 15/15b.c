#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 1024

char tab[BIG_N][BIG_N];
int n=-1,m=0,rx,ry;

int can_move_vertically(int x, int y, int vecy){
    if(tab[y+vecy][x] == '#') return 1; // can't
    if(tab[y+vecy][x] == '.') return 0; // can

    return can_move_vertically(x,y+vecy,vecy) + can_move_vertically(x + (tab[y+vecy][x] == '[' ? 1 : -1),y+vecy,vecy);
}

void move_vertically(int x, int y, int vecy){
    if(tab[y+vecy][x] == '[' || tab[y+vecy][x] == ']'){
        move_vertically(x + (tab[y+vecy][x] == '[' ? 1 : -1),y+vecy,vecy);
        move_vertically(x,y+vecy,vecy);
    }
    tab[y+vecy][x]=tab[y][x];
    if(tab[y][x] == '@') ry=y+vecy;
    tab[y][x]='.';
}

void move(int x, int y, char c){
    int vecx,vecy,tmpx;
    switch(c){
        case '<': vecx = -1; vecy =  0; break;
        case '^': vecx =  0; vecy = -1; break;
        case '>': vecx =  1; vecy =  0; break;
        case 'v': vecx =  0; vecy =  1; break;
    }

    if(vecy==0){
        tmpx=x;
        while(tab[y][tmpx+vecx] == '[' || tab[y][tmpx+vecx] == ']') tmpx+=vecx;

        if(tab[y][tmpx+vecx] == '#') return;

        while(tmpx != x){
            tab[y][tmpx+vecx] = tab[y][tmpx];
            tmpx-=vecx;
        }
        tab[y][x+vecx] = tab[y][x];
        rx=x+vecx;
        tab[y][x]='.';
    } else {
        if(can_move_vertically(x,y,vecy) == 0)
            move_vertically(x,y,vecy);
    }
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    int sum=0,d;

    char buff[BIG_N];
    while(fscanf(fp,"%s",buff) == 1){
        if(strchr(buff, '<') && n == -1)
            n=m;

        if(n == -1){
            d=0;
            for(int i=0;i<(int)strlen(buff);i++){
                if(buff[i] == '@'){
                    rx=d;
                    ry=m;
                    tab[m][d++] = '@';
                    tab[m][d++] = '.';
                } else if(buff[i] == 'O'){
                    tab[m][d++] = '[';
                    tab[m][d++] = ']';
                } else {
                    tab[m][d++] = buff[i];
                    tab[m][d++] = buff[i];
                }
            }
            tab[m][d]='\0';
        } else {
            strcpy(tab[m], buff);
        }

        m++;
    }
    fclose(fp);

    for(int i=n;i<m;i++)
        for(int j=0;j<(int)strlen(tab[i]);j++)
            move(rx,ry,tab[i][j]);

    for(int i=0;i<n;i++){
        for(int j=0;j<(int)strlen(tab[i]);j++){
            if(tab[i][j] == '[') sum+=100*i+j;
            if(argc > 2) printf("%c",tab[i][j]);
        }
        if(argc > 2) printf("\n");
    }

    printf("%d\n",sum);

    return 0;
}
