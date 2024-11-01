#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 16

int main() {
    int n;
    char s[MAX_N];
    scanf("%d %s", &n, s);

    // Initialize positions
    char positions[MAX_N];
    for (int i = 0; i < n; i++) {
        positions[i] = 'A';
    }

    // Process each train
    for (int i = 0; i < n; i++) {
        char target = s[i];
        int found = 0;

        // Find the first train that can move to the next station
        for (int j = 0; j < n; j++) {
            if (positions[j] == target) {
                if (j + 1 < n && positions[j + 1] == 'B') {
                    printf("%c A B\n", target);
                    positions[j + 1] = target;
                    positions[j] = 'B';
                    found = 1;
                    break;
                } else if (j + 2 < n && positions[j + 2] == 'C') {
                    printf("%c A C\n", target);
                    positions[j + 2] = target;
                    positions[j] = 'C';
                    found = 1;
                    break;
                }
            }
        }

        // If no valid move is found, output "NO" and exit
        if (!found) {
            printf("NO\n");
            return 0;
        }
    }

    // Move trains from B and C to D
    for (int i = n - 1; i >= 0; i--) {
        if (positions[i] == 'B' || positions[i] == 'C') {
            printf("%c %c D\n", positions[i], positions[i]);
            positions[i] = 'D';
        }
    }

    return 0;
}