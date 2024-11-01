#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int cmp(const void *a, const void *b){
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if(x < y) return -1;
    else if(x > y) return 1;
    else return 0;
}

int is_possible(ll *pos, int N, int C, ll distance){
    int count = 1;
    ll last = pos[0];
    for(int i=1;i<N;i++){
        if(pos[i] - last >= distance){
            count++;
            last = pos[i];
            if(count >= C) return 1;
        }
    }
    return 0;
}

int main(){
    int N, C;
    scanf("%d %d", &N, &C);
    ll *pos = (ll*)malloc(N * sizeof(ll));
    for(int i=0;i<N;i++) scanf("%lld", &pos[i]);
    qsort(pos, N, sizeof(ll), cmp);
    ll left = 0, right = pos[N-1] - pos[0];
    ll result = 0;
    while(left <= right){
        ll mid = left + (right - left)/2;
        if(is_possible(pos, N, C, mid)){
            result = mid;
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    printf("%lld\n", result);
    free(pos);
    return 0;
}