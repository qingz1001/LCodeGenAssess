#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 400000
#define MAXC 100

int n, c, q;
int ship_lengths[MAXC], ship_counts[MAXC];
int attack_positions[MAXN];

int can_place_ships(int position, int index) {
    if (index == c) {
        return 1;
    }
    int ship_length = ship_lengths[index];
    int ship_count = ship_counts[index];
    for (int i = 0; i < ship_count; i++) {
        if (position + ship_length <= n) {
            if (can_place_ships(position + ship_length, index + 1)) {
                return 1;
            }
        }
        position++;
    }
    return 0;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d", &n, &c, &q);
        for (int i = 0; i < c; i++) {
            scanf("%d %d", &ship_lengths[i], &ship_counts[i]);
        }
        for (int i = 0; i < q; i++) {
            scanf("%d", &attack_positions[i]);
        }

        int max_attack = 0;
        for (int i = 0; i < q; i++) {
            if (attack_positions[i] > max_attack) {
                max_attack = attack_positions[i];
            }
        }

        if (!can_place_ships(1, 0)) {
            printf("0\n");
            continue;
        }

        int min_attack_to_defeat = -1;
        for (int i = 1; i <= max_attack; i++) {
            if (!can_place_ships(i, 0)) {
                min_attack_to_defeat = i;
                break;
            }
        }

        if (min_attack_to_defeat == -1) {
            printf("-1\n");
        } else {
            printf("%d\n", min_attack_to_defeat);
        }
    }
    return 0;
}