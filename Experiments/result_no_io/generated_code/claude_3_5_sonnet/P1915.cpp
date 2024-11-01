#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SHRIMPS 1000
#define EPS 1e-6

struct Shrimp {
    double w, x, y, p, q;
    int eaten;
};

struct Nemo {
    double w, x, y;
};

struct Event {
    double t;
    int shrimp_id;
};

struct Nemo nemo;
struct Shrimp shrimps[MAX_SHRIMPS];
int n;
double V, T;

int compare_events(const void* a, const void* b) {
    struct Event* ea = (struct Event*)a;
    struct Event* eb = (struct Event*)b;
    if (fabs(ea->t - eb->t) < EPS) return 0;
    return ea->t < eb->t ? -1 : 1;
}

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double catch_time(int i, double t) {
    double dx = shrimps[i].x + shrimps[i].p * t - nemo.x;
    double dy = shrimps[i].y + shrimps[i].q * t - nemo.y;
    double dist = sqrt(dx*dx + dy*dy);
    return t + dist / V;
}

void solve() {
    struct Event events[MAX_SHRIMPS];
    int event_count = 0;

    for (int i = 0; i < n; i++) {
        if (shrimps[i].w < nemo.w) {
            double t = catch_time(i, 0);
            if (t <= T) {
                events[event_count].t = t;
                events[event_count].shrimp_id = i;
                event_count++;
            }
        }
    }

    qsort(events, event_count, sizeof(struct Event), compare_events);

    double total_weight = 0;
    int eaten_count = 0;

    for (int i = 0; i < event_count; i++) {
        int sid = events[i].shrimp_id;
        if (!shrimps[sid].eaten && shrimps[sid].w < nemo.w) {
            double t = events[i].t;
            nemo.x = shrimps[sid].x + shrimps[sid].p * t;
            nemo.y = shrimps[sid].y + shrimps[sid].q * t;
            nemo.w += shrimps[sid].w;
            total_weight += shrimps[sid].w;
            shrimps[sid].eaten = 1;
            eaten_count++;

            printf("%.6f %.6f %.6f %d\n", t, nemo.x, nemo.y, sid + 1);

            for (int j = i + 1; j < event_count; j++) {
                int next_sid = events[j].shrimp_id;
                if (!shrimps[next_sid].eaten && shrimps[next_sid].w < nemo.w) {
                    events[j].t = catch_time(next_sid, t);
                }
            }

            qsort(events + i + 1, event_count - i - 1, sizeof(struct Event), compare_events);
        }
    }

    printf("%d\n%.6f\n", eaten_count, total_weight);
}

int main() {
    scanf("%lf%lf%lf%lf%lf", &nemo.w, &V, &T, &nemo.x, &nemo.y);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf%lf%lf%lf", &shrimps[i].w, &shrimps[i].x, &shrimps[i].y, &shrimps[i].p, &shrimps[i].q);
        shrimps[i].eaten = 0;
    }

    solve();

    return 0;
}