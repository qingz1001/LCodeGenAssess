#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int ax, ay, bx, by;
        scanf("%d %d %d %d", &ax, &ay, &bx, &by);
        if ((ax == bx && ay != by) || (ax != bx && ay == by)) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }
    return 0;
}