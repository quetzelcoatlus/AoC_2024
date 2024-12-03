#include <stdio.h>
#include <stdlib.h>

#define BIG_N 1024

int main(int argc, char* argv[])
{
    int a[BIG_N],b[BIG_N],n,sum,c;

    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");

    n=0,sum=0;
    while(fscanf(f,"%d %d", &a[n], &b[n])==2) n++;

    for(int i=0; i<n; i++){
        c=0;
        for(int j=0; j<n; j++){
            if(a[i]==b[j])c++;
        }
        sum+=a[i]*c;
    }

    printf("%d\n",sum);

    fclose(f);

    return 0;
}
