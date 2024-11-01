#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int t;
} Zombie;

int cmp(const void *a, const void *b) {
    Zombie *z1 = (Zombie *)a;
    Zombie *z2 = (Zombie *)b;
    if (z1->t != z2->t)
        return z1->t - z2->t;
    return 0;
}

int main(){
    int n;
    scanf("%d",&n);
    Zombie rows[6][2000];
    int count[6] = {0};
    for(int i=0;i<n;i++){
        int P, t;
        scanf("%d %d", &P, &t);
        rows[P-1][count[P-1]].t = t + 59;
        count[P-1]++;
    }
    int total =0;
    for(int i=0;i<6;i++){
        if(count[i]==0) continue;
        qsort(rows[i], count[i], sizeof(Zombie), cmp);
        int nuts =0;
        int last = -1;
        for(int j=0;j<count[i];j++){
            if(rows[i][j].t > last){
                nuts++;
                last = rows[i][j].t;
            }
        }
        total += nuts;
    }
    printf("%d", total);
}