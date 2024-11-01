#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100

int n;
int knows[MAXN + 1][MAXN + 1];
int group[MAXN + 1];

bool can_place_in_group(int person, int g) {
    for (int i = 1; i <= n; i++) {
        if (knows[person][i] && group[i] != g) {
            return false;
        }
    }
    return true;
}

bool dfs(int person) {
    if (person > n) return true;

    for (int g = 1; g <= 2; g++) {
        if (can_place_in_group(person, g)) {
            group[person] = g;
            if (dfs(person + 1)) return true;
            group[person] = 0;
        }
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int j = 1;
        while (1) {
            scanf("%d", &knows[i][j]);
            if (knows[i][j] == 0) break;
            j++;
        }
    }

    if (!dfs(1)) {
        printf("No solution\n");
        return 0;
    }

    int count1 = 0, count2 = 0;
    int group1[MAXN], group2[MAXN];
    for (int i = 1; i <= n; i++) {
        if (group[i] == 1) group1[count1++] = i;
        else group2[count2++] = i;
    }

    printf("%d", count1);
    for (int i = 0; i < count1; i++) printf(" %d", group1[i]);
    printf("\n%d", count2);
    for (int i = 0; i < count2; i++) printf(" %d", group2[i]);
    printf("\n");

    return 0;
}