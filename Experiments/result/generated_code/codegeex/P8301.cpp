#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char a[1005], b[1005];
    scanf("%s", a);
    scanf("%s", b);

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}