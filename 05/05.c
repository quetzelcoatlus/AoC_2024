#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 10000

int find_low(int x, int* tab, int n){
    for(int i=0;i<n;i++) if(tab[i]==x) return i;
    return -1;
}

int find_high(int x, int* tab, int n){
    for(int i=0;i<n;i++) if(tab[i]==x) return i;
    return BIG_N;
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");

    int sum=0,rules[BIG_N][2],n=0,pages[BIG_N],m=0,good,l,h;
    char c, buff[BIG_N];

    while(fscanf(f,"%d|%d",&rules[n][0],&rules[n][1]) == 2) n++;

    // Putting last integer back into file buffer xD
    sprintf(buff,"%d", rules[n][0]);
    for (int i=(int)strlen(buff)-1; i>= 0; i--) ungetc(buff[i], f);

    while(fscanf(f,"%d%c",&pages[m++],&c) == 2){
        while(fscanf(f,"%d%c",&pages[m++],&c) == 2 && c == ',');

        good=1;
        for(int i=0; i<n; i++){
            l=find_low(rules[i][0],pages,m);
            h=find_high(rules[i][1],pages,m);
            if(l>h) {
                good=0;
                break;
            }
        }

        if(good) sum += pages[m/2];

        m=0;
    }

    printf("%d\n",sum);

    fclose(f);
    return 0;
}
