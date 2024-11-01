#include <stdio.h>
#include <string.h>

#define MAX_N 10000
#define MAX_M 10000
#define MAX_LEN 255

char names[MAX_N][MAX_LEN];
char queries[MAX_M][MAX_LEN];

int is_prefix(const char *str, const char *prefix) {
    while (*prefix && *str == *prefix) {
        str++;
        prefix++;
    }
    return *prefix == '\0';
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%s", names[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%s", queries[i]);
    }

    int play_count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (is_prefix(names[j], queries[i])) {
                play_count++;
                break;
            }
        }
    }

    printf("%d\n", play_count);

    // Calculate the number of possible permutations
    int permutations = 1;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            permutations *= 2; // 1 or 2
        } else if (i == n - 1) {
            permutations *= 2; // n-1 or n
        } else {
            permutations *= 3; // i-1, i, or i+1
        }
    }

    printf("%d\n", permutations);

    return 0;
}