#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 10
#define MAX_LEN 10

char table[MAX_N][MAX_N][MAX_LEN];
char letters[MAX_N];
int values[MAX_N];
int n;

bool is_valid(int base) {
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            int a = values[i-1];
            int b = values[j-1];
            int sum = a + b;
            int len = strlen(table[i][j]);
            for (int k = len - 1; k >= 0; k--) {
                char c = table[i][j][k];
                int index = strchr(letters, c) - letters;
                if (values[index] != sum % base) return false;
                sum /= base;
            }
            if (sum > 0) return false;
        }
    }
    return true;
}

bool solve(int index, int base) {
    if (index == n - 1) {
        return is_valid(base);
    }
    for (int i = 0; i < base; i++) {
        bool used = false;
        for (int j = 0; j < index; j++) {
            if (values[j] == i) {
                used = true;
                break;
            }
        }
        if (!used) {
            values[index] = i;
            if (solve(index + 1, base)) return true;
        }
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%s", table[i][j]);
        }
    }
    
    for (int i = 1; i < n; i++) {
        letters[i-1] = table[i][0][0];
    }
    letters[n-1] = '\0';
    
    for (int base = n - 1; base <= 36; base++) {
        if (solve(0, base)) {
            for (int i = 0; i < n - 1; i++) {
                printf("%c=%d ", letters[i], values[i]);
            }
            printf("\n%d\n", base);
            return 0;
        }
    }
    
    printf("ERROR!\n");
    return 0;
}