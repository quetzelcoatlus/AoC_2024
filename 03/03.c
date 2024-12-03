#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 10000

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");

    int a,b,sum=0;
    char *tmp, *tmp2, buff[BIG_N], c;

    while(fscanf(f,"%s",(char *)&buff) > 0) {
        tmp=buff;
        while((tmp2=strstr(tmp,"mul(")) != NULL){
            if(sscanf(tmp2,"mul(%d,%d%c",&a,&b,&c) == 3){
                if(c == ')'){
                    sum+=a*b;
                }
            }
            tmp=tmp2+1;
        }
    }
    printf("%d\n",sum);

    fclose(f);
    return 0;
}
