#include <stdio.h>
#include <stdlib.h>

#define WIDTH 101
#define HEIGHT 103
#define SECONDS 100

int positive_mod(int x, int m){
    return x % m < 0 ? x % m + m : x % m;
}

int main(int argc, char* argv[]) {
    int px, py, vx, vy, count[2][2] = {0};

    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");
    while(fscanf(fp,"p=%d,%d v=%d,%d\n",&px,&py,&vx,&vy)==4){
        px=positive_mod((px + vx * SECONDS),WIDTH);
        py=positive_mod((py + vy * SECONDS),HEIGHT);
        if(px != WIDTH/2 && py != HEIGHT/2)
            count[px / (WIDTH/2+1)][py / (HEIGHT/2+1)]++;
    }
    fclose(fp);

    printf("%d\n",count[0][0]*count[0][1]*count[1][0]*count[1][1]);

    return 0;
}
