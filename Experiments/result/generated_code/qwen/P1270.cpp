#include <stdio.h>
#include <stdlib.h>

#define MAX_EXHIBITS 100
#define MAX_PAINTINGS 20
#define TIME_TO_STOLEN 5

typedef struct {
    int time;
    int paintings;
} Room;

Room gallery[MAX_EXHIBITS];
int n;
int max_time;

int dfs(int index, int remaining_time) {
    if (remaining_time <= 0) return 0;
    if (gallery[index].paintings == 0) {
        int result = 0;
        for (int i = 2 * index + 1; i < 2 * index + 3; i++) {
            result += dfs(i, remaining_time - gallery[index].time);
        }
        return result;
    } else {
        int steal_now = gallery[index].paintings / 2;
        int not_steal_now = dfs(2 * index + 1, remaining_time - gallery[index].time) +
                             dfs(2 * index + 2, remaining_time - gallery[index].time);
        return steal_now + not_steal_now > steal_now ? steal_now : not_steal_now;
    }
}

int main() {
    scanf("%d", &max_time);
    char input[1000];
    fgets(input, sizeof(input), stdin);
    int pos = 0;
    n = 0;
    while (pos < strlen(input)) {
        sscanf(&input[pos], "%d %d", &gallery[n].time, &gallery[n].paintings);
        pos += sprintf(NULL, "%d %d", gallery[n].time, gallery[n].paintings) + 1;
        n++;
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        result = dfs(i, max_time - TIME_TO_STOLEN);
    }

    printf("%d\n", result);

    return 0;
}