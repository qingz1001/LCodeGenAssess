#include <stdio.h>

#define MAX_COWS 1001
#define MAX_BARNS 21

int barns[MAX_BARNS];
int cow_preferences[MAX_COWS][MAX_BARNS];
int assigned[MAX_BARNS];
int happiness[MAX_COWS];
int min_range = MAX_BARNS;

void backtrack(int current_cow, int max_rank) {
    if (current_cow == MAX_COWS) {
        int max_happiness = 0;
        int min_happiness = MAX_BARNS;
        for (int i = 1; i <= MAX_BARNS; i++) {
            if (assigned[i] > 0) {
                if (happiness[i] > max_happiness) max_happiness = happiness[i];
                if (happiness[i] < min_happiness) min_happiness = happiness[i];
            }
        }
        if (max_happiness - min_happiness < min_range) {
            min_range = max_happiness - min_happiness;
        }
        return;
    }

    for (int i = 1; i <= MAX_BARNS; i++) {
        if (assigned[i] < barns[i]) {
            assigned[i]++;
            happiness[i] = cow_preferences[current_cow][assigned[i] - 1];
            backtrack(current_cow + 1, max_rank);
            happiness[i] = 0;
            assigned[i]--;
        }
    }
}

int main() {
    int N, B;
    scanf("%d %d", &N, &B);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= B; j++) {
            scanf("%d", &cow_preferences[i][j]);
        }
    }

    for (int i = 1; i <= B; i++) {
        scanf("%d", &barns[i]);
    }

    backtrack(1, B);

    printf("%d\n", min_range);

    return 0;
}