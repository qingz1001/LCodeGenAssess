#include <stdio.h>
#include <stdbool.h>

#define MAX_N 9

int n;
int digits[MAX_N];
int count = 0;

bool check(int a, int b, int c, int d, int e) {
    int num1 = a * 100 + b * 10 + c;
    int num2 = d * 10 + e;
    int prod1 = num1 * e;
    int prod2 = num1 * d;
    int result = num1 * num2;
    
    if (prod1 < 100 || prod1 > 999) return false;
    if (prod2 < 100 || prod2 > 999) return false;
    if (result < 1000 || result > 9999) return false;
    
    int digits_used[10] = {0};
    digits_used[a] = digits_used[b] = digits_used[c] = digits_used[d] = digits_used[e] = 1;
    
    while (prod1 > 0) {
        if (!digits_used[prod1 % 10]) return false;
        prod1 /= 10;
    }
    while (prod2 > 0) {
        if (!digits_used[prod2 % 10]) return false;
        prod2 /= 10;
    }
    while (result > 0) {
        if (!digits_used[result % 10]) return false;
        result /= 10;
    }
    
    return true;
}

void solve() {
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            for (int c = 0; c < n; c++) {
                for (int d = 0; d < n; d++) {
                    for (int e = 0; e < n; e++) {
                        if (check(digits[a], digits[b], digits[c], digits[d], digits[e])) {
                            count++;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &digits[i]);
    }
    
    solve();
    
    printf("%d\n", count);
    return 0;
}