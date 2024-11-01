#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 10
#define MAX_LEN 3

char symbols[MAX_N];
char table[MAX_N][MAX_N][MAX_LEN];
int n, base;
int values[26];

int char_to_int(char c) {
    return values[c - 'A'];
}

int string_to_int(char* s) {
    int result = 0;
    for (int i = 0; s[i]; i++) {
        result = result * base + char_to_int(s[i]);
    }
    return result;
}

int check() {
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            int a = char_to_int(symbols[i]);
            int b = char_to_int(symbols[j]);
            int sum = string_to_int(table[i][j]);
            if (a + b != sum) {
                return 0;
            }
        }
    }
    return 1;
}

int solve(int pos) {
    if (pos == n - 1) {
        return check();
    }
    for (int i = 0; i < base; i++) {
        if (values[symbols[pos] - 'A'] == -1) {
            int used = 0;
            for (int j = 0; j < pos; j++) {
                if (values[symbols[j] - 'A'] == i) {
                    used = 1;
                    break;
                }
            }
            if (!used) {
                values[symbols[pos] - 'A'] = i;
                if (solve(pos + 1)) return 1;
                values[symbols[pos] - 'A'] = -1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    scanf("%s", table[0][0]);
    for (int i = 1; i < n; i++) {
        scanf("%s", &symbols[i]);
        for (int j = 1; j < n; j++) {
            scanf("%s", table[i][j]);
        }
    }

    memset(values, -1, sizeof(values));
    for (base = n - 1; base <= 16; base++) {
        if (solve(1)) {
            for (int i = 1; i < n; i++) {
                printf("%c=%d ", symbols[i], values[symbols[i] - 'A']);
            }
            printf("\n%d\n", base);
            return 0;
        }
    }

    printf("ERROR!\n");
    return 0;
}