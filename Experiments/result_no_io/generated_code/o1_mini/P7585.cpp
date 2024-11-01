#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef long long ll;

int main(){
    int M;
    ll N;
    if(scanf("%lld %d", &N, &M)!=2){
        return 1;
    }
    ll *x = (ll*)malloc(sizeof(ll)*M);
    if(!x){
        return 1;
    }
    ll max_x = 0;
    for(int i=0;i<M;i++){
        if(scanf("%lld", &x[i])!=1){
            free(x);
            return 1;
        }
        if(x[i] > max_x){
            max_x = x[i];
        }
    }
    ll left = 1, right = max_x, answer = max_x;
    while(left <= right){
        ll mid = left + (right - left)/2;
        ll total = 0;
        for(int i=0;i<M;i++){
            total += (x[i] + mid -1)/mid;
            if(total > N){
                break;
            }
        }
        if(total <= N){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%lld\n", answer);
    free(x);
    return 0;
}