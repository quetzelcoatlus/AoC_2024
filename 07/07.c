#include <stdio.h>
#include <stdlib.h>

int check_operators(long int value, long int *a, long int expr, int i, int n){
    if(i == n) return expr == value ? 1 : 0;

    return check_operators(value,a,expr+a[i],i+1,n) + check_operators(value,a,expr*a[i],i+1,n);
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";

    char *str = NULL;
    size_t size = 0;

    FILE* f = fopen(name,"r");

    int n;
    long int value, a[15], sum=0;

    while(getline(&str, &size, f) != -1){
        n=sscanf(str,"%ld: %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld\n",
            &value,&a[0],&a[1],&a[2],&a[3],&a[4],&a[5],&a[6],&a[7],&a[8],&a[9],&a[10],&a[11],&a[12],&a[13],&a[14]);

        if(check_operators(value,a,a[0],1,n-1))
            sum+=value;
    }

    printf("%ld\n",sum);

    free(str);
    fclose(f);

    return 0;
}
