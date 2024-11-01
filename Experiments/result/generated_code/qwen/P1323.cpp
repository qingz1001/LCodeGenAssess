#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Node;

int compare(const void *a, const void *b) {
    return ((Node *)b)->value - ((Node *)a)->value;
}

void removeDigits(int *digits, int length, int m) {
    for (int i = 0; i < m; i++) {
        int maxIndex = 0;
        for (int j = 1; j < length; j++) {
            if (digits[j] > digits[maxIndex]) {
                maxIndex = j;
            }
        }
        for (int j = maxIndex; j < length - 1; j++) {
            digits[j] = digits[j + 1];
        }
        length--;
    }
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);

    Node nodes[k];
    for (int i = 0; i < k; i++) {
        nodes[i].value = 1;
        nodes[i].index = i;
    }

    for (int i = 0; i < k; i++) {
        int p = nodes[i].value;
        nodes[k + 2 * i].value = 2 * p + 1;
        nodes[k + 2 * i].index = i;
        nodes[k + 2 * i + 1].value = 4 * p + 5;
        nodes[k + 2 * i + 1].index = i;
    }

    qsort(nodes, k * 2, sizeof(Node), compare);

    int digits[k * 2];
    for (int i = 0; i < k * 2; i++) {
        digits[i] = nodes[i].value;
    }

    printf("%d\n", digits[0]);
    removeDigits(digits, k * 2, m);
    printf("%d\n", digits[0]);

    return 0;
}