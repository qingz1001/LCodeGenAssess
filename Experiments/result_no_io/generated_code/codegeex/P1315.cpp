#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int t;
    int a;
    int b;
} Passenger;

int compare(const void *a, const void *b) {
    Passenger *p1 = (Passenger *)a;
    Passenger *p2 = (Passenger *)b;
    return p1->a - p2->a;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    int D[n-1];
    for (int i = 0; i < n-1; i++) {
        scanf("%d", &D[i]);
    }

    Passenger passengers[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &passengers[i].t, &passengers[i].a, &passengers[i].b);
    }

    // Sort passengers by their arrival time at the starting point
    qsort(passengers, m, sizeof(Passenger), compare);

    // Calculate the earliest time the bus can leave each station
    int earliest[n];
    earliest[0] = 0;
    for (int i = 1; i < n; i++) {
        earliest[i] = earliest[i-1] + D[i-1];
    }

    // Apply k accelerators optimally
    for (int i = 0; i < k; i++) {
        int max_gain = 0;
        int max_gain_index = -1;
        for (int j = 0; j < n-1; j++) {
            if (D[j] > 0) {
                int gain = 0;
                for (int p = 0; p < m; p++) {
                    if (passengers[p].a <= j+1 && passengers[p].b > j+1) {
                        gain += (earliest[j+1] + D[j] - passengers[p].t);
                    }
                }
                if (gain > max_gain) {
                    max_gain = gain;
                    max_gain_index = j;
                }
            }
        }
        if (max_gain_index != -1) {
            D[max_gain_index]--;
        }
    }

    // Calculate the total travel time for all passengers
    int total_travel_time = 0;
    for (int i = 0; i < m; i++) {
        int arrival_time = earliest[passengers[i].b-1] + D[passengers[i].b-2];
        total_travel_time += arrival_time - passengers[i].t;
    }

    printf("%d\n", total_travel_time);
    return 0;
}