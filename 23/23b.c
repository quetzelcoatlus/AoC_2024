#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_N 700

struct pc {
    char name[2];
    char links[BIG_N][2];
    int pcn;
};
int n=0;

char link[26][26][26][26] = {0};

void check_lan(char* linked, char links[BIG_N][2], int n, int pcn){
        if(n==pcn) return;
        int good=1;
        for(int i=0;i<(int)strlen(linked);i+=3){
            if(!link[linked[i]-'a'][linked[i+1]-'a'][links[n][0]-'a'][links[n][1]-'a']){
                good=0;
                break;
            }
        }

        char next[BIG_N];
        strcpy(next,linked);
        if(good){
            int len=strlen(next);
            next[len++]=',';
            next[len++]=links[n][0];
            next[len++]=links[n][1];
            next[len++]='\0';
        }

        check_lan(next,links,n+1,pcn);
        strcpy(linked,next);
}

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    struct pc pcs[BIG_N];
    for(int i=0;i<BIG_N;i++) pcs[i].pcn=0;

    char a1,a2,b1,b2;
    while(fscanf(fp,"%c%c-%c%c\n",&a1,&a2,&b1,&b2) == 4){
        link[a1-'a'][a2-'a'][b1-'a'][b2-'a']=1;
        link[b1-'a'][b2-'a'][a1-'a'][a2-'a']=1;

        struct pc *p=NULL;
        for(int i=0;i<n;i++){
            if(pcs[i].name[0] == a1 && pcs[i].name[1] == a2){
                p=&pcs[i];
                break;
            }
        }
        if(p == NULL){
            pcs[n].name[0]=a1;
            pcs[n].name[1]=a2;
            p=&pcs[n];
            n++;
        }
        p->links[p->pcn][0]=b1;
        p->links[p->pcn][1]=b2;
        (p->pcn)++;

        p=NULL;
        for(int i=0;i<n;i++){
            if(pcs[i].name[0] == b1 && pcs[i].name[1] == b2){
                p=&pcs[i];
                break;
            }
        }
        if(p == NULL){
            pcs[n].name[0]=b1;
            pcs[n].name[1]=b2;
            p=&pcs[n];
            n++;
        }
        p->links[p->pcn][0]=a1;
        p->links[p->pcn][1]=a2;
        (p->pcn)++;
    }

    char linked[BIG_N], result[BIG_N];
    int max_len=0;
    for(int i=0;i<n;i++){
        sprintf(linked,"%c%c",pcs[i].name[0],pcs[i].name[1]);
        check_lan(linked,pcs[i].links,0,pcs[i].pcn);

        if((int)strlen(linked) > max_len){
            strcpy(result,linked);
            max_len=(int)strlen(linked);
        }

    }

    //primitive sorting with strcmp
    for(int i=0;i<max_len;i++) if(result[i]==',') result[i]='\0';

    char tmp[3];
    for(int i=0;i<max_len;i+=3){
        for(int j=max_len-2;j>=i+3;j-=3){
            if(strcmp(result+j-3,result+j) > 0){
                strcpy(tmp,result+j-3);
                strcpy(result+j-3,result+j);
                strcpy(result+j,tmp);
            }
        }
    }

    for(int i=0;i<max_len;i++) if(result[i]=='\0') result[i]=',';

    fclose(fp);

    printf("%s\n",result);

    return 0;
}
