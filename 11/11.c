#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BIG_N 500000
#define BLINKS 25

int main(int argc, char* argv[]) {

    long long int tab[2][BIG_N];
    int n=-1, m, t=0, digits, div;

    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");
    while(fscanf(f,"%lld",&tab[t][++n]) > 0);
    fclose(f);

    for(int i=0; i<BLINKS; i++){
        m=0;
        for(int j=0; j<n; j++){
            if(tab[t][j] == 0){
                tab[(t+1)%2][m++] = 1;
            } else {
                digits=(int)log10(tab[t][j]) + 1;
                if(digits % 2 == 0){
                    div=(int)pow(10, digits/2);
                    tab[(t+1)%2][m++] = tab[t][j]/div;
                    tab[(t+1)%2][m++] = tab[t][j]%div;
                } else {
                    tab[(t+1)%2][m++] = tab[t][j]*2024;
                }
            }
        }
        n=m;
        t=(t+1)%2;
    }

    printf("%d\n",n);

    return 0;
}
