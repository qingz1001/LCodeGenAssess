#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int tech_innovators[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &tech_innovators[i]);
    }

    int special_contributors[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &special_contributors[i]);
    }

    // Using a boolean array to mark the winners of the special contribution award
    bool special_winner[n];
    for (int i = 0; i < n; i++) {
        special_winner[i] = false;
    }

    // Mark the winners of the special contribution award
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (special_contributors[i] == tech_innovators[j]) {
                special_winner[j] = true;
                break;
            }
        }
    }

    // Output the winners who received both awards
    for (int i = 0; i < n; i++) {
        if (special_winner[i]) {
            printf("%d ", tech_innovators[i]);
        }
    }

    return 0;
}