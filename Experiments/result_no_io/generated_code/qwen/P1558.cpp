#include <stdio.h>
#include <stdlib.h>

#define MAX_L 100000
#define MAX_T 30
#define MAX_O 100000

int main() {
    int L, T, O;
    scanf("%d %d %d", &L, &T, &O);

    int *colors = (int *)malloc((L + 1) * sizeof(int));
    for (int i = 1; i <= L; i++) {
        colors[i] = 1;
    }

    for (int i = 0; i < O; i++) {
        char action[2];
        scanf("%s", action);
        if (action[0] == 'C') {
            int A, B, C;
            scanf("%d %d %d", &A, &B, &C);
            if (A > B) {
                int temp = A;
                A = B;
                B = temp;
            }
            for (int j = A; j <= B; j++) {
                colors[j] = C;
            }
        } else if (action[0] == 'P') {
            int A, B;
            scanf("%d %d", &A, &B);
            if (A > B) {
                int temp = A;
                A = B;
                B = temp;
            }
            int count[MAX_T + 1] = {0};
            for (int j = A; j <= B; j++) {
                count[colors[j]] = 1;
            }
            int result = 0;
            for (int j = 1; j <= T; j++) {
                if (count[j] == 1) {
                    result++;
                }
            }
            printf("%d\n", result);
        }
    }

    free(colors);
    return 0;
}