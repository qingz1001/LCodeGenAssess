#include <stdio.h>
#include <stdlib.h>

#define MOD 10000

typedef struct {
    int length;
    int *name;
} Leader;

int main() {
    int n, t;
    scanf("%d %d", &n, &t);
    Leader leaders[t];
    for (int i = 0; i < t; i++) {
        scanf("%d", &leaders[i].length);
        leaders[i].name = (int *)malloc(leaders[i].length * sizeof(int));
        for (int j = 0; j < leaders[i].length; j++) {
            scanf("%d", &leaders[i].name[j]);
        }
    }

    long long total_time = 0;
    for (int i = 0; i < t; i++) {
        long long time = 0;
        int pos = 0;
        for (int j = 0; j < leaders[i].length; j++) {
            while (pos > 0 && leaders[i].name[pos - 1] != leaders[i].name[j]) {
                pos--;
            }
            if (pos == 0) {
                time += n + 1;
            } else {
                time += n - pos + 1;
            }
            pos++;
        }
        total_time += time;
    }

    printf("%04lld\n", total_time % MOD);

    for (int i = 0; i < t; i++) {
        free(leaders[i].name);
    }

    return 0;
}