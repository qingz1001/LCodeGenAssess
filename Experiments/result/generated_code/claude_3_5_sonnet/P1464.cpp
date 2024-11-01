#include <stdio.h>
#include <string.h>

#define MAX 21

long long memo[MAX][MAX][MAX];

long long w(long long a, long long b, long long c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 1;
    }
    
    if (a > 20 || b > 20 || c > 20) {
        return w(20, 20, 20);
    }
    
    if (memo[a][b][c] != -1) {
        return memo[a][b][c];
    }
    
    if (a < b && b < c) {
        memo[a][b][c] = w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c);
    } else {
        memo[a][b][c] = w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1);
    }
    
    return memo[a][b][c];
}

int main() {
    long long a, b, c;
    
    memset(memo, -1, sizeof(memo));
    
    while (1) {
        scanf("%lld %lld %lld", &a, &b, &c);
        if (a == -1 && b == -1 && c == -1) {
            break;
        }
        printf("w(%lld, %lld, %lld) = %lld\n", a, b, c, w(a, b, c));
    }
    
    return 0;
}