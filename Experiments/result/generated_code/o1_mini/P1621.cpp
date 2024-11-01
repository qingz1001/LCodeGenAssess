#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100005

int parent[MAX];
int rank_set[MAX];

int find_set(int x){
    if(parent[x]!=x){
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y){
    int fx = find_set(x);
    int fy = find_set(y);
    if(fx == fy) return;
    if(rank_set[fx] < rank_set[fy]){
        parent[fx] = fy;
    }
    else{
        parent[fy] = fx;
        if(rank_set[fx]==rank_set[fy]){
            rank_set[fx]++;
        }
    }
}

int main(){
    int a, b, p;
    scanf("%d %d %d", &a, &b, &p);
    int size = b - a +1;
    for(int i=0;i<size;i++){
        parent[i] = i;
        rank_set[i] = 0;
    }

    char is_prime[b+1];
    memset(is_prime, 1, sizeof(is_prime));
    is_prime[0] = is_prime[1] = 0;
    for(int i=2;i<=b;i++){
        if(is_prime[i]){
            if(i >= p){
                // Find first multiple in [a,b]
                int start = a / i * i;
                if(start < a) start += i;
                if(start < i) start += i;
                int first = -1;
                for(int j = start; j <= b; j += i){
                    if(first == -1){
                        first = j;
                    }
                    else{
                        union_sets(first - a, j - a);
                    }
                }
            }
            for(long long j=(long long)i * i; j<=b; j+=i){
                is_prime[j] = 0;
            }
        }
    }

    int count =0;
    for(int i=0;i<size;i++){
        if(find_set(i) == i){
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}