#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int sum=0,a,b,asc,good;
    char* name = argc > 1 ? argv[1] : "input";

    char *str = NULL, *tmp;
    size_t size = 0;

    FILE* f = fopen(name,"r");
    while(getline(&str, &size, f) != -1){
        tmp=str;
        sscanf(str,"%d %d",&a,&b);

        asc = b>a ? 1 : 0;
        if(asc){
            if(b-a>0 && b-a <4)
                good=1;
            else
                good=0;
        } else {
            if(a-b>0 && a-b <4)
                good=1;
            else
                good=0;
        }
        a=b;

        //shift string for 2 numbers
        while(*tmp >='0' && *tmp <= '9') tmp++;
        tmp++;
        while(*tmp >='0' && *tmp <= '9') tmp++;

        while(sscanf(tmp,"%d",&b) > 0){
            if(asc){
                if(b-a <1 || b-a >3)
                    good=0;
            } else {
                if(a-b <1 || a-b >3)
                    good=0;
            }
            a=b;
            tmp++;
            while(*tmp >='0' && *tmp <= '9') tmp++;
        }
        if(good) sum++;
    }

    printf("%d\n",sum);

    free(str);
    fclose(f);

    return 0;
}
