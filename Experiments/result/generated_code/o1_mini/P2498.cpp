#include<stdio.h>
#include<math.h>
#include<float.h>

int main(){
    int n, row, line;
    scanf("%d %d %d", &n, &row, &line);
    double x, y;
    double min_start = DBL_MAX, min_end = DBL_MAX;
    for(int i=0;i<n;i++){
        scanf("%lf %lf", &x, &y);
        double dist_start = sqrt((x-1)*(x-1) + (y-1)*(y-1));
        if(dist_start < min_start){
            min_start = dist_start;
        }
        double dist_end = sqrt((x - row)*(x - row) + (y - line)*(y - line));
        if(dist_end < min_end){
            min_end = dist_end;
        }
    }
    double D = (min_start < min_end) ? min_start : min_end;
    int D_int = (int)D;
    printf("%d.00\n", D_int);
}