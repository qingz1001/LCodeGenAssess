#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 256

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    char names[n][MAX_NAME_LEN];
    for (int i = 0; i < n; i++) {
        scanf("%s", names[i]);
    }

    char targets[m][MAX_NAME_LEN];
    for (int i = 0; i < m; i++) {
        scanf("%s", targets[i]);
    }

    int play_count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (strncmp(names[j], targets[i], strlen(targets[i])) == 0) {
                play_count++;
                break;
            }
        }
    }

    printf("%d\n", play_count);

    long long arrangements = 1;
    for (int i = 0; i < n; i++) {
        arrangements *= 3;
    }

    printf("%lld\n", arrangements);

    return 0;
}