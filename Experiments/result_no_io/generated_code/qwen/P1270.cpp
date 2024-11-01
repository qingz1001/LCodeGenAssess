#include <stdio.h>
#include <stdlib.h>

#define MAX_EXHIBITS 20
#define MAX_CORRIDORS 100
#define TIME_TO_STEAL 5

typedef struct {
    int time;
    int exhibits[MAX_EXHIBITS];
    int num_exhibits;
} Corridor;

int max_stolen_paintings = 0;

void dfs(Corridor corridors[], int index, int remaining_time) {
    if (remaining_time <= 0) return;
    
    int current_time = corridors[index].time;
    int new_remaining_time = remaining_time - current_time;
    
    for (int i = 0; i < corridors[index].num_exhibits; i++) {
        if (corridors[index].exhibits[i] > 0) {
            int stolen_pictures = corridors[index].exhibits[i] / TIME_TO_STEAL;
            if (new_remaining_time >= stolen_pictures * TIME_TO_STEAL + 1) {
                max_stolen_paintings = (max_stolen_paintings > max_stolen_paintings + stolen_pictures) ? max_stolen_paintings : max_stolen_paintings + stolen_pictures;
                dfs(corridors, index + 1, new_remaining_time - stolen_pictures * TIME_TO_STEAL);
            }
        } else {
            dfs(corridors, index + 1, new_remaining_time);
        }
    }
}

int main() {
    int police_arrival_time;
    scanf("%d", &police_arrival_time);
    
    Corridor corridors[MAX_CORRIDORS];
    int corridor_count = 0;
    
    while (scanf("%d %d", &corridors[corridor_count].time, &corridors[corridor_count].exhibits[0]) == 2) {
        corridors[corridor_count].num_exhibits = 1;
        
        if (corridors[corridor_count].exhibits[0] != 0) {
            scanf("%d", &corridors[corridor_count].exhibits[1]);
            corridors[corridor_count].num_exhibits++;
        }
        
        corridor_count++;
    }
    
    dfs(corridors, 0, police_arrival_time - 1);
    
    printf("%d\n", max_stolen_paintings);
    
    return 0;
}