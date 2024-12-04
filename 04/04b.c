#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 1024

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");

    char tab[BIG_N][BIG_N];
    int n=-1,sum=0,m,good;

    while(fscanf(f,"%s",(char *)&tab[++n]) > 0);
    m=strlen(tab[0]);

    for(int i=1;i<n-1;i++){
        for(int j=1;j<m-1;j++){
            if(tab[i][j]== 'A'){
                good=1;
                if((!(tab[i-1][j-1] == 'M') || !(tab[i+1][j+1] == 'S')) && (!(tab[i-1][j-1] == 'S') || !(tab[i+1][j+1] == 'M'))) good=0;
                if((!(tab[i-1][j+1] == 'M') || !(tab[i+1][j-1] == 'S')) && (!(tab[i-1][j+1] == 'S') || !(tab[i+1][j-1] == 'M'))) good=0;
                sum+=good;
            }
        }
    }

    printf("%d\n",sum);

    fclose(f);
    return 0;
}
