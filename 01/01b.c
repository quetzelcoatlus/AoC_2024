#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int a[2000],b[2000],n,sum,c;
    char* name = argc > 1 ? argv[1] : "input";

    n=0,sum=0;
    FILE* f = fopen(name,"r");
    while(fscanf(f,"%d %d", &a[n], &b[n])==2) n++;

    for(int i=0; i<n; i++){
        c=0;
        for(int j=0; j<n; j++){
            if(a[i]==b[j])c++;
        }
        sum+=a[i]*c;
    }

    printf("%d\n",sum);

    return 0;
}
