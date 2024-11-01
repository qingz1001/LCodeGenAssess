#include <stdio.h>
#include <math.h>

// Function to compute the maximum distance achievable in t seconds
long long max_distance(long long t, long long M) {
    // The maximum number of blinks possible is bounded by t and magic
    long long left = 0;
    long long right = t;
    long long B_max = 0;
    while(left <= right){
        long long mid = left + (right - left) / 2;
        // Calculate required rest
        long long required_magic = 10 * mid;
        long long rest = 0;
        if(required_magic > M){
            rest = (required_magic - M + 3) / 4; // Ceiling division
        }
        if(mid + rest <= t){
            B_max = mid;
            left = mid + 1;
        }
        else{
            right = mid -1;
        }
    }
    // Now calculate the total distance
    long long required_magic = 10 * B_max;
    long long rest = 0;
    if(required_magic > M){
        rest = (required_magic - M + 3) / 4; // Ceiling division
    }
    long long run = t - B_max - rest;
    if(run <0) run=0;
    return 60*B_max + 17*run;
}

int main(){
    long long M, S, T;
    scanf("%lld %lld %lld", &M, &S, &T);
    
    // Binary search for the minimal time to escape
    long long left = 0, right = T, answer = -1;
    while(left <= right){
        long long mid = left + (right - left)/2;
        long long dist = max_distance(mid, M);
        if(dist >= S){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    if(answer != -1 && answer <= T){
        printf("Yes\n%lld\n", answer);
    }
    else{
        long long dist = max_distance(T, M);
        printf("No\n%lld\n", dist);
    }
    return 0;
}