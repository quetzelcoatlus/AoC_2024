#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRETS_NO 2000

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    long long secret,tmp,sum=0;
    while(fscanf(fp,"%lld",&secret) == 1){
        for(int i=0;i<SECRETS_NO;i++){
            tmp = ((secret<<6) ^ secret) % 16777216;
            tmp = ((tmp>>5) ^ tmp ) % 16777216;
            tmp = ((tmp<<11) ^ tmp ) % 16777216;

            secret=tmp;
        }
        sum+=secret;
    }

    fclose(fp);

    printf("%lld\n",sum);

    return 0;
}
