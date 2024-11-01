#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define INF 0x3f3f3f3f

int n, m, k;
int D[MAXN];
struct Passenger {
    int t, a, b;
} passengers[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void solve() {
    for (int i = 1; i <= n - 1; i++) {
        scanf("%d", &D[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &passengers[i].t, &passengers[i].a, &passengers[i].b);
    }

    // Sort passengers by their arrival time
    qsort(passengers, m, sizeof(struct Passenger), [](const void *a, const void *b) {
        return ((struct Passenger *)a)->t - ((struct Passenger *)b)->t;
    });

    int current_time = 0;
    int total_travel_time = 0;

    for (int i = 0; i < m; i++) {
        int passenger_time = passengers[i].t;
        int start_point = passengers[i].a;
        int end_point = passengers[i].b;

        if (current_time < passenger_time) {
            current_time = passenger_time;
        }

        int travel_time = 0;
        for (int j = start_point; j < end_point; j++) {
            if (current_time + D[j - 1] > passenger_time) {
                int wait_time = current_time + D[j - 1] - passenger_time;
                if (wait_time > 0 && k > 0) {
                    wait_time = min(wait_time, k);
                    k -= wait_time;
                }
                current_time += wait_time;
            }
            current_time += D[j - 1];
            travel_time += current_time - passenger_time;
        }

        total_travel_time += travel_time;
    }

    printf("%d\n", total_travel_time);
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    solve();
    return 0;
}