#include <stdio.h>
#include <stdint.h>

typedef unsigned long long ull;

// Function to compute 1 + k + k^2 + k^3
ull sum_formula(ull k) {
    return 1 + k + k * k + k * k * k;
}

// Function to count the number of valid (s, k) pairs for a given m
ull count_pairs(ull m) {
    ull count = 0;
    for(ull k = 2; ; k++) {
        ull sum = sum_formula(k);
        if(sum > m) break;
        count += m / sum;
        if(k > m) break; // To prevent potential infinite loops
    }
    return count;
}

int main(){
    ull n;
    scanf("%llu", &n);
    if(n == 0){
        printf("-1\n");
        return 0;
    }
    ull left = 1, right = 1000000000000000000ULL, answer = -1;
    while(left <= right){
        ull mid = left + (right - left) / 2;
        ull cnt = count_pairs(mid);
        if(cnt < n){
            left = mid +1;
        }
        else{
            if(cnt == n){
                answer = mid;
            }
            right = mid -1;
        }
    }
    // Verify if the answer indeed has count == n
    if(answer != (ull)(-1)){
        if(count_pairs(answer) != n){
            answer = (ull)(-1);
        }
    }
    printf("%llu\n", answer);
    return 0;
}