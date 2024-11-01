#include <stdio.h>
#include <stdlib.h>

#define MAX_TIME 6000
#define MAX_ROOMS 100

int max(int a, int b) {
    return a > b ? a : b;
}

int steal(int time_left, int* corridor_times, int* paintings, int index, int size) {
    if (time_left <= 1) return 0; // 1 second for escape
    if (index >= size) return 0;

    int corridor_time = corridor_times[index];
    int num_paintings = paintings[index];

    if (num_paintings == 0) {
        // This is a fork, recursively solve both branches
        return max(steal(time_left - corridor_time, corridor_times, paintings, index + 1, size),
                   steal(time_left - corridor_time, corridor_times, paintings, index + 2, size));
    } else {
        // This is a room, calculate the maximum paintings that can be stolen
        int time_to_steal = num_paintings * 5;
        if (time_left - corridor_time - time_to_steal > 1) {
            return num_paintings + steal(time_left - corridor_time - time_to_steal, corridor_times, paintings, index + 1, size);
        } else {
            return steal(time_left - corridor_time, corridor_times, paintings, index + 1, size);
        }
    }
}

int main() {
    int police_time;
    scanf("%d", &police_time);

    int corridor_times[MAX_ROOMS * 2];
    int paintings[MAX_ROOMS * 2];
    int size = 0;

    while (scanf("%d %d", &corridor_times[size], &paintings[size]) != EOF) {
        size++;
    }

    int result = steal(police_time, corridor_times, paintings, 0, size);
    printf("%d\n", result);

    return 0;
}