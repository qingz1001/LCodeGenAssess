#include <stdio.h>

int main() {
    int n, w;
    scanf("%d %d", &n, &w);
    int arr[n+1];
    for (int i = 1; i <= n; i++) {
        arr[i] = 0;
    }
    while (w--) {
        int op, a, b;
        scanf("%d %d %d", &op, &a, &b);
        if (op == 1) {
            arr[a] += b;
        } else if (op == 2) {
            long long sum = 0;
            for (int i = a; i <= b; i++) {
                sum += arr[i];
            }
            printf("%lld\n", sum);
        }
    }
    return 0;
}