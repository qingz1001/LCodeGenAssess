#include <stdio.h>
#include <stdlib.h>

int books[501], assignments[501][2];

void print_assignments(int m, int k) {
    for (int i = 0; i < k; i++) {
        printf("%d %d\n", assignments[i][0], assignments[i][1]);
    }
}

void assign_books(int m, int k) {
    int left = 0, right = 0, sum = 0;
    for (int i = 0; i < m; i++) {
        right += books[i];
        while (sum >= right) {
            sum -= left;
            left++;
        }
        sum += right;
        assignments[k - 1][0] = left;
        assignments[k - 1][1] = i;
        k--;
        if (k == 0) break;
    }
    for (int i = 0; i < k - 1; i++) {
        assignments[i][0] = assignments[i + 1][0] + 1;
        assignments[i][1] = assignments[i + 1][1];
    }
}

int main() {
    int m, k;
    scanf("%d %d", &m, &k);
    for (int i = 0; i < m; i++) {
        scanf("%d", &books[i]);
    }
    assign_books(m, k);
    print_assignments(m, k);
    return 0;
}