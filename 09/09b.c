#include <stdio.h>
#include <stdlib.h>

#define BIG_N 1<<18

int main(int argc, char* argv[]) {
    char* name = argc > 1 ? argv[1] : "input";
    FILE* f = fopen(name,"r");

    int c, tab[BIG_N]={-1},p=0,q=0,file=1,id,l,r;
    int count_r,count_l,tmp_l;
    long int sum=0;

    while((c=fgetc(f)) != EOF){
        id = file == 1 ? p++ : -1;
        for(int i = '0'; i<c; i++)
            tab[q++]=id;
        file = (file+1)%2;
    }
    p--;

    r=q-1;
    while(p>1){
        l=0;
        while(tab[r] != p) r--;
        count_r=0;
        while(tab[r] == p) {
            count_r++;
            r--;
        }
        while(l<r){
            if(tab[l] == -1){
                count_l=0;
                tmp_l=l;
                while(tab[tmp_l] == -1){
                    count_l++;
                    tmp_l++;
                }
                if(count_l>=count_r)
                    break;
            }
            l++;
        }

        if(l<r){
            for(int i=0; i<count_r; i++){
                tab[l++]=p;
                tab[++r]=-1;
            }
        }
        p--;
    }

    for(int i=0; i<BIG_N; i++)
        if(tab[i]!=-1)
            sum+=i*tab[i];

    printf("%ld\n",sum);

    fclose(f);

    return 0;
}
