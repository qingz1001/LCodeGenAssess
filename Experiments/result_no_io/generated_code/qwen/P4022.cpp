#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 1000
#define MAX_LEN 1100000

int n, m;
char library[MAX_M][MAX_LEN];
char essays[MAX_N][MAX_LEN];

int is_substring(const char *haystack, const char *needle) {
    return strstr(haystack, needle) != NULL;
}

int find_L0(int essay_index, int min_length) {
    const char *essay = essays[essay_index];
    int len = strlen(essay);
    int familiar_count = 0;

    for (int i = 0; i <= len - min_length; i++) {
        if (is_substring(library[0], essay + i)) {
            familiar_count += min_length;
            break;
        }
    }

    if (familiar_count == 0) return 0;

    int total_familiar = familiar_count;
    int remaining_length = len - familiar_count;

    for (int i = 1; i < m && remaining_length > 0; i++) {
        for (int j = 0; j <= remaining_length - min_length; j++) {
            if (is_substring(library[i], essay + familiar_count + j)) {
                familiar_count += min_length;
                remaining_length -= min_length;
                break;
            }
        }
    }

    return familiar_count >= 0.9 * len ? min_length : 0;
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
        int l = 1, r = strlen(essays[i]), result = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (find_L0(i, mid)) {
                result = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        printf("%d\n", result);
    }

    return 0;
}