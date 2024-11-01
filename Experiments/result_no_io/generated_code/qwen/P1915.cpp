#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-6

typedef struct {
    double w, x, y, px, py;
} Shrimp;

typedef struct {
    double w, x, y, t, s;
} Action;

int main() {
    FILE *in = fopen("nemo1.in", "r");
    if (!in) {
        fprintf(stderr, "Failed to open input file\n");
        return 1;
    }

    double w0, V, T, x0, y0;
    fscanf(in, "%lf %lf %lf %lf %lf", &w0, &V, &T, &x0, &y0);

    int n;
    fscanf(in, "%d", &n);
    Shrimp shrimps[n];
    for (int i = 0; i < n; ++i) {
        fscanf(in, "%lf %lf %lf %lf %lf", &shrimps[i].w, &shrimps[i].x, &shrimps[i].y, &shrimps[i].px, &shrimps[i].py);
    }

    fclose(in);

    // Your algorithm goes here

    // Example output
    FILE *out = fopen("nemo1.out", "w");
    if (!out) {
        fprintf(stderr, "Failed to open output file\n");
        return 1;
    }

    fprintf(out, "1\n");
    fprintf(out, "%.6f\n", w0 + shrimps[0].w);
    fprintf(out, "%.6f %.6f %.6f 0\n", T, x0 + V * cos(0), y0 + V * sin(0));

    fclose(out);

    return 0;
}