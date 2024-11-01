#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CURRENCIES 30
#define MAX_EXCHANGES 900

typedef struct {
    char name[32];
    double rate;
    int next;
} Exchange;

Exchange exchanges[MAX_EXCHANGES];
int head[MAX_CURRENCIES];
int n, m, case_num;

void init() {
    memset(head, -1, sizeof(head));
    memset(exchanges, 0, sizeof(exchanges));
}

int find(char *name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(name, exchanges[head[i]].name) == 0) {
            return i;
        }
    }
    return -1;
}

void add_exchange(char *source, double rate, char *dest) {
    int src_index = find(source);
    if (src_index == -1) {
        src_index = n++;
        strcpy(exchanges[src_index].name, source);
    }
    int dest_index = find(dest);
    if (dest_index == -1) {
        dest_index = n++;
        strcpy(exchanges[dest_index].name, dest);
    }
    exchanges[n].rate = rate;
    exchanges[n].next = head[src_index];
    head[src_index] = n++;
}

int bellman_ford(int start) {
    double dist[MAX_CURRENCIES];
    int prev[MAX_CURRENCIES];
    for (int i = 0; i < n; i++) {
        dist[i] = -1.0;
        prev[i] = -1;
    }
    dist[start] = 1.0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            if (head[j] != -1) {
                int current = head[j];
                while (current != -1) {
                    int next = current + 1;
                    double new_dist = dist[j] * exchanges[current].rate;
                    if (new_dist > dist[exchanges[current + 1].next]) {
                        dist[exchanges[current + 1].next] = new_dist;
                        prev[exchanges[current + 1].next] = j;
                    }
                    current = exchanges[current].next;
                }
            }
        }
    }

    for (int j = 0; j < n; j++) {
        if (head[j] != -1) {
            int current = head[j];
            while (current != -1) {
                int next = current + 1;
                double new_dist = dist[j] * exchanges[current].rate;
                if (new_dist > dist[exchanges[current + 1].next]) {
                    return 1; // Negative cycle found
                }
                current = exchanges[current].next;
            }
        }
    }

    return 0; // No negative cycle
}

int main() {
    while (scanf("%d", &n) && n) {
        init();
        for (int i = 0; i < n; i++) {
            char currency[32];
            scanf("%s", currency);
        }
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            char source[32], dest[32];
            double rate;
            scanf("%s %lf %s", source, &rate, dest);
            add_exchange(source, rate, dest);
        }
        case_num++;
        if (bellman_ford(0)) {
            printf("Case %d: Yes\n", case_num);
        } else {
            printf("Case %d: No\n", case_num);
        }
    }
    return 0;
}