#include <stdio.h>
#include <stdlib.h>

#define MAX_S 125001
#define MAX_PAIRS 10000

typedef struct {
    int a;
    int b;
} Pair;

int compare(const void *p1, const void *p2) {
    Pair *pair1 = (Pair *)p1;
    Pair *pair2 = (Pair *)p2;
    if (pair1->b != pair2->b)
        return pair1->b - pair2->b;
    return pair1->a - pair2->a;
}

int main(){
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    
    int *S_present = calloc(MAX_S, sizeof(int));
    if(!S_present){
        return 1;
    }
    
    int p, q;
    int x;
    int max_x = 0;
    for(p = 0; p <= m; p++){
        for(q = 0; q <= m; q++){
            x = p*p + q*q;
            if(x < MAX_S){
                S_present[x] = 1;
                if(x > max_x){
                    max_x = x;
                }
            }
        }
    }
    
    Pair *pairs = malloc(MAX_PAIRS * sizeof(Pair));
    if(!pairs){
        free(S_present);
        return 1;
    }
    int pair_count = 0;
    
    int b;
    for(b = 1; b <= max_x / (n-1) && pair_count < MAX_PAIRS; b++){
        for(int a = 0; a <= max_x - (n-1)*b && pair_count < MAX_PAIRS; a++){
            if(S_present[a]){
                int k;
                for(k = 1; k < n; k++){
                    if(!S_present[a + k*b]){
                        break;
                    }
                }
                if(k == n){
                    pairs[pair_count].a = a;
                    pairs[pair_count].b = b;
                    pair_count++;
                }
            }
        }
    }
    
    if(pair_count == 0){
        printf("NONE\n");
    }
    else{
        qsort(pairs, pair_count, sizeof(Pair), compare);
        for(int i = 0; i < pair_count; i++){
            printf("%d %d\n", pairs[i].a, pairs[i].b);
        }
    }
    
    free(S_present);
    free(pairs);
    return 0;
}