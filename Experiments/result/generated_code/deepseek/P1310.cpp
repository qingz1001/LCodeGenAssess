#include <stdio.h>
#include <string.h>

#define MOD 10007

typedef struct {
    int zero;
    int one;
} Result;

Result dp[100001];
char expr[100001];

Result combine(Result left, Result right, char op) {
    Result res;
    if (op == '+') {
        res.zero = (left.zero * right.zero + left.zero * right.one + left.one * right.zero) % MOD;
        res.one = (left.one * right.one) % MOD;
    } else if (op == '*') {
        res.zero = (left.zero * right.zero) % MOD;
        res.one = (left.zero * right.one + left.one * right.zero + left.one * right.one) % MOD;
    }
    return res;
}

int main() {
    int L;
    scanf("%d", &L);
    scanf("%s", expr);

    int stack[100001], top = -1;
    Result results[100001];

    for (int i = 0; i < L; i++) {
        if (expr[i] == '(') {
            stack[++top] = i;
            dp[i].zero = 1;
            dp[i].one = 1;
        } else if (expr[i] == ')') {
            int start = stack[top--];
            Result res = dp[start];
            if (top >= 0) {
                dp[stack[top]] = combine(dp[stack[top]], res, expr[stack[top] + 1]);
            } else {
                results[i] = res;
            }
        } else if (expr[i] == '+' || expr[i] == '*') {
            if (top >= 0) {
                dp[stack[top]] = combine(dp[stack[top]], dp[i], expr[i]);
            }
        }
    }

    printf("%d\n", results[L - 1].zero);
    return 0;
}