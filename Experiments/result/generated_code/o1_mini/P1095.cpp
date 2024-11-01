#include <stdio.h>

typedef long long ll;

int main(){
    int M;
    ll S;
    int T;
    scanf("%d %lld %d", &M, &S, &T);
    
    int left = 0, right = T;
    int answer = T +1;
    while(left <= right){
        int mid = left + (right - left)/2;
        ll temp = 4LL * mid + M -3;
        ll b;
        if(temp >=0){
            b = temp /14;
        }
        else{
            b =0;
        }
        if(b > mid){
            b = mid;
        }
        ll distance = 60LL * b + 17LL * (mid - b);
        if(distance >= S){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    if(answer <= T){
        printf("Yes\n%d\n", answer);
    }
    else{
        ll temp = 4LL * T + M -3;
        ll b;
        if(temp >=0){
            b = temp /14;
        }
        else{
            b =0;
        }
        if(b > T){
            b = T;
        }
        ll distance = 60LL * b + 17LL * (T - b);
        printf("No\n%lld\n", distance);
    }
    return 0;
}