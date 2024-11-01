#include <stdio.h>
#include <stdlib.h>

#define MAX_GARBAGE 100
#define MAX_TIME 1001

typedef struct {
    int time;
    int food;
    int height;
} Garbage;

int compare(const void *a, const void *b) {
    return ((Garbage *)a)->time - ((Garbage *)b)->time;
}

int main() {
    int D, G;
    scanf("%d %d", &D, &G);

    Garbage garbage[MAX_GARBAGE];
    for (int i = 0; i < G; i++) {
        scanf("%d %d %d", &garbage[i].time, &garbage[i].food, &garbage[i].height);
    }

    qsort(garbage, G, sizeof(Garbage), compare);

    int dp[MAX_TIME] = {0};
    int max_life = 10;
    int total_height = 0;
    int escape_time = -1;

    for (int i = 0; i < G; i++) {
        int current_time = garbage[i].time;
        
        if (current_time > max_life) {
            break;
        }

        for (int j = max_life; j >= current_time; j--) {
            if (j - current_time <= 10 || dp[j - current_time] > 0) {
                int new_life = j + garbage[i].food;
                if (new_life > max_life) {
                    max_life = new_life;
                }
                if (dp[j] < dp[j - current_time] + garbage[i].height) {
                    dp[j] = dp[j - current_time] + garbage[i].height;
                }
                if (dp[j] >= D && escape_time == -1) {
                    escape_time = j;
                }
            }
        }

        total_height += garbage[i].height;
        if (total_height >= D && escape_time == -1) {
            escape_time = current_time;
        }
    }

    if (escape_time != -1) {
        printf("%d\n", escape_time);
    } else {
        printf("%d\n", max_life);
    }

    return 0;
}