#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#define BIG_N 1024
#define SMALL_N 16

char gates[BIG_N][4][SMALL_N];
int g=0;

int r(char* c, char* y){
    for(int i=0;i<g;i++)
        if(!strcmp(y,gates[i][1]) && (!strcmp(c,gates[i][0]) || !strcmp(c,gates[i][2])))
            return 1;

    return 0;
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    int d;
    char buff[SMALL_N] = {0};
    while(fscanf(fp,"%s %d",buff,&d) == 2);

    strcpy(gates[g][0], buff);
    fscanf(fp,"%s %s -> %s",gates[g][1],gates[g][2],gates[g][3]);
    g++;
    while (fscanf(fp,"%s %s %s -> %s",gates[g][0],gates[g][1],gates[g][2],gates[g][3]) == 4) g++;
    fclose(fp);

    char list[BIG_N] = {0};

    // 4 cases gotten thanks to u/4HbQ
    for(int i=0;i<g;i++){
        int good=0;
        if(!strcmp(gates[i][1],"XOR") &&
                gates[i][0][0] != 'x' && gates[i][0][0] != 'y' && gates[i][0][0] != 'z' &&
                gates[i][2][0] != 'x' && gates[i][2][0] != 'y' && gates[i][2][0] != 'z' &&
                gates[i][3][0] != 'x' && gates[i][3][0] != 'y' && gates[i][3][0] != 'z')
            good++;

        if(!strcmp(gates[i][1],"AND") && strcmp(gates[i][0],"x00") && strcmp(gates[i][2],"x00") && r(gates[i][3],"XOR"))
            good++;

        if(!strcmp(gates[i][1],"XOR") && strcmp(gates[i][0],"x00") && strcmp(gates[i][2],"x00") && r(gates[i][3],"OR"))
            good++;

        if(strcmp(gates[i][1],"XOR") && gates[i][3][0] == 'z' && strcmp(gates[i][3],"z45"))
            good++;

        if(good){
            if(strlen(list) > 0) strcat(list,",");
            strcat(list,gates[i][3]);
        }
    }

    //primitive sorting with strcmp
    int max_len=strlen(list);
    for(int i=0;i<max_len;i++) if(list[i]==',') list[i]='\0';

    char tmp[4];
    for(int i=0;i<max_len;i+=4){
        for(int j=max_len-3;j>=i+4;j-=4){
            if(strcmp(list+j-4,list+j) > 0){
                strcpy(tmp,list+j-4);
                strcpy(list+j-4,list+j);
                strcpy(list+j,tmp);
            }
        }
    }

    for(int i=0;i<max_len;i++) if(list[i]=='\0') list[i]=',';

    printf("%s\n",list);

    return 0;
}
