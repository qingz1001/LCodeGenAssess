#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    ll *A = (ll*)malloc(N * sizeof(ll));
    ll maxA = 0, sumA = 0;
    for(int i=0;i<N;i++){
        scanf("%lld", &A[i]);
        if(A[i] > maxA) maxA = A[i];
        sumA += A[i];
    }
    ll low = maxA, high = sumA, mid, res = sumA;
    while(low <= high){
        mid = low + (high - low)/2;
        int cnt = 1;
        ll current = 0;
        for(int i=0;i<N;i++){
            if(current + A[i] > mid){
                cnt++;
                current = A[i];
            }
            else{
                current += A[i];
            }
        }
        if(cnt <= M){
            res = mid;
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }
    printf("%lld\n", res);
    free(A);
    return 0;
}