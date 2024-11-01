#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int health = 10, experience = 0, level = 0;

    for (int i = 0; i < n; i++) {
        int x, a;
        scanf("%d %d", &x, &a);
        if (health - x <= 0) {
            break;
        }
        health -= x;
        experience += a;
        while (experience >= (1 << level)) {
            level++;
            experience -= (1 << (level - 1));
        }
    }

    printf("%d %d\n", level, experience);
    return 0;
}