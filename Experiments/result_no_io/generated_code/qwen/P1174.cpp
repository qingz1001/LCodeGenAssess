#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_M 200

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int score[MAX_M];
    char reward[MAX_M];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d %c", &score[j], &reward[j]);
        }
    }

    while (k > 0) {
        int max_score = -1;
        int max_index = -1;

        for (int j = 0; j < m; j++) {
            if (score[j] > max_score) {
                max_score = score[j];
                max_index = j;
            }
        }

        if (max_index != -1) {
            score[max_index] = 0;
            k--;
            if (reward[max_index] == 'Y') {
                k++;
            }
        } else {
            break;
        }
    }

    int total_score = 0;
    for (int j = 0; j < m; j++) {
        total_score += score[j];
    }

    printf("%d\n", total_score);

    return 0;
}