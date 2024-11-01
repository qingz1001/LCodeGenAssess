#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 10000
#define MAX_K 100000

int n, m, k;
int D[MAX_N];
struct Passenger {
    int T, A, B;
} passengers[MAX_M];

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &D[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &passengers[i].T, &passengers[i].A, &passengers[i].B);
    }

    // Sort passengers by their arrival time
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (passengers[j].T > passengers[j + 1].T) {
                struct Passenger temp = passengers[j];
                passengers[j] = passengers[j + 1];
                passengers[j + 1] = temp;
            }
        }
    }

    int total_time = 0;
    int current_time = 0;
    int remaining_k = k;

    for (int i = 0; i < m; i++) {
        int passenger_arrival_time = passengers[i].T;
        int passenger_start_time = max(current_time, passenger_arrival_time);
        int passenger_travel_time = passenger_start_time + D[passenger_start_time - 1] * (passengers[i].B - passengers[i].A);

        if (remaining_k >= (passenger_travel_time - passenger_arrival_time)) {
            passenger_travel_time -= passenger_arrival_time;
            remaining_k -= (passenger_travel_time - passenger_arrival_time);
        } else {
            passenger_travel_time -= remaining_k;
            remaining_k = 0;
        }

        total_time += passenger_travel_time - passenger_arrival_time;
        current_time = passenger_travel_time;
    }

    printf("%d\n", total_time);
    return 0;
}