#include <stdio.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 100000
#define MAX_WORD_LEN 11

int n, m;
char words[MAX_N][MAX_WORD_LEN];
char article[MAX_M][MAX_WORD_LEN];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%s", article[i]);
    }

    int max_count = 0;
    int min_length = m + 1;

    for (int start = 0; start < m; start++) {
        int count = 0;
        int length = 0;
        char seen[MAX_WORD_LEN] = {0};
        for (int end = start; end < m; end++) {
            if (!seen[article[end][0]]) {
                for (int j = 0; j < n; j++) {
                    if (strcmp(words[j], article[end]) == 0) {
                        count++;
                        break;
                    }
                }
                seen[article[end][0]] = 1;
            }
            length++;
            if (count > max_count || (count == max_count && length < min_length)) {
                max_count = count;
                min_length = length;
            }
        }
    }

    printf("%d\n%d\n", max_count, min_length);

    return 0;
}