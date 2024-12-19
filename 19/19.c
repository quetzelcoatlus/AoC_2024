#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 1024
#define SMALL_N 32

char patterns[BIG_N][SMALL_N],filtered[BIG_N][SMALL_N];
int n=0,f=0;

char* sstarts(char* string, const char* start){
    int i=0;
    for( ; start[i] != '\0'; i++)
        if(string[i] != start[i])
            return NULL;

    return string+i;
}

int check_string(char *string, char tab[BIG_N][SMALL_N], int n, int ignore){
    char *p;
    for(int i=0; i<n; i++)
        if(i == ignore || (p=sstarts(string,tab[i])) == NULL)
            continue;
        else if(*p == '\0' || check_string(p,tab,n,ignore))
            return 1;

    return 0;
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    char c;
    while(fscanf(fp,"%s%c\n",patterns[n],&c) == 2){
        n++;
        if(c == '\n') break;
        patterns[n-1][strlen(patterns[n-1])-1] = '\0';
    }

    for(int i=0;i<n;i++)
        if(!check_string(patterns[i],patterns,n,i))
            strcpy(filtered[f++], patterns[i]);

    char buff[BIG_N];
    int sum=0;
    while(fscanf(fp,"%s",buff) == 1)
        if(check_string(buff,filtered,f,BIG_N))
            sum++;

    fclose(fp);

    printf("%d\n",sum);

    return 0;
}
