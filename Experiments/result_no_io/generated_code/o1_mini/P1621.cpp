#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int parent;
} DSU;

int find_set(DSU *dsu, int x){
    if(dsu[x].parent != x){
        dsu[x].parent = find_set(dsu, dsu[x].parent);
    }
    return dsu[x].parent;
}

void union_set(DSU *dsu, int x, int y){
    int fx = find_set(dsu, x);
    int fy = find_set(dsu, y);
    if(fx != fy){
        dsu[fx].parent = fy;
    }
}

int main(){
    int a, b, p;
    scanf("%d %d %d", &a, &b, &p);
    int size = b - a + 1;
    DSU *dsu = (DSU*)malloc((size) * sizeof(DSU));
    for(int i=0;i<size;i++) dsu[i].parent = i;
    int limit = (int)sqrt(b) +1;
    char *is_prime = (char*)malloc((b+1) * sizeof(char));
    for(int i=0;i<=b;i++) is_prime[i] = 1;
    is_prime[0] = is_prime[1] = 0;
    for(int i=2;i<=b;i++){
        if(is_prime[i]){
            if(i >= p){
                int start = a / i * i;
                if(start < a) start += i;
                if(start == i) start += i;
                int first = start;
                int prev = -1;
                for(int j = first; j <= b; j += i){
                    if(j >= a){
                        if(prev == -1){
                            prev = j;
                        }
                        else{
                            union_set(dsu, j - a, prev - a);
                        }
                    }
                }
            }
            for(int j=2*i; j<=b; j+=i){
                is_prime[j] = 0;
            }
        }
    }
    int count = 0;
    for(int i=0;i<size;i++) {
        if(dsu[i].parent == i){
            count++;
        }
    }
    printf("%d", count);
    free(dsu);
    free(is_prime);
    return 0;
}