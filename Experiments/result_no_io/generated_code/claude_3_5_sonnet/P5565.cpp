#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 998244353
#define MAXN 400005

char expr[MAXN];
int n, m;
int stack[MAXN], top;
int left[MAXN], right[MAXN];
int values[MAXN], ops[MAXN];

int quick_pow(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        if (exp & 1) result = (long long)result * base % MOD;
        base = (long long)base * base % MOD;
        exp >>= 1;
    }
    return result;
}

void preprocess() {
    top = 0;
    for (int i = 0; i < n; i++) {
        if (expr[i] == '(') {
            stack[top++] = i;
        } else if (expr[i] == ')') {
            left[i] = stack[--top];
            right[left[i]] = i;
        }
    }
}

int calc(int l, int r) {
    if (l == r) return values[l];
    int op = ops[r];
    int lv = calc(l, r - 1);
    int rv = values[r];
    if (op == 1) return (lv + rv - (long long)lv * rv % MOD + MOD) % MOD;
    if (op == 2) return (long long)lv * rv % MOD;
    return (lv + rv - 2LL * lv * rv % MOD + MOD) % MOD;
}

int solve() {
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (expr[i] == '(' || expr[i] == ')') continue;
        int j = i;
        while (j < n && expr[j] != ')') j++;
        j--;
        int val = calc(i, j);
        result = (result + val) % MOD;
        i = j;
    }
    return result;
}

int main() {
    scanf("%d", &m);
    scanf("%s", expr);
    n = strlen(expr);
    preprocess();

    for (int i = 0; i < n; i++) {
        if (expr[i] >= 'a' && expr[i] <= 'z') {
            values[i] = 1;
        } else if (expr[i] == '0') {
            values[i] = 0;
        } else if (expr[i] == '1') {
            values[i] = 1;
        } else if (expr[i] == '|') {
            ops[i] = 1;
        } else if (expr[i] == '&') {
            ops[i] = 2;
        } else if (expr[i] == '^') {
            ops[i] = 3;
        }
    }

    printf("%d\n", solve());

    for (int i = 0; i < m; i++) {
        int pos;
        char ch;
        scanf("%d %c", &pos, &ch);
        pos--;
        expr[pos] = ch;
        if (ch >= 'a' && ch <= 'z') {
            values[pos] = 1;
        } else if (ch == '0') {
            values[pos] = 0;
        } else if (ch == '1') {
            values[pos] = 1;
        } else if (ch == '|') {
            ops[pos] = 1;
        } else if (ch == '&') {
            ops[pos] = 2;
        } else if (ch == '^') {
            ops[pos] = 3;
        }
        printf("%d\n", solve());
    }

    return 0;
}