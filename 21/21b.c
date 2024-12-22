#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#define BIG_N 1024
#define SMALL_N 256
#define ROBOTS_NO 25

char nums[4][3] = {
    { '7' , '8', '9' },
    { '4' , '5', '6' },
    { '1' , '2', '3' },
    { 'X' , '0', 'A' }};

char num_pos[SMALL_N][2];

char directs[2][3] = {
    { 'X' , '^' , 'A' },
    { '<' , 'v' , '>' }};

char dir_pos[SMALL_N][2];

char cache[BIG_N][SMALL_N];
long long counts[BIG_N];
int c=0;

void resolve_numeric(char* input, char* output){
    int x=num_pos['A'][0], y=num_pos['A'][1], i=0;

    output[i++]='A'; //Part 2 specific - we start from A to walk over pairs
    while(*input){
        int nx=num_pos[(int)*input][0], ny=num_pos[(int)*input][1];
        if(y<3 || (y==3 && nx>0)) while(nx < x){ output[i++]='<'; x--;}
        if(x>0 || (x==0 && ny<3)) while(ny > y){ output[i++]='v'; y++;}
        while(ny < y){ output[i++]='^'; y--;}
        while(nx < x){ output[i++]='<'; x--;}
        while(nx > x){ output[i++]='>'; x++;}
        while(ny > y){ output[i++]='v'; y++;}
        output[i++]='A';
        input++;
    }
    output[i]='\0';
}

long long resolve_directionals(char a, char b, int depth){
    int x=dir_pos[(int)a][0], y=dir_pos[(int)a][1], nx=dir_pos[(int)b][0], ny=dir_pos[(int)b][1], len=0;

    char output[SMALL_N];
    output[len++]='A';
    if(y==1 || nx>0) while(nx < x){ output[len++]='<'; x--;}
    if(x>0) while(ny < y){ output[len++]='^'; y--;}
    while(ny > y){ output[len++]='v'; y++;}
    while(nx < x){ output[len++]='<'; x--;}
    while(nx > x){ output[len++]='>'; x++;}
    while(ny < y){ output[len++]='^'; y--;}
    output[len++]='A';
    output[len]='\0';

    if(depth == 1)
        return strlen(output)-1;

    char key[SMALL_N];
    sprintf(key,"%c%c%d",a,b,depth);
    ENTRY entry = {.key = key}, *found_entry;

    if((found_entry=hsearch(entry, FIND)) != NULL)
        return *( (long long *) found_entry->data);

    long long total=0;
    for(int i=0;i<(int)strlen(output)-1;i++)
        total+=resolve_directionals(output[i],output[i+1],depth-1);

    strcpy(cache[c], key);
    counts[c] = total;
    entry.key = cache[c];
    entry.data = &counts[c];
    if(hsearch(entry, ENTER) == NULL)
        fprintf(stderr,"hsearch ENTER failed for \"%s\"\n",cache[c]);
    c++;

    return total;
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            num_pos[(int)nums[j][i]][0] = i;
            num_pos[(int)nums[j][i]][1] = j;
        }
        for(int j=0;j<2;j++){
            dir_pos[(int)directs[j][i]][0] = i;
            dir_pos[(int)directs[j][i]][1] = j;
        }
    }

    hcreate(BIG_N);
    char buff[SMALL_N], input[BIG_N];
    long long sum=0,d;
    while(fscanf(fp,"%s",buff) == 1){
        sscanf(buff,"%lld",&d);
        resolve_numeric(buff, input);
        long long len=0;
        for(int i=0;i<(int)strlen(input)-1;i++)
            len+=resolve_directionals(input[i],input[i+1],ROBOTS_NO);

        sum += d*len;
    }

    fclose(fp);
    hdestroy();

    printf("%lld\n",sum);

    return 0;
}
