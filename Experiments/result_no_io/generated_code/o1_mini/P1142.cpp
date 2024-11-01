#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long dy;
    long long dx;
} Slope;

long long gcd(long long a, long long b){
    if(b == 0) return a;
    return gcd(b, a % b);
}

int compare(const void *a, const void *b){
    Slope *s1 = (Slope *)a;
    Slope *s2 = (Slope *)b;
    if(s1->dy == s2->dy){
        if(s1->dx == s2->dx){
            return 0;
        }
        return s1->dx < s2->dx ? -1 : 1;
    }
    return s1->dy < s2->dy ? -1 : 1;
}

int main(){
    int n;
    scanf("%d", &n);
    int x[n], y[n];
    for(int i=0;i<n;i++) scanf("%d %d", &x[i], &y[i]);
    if(n ==0){
        printf("0\n");
        return 0;
    }
    int max_points =1;
    Slope slopes[n-1];
    for(int i=0;i<n;i++){
        int count =0;
        for(int j=0;j<n;j++) if(j !=i){
            long long dy = y[j] - y[i];
            long long dx = x[j] - x[i];
            if(dx ==0){
                dy = 1;
            }
            else if(dy ==0){
                dx =1;
            }
            else{
                if(dx <0){
                    dx = -dx;
                    dy = -dy;
                }
                long long g = gcd(abs(dy), abs(dx));
                dy /= g;
                dx /= g;
            }
            slopes[count].dy = dy;
            slopes[count].dx = dx;
            count++;
        }
        if(count ==0){
            if(max_points <1) max_points =1;
            continue;
        }
        qsort(slopes, count, sizeof(Slope), compare);
        int current =1;
        int local_max =1;
        for(int k=1;k<count;k++){
            if(slopes[k].dy == slopes[k-1].dy && slopes[k].dx == slopes[k-1].dx){
                current++;
            }
            else{
                if(current > local_max) local_max = current;
                current =1;
            }
        }
        if(current > local_max) local_max = current;
        if(local_max +1 > max_points) max_points = local_max +1;
    }
    printf("%d\n", max_points);
    return 0;
}