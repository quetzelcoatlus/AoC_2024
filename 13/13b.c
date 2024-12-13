#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    long long int sum=0, a,b,c,d,e,f,x,y,denominator;

    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");
    while(fscanf(fp,"Button A: X+%lld, Y+%lld\n",&a,&d) == 2){
        fscanf(fp,"Button B: X+%lld, Y+%lld\n",&b,&e);
        fscanf(fp,"Prize: X=%lld, Y=%lld\n",&c, &f);

        c+=10000000000000LL;
        f+=10000000000000LL;

        denominator = (a * e - b * d);
        x = (c * e - b * f) / denominator;
        y = (a * f - c * d) / denominator;

        if(x>=0 && y>=0 && a*x+b*y == c && d*x+e*y == f)
            sum+=3*x+y;
    }
    fclose(fp);

    printf("%lld\n",sum);

    return 0;
}
