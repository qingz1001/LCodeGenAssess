#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 201

char A[MAX_LEN];
int len;

int check(long long pos) {
    int i = 0;
    char buf[20];
    while (i < len) {
        long long num = pos;
        int digits = 0;
        while (num) {
            buf[digits++] = num % 10 + '0';
            num /= 10;
        }
        for (int j = digits - 1; j >= 0 && i < len; j--, i++) {
            if (buf[j] != A[i]) return 0;
        }
        pos++;
    }
    return 1;
}

long long binary_search() {
    long long left = 1, right = 1e15, mid;
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
    printf("%lld\n", binary_search());
    return 0;
}