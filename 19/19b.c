#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#define BIGGER_N 32768
#define BIG_N 1024
#define SMALL_N 64

char patterns[BIG_N][SMALL_N],cache[BIGGER_N][SMALL_N];
long int counts[BIGGER_N];
int n=0,c=0;

char* sstarts(char* string, const char* start){
    int i=0;
    for( ; start[i] != '\0'; i++)
        if(string[i] != start[i])
            return NULL;

    return string+i;
}

long int check_string(char *string){
    ENTRY entry = {.key = string}, *found_entry;

    if((found_entry=hsearch(entry, FIND)) != NULL)
        return *( (long int *) found_entry->data);


    char *p;
    long int count=0;
    for(int i=0; i<n; i++){
        if((p=sstarts(string,patterns[i])) != NULL){
            if(*p == '\0')
                count++;
            else
                count += check_string(p);
        }
    }

    strcpy(cache[c], string);
    counts[c] = count;
    entry.key = cache[c];
    entry.data = &counts[c];
    if(hsearch(entry, ENTER) == NULL)
        fprintf(stderr,"hsearch ENTER failed for \"%s\"\n",cache[c]);
    c++;

    return count;
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

    hcreate(BIGGER_N);

    char buff[SMALL_N];
    long int sum=0;
    while(fscanf(fp,"%s",buff) == 1)
        sum+=check_string(buff);

    fclose(fp);
    hdestroy();

    printf("%ld\n",sum);

    return 0;
}
