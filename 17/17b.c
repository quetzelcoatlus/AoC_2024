#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define combo(x) ((x) < 4 ? (x) : ((x) == 4 ? A : ((x) == 5 ? B : C)))

#define MAX_PROGRAMS 64
int p[MAX_PROGRAMS],n=0;

int run_program(long long A, int index){
    int i=0;
    long long B=0,C=0;
    while(i<n){
        switch(p[i]){
            case 0: A = A >> combo(p[i+1]); break;
            case 1: B ^= p[i+1]; break;
            case 2: B = combo(p[i+1]) % 8; break;
            case 3: if(A != 0) i = p[i+1]-2; break;
            case 4: B ^= C; break;
            case 5: if(combo(p[i+1]) % 8 != p[index]) return 0; index++; break;
            case 6: B = A >> combo(p[i+1]); break;
            case 7: C = A >> combo(p[i+1]); break;
        }

        i+=2;
    }
    return (index == n);
}

long long solve(long long A, int index){
    long long sum=0;

    for(int i=0; i<8; i++){
        long long AA = (A<<3) + i;
        if(!run_program(AA, index))
            continue;

        if(index == 0)
            return AA;

        sum+=solve(AA, index-1);
    }
    return sum;
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    int trash;

    fscanf(fp,"Register A: %d\n Register B: %d\n Register C: %d\n\nProgram: ", &trash, &trash, &trash);
    while(fscanf(fp,"%d,",&p[n]) == 1) n++;
    fclose(fp);

    printf("%lld\n", solve(0,n-1));

    return 0;
}
