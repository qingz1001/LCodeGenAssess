#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50
#define MAX_M 300

typedef struct {
    int start_pos;
    int start_time;
    int travel_time;
} PatrolCar;

int n, m;
PatrolCar patrol_cars[MAX_M];

int time_to_seconds(int hhmmss) {
    int hours = hhmmss / 10000;
    int minutes = (hhmmss % 10000) / 100;
    int seconds = hhmmss % 100;
    return hours * 3600 + minutes * 60 + seconds;
}

int seconds_to_time(int seconds) {
    int hours = seconds / 3600;
    seconds %= 3600;
    int minutes = seconds / 60;
    seconds %= 60;
    return hours * 10000 + minutes * 100 + seconds;
}

int min_encounters(int target_time) {
    int encounters = 0;
    for (int i = 0; i < m; i++) {
        int patrol_start_time = time_to_seconds(patrol_cars[i].start_time);
        int patrol_end_time = patrol_start_time + patrol_cars[i].travel_time;
        int target_end_time = target_time + (patrol_cars[i].start_pos - 1) * 600;

        if (target_end_time >= patrol_start_time && target_end_time <= patrol_end_time) {
            encounters++;
        }
    }
    return encounters;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &patrol_cars[i].start_pos, &patrol_cars[i].start_time, &patrol_cars[i].travel_time);
    }

    int min_encounters_count = m;
    int best_arrival_time = 0;

    for (int speed = 60; speed <= 120; speed++) {
        int travel_time = (n - 1) * 10 * 3600 / speed;
        int target_start_time = time_to_seconds(60000);
        int target_end_time = target_start_time + travel_time;

        int encounters = min_encounters(target_start_time);
        if (encounters < min_encounters_count) {
            min_encounters_count = encounters;
            best_arrival_time = target_end_time;
        }
    }

    printf("%d\n", min_encounters_count);
    printf("%06d\n", seconds_to_time(best_arrival_time));

    return 0;
}