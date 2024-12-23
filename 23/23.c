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

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* fp = fopen(name,"r");

    struct pc pcs[BIG_N];
    for(int i=0;i<BIG_N;i++) pcs[i].pcn=0;

    int sum=0, link[26][26][26][26] = {0};
    char a1,a2,b1,b2;
    while(fscanf(fp,"%c%c-%c%c\n",&a1,&a2,&b1,&b2) == 4){
        link[a1-'a'][a2-'a'][b1-'a'][b2-'a']=1;
        link[b1-'a'][b2-'a'][a1-'a'][a2-'a']=1;

        struct pc *p=NULL;
        for(int i=0;i<n;i++){ // try to find a1a2 in list
            if(pcs[i].name[0] == a1 && pcs[i].name[1] == a2){
                p=&pcs[i];
                break;
            }
        }
        if(p == NULL){ // if not found, create entry
            pcs[n].name[0]=a1;
            pcs[n].name[1]=a2;
            p=&pcs[n];
            n++;
        }
        p->links[p->pcn][0]=b1; // link it with b1b2
        p->links[p->pcn][1]=b2;
        (p->pcn)++;

        p=NULL;                 // do the same to link b1b2 -> a1a2
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

    fclose(fp);

    for(int i=0;i<n;i++)
        for(int j=0;j<pcs[i].pcn;j++)
            for(int k=j+1;k<pcs[i].pcn;k++)
                if(link[pcs[i].links[j][0]-'a'][pcs[i].links[j][1]-'a'][pcs[i].links[k][0]-'a'][pcs[i].links[k][1]-'a'] == 1)
                    if(pcs[i].name[0] == 't' || pcs[i].links[j][0] == 't' || pcs[i].links[k][0] == 't')
                        sum++;


    printf("%d\n",sum/3); // every set is counted thrice, thus divide result

    return 0;
}
