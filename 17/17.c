#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROGRAMS 64

#define combo(x) ((x) < 4 ? (x) : ((x) == 4 ? A : ((x) == 5 ? B : C)))

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    int A,B,C,p[MAX_PROGRAMS],n=0;

    fscanf(fp,"Register A: %d\n Register B: %d\n Register C: %d\n\nProgram: ", &A, &B, &C);
    while(fscanf(fp,"%d,",&p[n]) == 1) n++;
    fclose(fp);

    int i=0,first=0;
    while(i<n){
        switch(p[i]){
            case 0: A = A >> combo(p[i+1]); break;
            case 1: B ^= p[i+1]; break;
            case 2: B = combo(p[i+1]) % 8; break;
            case 3: if(A != 0) i = p[i+1]-2; break;
            case 4: B ^= C; break;
            case 5: printf("%c%d", ((first++ == 0) ? '\0' : ','), combo(p[i+1]) % 8); break;
            case 6: B = A >> combo(p[i+1]); break;
            case 7: C = A >> combo(p[i+1]); break;
        }

        i+=2;
    }

    printf("\n");

    return 0;
}
