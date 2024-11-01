#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SHRIMPS 1000

typedef struct {
    double w, x, y, p, q;
} Shrimp;

typedef struct {
    double t, x, y;
    int s;
} EatenShrimp;

double w0, V, T, x0, y0;
int n;
Shrimp shrimps[MAX_SHRIMPS];
EatenShrimp eaten[MAX_SHRIMPS];
int eaten_count = 0;

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int can_eat(double nemo_weight, double shrimp_weight) {
    return nemo_weight > shrimp_weight;
}

void eat_shrimp(double t, double x, double y, int s) {
    eaten[eaten_count].t = t;
    eaten[eaten_count].x = x;
    eaten[eaten_count].y = y;
    eaten[eaten_count].s = s;
    eaten_count++;
}

void solve() {
    // 在这里实现你的算法
    // 使用 eat_shrimp 函数记录 Nemo 吃掉的虾
}

int main() {
    FILE *in = fopen("nemo1.in", "r");
    FILE *out = fopen("nemo1.out", "w");

    fscanf(in, "%lf %lf %lf %lf %lf", &w0, &V, &T, &x0, &y0);
    fscanf(in, "%d", &n);

    for (int i = 0; i < n; i++) {
        fscanf(in, "%lf %lf %lf %lf %lf", &shrimps[i].w, &shrimps[i].x, &shrimps[i].y, &shrimps[i].p, &shrimps[i].q);
    }

    solve();

    double total_weight = 0;
    for (int i = 0; i < eaten_count; i++) {
        total_weight += shrimps[eaten[i].s - 1].w;
    }

    fprintf(out, "%d\n", eaten_count);
    fprintf(out, "%.6f\n", total_weight);

    for (int i = 0; i < eaten_count; i++) {
        fprintf(out, "%.6f %.6f %.6f %d\n", eaten[i].t, eaten[i].x, eaten[i].y, eaten[i].s);
    }

    fclose(in);
    fclose(out);

    return 0;
}