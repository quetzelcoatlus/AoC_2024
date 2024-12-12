#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 1024

char tab[BIG_N][BIG_N], been[BIG_N][BIG_N];
int n=-1,m;

int vec[4][2] = { {-1, 0}, { 0,-1}, { 1, 0}, { 0, 1} };

void calculate(int i, int j, int* area, int* perimeter){
    been[i][j] = 1;
    (*area)++;

    for(int k=0;k<4;k++){
        int i2=i+vec[k][0], j2=j+vec[k][1];
        if(i2<0 || j2<0 || i2==n || j2==m || tab[i2][j2] != tab[i][j]){
            (*perimeter)++;
        } else if(!been[i2][j2]){
            calculate(i2,j2,area,perimeter);
        }
    }
}

int main(int argc, char* argv[]) {
    int sum=0, area, perimeter;

    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");
    while(fscanf(f,"%s",(char *)&tab[++n]) > 0);
    fclose(f);

    m=strlen(tab[0]);

    memset(been, 0, sizeof(been));

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!been[i][j]){
                area=perimeter=0;
                calculate(i,j,&area,&perimeter);
                sum += area * perimeter;
            }
        }
    }

    printf("%d\n",sum);

    return 0;
}
