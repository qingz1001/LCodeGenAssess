#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int initial_health = 10;
    int total_experience = 0;

    for (int i = 0; i < n; i++) {
        int x, a;
        scanf("%d %d", &x, &a);

        // Calculate new health
        initial_health -= x;
        if (initial_health <= 0) {
            break; // Player dies, stop further operations
        }
        if (initial_health > 10) {
            initial_health = 10; // Health cannot exceed 10
        }

        // Add experience
        total_experience += a;
    }

    // Calculate level
    int level = 0;
    while (total_experience >= (1 << level)) {
        total_experience -= (1 << level);
        level++;
    }

    printf("%d %d\n", level, total_experience);
    return 0;
}