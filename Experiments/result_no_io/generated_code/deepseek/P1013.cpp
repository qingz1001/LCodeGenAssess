#include <stdio.h>
#include <string.h>

#define MAXN 10

int n;
char table[MAXN][MAXN][3];
char letters[MAXN];
int values[MAXN];

int find_letter_index(char c) {
    for (int i = 0; i < n; i++) {
        if (letters[i] == c) return i;
    }
    return -1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%s", table[i][j]);
        }
    }

    // Extract letters from the first row
    for (int i = 1; i < n; i++) {
        letters[i-1] = table[0][i][0];
    }

    // Assign values to letters
    for (int i = 0; i < n-1; i++) {
        values[i] = i;
    }

    // Check the table for consistency
    int base = n - 1;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            int len = strlen(table[i][j]);
            if (len == 1) {
                int val = find_letter_index(table[i][j][0]);
                if (val == -1 || (values[i-1] + values[j-1]) % base != val) {
                    printf("ERROR!\n");
                    return 0;
                }
            } else if (len == 2) {
                int val1 = find_letter_index(table[i][j][0]);
                int val2 = find_letter_index(table[i][j][1]);
                if (val1 == -1 || val2 == -1 || (values[i-1] + values[j-1]) / base != val1 || (values[i-1] + values[j-1]) % base != val2) {
                    printf("ERROR!\n");
                    return 0;
                }
            } else {
                printf("ERROR!\n");
                return 0;
            }
        }
    }

    // Output the results
    for (int i = 0; i < n-1; i++) {
        printf("%c=%d ", letters[i], values[i]);
    }
    printf("\n%d\n", base);

    return 0;
}