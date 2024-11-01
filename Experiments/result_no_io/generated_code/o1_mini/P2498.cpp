#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Boss;

int main(){
    int n, row, line;
    scanf("%d %d %d", &n, &row, &line);
    
    Boss *bosses = (Boss*)malloc(sizeof(Boss) * n);
    for(int i=0;i<n;i++){
        scanf("%d %d", &bosses[i].x, &bosses[i].y);
    }
    
    double D_min = 1e18;
    
    for(int i=0;i<n;i++){
        double dx = bosses[i].x - 1.0;
        double dy = bosses[i].y - 1.0;
        double dist = sqrt(dx*dx + dy*dy);
        if(dist < D_min){
            D_min = dist;
        }
        
        dx = bosses[i].x - (double)row;
        dy = bosses[i].y - (double)line;
        dist = sqrt(dx*dx + dy*dy);
        if(dist < D_min){
            D_min = dist;
        }
    }
    
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            double dx = bosses[i].x - bosses[j].x;
            double dy = bosses[i].y - bosses[j].y;
            double dist = sqrt(dx*dx + dy*dy) / 2.0;
            if(dist < D_min){
                D_min = dist;
            }
        }
    }
    
    // If there are no bosses, set D_min to the distance between start and end
    if(n == 0){
        double dx = (double)(row - 1);
        double dy = (double)(line - 1);
        D_min = sqrt(dx*dx + dy*dy);
    }
    
    printf("%.2lf\n", D_min);
    
    free(bosses);
    return 0;
}