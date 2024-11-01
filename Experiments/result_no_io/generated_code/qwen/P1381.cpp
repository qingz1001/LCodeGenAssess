#include <stdio.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 100000
#define MAX_WORD_LEN 11

int main() {
    int n, m;
    char to_learn[MAX_N][MAX_WORD_LEN];
    char article[MAX_M][MAX_WORD_LEN];
    int count[MAX_M] = {0};
    int max_count = 0;
    int min_length = INT_MAX;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", to_learn[i]);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%s", article[i]);
    }

    for (int start = 0; start < m; start++) {
        memset(count, 0, sizeof(count));
        int current_count = 0;
        for (int end = start; end < m; end++) {
            if (strcmp(article[end], to_learn[0]) == 0) {
                count[0]++;
                current_count++;
            }
            for (int j = 1; j < n && count[j - 1] > 0; j++) {
                if (strcmp(article[end], to_learn[j]) == 0) {
                    count[j]++;
                    current_count++;
                } else {
                    break;
                }
            }
            if (current_count > max_count || (current_count == max_count && end - start + 1 < min_length)) {
                max_count = current_count;
                min_length = end - start + 1;
            }
        }
    }

    printf("%d\n%d\n", max_count, min_length);

    return 0;
}