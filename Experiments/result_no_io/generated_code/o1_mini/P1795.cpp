#include <stdio.h>
#include <stdint.h>

typedef long long ll;

int main(){
    int N;
    scanf("%d", &N);
    while(N--){
        ll A;
        scanf("%lld", &A);
        if(A <=2){
            putchar('1');
            putchar('\n');
            continue;
        }
        // Binary search for k
        ll left=1, right=44721, k=right;
        while(left <= right){
            ll mid = left + (right - left)/2;
            ll total = 2 + mid + (mid*(mid+1))/2;
            if(total >= A){
                k = mid;
                right = mid -1;
            }
            else{
                left = mid +1;
            }
        }
        // Compute previous length
        ll prev_k = k-1;
        ll prev_length = 2 + prev_k + (prev_k*(prev_k+1))/2;
        if(A <= prev_length + k){
            putchar('0');
            putchar('\n');
        }
        else{
            putchar('1');
            putchar('\n');
        }
    }
}