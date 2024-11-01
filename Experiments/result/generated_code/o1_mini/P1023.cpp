#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int price;
    int sales;
} Point;

// Comparator for qsort
int compare(const void *a, const void *b){
    int pa = ((Point*)a)->price;
    int pb = ((Point*)b)->price;
    if(pa < pb) return -1;
    else if(pa > pb) return 1;
    else return 0;
}

int main(){
    int G;
    scanf("%d", &G);
    
    int C, S_c;
    scanf("%d %d", &C, &S_c);
    
    // Maximum possible points
    int max_points = 100005;
    Point *points = (Point*)malloc(sizeof(Point)*max_points);
    int count = 0;
    
    // Add cost point
    points[count].price = C;
    points[count].sales = S_c;
    count++;
    
    // Read other points
    while(1){
        int p, s;
        scanf("%d %d", &p, &s);
        if(p == -1 && s == -1) break;
        points[count].price = p;
        points[count].sales = s;
        count++;
    }
    
    // Read D
    int D;
    scanf("%d", &D);
    
    // Sort points by price
    qsort(points, count, sizeof(Point), compare);
    
    // Remove duplicates, keep the last occurrence
    int unique = 1;
    for(int i=1;i<count;i++){
        if(points[i].price == points[i-1].price){
            points[i-1].sales = points[i].sales;
        }
        else{
            points[unique++] = points[i];
        }
    }
    count = unique;
    
    // Find max price
    int max_price = points[count-1].price;
    int max_sales = points[count-1].sales;
    
    // Function to get q(P)
    // Precompute segments
    // Each segment from points[i] to points[i+1]
    // After last point, q decreases by D per price
    // Assume P >= C
    // To optimize, iterate P from C up to when q(P) <=0
    // and collect all P and q(P)
    
    // First, find q(G)
    double qG = 0.0;
    if(G < C){
        qG = 0.0;
    }
    else{
        // Binary search to find where G is
        int found = 0;
        for(int i=0;i<count;i++){
            if(points[i].price == G){
                qG = points[i].sales;
                found = 1;
                break;
            }
        }
        if(!found){
            // Find the segment
            for(int i=0;i<count-1;i++){
                if(points[i].price < G && G < points[i+1].price){
                    double slope = (double)(points[i+1].sales - points[i].sales)/(points[i+1].price - points[i].price);
                    qG = points[i].sales + slope * (G - points[i].price);
                    qG = floor(qG);
                    break;
                }
            }
            if(G > points[count-1].price){
                qG = points[count-1].sales - D * (G - points[count-1].price);
                if(qG < 0) qG = 0;
            }
            else if(G == points[count-1].price){
                qG = points[count-1].sales;
            }
        }
    }
    
    // Initialize T_low and T_high
    double T_low = -1e12;
    double T_high = 1e12;
    int no_solution = 0;
    
    // Iterate P from C up to when q(P) <=0
    // To optimize, iterate through segments
    for(int i=0;i<count;i++){
        // Current point
        int P = points[i].price;
        // Get q(P)
        int qP = points[i].sales;
        // Skip if P < C
        if(P < C) continue;
        // Calculate constraint
        if(qG > qP){
            double numerator = (double)(P - C)*qP - (double)(G - C)*qG;
            double denominator = (double)(qG - qP);
            double temp = numerator / denominator;
            double ceil_temp = ceil(temp);
            if(ceil_temp > T_low){
                T_low = ceil_temp;
            }
        }
        else if(qG < qP){
            double numerator = (double)(P - C)*qP - (double)(G - C)*qG;
            double denominator = (double)(qG - qP);
            double floor_temp = floor(numerator / denominator);
            if(floor_temp < T_high){
                T_high = floor_temp;
            }
        }
        else{
            if(G < P){
                no_solution = 1;
                break;
            }
        }
    }
    
    if(no_solution){
        printf("NO SOLUTION");
        return 0;
    }
    
    // After last point, q(P) decreases by D
    // Iterate P from max_price +1 until q(P) >0
    int P = max_price +1;
    int qP = max_sales - D;
    while(qP >0 && P <= 100000){
        if(qG > qP){
            double numerator = (double)(P - C)*qP - (double)(G - C)*qG;
            double denominator = (double)(qG - qP);
            double temp = numerator / denominator;
            double ceil_temp = ceil(temp);
            if(ceil_temp > T_low){
                T_low = ceil_temp;
            }
        }
        else if(qG < qP){
            double numerator = (double)(P - C)*qP - (double)(G - C)*qG;
            double denominator = (double)(qG - qP);
            double floor_temp = floor(numerator / denominator);
            if(floor_temp < T_high){
                T_high = floor_temp;
            }
        }
        else{
            if(G < P){
                no_solution = 1;
                break;
            }
        }
        P++;
        qP -= D;
    }
    
    if(no_solution){
        printf("NO SOLUTION");
        return 0;
    }
    
    // Handle G itself
    // Already considered in the loop
    
    // Check if T_low <= T_high
    if(T_low > T_high){
        printf("NO SOLUTION");
        return 0;
    }
    
    // Find T in [T_low, T_high] with minimal |T|
    // Prefer smallest |T|
    // If tie, choose the one closer to zero
    long long TL = ceil(T_low);
    long long TH = floor(T_high);
    
    // Clamp TL and TH to integer range
    if(TL < -1e9) TL = -1000000000;
    if(TH > 1e9) TH = 1000000000;
    
    // Find the best T
    long long best_T = 0;
    int found = 0;
    // If 0 is within [TL, TH], it's the best
    if(TL <=0 && 0 <= TH){
        best_T = 0;
        found = 1;
    }
    else{
        // Find the closest to zero
        if(TH <0){
            best_T = (long long)TH;
            found =1;
        }
        else if(TL >0){
            best_T = (long long)TL;
            found =1;
        }
        else{
            // TL <=0 and TH >=0, already handled
            // Should not reach here
        }
    }
    
    if(found){
        printf("%lld", best_T);
    }
    else{
        printf("NO SOLUTION");
    }
    
    free(points);
    return 0;
}