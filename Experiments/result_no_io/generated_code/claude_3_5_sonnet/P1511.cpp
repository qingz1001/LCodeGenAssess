#include <stdio.h>
#include <string.h>

#define MAX_LEN 201

char A[MAX_LEN];
int len;

int check(long long pos) {
    int i = 0;
    char buf[20];
    while (i < len) {
        long long num = pos;
        int j = 0;
        while (num) {
            buf[j++] = num % 10 + '0';
            num /= 10;
        }
        while (j > 0 && i < len) {
            if (A[i] != buf[--j]) return 0;
            i++;
        }
        pos++;
    }
    return 1;
}

int digits(long long n) {
    int cnt = 0;
    while (n) {
        cnt++;
        n /= 10;
    }
    return cnt;
}

long long solve() {
    long long left = 1, right = 1e18, mid;
    while (left < right) {
        mid = (left + right) / 2;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }
    return left;
}

int main() {
    scanf("%s", A);
    len = strlen(A);
    long long ans = solve();
    long long pos = 0;
    for (long long i = 1; i < ans; i++) {
        pos += digits(i);
    }
    printf("%lld\n", pos + 1);
    return 0;
}