#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *scores = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &scores[i]);
    }

    // Sort the scores in descending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (scores[i] < scores[j]) {
                int temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }

    // Determine the minimum number of gifts needed
    int min_gifts = k;
    for (int i = k; i < n; i++) {
        if (scores[i] != scores[i - 1]) {
            min_gifts++;
        } else {
            break;
        }
    }

    printf("%d\n", min_gifts);

    free(scores);
    return 0;
}