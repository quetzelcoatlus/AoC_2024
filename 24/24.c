#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#define BIG_N 1024
#define SMALL_N 16

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    hcreate(BIG_N);
    char buff[SMALL_N], cache[BIG_N][SMALL_N], values[BIG_N];
    int n=0,d;
    while(fscanf(fp,"%s %d",buff,&d) == 2){
        buff[(int)strlen(buff)-1]='\0';

        strcpy(cache[n],buff);
        values[n]=d;
        ENTRY entry = {.key = cache[n], .data=&values[n]};
        hsearch(entry, ENTER);
        n++;
    }

    char gates[BIG_N][4][SMALL_N];
    int g=0;
    strcpy(gates[g][0], buff);
    fscanf(fp,"%s %s -> %s",gates[g][1],gates[g][2],gates[g][3]);
    g++;
    while (fscanf(fp,"%s %s %s -> %s",gates[g][0],gates[g][1],gates[g][2],gates[g][3]) == 4) g++;
    fclose(fp);

    int gleft=g;
    while(gleft){ // go over list of expressions over and over resolving what we can
        for(int i=0;i<g;i++){
            ENTRY entry = {.key = gates[i][3]} , *found_entry1, *found_entry2;
            if((found_entry1=hsearch(entry, FIND)) != NULL)
                continue;

            entry.key = gates[i][0];
            if((found_entry1=hsearch(entry, FIND)) != NULL){
                entry.key = gates[i][2];
                if((found_entry2=hsearch(entry, FIND)) != NULL){
                    char x1 = *( (char *) found_entry1->data);
                    char x2 = *( (char *) found_entry2->data);

                    if(!strcmp(gates[i][1],"AND")) values[n] = x1 & x2;
                    if(!strcmp(gates[i][1],"OR")) values[n] = x1 | x2;
                    if(!strcmp(gates[i][1],"XOR")) values[n] = x1 ^ x2;

                    strcpy(cache[n],gates[i][3]);
                    ENTRY entry = {.key = cache[n], .data=&values[n]};
                    hsearch(entry, ENTER);
                    n++;
                    gleft--;
                }
            }
        }
    }


    int i=0;
    ENTRY entry,*found_entry;
    sprintf(buff,"z%02d",i);
    entry.key=buff;

    long long result=0;
    while((found_entry=hsearch(entry, FIND)) != NULL){
        long long bit = *( (char *) found_entry->data);
        result += (bit << i);
        sprintf(buff,"z%02d",++i);
    }
    hdestroy();

    printf("%lld\n",result);

    return 0;
}
