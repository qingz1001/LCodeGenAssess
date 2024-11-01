#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

long long heights[MAXN];
long long n = 0;

int main(){
    // Read all heights
    while(scanf("%lld", &heights[n]) != EOF){
        n++;
        if(n >= MAXN) break;
    }

    // Part 1: Longest Non-Increasing Subsequence
    long long tails1[MAXN];
    long long len1 = 0;
    for(long long i = 0; i < n; i++){
        long long h = heights[i];
        long long left = 0, right = len1;
        while(left < right){
            long long mid = (left + right) / 2;
            if(tails1[mid] < h){
                right = mid;
            }
            else{
                left = mid + 1;
            }
        }
        tails1[left] = h;
        if(left == len1) len1++;
    }

    // Part 2: Minimum Number of Systems
    long long systems[MAXN];
    long long len2 = 0;
    for(long long i = 0; i < n; i++){
        long long h = heights[i];
        long long left = 0, right = len2;
        while(left < right){
            long long mid = (left + right) / 2;
            if(systems[mid] >= h){
                right = mid;
            }
            else{
                left = mid + 1;
            }
        }
        if(left < len2){
            systems[left] = h;
        }
        else{
            systems[len2++] = h;
        }
    }

    // Output
    printf("%lld\n%lld\n", len1, len2);
    return 0;
}