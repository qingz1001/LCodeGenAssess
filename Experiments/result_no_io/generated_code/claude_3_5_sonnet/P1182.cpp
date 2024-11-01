#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

long long arr[MAX_N];
int N, M;

int check(long long mid) {
    int count = 1;
    long long sum = 0;
    for (int i = 0; i < N; i++) {
        if (sum + arr[i] > mid) {
            count++;
            sum = arr[i];
        } else {
            sum += arr[i];
        }
    }
    return count <= M;
}

long long binary_search(long long left, long long right) {
    while (left < right) {
        long long mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &N, &M);
    
    long long sum = 0;
    long long max_val = 0;
    for (int i = 0; i < N; i++) {
        scanf("%lld", &arr[i]);
        sum += arr[i];
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    
    long long result = binary_search(max_val, sum);
    printf("%lld\n", result);
    
    return 0;
}