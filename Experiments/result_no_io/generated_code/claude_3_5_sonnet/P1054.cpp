#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 55
#define MOD 10007

typedef long long ll;

char expr[MAX_LEN];
int n, len;
ll coef[11];

void init() {
    memset(coef, 0, sizeof(coef));
}

void remove_spaces() {
    int i, j;
    for (i = j = 0; expr[i]; i++)
        if (!isspace(expr[i]))
            expr[j++] = expr[i];
    expr[j] = '\0';
    len = j;
}

ll quick_pow(ll base, int exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

void calc(int l, int r, int sign) {
    int i, j, k, num = 0, exp = 1;
    for (i = l; i <= r; i++) {
        if (expr[i] == '(') {
            for (j = i + 1, k = 1; k > 0; j++) {
                if (expr[j] == '(') k++;
                if (expr[j] == ')') k--;
            }
            calc(i + 1, j - 2, sign);
            i = j - 1;
        } else if (expr[i] == 'a') {
            for (j = i + 1; j <= r && expr[j] == '^'; j += 2)
                exp = exp * (expr[j + 1] - '0') % 10;
            coef[exp] = (coef[exp] + sign + MOD) % MOD;
            exp = 1;
            i = j - 1;
        } else if (isdigit(expr[i])) {
            for (j = i; j <= r && isdigit(expr[j]); j++)
                num = num * 10 + expr[j] - '0';
            coef[0] = (coef[0] + sign * num % MOD + MOD) % MOD;
            num = 0;
            i = j - 1;
        } else if (expr[i] == '+' || expr[i] == '-') {
            calc(i + 1, r, sign * (expr[i] == '+' ? 1 : -1));
            break;
        }
    }
}

int compare(const ll* a, const ll* b) {
    for (int i = 10; i >= 0; i--)
        if (a[i] != b[i])
            return 0;
    return 1;
}

int main() {
    ll standard[11];
    char result[27] = {0};
    int count = 0;

    scanf("%s", expr);
    remove_spaces();
    calc(0, len - 1, 1);
    memcpy(standard, coef, sizeof(coef));

    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        init();
        fgets(expr, MAX_LEN, stdin);
        remove_spaces();
        calc(0, len - 1, 1);
        if (compare(coef, standard)) {
            result[count++] = 'A' + i;
        }
    }

    printf("%s\n", result);
    return 0;
}