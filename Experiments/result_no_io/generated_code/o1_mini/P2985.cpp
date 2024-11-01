#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef long long ll;

ll N, D;
ll H[50005];
ll assignment[50005];
ll sumH = 0;

int main(){
    scanf("%lld %lld", &N, &D);
    for(ll i=1;i<=N;i++) {
        scanf("%lld", &H[i]);
        sumH += H[i];
    }
    ll low = 0, high = sumH + 1, mid, res = 0;
    ll temp_assign[50005];
    while(low < high){
        mid = low + (high - low) / 2;
        ll day = 1;
        ll current = 0;
        int possible = 1;
        for(ll i=1;i<=N;i++){
            current = current / 2;
            if(current >= mid){
                temp_assign[i] = day;
                current += H[i];
            }
            else{
                if(day > D){
                    possible = 0;
                    break;
                }
                ll needed = mid - current;
                current += H[i];
                temp_assign[i] = day;
                if(current < mid){
                    possible = 0;
                    break;
                }
            }
        }
        if(possible && day <= D){
            low = mid +1;
            for(ll i=1;i<=N;i++) assignment[i] = temp_assign[i];
            res = mid;
        }
        else{
            high = mid;
        }
    }
    // Final assignment
    ll final_X = res;
    // Reset for final assignment
    ll day =1;
    ll current =0;
    for(ll i=1;i<=N;i++){
        current = current / 2;
        if(current >= final_X){
            assignment[i] = day;
            current += H[i];
        }
        else{
            if(day < D){
                day++;
                current = current / 2;
            }
            assignment[i] = day;
            current += H[i];
        }
    }
    printf("%lld\n", final_X);
    for(ll i=1;i<=N;i++) printf("%lld\n", assignment[i]);
    return 0;
}