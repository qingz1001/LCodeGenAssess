#include <stdio.h>
#include <stdlib.h>

#define MAXN 30000
#define MAXM 5000

typedef struct {
    int a, b, c;
} Section;

int compare(const void *a, const void *b) {
    return ((Section *)a)->b - ((Section *)b)->b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Section sections[MAXM];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &sections[i].a, &sections[i].b, &sections[i].c);
    }

    qsort(sections, m, sizeof(Section), compare);

    int microphones[MAXN + 1] = {0};
    int total_microphones = 0;

    for (int i = 0; i < m; i++) {
        int count = 0;
        for (int j = sections[i].a; j <= sections[i].b; j++) {
            if (microphones[j]) count++;
        }

        if (count < sections[i].c) {
            int need = sections[i].c - count;
            total_microphones += need;
            for (int j = sections[i].b; need > 0 && j >= sections[i].a; j--) {
                if (!microphones[j]) {
                    microphones[j] = 1;
                    need--;
                }
            }
        }
    }

    printf("%d\n", total_microphones);

    return 0;
}