#include <stdio.h>

typedef long long ll;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    ll counts[M];
    ll maxx = 0;
    for(int i=0;i<M;i++){
        scanf("%lld", &counts[i]);
        if(counts[i] > maxx) maxx = counts[i];
    }
    ll left =1, right = maxx, ans = maxx;
    while(left <= right){
        ll mid = left + (right - left)/2;
        ll total =0;
        for(int i=0;i<M;i++) {
            total += (counts[i] + mid -1)/mid;
            if(total > N) break;
        }
        if(total <= N){
            ans = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%lld\n", ans);
}