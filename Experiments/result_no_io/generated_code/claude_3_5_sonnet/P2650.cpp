#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 100005

typedef long long ll;

typedef struct {
    ll time;
    int type;
} Event;

Event events[MAX_N * 2];
int event_count = 0;

int cmp(const void *a, const void *b) {
    Event *ea = (Event *)a;
    Event *eb = (Event *)b;
    if (ea->time != eb->time) {
        return ea->time < eb->time ? -1 : 1;
    }
    return ea->type - eb->type;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        ll a, b;
        scanf("%lld %lld", &a, &b);
        events[event_count++] = (Event){a + 1, 1};
        events[event_count++] = (Event){a + b, -1};
    }

    qsort(events, event_count, sizeof(Event), cmp);

    ll prev_time = 0;
    int count = 0;
    ll prefix_sum[MAX_N * 2 + 1];
    memset(prefix_sum, 0, sizeof(prefix_sum));

    for (int i = 0; i < event_count; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + count * (events[i].time - prev_time);
        count += events[i].type;
        prev_time = events[i].time;
    }

    for (int i = 0; i < m; i++) {
        ll x, y;
        scanf("%lld %lld", &x, &y);
        y += x;

        int left = 0, right = event_count - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (events[mid].time <= x) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        int start = left;

        left = 0, right = event_count - 1;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (events[mid].time > y) {
                right = mid - 1;
            } else {
                left = mid;
            }
        }
        int end = left;

        ll result = prefix_sum[end + 1] - prefix_sum[start];
        if (start < event_count && events[start].time <= y) {
            result += count * (y - events[start].time + 1);
        }
        if (end >= 0 && events[end].time >= x) {
            result -= count * (x - events[end].time);
        }

        printf("%lld\n", result);
    }

    return 0;
}