#include <stdio.h>
#include <stdlib.h>

#define MAX_ROOMS 100

int max_paintings = 0;
int police_time;
int rooms[MAX_ROOMS][2];
int room_count = 0;

void dfs(int current_room, int time_spent, int paintings_stolen) {
    if (time_spent >= police_time - 1) {
        return;
    }

    if (rooms[current_room][1] > 0) {
        int new_paintings = rooms[current_room][1];
        int new_time = time_spent + rooms[current_room][0] * 2 + new_paintings * 5;
        
        if (new_time < police_time) {
            if (paintings_stolen + new_paintings > max_paintings) {
                max_paintings = paintings_stolen + new_paintings;
            }
        }
    } else {
        dfs(current_room + 1, time_spent + rooms[current_room][0], paintings_stolen);
        dfs(current_room + rooms[current_room + 1][1] + 2, time_spent + rooms[current_room][0], paintings_stolen);
    }
}

int main() {
    scanf("%d", &police_time);

    while (1) {
        scanf("%d %d", &rooms[room_count][0], &rooms[room_count][1]);
        if (rooms[room_count][0] == 0 && rooms[room_count][1] == 0) {
            break;
        }
        room_count++;
    }

    dfs(0, 0, 0);

    printf("%d\n", max_paintings);

    return 0;
}