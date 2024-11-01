#include <stdio.h>
#include <string.h>

#define MAX_LEN 100001
#define MAX_COLORS 31

int main() {
    int L, T, O;
    scanf("%d %d %d", &L, &T, &O);

    int color[MAX_LEN] = {0}; // 初始化所有方格的颜色为0（即无颜色）

    char command[3];
    int A, B, C;

    for (int i = 0; i < O; i++) {
        scanf("%s %d %d", command, &A, &B);

        if (command[0] == 'C') {
            scanf("%d", &C);
            if (A > B) {
                int temp = A;
                A = B;
                B = temp;
            }
            for (int j = A; j <= B; j++) {
                color[j] = C;
            }
        } else if (command[0] == 'P') {
            if (A > B) {
                int temp = A;
                A = B;
                B = temp;
            }
            int count[MAX_COLORS] = {0};
            for (int j = A; j <= B; j++) {
                count[color[j]]++;
            }
            int result = 0;
            for (int j = 1; j <= T; j++) {
                if (count[j] > 0) {
                    result++;
                }
            }
            printf("%d\n", result);
        }
    }

    return 0;
}