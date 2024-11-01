#include <stdio.h>
#include <math.h>

typedef struct {
    long long x;
    long long y;
} Point;

int main(){
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    int N;
    fscanf(fin, "%d", &N);
    Point points[N];
    for(int i=0;i<N;i++) {
        fscanf(fin, "%lld %lld", &points[i].x, &points[i].y);
    }
    double area=0.0;
    for(int i=0;i<N;i++) {
        int j=(i+1)%N;
        area += (double)(points[i].x)*points[j].y - (double)(points[j].x)*points[i].y;
    }
    area = fabs(area)/2.0;
    fprintf(fout, "%.2lf\n", area);
    fclose(fin);
    fclose(fout);
    return 0;
}