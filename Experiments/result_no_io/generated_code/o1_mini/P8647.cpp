#include <stdio.h>
#include <stdint.h>

typedef long long ll;

int main(){
    int N;
    ll K;
    scanf("%d %lld", &N, &K);
    int H, W;
    int max_L = 0;
    int Hs[N], Ws[N];
    for(int i=0;i<N;i++){
        scanf("%d %d", &H, &W);
        Hs[i] = H;
        Ws[i] = W;
        if(H > max_L) max_L = H;
        if(W > max_L) max_L = W;
    }
    ll left =1, right = max_L, res=1;
    while(left <= right){
        ll mid = left + (right - left) / 2;
        ll total =0;
        for(int i=0;i<N;i++){
            total += (Hs[i]/mid) * (ll)(Ws[i]/mid);
            if(total >= K) break;
        }
        if(total >= K){
            res = mid;
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    printf("%lld", res);
}