#include <stdio.h>
#include <limits.h>

#define N 5
#define KM 10
#define TOTAL_KM 25

int times[N][KM];
int best_time = INT_MAX;
int best_assignment[N];

void dfs(int athlete, int current_km, int current_time, int assignment[N]) {
    if (current_km == TOTAL_KM) {
        if (current_time < best_time) {
            best_time = current_time;
            for (int i = 0; i < N; i++) {
                best_assignment[i] = assignment[i];
            }
        }
        return;
    }

    if (athlete >= N) return;

    for (int km = 1; km <= KM; km++) {
        if (current_km + km > TOTAL_KM) break;
        assignment[athlete] = km;
        dfs(athlete + 1, current_km + km, current_time + times[athlete][km - 1], assignment);
        assignment[athlete] = 0;
    }
}

int main() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < KM; j++) {
            scanf("%d", &times[i][j]);
        }
    }

    int assignment[N] = {0};
    dfs(0, 0, 0, assignment);

    printf("%d\n", best_time);
    for (int i = 0; i < N; i++) {
        printf("%d ", best_assignment[i]);
    }
    printf("\n");

    return 0;
}