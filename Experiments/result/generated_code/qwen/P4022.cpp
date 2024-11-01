#include <stdio.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 1000
#define MAX_LEN 1100000

int n, m;
char library[MAX_M][MAX_LEN];
char essays[MAX_N][MAX_LEN];

int is_substring(const char *str, const char *sub) {
    return strstr(str, sub) != NULL;
}

int find_L0(int essay_index, int min_length) {
    char *essay = essays[essay_index];
    int len = strlen(essay);
    int familiar_len = 0;

    for (int i = 0; i <= len - min_length; i++) {
        if (is_substring(library[0], essay + i)) {
            familiar_len += min_length;
            break;
        }
    }

    for (int j = 1; j < m; j++) {
        for (int i = 0; i <= len - min_length; i++) {
            if (is_substring(library[j], essay + i)) {
                familiar_len += min_length;
                break;
            }
        }
    }

    return familiar_len >= (len * 9) / 10 ? min_length : 0;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%s", library[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%s", essays[i]);
    }

    for (int i = 0; i < n; i++) {
        int L0 = 0;
        int len = strlen(essays[i]);
        for (int l = len; l > 0; l--) {
            if (find_L0(i, l) > 0) {
                L0 = l;
                break;
            }
        }
        printf("%d\n", L0);
    }

    return 0;
}