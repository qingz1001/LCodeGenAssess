#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int dy;
    int dx;
} Slope;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int compare_slope(const void *a, const void *b) {
    Slope *s1 = (Slope *)a;
    Slope *s2 = (Slope *)b;
    if (s1->dy != s2->dy)
        return s1->dy - s2->dy;
    return s1->dx - s2->dx;
}

int main(){
    int n;
    scanf("%d", &n);
    Point points[n];
    for(int i=0;i<n;i++){
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    if(n ==0){
        printf("0\n");
        return 0;
    }
    int max_count =1;
    for(int i=0;i<n;i++){
        Slope slopes[n-1];
        int m=0;
        for(int j=0;j<n;j++){
            if(i == j)
                continue;
            int dy = points[j].y - points[i].y;
            int dx = points[j].x - points[i].x;
            if(dx ==0 && dy ==0){
                // No duplicates as per problem statement
                continue;
            }
            if(dx ==0){
                slopes[m].dy =1;
                slopes[m].dx =0;
            }
            else if(dy ==0){
                slopes[m].dy =0;
                slopes[m].dx =1;
            }
            else{
                int sign = 1;
                if((dy <0 && dx >0) || (dy >0 && dx <0)){
                    sign = -1;
                }
                dy = abs(dy);
                dx = abs(dx);
                int g = gcd(dy, dx);
                slopes[m].dy = sign * (dy / g);
                slopes[m].dx = dx / g;
            }
            m++;
        }
        if(m ==0){
            if(max_count <1)
                max_count =1;
            continue;
        }
        qsort(slopes, m, sizeof(Slope), compare_slope);
        int current_max =1;
        for(int k=1;k<m;k++){
            if(slopes[k].dy == slopes[k-1].dy && slopes[k].dx == slopes[k-1].dx){
                current_max++;
            }
            else{
                if(current_max > max_count)
                    max_count = current_max;
                current_max =1;
            }
        }
        if(current_max > max_count)
            max_count = current_max;
        if(max_count < current_max +1)
            max_count = current_max +1;
        if(max_count < current_max +1)
            max_count = current_max +1;
        if(max_count < m +1)
            max_count = m +1;
        if(max_count < m +1)
            max_count = m +1;
        if(max_count < current_max +1)
            max_count = current_max +1;
        if(max_count < current_max +1)
            max_count = current_max +1;
        if(max_count < current_max +1){
            max_count = current_max +1;
        }
        if(max_count < current_max +1)
            max_count = current_max +1;
        if(max_count < current_max +1)
            max_count = current_max +1;
        if(max_count < current_max +1)
            max_count = current_max +1;
        if(max_count < current_max +1){
            max_count = current_max +1;
        }
        if(max_count < current_max +1){
            max_count = current_max +1;
        }
        if(current_max > max_count){
            max_count = current_max;
        }
        // Alternatively, after the loop
        if(current_max > max_count){
            max_count = current_max;
        }
    }
    printf("%d\n", max_count);
    return 0;
}