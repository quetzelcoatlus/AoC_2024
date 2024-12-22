#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRETS_NO 2000

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    long long secret,tmp,lastd;
    int sums[19][19][19][19] = {0};
    while(fscanf(fp,"%lld",&secret) == 1){
        lastd = secret % 10;
        int a1=-1,a2=-1,a3=-1,a4=-1;
        char visited[19][19][19][19] = {0};

        for(int i=0;i<SECRETS_NO;i++){
            tmp = ((secret << 6) ^ secret) % 16777216;
            tmp = ((tmp >> 5) ^ tmp ) % 16777216;
            tmp = ((tmp << 11) ^ tmp ) % 16777216;

            a1=a2;
            a2=a3;
            a3=a4;
            a4=(tmp % 10) - lastd;
            if(a1!=-1){
                if(!visited[a1+9][a2+9][a3+9][a4+9]){
                    visited[a1+9][a2+9][a3+9][a4+9]=1;
                    sums[a1+9][a2+9][a3+9][a4+9]+=(tmp % 10);
                }
            }

            lastd = tmp % 10;
            secret = tmp;
        }
    }

    fclose(fp);
    int sum=0;

    for(int a1=-9;a1<=9;a1++)
        for(int a2=-9;a2<=9;a2++)
            for(int a3=-9;a3<=9;a3++)
                for(int a4=-9;a4<=9;a4++)
                    if(sums[a1+9][a2+9][a3+9][a4+9] > sum)
                        sum=sums[a1+9][a2+9][a3+9][a4+9];

    printf("%d\n",sum);

    return 0;
}
