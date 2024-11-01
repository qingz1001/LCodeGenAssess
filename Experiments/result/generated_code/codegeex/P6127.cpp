#include <stdio.h>
#include <string.h>

#define MAX_N 6
#define MAX_EXPR_LEN (MAX_N * 4)

char propositions[MAX_N + 1];
char expr[MAX_EXPR_LEN];
int n, count;

void gen_expr(int mask, int pos, int neg) {
    if (pos == n) {
        int is_true = 1;
        for (int i = 0; i < (1 << n); i++) {
            int val = (i & mask) | neg;
            if ((val & (1 << n)) != (i & (1 << n))) {
                is_true = 0;
                break;
            }
        }
        if (is_true) {
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    expr[count++] = propositions[i];
                    if (count < MAX_EXPR_LEN - 1) {
                        expr[count++] = '&';
                    }
                }
            }
            if (count > 0) {
                count--;
            }
            expr[count] = '\0';
        }
        return;
    }
    gen_expr(mask, pos + 1, neg);
    gen_expr(mask | (1 << pos), pos + 1, neg);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        propositions[i] = 'a' + i;
    }
    for (int i = 0; i < (1 << n); i++) {
        char line[9];
        scanf("%s", line);
        int mask = 0, neg = 0;
        for (int j = 0; j < n; j++) {
            if (line[j] == 'T') {
                mask |= (1 << j);
            } else {
                neg |= (1 << j);
            }
        }
        if (line[n] == 'T') {
            gen_expr(mask, 0, neg);
        }
    }
    if (count > 0) {
        expr[count - 1] = '\0';
        for (int i = 0; i < count; i++) {
            printf("%c", expr[i]);
        }
    } else {
        printf("False");
    }
    return 0;
}