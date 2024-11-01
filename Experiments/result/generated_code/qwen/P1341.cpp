#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 26
#define MAX_LEN 500

typedef struct {
    char a, b;
} Pair;

int compare(const void *a, const void *b) {
    return ((Pair *)a)->a - ((Pair *)b)->a;
}

void findString(int n, Pair pairs[], char result[]) {
    int used[MAX_N] = {0};
    for (int i = 0; i < n; i++) {
        if (!used[pairs[i].a]) {
            result[0] = pairs[i].a;
            used[pairs[i].a] = 1;
            break;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            if (pairs[j].a == result[i - 1] && !used[pairs[j].b]) {
                result[i] = pairs[j].b;
                used[pairs[j].b] = 1;
                break;
            } else if (pairs[j].b == result[i - 1] && !used[pairs[j].a]) {
                result[i] = pairs[j].a;
                used[pairs[j].a] = 1;
                break;
            }
        }
    }

    for (int i = 0; i < n + 1; i++) {
        for (int j = i + 1; j < n + 1; j++) {
            if (result[i] > result[j]) {
                char temp = result[i];
                result[i] = result[j];
                result[j] = temp;
            }
        }
    }

    result[n + 1] = '\0';
}

int main() {
    int n;
    scanf("%d", &n);
    Pair pairs[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf(" %c%c", &pairs[i].a, &pairs[i].b);
    }

    qsort(pairs, n, sizeof(Pair), compare);

    char result[MAX_LEN];
    findString(n, pairs, result);

    for (int i = 0; i < n + 1; i++) {
        printf("%c", result[i]);
    }
    printf("\n");

    return 0;
}