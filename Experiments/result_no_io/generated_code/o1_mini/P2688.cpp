#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pos;
    int step;
} Attack;

int cmp_attack(const void* a, const void* b) {
    Attack* aa = (Attack*)a;
    Attack* bb = (Attack*)b;
    if (aa->pos < bb->pos) return -1;
    if (aa->pos > bb->pos) return 1;
    return 0;
}

int cmp_step(const void* a, const void* b) {
    Attack* aa = (Attack*)a;
    Attack* bb = (Attack*)b;
    if (aa->step < bb->step) return -1;
    if (aa->step > bb->step) return 1;
    return 0;
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        long long n;
        int c, q;
        scanf("%lld %d %d", &n, &c, &q);
        long long S = 0;
        for(int i=0;i<c;i++){
            long long ci, ti;
            scanf("%lld %lld", &ci, &ti);
            S += ci * ti;
        }
        if(S > n){
            printf("0\n");
            // Consume attack inputs
            for(int i=0;i<q;i++){
                long long tmp;
                scanf("%lld", &tmp);
            }
            continue;
        }
        Attack* attacks = (Attack*)malloc(sizeof(Attack)*q);
        for(int i=0;i<q;i++){
            scanf("%d", &attacks[i].pos);
            attacks[i].step = i+1;
        }
        // Remove duplicates and keep first occurrence
        qsort(attacks, q, sizeof(Attack), cmp_attack);
        int unique = 0;
        for(int i=0;i<q;i++){
            if(i == 0 || attacks[i].pos != attacks[i-1].pos){
                attacks[unique++] = attacks[i];
            }
        }
        // Now sort the unique attacks by step
        qsort(attacks, unique, sizeof(Attack), cmp_step);
        // Calculate threshold
        long long threshold = n - S + 1;
        if(threshold <=0 ){
            printf("0\n");
            free(attacks);
            continue;
        }
        if(unique < threshold){
            printf("-1\n");
        }
        else{
            printf("%d\n", attacks[threshold-1].step);
        }
        free(attacks);
    }
    return 0;
}