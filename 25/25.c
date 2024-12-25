#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEIGHT 7
#define WIDTH 5

#define BIG_N 1024
#define SMALL_N 8

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    char locks[BIG_N][WIDTH] = {0}, keys[BIG_N][WIDTH] = {0}, buff[SMALL_N],lock;
    int l=0,k=0;

    while(fscanf(fp,"%s",buff) == 1){
        if(*buff == '#') lock=1; else lock=0;

        for(int i=0;i<HEIGHT-1;i++){
            fscanf(fp,"%s",buff);
            if(i==5 && lock == 0) break;
            for(int j=0;j<WIDTH;j++){
                if(buff[j] == '#'){
                    if(lock==1) locks[l][j]++; else keys[k][j]++;
                }
            }
        }
        if(lock==1) l++; else k++;
    }

    fclose(fp);

    int sum=0;
    for(int i=0;i<l;i++){
        for(int j=0;j<k;j++){
            int good=1;
            for(int c=0;c<WIDTH;c++){
                if(locks[i][c]+keys[j][c] > 5){
                    good=0;
                    break;
                }
            }
            if(good) sum++;
        }
    }

    printf("%d\n",sum);

    return 0;
}
