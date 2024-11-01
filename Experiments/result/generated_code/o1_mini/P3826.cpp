#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>

typedef struct {
    int64_t a;
    int64_t s;
    int64_t c;
    int64_t x;
} Veg;

int cmp(const void *a, const void *b){
    Veg *va = (Veg*)a;
    Veg *vb = (Veg*)b;
    if(vb->a != va->a) return (vb->a > va->a) - (vb->a < va->a);
    else return (vb->s > va->s) - (vb->s < va->s);
}

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    Veg *vegs = (Veg*)malloc(n*sizeof(Veg));
    for(int i=0;i<n;i++) scanf("%" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64, &vegs[i].a, &vegs[i].s, &vegs[i].c, &vegs[i].x);
    qsort(vegs, n, sizeof(Veg), cmp);
    int64_t *queries = (int64_t*)malloc(k*sizeof(int64_t));
    for(int i=0;i<k;i++) scanf("%" SCNd64, &queries[i]);
    for(int i=0;i<k;i++){
        int64_t p = queries[i];
        if(p ==0){
            printf("0\n");
            continue;
        }
        int64_t total = m * p;
        int64_t profit =0;
        int64_t remaining = total;
        for(int j=0;j<n && remaining >0;j++){
            Veg v = vegs[j];
            int64_t available;
            if(v.x ==0){
                available = v.c;
            }
            else{
                available = v.x * p;
                if(available > v.c) available = v.c;
            }
            if(available <=0) continue;
            if(available >=1){
                profit += v.a + v.s;
                available -=1;
                remaining -=1;
            }
            if(available >0 && remaining >0){
                if(available > remaining) available = remaining;
                profit += v.a * available;
                remaining -= available;
            }
        }
        printf("%" PRId64 "\n", profit);
    }
    free(vegs);
    free(queries);
}