#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    long long *a = (long long*)malloc((n+1)*sizeof(long long));
    long long *b = (long long*)malloc((n+1)*sizeof(long long));
    for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
    for(int i=1;i<=n;i++) scanf("%lld", &b[i]);
    int m;
    scanf("%d", &m);
    // Store combinations
    typedef struct {
        int k;
        long long c1;
        long long c2;
        int *group;
    } Combo;
    Combo *combos = (Combo*)malloc(m*sizeof(Combo));
    for(int i=0;i<m;i++){
        scanf("%d %lld %lld", &combos[i].k, &combos[i].c1, &combos[i].c2);
        combos[i].group = (int*)malloc(combos[i].k*sizeof(int));
        for(int j=0;j<combos[i].k;j++) scanf("%d", &combos[i].group[j]);
    }
    // Assign crops to A or B based on individual profit
    // 0 for A, 1 for B
    char *assign = (char*)malloc((n+1)*sizeof(char));
    for(int i=1;i<=n;i++){
        if(b[i] > a[i]) assign[i] = 1;
        else assign[i] = 0;
    }
    // Calculate initial profit
    long long total = 0;
    for(int i=1;i<=n;i++) total += assign[i] ? b[i] : a[i];
    // Add combination bonuses
    for(int i=0;i<m;i++){
        int allA = 1, allB = 1;
        for(int j=0;j<combos[i].k;j++){
            int crop = combos[i].group[j];
            if(assign[crop]) allA = 0;
            else allB = 0;
            if(!allA && !allB) break;
        }
        if(allA){
            total += combos[i].c1;
        }
        else if(allB){
            total += combos[i].c2;
        }
    }
    printf("%lld\n", total);
    // Free memory
    free(a);
    free(b);
    for(int i=0;i<m;i++) free(combos[i].group);
    free(combos);
    free(assign);
    return 0;
}