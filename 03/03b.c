#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 10000

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");

    int a,b,sum=0,dont=0;
    char *tmp, *tmp2, buff[BIG_N], c;

    while(fscanf(f,"%s",(char*)&buff) > 0) {
        tmp=buff;
        while((tmp2=strstr(tmp,"mul(")) != NULL){
            if(strstr(tmp,"don't()") && strstr(tmp,"don't()")<tmp2){
                dont=1;
                tmp2=tmp=strstr(tmp,"don't()");
            }
            if(strstr(tmp,"do()") && strstr(tmp,"do()")<tmp2){
                dont=0;
                tmp2=tmp=strstr(tmp,"do()");
            }

            if(sscanf(tmp2,"mul(%d,%d%c",&a,&b,&c) == 3){
                if(c == ')' && !dont){
                    sum+=a*b;
                }
            }
            tmp=tmp2+1;
        }
        while(strstr(tmp,"don't()")){
            dont=1;
            tmp=strstr(tmp,"don't()")+1;
        }
        while(strstr(tmp,"do()")){
            dont=0;
            tmp=strstr(tmp,"do()")+1;
        }
    }

    printf("%d\n",sum);

    fclose(f);
    return 0;
}
