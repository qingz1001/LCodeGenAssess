#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} Point;

// Compare function for qsort: first by x, then by y
int cmp(const void *a, const void *b){
    Point *p = (Point*)a;
    Point *q = (Point*)b;
    if(p->x != q->x) return p->x - q->x;
    return p->y - q->y;
}

// Cross product of OA and OB vectors
long long cross(Point O, Point A, Point B){
    long long val = (long long)(A.x - O.x)*(B.y - O.y) - (long long)(A.y - O.y)*(B.x - O.x);
    return val;
}

// Compute convex hull using Andrew's algorithm
int convex_hull(Point *points, int n, Point *h){
    if(n == 0) return 0;
    qsort(points, n, sizeof(Point), cmp);
    int k = 0;
    // Lower hull
    for(int i=0;i<n;i++){
        while(k >=2 && cross(h[k-2], h[k-1], points[i]) <=0) k--;
        h[k++] = points[i];
    }
    // Upper hull
    int t = k+1;
    for(int i=n-2;i>=0;i--){
        while(k >=t && cross(h[k-2], h[k-1], points[i]) <=0) k--;
        h[k++] = points[i];
    }
    if(k >1) k--;
    return k;
}

// Compute area using shoelace formula
double polygon_area(Point *poly, int n){
    long long area=0;
    for(int i=0;i<n;i++){
        int j=(i+1)%n;
        area += (long long)poly[i].x * poly[j].y - (long long)poly[j].x * poly[i].y;
    }
    return fabs(area)/2.0;
}

int main(){
    FILE *fin = fopen("input.txt","r");
    int N;
    fscanf(fin, "%d", &N);
    Point *points = (Point*)malloc(N * sizeof(Point));
    for(int i=0;i<N;i++) fscanf(fin, "%d %d", &points[i].x, &points[i].y);
    fclose(fin);
    
    // Compute polygon area
    double poly_area = polygon_area(points, N);
    
    // Compute convex hull
    Point *hull = (Point*)malloc(2*N * sizeof(Point));
    int m = convex_hull(points, N, hull);
    double hull_area = polygon_area(hull, m);
    
    free(points);
    free(hull);
    
    double shadow = hull_area - poly_area;
    if(shadow < 0) shadow = -shadow;
    
    FILE *fout = fopen("output.txt","w");
    fprintf(fout, "%.2lf\n", shadow);
    fclose(fout);
    
    return 0;
}