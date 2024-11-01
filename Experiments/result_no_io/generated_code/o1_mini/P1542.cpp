#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
    double s;
} Location;

int main(){
    int n;
    scanf("%d", &n);
    Location* loc = (Location*)malloc(n * sizeof(Location));
    for(int i=0;i<n;i++) {
        scanf("%lf %lf %lf", &loc[i].x, &loc[i].y, &loc[i].s);
    }
    double left=0.0, right=1e14, mid, eps=1e-7;
    for(int it=0; it<100; it++){
        mid=(left+right)/2.0;
        double time=0.0;
        int valid=1;
        for(int i=0;i<n;i++){
            double travel = loc[i].s / mid;
            time += travel;
            if(time < loc[i].x){
                time = loc[i].x;
            }
            if(time > loc[i].y){
                valid=0;
                break;
            }
        }
        if(valid){
            right=mid;
        }
        else{
            left=mid;
        }
        if(right - left < eps) break;
    }
    printf("%.2lf\n", right);
    free(loc);
    return 0;
}