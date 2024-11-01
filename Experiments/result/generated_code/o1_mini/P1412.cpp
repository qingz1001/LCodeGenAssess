#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int type;
    double x;
} Planet;

int main(){
    int n, k, c;
    double w;
    scanf("%d %d %d %lf", &n, &k, &c, &w);
    Planet* planets = (Planet*)malloc(n * sizeof(Planet));
    for(int i=0;i<n;i++) {
        scanf("%d %lf", &planets[i].type, &planets[i].x);
    }
    double A=0.0;
    for(int i=n-1;i>=0;i--){
        if(planets[i].type ==1){
            double exploit = planets[i].x + A * (1.0 - k / 100.0);
            if(exploit > A){
                A = exploit;
            }
        }
        else{
            double repair = -planets[i].x + A * (1.0 + c / 100.0);
            if(repair > A){
                A = repair;
            }
        }
    }
    double total = A * w;
    printf("%.2lf\n", total);
    free(planets);
    return 0;
}