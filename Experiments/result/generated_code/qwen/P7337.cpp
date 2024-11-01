#include <stdio.h>

int main() {
    int n, m, type;
    scanf("%d %d %d", &n, &m, &type);

    int t[n], q[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &q[i]);
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (t[i] == 1 && q[i] == 1) {
            count++;
        }
    }

    int result = n - count + (count >= m ? m : count);
    printf("%d\n", result);

    return 0;
}