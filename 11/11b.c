#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <search.h>
#include <string.h>

#define BIG_N 500000
#define STR_SIZE 32
#define BLINKS 75

char keys[BIG_N][STR_SIZE];
long int values[BIG_N];
int n=0;

long int count(long int value, int blinks){
    if(blinks == 0) return 1;

    char key[STR_SIZE];
    sprintf(key,"%ld-%d",value,blinks);
    ENTRY entry = {.key = key}, *found_entry;

    if((found_entry=hsearch(entry, FIND)) != NULL)
        return *( (long int *) found_entry->data);

    long int result;
    if(value == 0){
        result=count(1,blinks-1);
    } else {
        long int digits=(int)log10(value) + 1;
        if(digits % 2 == 0){
            long int div=(int)pow(10, digits/2);
            result=count(value/div,blinks-1);
            result+=count(value%div,blinks-1);
        } else {
            result=count(value*2024,blinks-1);
        }
    }

    strcpy(keys[n], key);
    values[n] = result;
    entry.key = keys[n];
    entry.data = &values[n];
    hsearch(entry, ENTER);
    n++;

    return result;
}

int main(int argc, char* argv[]) {
    long int sum=0, d;

    hcreate(BIG_N);

    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");
    while(fscanf(f,"%ld",&d) > 0) sum+=count(d,BLINKS);
    fclose(f);

    hdestroy();

    printf("%ld\n",sum);

    return 0;
}
