#include <stdio.h>
#include <string.h>

#define MOD 10007

typedef struct {
    int zero;
    int one;
} Result;

Result dp[100005][2];
char expr[100005];
int L;

Result combine(Result a, Result b, char op) {
    Result res;
    if (op == '+') {
        res.zero = (a.zero * b.zero + a.zero * b.one + a.one * b.zero) % MOD;
        res.one = (a.one * b.one) % MOD;
    } else if (op == '*') {
        res.zero = (a.zero * b.zero + a.zero * b.one + a.one * b.zero) % MOD;
        res.one = (a.one * b.one) % MOD;
    }
    return res;
}

Result solve(int l, int r) {
    if (l == r) {
        Result res = {1, 1};
        return res;
    }
    int i = l;
    int balance = 0;
    for (i = l; i <= r; i++) {
        if (expr[i] == '(') balance++;
        if (expr[i] == ')') balance--;
        if (balance == 0) break;
    }
    if (i == r) return solve(l + 1, r - 1);
    Result left = solve(l, i);
    Result right = solve(i + 1, r);
    return combine(left, right, expr[i]);
}

int main() {
    scanf("%d", &L);
    scanf("%s", expr);
    Result res = solve(0, L - 1);
    printf("%d\n", res.zero);
    return 0;
}