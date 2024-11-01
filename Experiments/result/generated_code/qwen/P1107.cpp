#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000
#define MAX_H 2000
#define MAX_NI 5000

int main() {
    int N, H, Delta;
    scanf("%d %d %d", &N, &H, &Delta);

    int trees[MAX_N][MAX_NI];
    int max_sweet = 0;

    for (int i = 0; i < N; ++i) {
        int Ni;
        scanf("%d", &Ni);
        for (int j = 0; j < Ni; ++j) {
            scanf("%d", &trees[i][j]);
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < trees[i][0]; ++j) {
            int height = trees[i][j];
            if (height + Delta <= H) {
                int current_sweet = 1;
                int next_tree = -1;
                for (int k = 0; k < N; ++k) {
                    if (k != i && trees[k][0] > 0 && trees[k][0] < trees[next_tree][0]) {
                        next_tree = k;
                    }
                }
                if (next_tree != -1) {
                    current_sweet += trees[next_tree][0];
                }
                max_sweet = (current_sweet > max_sweet) ? current_sweet : max_sweet;
            }
        }
    }

    printf("%d\n", max_sweet);

    return 0;
}