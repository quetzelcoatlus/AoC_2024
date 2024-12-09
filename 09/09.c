#include <stdio.h>
#include <stdlib.h>

#define BIG_N 1<<18

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");

    int c, tab[BIG_N]={-1},p=0,q=0,file=1,id,l,r;
    long int sum=0;

    while((c=fgetc(f)) != EOF){
        id = file == 1 ? p++ : -1;
        for(int i = '0'; i<c; i++)
            tab[q++]=id;
        file = (file+1)%2;
    }

    l=0;
    r=q-1;
    while(l<r){
        if(tab[l] == -1)
            tab[l]=tab[r--];
        while(tab[r] == -1) r--;
        l++;
    }

    for(int i=0; i<=r; i++)
        sum+=i*tab[i];

    printf("%ld\n",sum);

    fclose(f);

    return 0;
}
