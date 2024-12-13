#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int sum=0, a,b,c,d,e,f,x,y,denominator;

    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");
    while(fscanf(fp,"Button A: X+%d, Y+%d\n",&a,&d) == 2){
        fscanf(fp,"Button B: X+%d, Y+%d\n",&b,&e);
        fscanf(fp,"Prize: X=%d, Y=%d\n",&c, &f);

        denominator = (a * e - b * d);
        x = (c * e - b * f) / denominator;
        y = (a * f - c * d) / denominator;

        if(x>=0 && y>=0 && x<=100 && y<=100 && a*x+b*y == c && d*x+e*y == f)
            sum+=3*x+y;
    }
    fclose(fp);

    printf("%d\n",sum);

    return 0;
}
