#include <stdio.h>

void combination(int n, int r, int k, int data[]) {
    static int solution[21];
    int i;
    if (k == r) {
        for (i = 0; i < r; i++) {
            printf("%3d", solution[i]);
        }
        printf("\n");
    } else {
        for (i = data[k-1] + 1; i <= n; i++) {
            solution[k] = i;
            combination(n, r, k + 1, data);
        }
    }
}

int main() {
    int n, r;
    scanf("%d %d", &n, &r);
    combination(n, r, 0, NULL);
    return 0;
}