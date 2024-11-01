#include <stdio.h>

typedef long long ll;

ll count_less(ll N, ll K) {
    if (K > N) return 0;
    ll count = 0;
    ll current = 1;
    while(current < K){
        ll first = current;
        ll last = current + 1;
        ll steps = 0;
        while(first <= N){
            steps += (N < last ? (N - first + 1) : (last - first));
            first *= 10;
            last *= 10;
        }
        count += steps;
        current +=1;
    }
    return count;
}

int main(){
    ll K, M;
    scanf("%lld %lld", &K, &M);
    if(M <1){
        printf("0\n");
        return 0;
    }
    ll low = K;
    ll high = K;
    // Estimate high
    for(int i=0;i<20;i++) high = high*10 +9;
    ll result = 0;
    while(low <= high){
        ll mid = low + (high - low)/2;
        if(mid < K){
            low = mid +1;
            continue;
        }
        ll cnt = count_less(mid, K);
        if(cnt +1 < M){
            low = mid +1;
        }
        else{
            if(cnt +1 == M){
                result = mid;
            }
            high = mid -1;
        }
    }
    if(result !=0){
        printf("%lld\n", result);
    }
    else{
        printf("0\n");
    }
    return 0;
}