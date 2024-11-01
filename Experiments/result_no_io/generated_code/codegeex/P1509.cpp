#include <stdio.h>

typedef struct MM {
    int rmb; // 请吃饭的花费
    int rp;  // 请吃饭的人品
    int time; // 搞定所需时间
} MM;

int compare(const void *a, const void *b) {
    MM *mm1 = (MM *)a;
    MM *mm2 = (MM *)b;
    if (mm1->time != mm2->time) {
        return mm1->time - mm2->time;
    } else if (mm1->rp != mm2->rp) {
        return mm1->rp - mm2->rp;
    } else {
        return mm1->rmb - mm2->rmb;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    MM mm[101];

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &mm[i].rmb, &mm[i].rp, &mm[i].time);
    }

    int m, r;
    scanf("%d %d", &m, &r);

    qsort(mm, n, sizeof(MM), compare);

    int maxMM = 0;
    int totalTime = 0;

    for (int i = 0; i < n; i++) {
        if (m >= mm[i].rmb && r >= mm[i].rp) {
            m -= mm[i].rmb;
            r -= mm[i].rp;
            totalTime += mm[i].time;
            maxMM++;
        }
    }

    printf("%d\n", totalTime);
    return 0;
}