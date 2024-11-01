#include <stdio.h>
#include <stdlib.h>

#define MAXN 30000
#define MAXM 5000

typedef struct {
    int a, b, c;
} Section;

Section sections[MAXM];
int count[MAXN + 1];

int compare(const void *a, const void *b) {
    return ((Section *)a)->a - ((Section *)b)->a;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &sections[i].a, &sections[i].b, &sections[i].c);
    }

    qsort(sections, m, sizeof(Section), compare);

    int total_mics = 0;

    for (int i = 0; i < m; i++) {
        int a = sections[i].a;
        int b = sections[i].b;
        int c = sections[i].c;

        int current_mics = 0;
        for (int j = a; j <= b; j++) {
            if (count[j] > 0) {
                current_mics++;
            }
        }

        if (current_mics < c) {
            int needed = c - current_mics;
            total_mics += needed;

            for (int j = b; j >= a && needed > 0; j--) {
                if (count[j] == 0) {
                    count[j] = 1;
                    needed--;
                }
            }
        }
    }

    printf("%d\n", total_mics);

    return 0;
}