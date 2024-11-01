#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000001

int n, m;
int classrooms[MAX_N];
int requests[MAX_N][3];
int changes[MAX_N];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &classrooms[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &requests[i][0], &requests[i][1], &requests[i][2]);
    }

    for (int i = 0; i < m; i++) {
        int d = requests[i][0];
        int s = requests[i][1];
        int t = requests[i][2];

        for (int j = s; j <= t; j++) {
            changes[j] += d;
            if (changes[j] > classrooms[j]) {
                printf("-1\n%d\n", i + 1);
                return 0;
            }
        }
    }

    printf("0\n");
    return 0;
}