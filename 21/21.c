#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 1024
#define SMALL_N 256
#define ROBOTS_NO 2

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

void resolve_numeric(char* input, char* output){
    int x=num_pos['A'][0], y=num_pos['A'][1], i=0;

    while(*input){
        int nx=num_pos[(int)*input][0], ny=num_pos[(int)*input][1];
        if(y<3 || (y==3 && nx>0)) while(nx < x){ output[i++]='<'; x--;}
        if(x>0 || (x==0 && ny<3)) while(ny > y){ output[i++]='v'; y++;}
        while(nx > x){ output[i++]='>'; x++;}
        while(ny < y){ output[i++]='^'; y--;}
        while(nx < x){ output[i++]='<'; x--;}
        while(ny > y){ output[i++]='v'; y++;}
        output[i++]='A';
        input++;
    }
    output[i]='\0';
}

void resolve_directional(char* input, char* output){
    int x=dir_pos['A'][0], y=dir_pos['A'][1], i=0;

    while(*input){
        int nx=dir_pos[(int)*input][0], ny=dir_pos[(int)*input][1];
        while(nx > x){ output[i++]='>'; x++;}
        while(ny > y){ output[i++]='v'; y++;}
        while(ny < y){ output[i++]='^'; y--;}
        while(nx < x){ output[i++]='<'; x--;}
        output[i++]='A';
        input++;
    }
    output[i]='\0';
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


    char buff[SMALL_N], input[BIG_N], output[BIG_N];
    int sum=0,d;
    while(fscanf(fp,"%s",buff) == 1){
        sscanf(buff,"%d",&d);
        resolve_numeric(buff, input);
        for(int i=0;i<ROBOTS_NO;i++){
            resolve_directional(input, output);
            strcpy(input,output);
        }

        sum += d*strlen(output);
    }

    fclose(fp);

    printf("%d\n",sum);

    return 0;
}
