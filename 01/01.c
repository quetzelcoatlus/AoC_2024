#include <stdio.h>
#include <stdlib.h>

#define BIG_N 1024

int comp (const void * elem1, const void * elem2)
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}
int main(int argc, char* argv[])
{
    int a[BIG_N],b[BIG_N],n=0,sum=0;

    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");

    while(fscanf(f,"%d %d", &a[n], &b[n])==2) n++;

    qsort (a, n, sizeof(*a), comp);
    qsort (b, n, sizeof(*a), comp);

    for(int i=0;i<n;i++) sum+=abs(a[i]-b[i]);

    printf("%d\n",sum);

    fclose(f);

    return 0;
}
