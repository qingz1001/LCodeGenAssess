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
    for(int i=0; i<n; i++){
        scanf("%d %lf", &planets[i].type, &planets[i].x);
    }
    
    double M = 0.0;
    for(int i=n-1; i>=0; i--){
        if(planets[i].type ==1){
            double option1 = planets[i].x + (1.0 - k * 0.01) * M;
            double option2 = M;
            if(option1 > option2){
                M = option1;
            }
            else{
                M = option2;
            }
        }
        else{
            double benefit = (c * 0.01) * M;
            if(benefit > planets[i].x){
                double option1 = -planets[i].x + (1.0 + c * 0.01) * M;
                double option2 = M;
                if(option1 > option2){
                    M = option1;
                }
                else{
                    M = option2;
                }
            }
            else{
                // Do not repair
                // M remains the same
            }
        }
    }
    
    double total = M * w;
    // To handle negative zero, add a small value
    if(total == -0.0) total = 0.0;
    printf("%.2lf\n", total);
    
    free(planets);
    return 0;
}