#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 1024

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");

    char tab[BIG_N][BIG_N], bool[BIG_N][BIG_N]={0};
    int n=-1,sum=0,m,y,x,d;

    while(fscanf(f,"%s",(char *)&tab[++n]) > 0);

    m=strlen(tab[0]);

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(tab[i][j] != '.'){
                for(int k=0;k<n;k++){
                    for(int l=0;l<m;l++){
                        if(tab[k][l] == tab[i][j] && (i!=k || j!=l)){
                            d=1;
                            y=i-d*(i-k);
                            x=j-d*(j-l);

                            while(y>=0 && y<n && x>=0 && x<m){
                                if(!bool[y][x]){
                                    bool[y][x]=1;
                                    sum++;
                                }
                                d++;
                                y=i-d*(i-k);
                                x=j-d*(j-l);
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
