#include <stdio.h>
#include <stdlib.h>

#define MAX_ROOMS 100

int max_paintings = 0;
int police_time;

struct Room {
    int time;
    int paintings;
    struct Room* left;
    struct Room* right;
};

struct Room* create_room(int time, int paintings) {
    struct Room* room = (struct Room*)malloc(sizeof(struct Room));
    room->time = time;
    room->paintings = paintings;
    room->left = NULL;
    room->right = NULL;
    return room;
}

struct Room* build_museum(int** data, int* index) {
    int time = (*data)[*index];
    (*index)++;
    int paintings = (*data)[*index];
    (*index)++;

    struct Room* room = create_room(time, paintings);

    if (paintings == 0) {
        room->left = build_museum(data, index);
        room->right = build_museum(data, index);
    }

    return room;
}

void steal_paintings(struct Room* room, int time, int paintings) {
    if (room == NULL || time > police_time - 1) return;

    time += room->time;
    if (room->paintings > 0) {
        paintings += room->paintings;
        time += room->paintings * 5;
    }

    if (time <= police_time - 1) {
        if (paintings > max_paintings) {
            max_paintings = paintings;
        }
    } else {
        return;
    }

    steal_paintings(room->left, time, paintings);
    steal_paintings(room->right, time, paintings);
}

int main() {
    scanf("%d", &police_time);

    int* data = (int*)malloc(MAX_ROOMS * 2 * sizeof(int));
    int count = 0;
    while (scanf("%d", &data[count]) != EOF) {
        count++;
    }

    int index = 0;
    struct Room* museum = build_museum(&data, &index);

    steal_paintings(museum, 0, 0);

    printf("%d\n", max_paintings);

    free(data);
    return 0;
}