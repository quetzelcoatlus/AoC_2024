#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 1024

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");

    char tab[BIG_N][BIG_N], bool[BIG_N][BIG_N]={0};
    int n=-1,sum=0,m,y,x;

    while(fscanf(f,"%s",(char *)&tab[++n]) > 0);

    m=strlen(tab[0]);

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(tab[i][j] != '.'){
                for(int k=0;k<n;k++){
                    for(int l=0;l<m;l++){
                        if(tab[k][l] == tab[i][j] && (i!=k || j!=l)){
                            y=i-2*(i-k);
                            x=j-2*(j-l);
                            if(y>=0 && y<n && x>=0 && x<m && !bool[y][x]){
                                bool[y][x]=1;
                                sum++;
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%d\n",sum);

    fclose(f);
    return 0;
}
