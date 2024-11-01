#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAXN 105
#define MAXM 105
#define INF 1e18

int n, m;
double a[MAXN], b[MAXN], c[MAXN];
int d[MAXM];
bool graph[MAXN][MAXM];

double EPS = 1e-8;
double flow[MAXN][MAXM];
double dist[MAXN + MAXM];
bool vis[MAXN + MAXM];
int pre[MAXN + MAXM];

bool spfa(double mid) {
    for (int i = 0; i < n + m; i++) {
        dist[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    dist[n + m - 1] = 0;
    vis[n + m - 1] = true;
    
    int queue[MAXN + MAXM], front = 0, rear = 0;
    queue[rear++] = n + m - 1;
    
    while (front != rear) {
        int u = queue[front++];
        if (front == MAXN + MAXM) front = 0;
        vis[u] = false;
        
        if (u < n) {
            for (int v = 0; v < m; v++) {
                if (graph[u][v]) {
                    double w = mid;
                    if (flow[u][v] > EPS) w = 0;
                    if (dist[u] > dist[n + v] + w + EPS) {
                        dist[u] = dist[n + v] + w;
                        pre[u] = n + v;
                        if (!vis[u]) {
                            vis[u] = true;
                            queue[rear++] = u;
                            if (rear == MAXN + MAXM) rear = 0;
                        }
                    }
                }
            }
        } else if (u < n + m - 1) {
            int v = u - n;
            for (int i = 0; i < n; i++) {
                if (graph[i][v]) {
                    double w = -mid;
                    if (flow[i][v] < c[i] - EPS) w = 0;
                    if (dist[i] > dist[u] + w + EPS) {
                        dist[i] = dist[u] + w;
                        pre[i] = u;
                        if (!vis[i]) {
                            vis[i] = true;
                            queue[rear++] = i;
                            if (rear == MAXN + MAXM) rear = 0;
                        }
                    }
                }
            }
        } else {
            for (int v = 0; v < m; v++) {
                if (dist[n + v] > dist[u] + EPS) {
                    dist[n + v] = dist[u];
                    pre[n + v] = u;
                    if (!vis[n + v]) {
                        vis[n + v] = true;
                        queue[rear++] = n + v;
                        if (rear == MAXN + MAXM) rear = 0;
                    }
                }
            }
        }
    }
    
    return dist[n + m - 1] < -EPS;
}

void update_flow(double mid) {
    int u = n + m - 1;
    while (pre[u] != -1) {
        int v = pre[u];
        if (u < n + m - 1 && v < n) {
            flow[v][u - n] = fmin(flow[v][u - n] + mid, c[v]);
        } else if (u < n && v < n + m - 1) {
            flow[u][v - n] = fmax(flow[u][v - n] - mid, 0);
        }
        u = v;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &a[i], &b[i], &c[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            scanf("%d", &x);
            graph[i][j] = x;
        }
    }
    
    double left = 0, right = 1e5;
    while (right - left > EPS) {
        double mid = (left + right) / 2;
        if (spfa(mid)) {
            left = mid;
            update_flow(mid);
        } else {
            right = mid;
        }
    }
    
    double total_flow = 0, total_cost = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            total_flow += flow[i][j];
            total_cost += a[i] * flow[i][j] * flow[i][j] + b[i] * flow[i][j];
        }
    }
    
    int int_flow = (int)(total_flow + 0.5);
    printf("%d\n", int_flow);
    
    long long numerator = (long long)(total_cost * 1e6 + 0.5);
    long long denominator = 1e6;
    long long gcd = numerator;
    while (denominator) {
        long long temp = gcd % denominator;
        gcd = denominator;
        denominator = temp;
    }
    numerator /= gcd;
    denominator = 1e6 / gcd;
    printf("%lld/%lld\n", numerator, denominator);
    
    return 0;
}