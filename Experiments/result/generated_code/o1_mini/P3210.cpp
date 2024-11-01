#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Comparator for descending order
int cmp_desc(const void *a, const void *b) {
    ll x = *(const ll*)a;
    ll y = *(const ll*)b;
    if(x > y) return -1;
    else if(x < y) return 1;
    else return 0;
}

int main(){
    int N;
    if(scanf("%d", &N)!=1){
        return 0;
    }
    ll *segments = (ll*)malloc(sizeof(ll)*N);
    if(!segments){
        return 0;
    }
    int seg_count=0;
    ll current_sum=0;
    for(int i=0;i<N;i++){
        int ai;
        if(scanf("%d", &ai)!=1){
            ai=0;
        }
        if(ai >0){
            current_sum += ai;
        }
        else{
            if(current_sum >0){
                segments[seg_count++] = current_sum;
                current_sum =0;
            }
        }
    }
    if(current_sum >0){
        segments[seg_count++] = current_sum;
    }
    if(seg_count >0){
        qsort(segments, seg_count, sizeof(ll), cmp_desc);
    }
    ll player1=0, player2=0;
    for(int i=0;i<seg_count;i++){
        if(i%2==0){
            player1 += segments[i];
        }
        else{
            player2 += segments[i];
        }
    }
    printf("%lld %lld\n", player1, player2);
    free(segments);
    return 0;
}