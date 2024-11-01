#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start_time;
    int start_station;
    int end_station;
} Passenger;

int compare(const void *a, const void *b) {
    Passenger *p1 = (Passenger *)a;
    Passenger *p2 = (Passenger *)b;
    if (p1->start_time == p2->start_time) {
        return p1->start_station - p2->start_station;
    }
    return p1->start_time - p2->start_time;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    int *time = (int *)malloc((n - 1) * sizeof(int));
    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &time[i]);
    }
    
    Passenger *passengers = (Passenger *)malloc(m * sizeof(Passenger));
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &passengers[i].start_time, &passengers[i].start_station, &passengers[i].end_station);
    }
    
    qsort(passengers, m, sizeof(Passenger), compare);
    
    int *max_time = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < m; i++) {
        for (int j = passengers[i].start_station; j < passengers[i].end_station; j++) {
            max_time[j] = max_time[j] > passengers[i].start_time ? max_time[j] : passengers[i].start_time;
        }
    }
    
    int *travel_time = (int *)calloc(n, sizeof(int));
    int current_time = 0;
    for (int i = 0; i < n - 1; i++) {
        if (current_time < max_time[i]) {
            current_time = max_time[i];
        }
        travel_time[i] = current_time;
        current_time += time[i];
    }
    
    int total_travel_time = 0;
    for (int i = 0; i < m; i++) {
        total_travel_time += travel_time[passengers[i].end_station - 1] - passengers[i].start_time;
    }
    
    for (int i = 0; i < n - 1 && k > 0; i++) {
        int max_reduction = 0;
        int max_reduction_index = -1;
        for (int j = i; j < n - 1 && k > 0; j++) {
            if (time[j] > 0) {
                int reduction = travel_time[j] - travel_time[j + 1];
                if (reduction > max_reduction) {
                    max_reduction = reduction;
                    max_reduction_index = j;
                }
            }
        }
        if (max_reduction_index != -1) {
            time[max_reduction_index]--;
            k--;
            for (int j = 0; j < m; j++) {
                if (passengers[j].start_station <= max_reduction_index + 1 && passengers[j].end_station > max_reduction_index + 1) {
                    travel_time[max_reduction_index]--;
                }
            }
        }
    }
    
    for (int i = 0; i < m; i++) {
        total_travel_time += travel_time[passengers[i].end_station - 1] - passengers[i].start_time;
    }
    
    printf("%d\n", total_travel_time);
    
    free(time);
    free(passengers);
    free(max_time);
    free(travel_time);
    
    return 0;
}