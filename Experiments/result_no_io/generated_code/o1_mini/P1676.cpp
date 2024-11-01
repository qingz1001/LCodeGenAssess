#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int cmp(const void *a, const void *b){
    ll A = *(ll*)a;
    ll B = *(ll*)b;
    if(A < B) return -1;
    else if(A > B) return 1;
    else return 0;
}

int can_place(ll *positions, int n, int m, ll distance){
    int count = 1;
    ll last = positions[0];
    for(int i=1;i<n;i++){
        if(positions[i] - last >= distance){
            count++;
            last = positions[i];
            if(count >= m) return 1;
        }
    }
    return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    ll *positions = (ll*)malloc(n * sizeof(ll));
    for(int i=0;i<n;i++) scanf("%lld", &positions[i]);
    qsort(positions, n, sizeof(ll), cmp);
    ll low = 0;
    ll high = positions[n-1] - positions[0];
    ll result = 0;
    while(low <= high){
        ll mid = low + (high - low)/2;
        if(can_place(positions, n, m, mid)){
            result = mid;
            low = mid +1;
        }
        else{
            high = mid -1;
        }
    }
    printf("%lld\n", result);
    free(positions);
    return 0;
}