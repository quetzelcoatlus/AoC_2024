#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 1024

int in_range(int i, int n){
    return (i>=0 && i<n);
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");

    char tab[BIG_N][BIG_N];
    int n=-1,sum=0,m,good;

    int nvec[8][3]={{-1,-2,-3},{-1,-2,-3},{-1,-2,-3},{0,0,0},{1,2,3},{1,2,3},{1,2,3},{0,0,0}};
    int mvec[8][3]={{-1,-2,-3},{0,0,0},{1,2,3},{1,2,3},{1,2,3},{0,0,0},{-1,-2,-3},{-1,-2,-3}};
    char xmas[]="MAS";

    while(fscanf(f,"%s",(char *)&tab[++n]) > 0);
    m=strlen(tab[0]);

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(tab[i][j]== 'X'){
                for(int k=0; k<8; k++){
                    good=1;
                    for (int l=0; l<3;l++){
                        if(!in_range(i+nvec[k][l],n) || !in_range(j+mvec[k][l],m) || tab[i+nvec[k][l]][j+mvec[k][l]] != xmas[l])
                            good=0;
                    }
                    sum+=good;
                }
            }
        }
    }

    printf("%d\n",sum);

    fclose(f);
    return 0;
}
