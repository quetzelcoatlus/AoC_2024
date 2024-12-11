#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BIG_N 500000
#define BLINKS 75

long int tab[BIG_N][3];
int n=0;

long int count(long int value, int blinks){
    if(blinks == 0) return 1;

    for(int i=0;i<n;i++)
        if(tab[i][0] == value && tab[i][1] == blinks)
            return tab[i][2];

    long int result;
    if(value == 0){
        result=count(1,blinks-1);
    } else {
        long int digits=(int)log10(value) + 1;
        if(digits % 2 == 0){
            long int div=(int)pow(10, digits/2);
            result=count(value/div,blinks-1);
            result+=count(value%div,blinks-1);
        } else {
            result=count(value*2024,blinks-1);
        }
    }

    tab[n][0]=value;
    tab[n][1]=blinks;
    tab[n++][2]=result;
    return result;
}

int main(int argc, char* argv[]) {

    long int sum=0, d;

    for(int i=0;i<BIG_N;i++)
        for(int k=0;k<3;k++)
            tab[i][k] = -1;

    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");
    while(fscanf(f,"%ld",&d) > 0) sum+=count(d,BLINKS);
    fclose(f);

    printf("%ld\n",sum);

    return 0;
}
