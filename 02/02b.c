#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int sum=0,n,k,asc,good;
    char* name = argc > 1 ? argv[1] : "input";

    char *str = NULL;
    size_t size = 0;

    FILE* f = fopen(name,"r");

    int a[20],b[20];

    while(getline(&str, &size, f) != -1){
        n=sscanf(str,"%d %d %d %d %d %d %d %d %d %d\n", &a[0],&a[1],&a[2],&a[3],&a[4],&a[5],&a[6],&a[7],&a[8],&a[9]);

        for(int i=0; i<n; i++){
            k=0;
            for(int j=0;j<n;j++) if(j!=i) b[k++]=a[j]; //ignoring one level

            asc = b[1]>b[0] ? 1 : 0;
            good=1;
            for(int j=0;j<n-2;j++){
                if(asc){
                    if(b[j+1]-b[j]<1 || b[j+1]-b[j] >3)
                        good=0;
                } else {
                    if(b[j]-b[j+1] <1 || b[j]-b[j+1] >3)
                        good=0;
                }
            }
            if(good){
                sum++;
                break;
            }


        }
    }

    printf("%d\n",sum);

    free(str);
    fclose(f);

    return 0;
}
