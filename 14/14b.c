#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 101
#define HEIGHT 103
#define BIG_N 1024

int px[BIG_N],vx[BIG_N],py[BIG_N],vy[BIG_N];
int n=0;

int positive_mod(int x, int m){
    return x % m < 0 ? x % m + m : x % m;
}

int distance(int x1, int y1, int x2, int y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

int get_mean_dist() {
    int sum = 0;

    for (int i=0; i<n-1; i++)
        sum += distance(px[i],py[i],px[i+1],py[i+1]);

    return sum / n;
}

int main(int argc, char* argv[]) {
    int seconds=0;
    int dist1, dist2;

    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");
    while(fscanf(fp,"p=%d,%d v=%d,%d\n",&px[n],&py[n],&vx[n],&vy[n])==4) n++;
    fclose(fp);

    dist2 = get_mean_dist();

    do{
        dist1 = dist2;
        seconds++;
        for(int i=0; i<n; i++){
            px[i]=positive_mod((px[i] + vx[i]),WIDTH);
            py[i]=positive_mod((py[i] + vy[i]),HEIGHT);
        }
        dist2=get_mean_dist();
    } while(dist2 > dist1 / 2);

    if(argc > 2){
        int bool[WIDTH][HEIGHT] = {0};
        for(int i=0; i<n; i++) bool[px[i]][py[i]]=1;
        for(int j=0; j<HEIGHT; j++){
            for(int i=0;i<WIDTH;i++){
                if(bool[i][j] == 1) printf("#");
                else printf(".");
            }
            printf("\n");
        }
    }

    printf("%d\n", seconds);

    return 0;
}
