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
    int hh = hhmmss / 10000;
    int mm = (hhmmss % 10000) / 100;
    int ss = hhmmss % 100;
    return hh * 3600 + mm * 60 + ss;
}

int seconds_to_time(int seconds) {
    int hh = seconds / 3600;
    seconds %= 3600;
    int mm = seconds / 60;
    int ss = seconds % 60;
    return hh * 10000 + mm * 100 + ss;
}

int min_encounters(int target_speed) {
    int encounters = 0;
    int target_start_time = time_to_seconds(60000);
    int target_travel_time = (n - 1) * 10 * 3600 / target_speed;
    int target_end_time = target_start_time + target_travel_time;

    for (int i = 0; i < m; i++) {
        int patrol_start_time = time_to_seconds(patrol_cars[i].start_time);
        int patrol_end_time = patrol_start_time + patrol_cars[i].travel_time;

        if (patrol_start_time < target_end_time && patrol_end_time > target_start_time) {
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

    int min_encounters_count = MAX_M;
    int best_speed = 60;

    for (int speed = 60; speed <= 120; speed++) {
        int encounters = min_encounters(speed);
        if (encounters < min_encounters_count) {
            min_encounters_count = encounters;
            best_speed = speed;
        }
    }

    int target_start_time = time_to_seconds(60000);
    int target_travel_time = (n - 1) * 10 * 3600 / best_speed;
    int target_end_time = target_start_time + target_travel_time;

    printf("%d\n", min_encounters_count);
    printf("%06d\n", seconds_to_time(target_end_time));

    return 0;
}