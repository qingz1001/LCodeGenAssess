#include <stdio.h>
#include <stdlib.h>

#define MOD 10000

typedef struct {
    int *data;
    int size;
} String;

void initString(String *s, int length) {
    s->data = (int *)malloc(length * sizeof(int));
    s->size = length;
}

void freeString(String *s) {
    free(s->data);
}

int hash(String *s, int mod) {
    long long h = 0;
    for (int i = 0; i < s->size; i++) {
        h = (h * 10 + s->data[i]) % mod;
    }
    return (int)h;
}

int main() {
    int n, t;
    scanf("%d %d", &n, &t);

    String *chiefs = (String *)malloc(t * sizeof(String));
    for (int i = 0; i < t; i++) {
        int m;
        scanf("%d", &m);
        initString(&chiefs[i], m);
        for (int j = 0; j < m; j++) {
            scanf("%d", &chiefs[i].data[j]);
        }
    }

    int *results = (int *)calloc(t, sizeof(int));

    for (int i = 0; i < t; i++) {
        int targetHash = hash(&chiefs[i], MOD);
        int maxTime = 0;
        for (int j = 0; j < n; j++) {
            int time = 0;
            int currentHash = 0;
            for (int k = 0; k < chiefs[i].size; k++) {
                if (j + k >= n) break;
                currentHash = (currentHash * 10 + (j + k + 1)) % MOD;
                if (currentHash == targetHash) {
                    time = k + 1;
                    break;
                }
            }
            if (time > maxTime) {
                maxTime = time;
            }
        }
        results[i] = maxTime;
    }

    for (int i = 0; i < t; i++) {
        printf("%04d\n", results[i]);
    }

    for (int i = 0; i < t; i++) {
        freeString(&chiefs[i]);
    }
    free(chiefs);
    free(results);

    return 0;
}