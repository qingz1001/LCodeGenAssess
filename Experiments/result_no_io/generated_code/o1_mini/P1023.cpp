#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int P;
    int Q;
} Point;

int compare(const void *a, const void *b) {
    Point *pa = (Point *)a;
    Point *pb = (Point *)b;
    if (pa->P != pb->P)
        return pa->P - pb->P;
    return pa->Q - pb->Q;
}

int main(){
    int P_gov;
    scanf("%d", &P_gov);
    
    int C, Q_c;
    scanf("%d %d", &C, &Q_c);
    
    Point points[100005];
    int n =0;
    points[n].P = C;
    points[n].Q = Q_c;
    n++;
    
    while(1){
        int Pi, Qi;
        scanf("%d %d", &Pi, &Qi);
        if(Pi == -1 && Qi == -1) break;
        // Avoid adding duplicate P
        int duplicate = 0;
        for(int i=0;i<n;i++) {
            if(points[i].P == Pi){
                points[i].Q = Qi;
                duplicate =1;
                break;
            }
        }
        if(!duplicate){
            points[n].P = Pi;
            points[n].Q = Qi;
            n++;
        }
    }
    
    int D;
    scanf("%d", &D);
    
    // Sort points by P ascending
    qsort(points, n, sizeof(Point), compare);
    
    // Find Q_gov
    double Q_gov;
    if(P_gov < points[0].P){
        // Price below minimum, not possible
        Q_gov = 0;
    }
    else {
        // Find interval
        int i;
        for(i=0;i<n-1;i++) {
            if(P_gov >= points[i].P && P_gov <= points[i+1].P){
                if(points[i+1].P == points[i].P){
                    Q_gov = points[i].Q;
                }
                else{
                    double slope = (double)(points[i+1].Q - points[i].Q)/(points[i+1].P - points[i].P);
                    Q_gov = points[i].Q + slope * (P_gov - points[i].P);
                }
                break;
            }
        }
        if(i == n-1){
            // Above last P
            double Q_last = points[n-1].Q;
            Q_gov = Q_last - D * (P_gov - points[n-1].P);
        }
    }
    
    if(Q_gov <= 0){
        printf("NO SOLUTION");
        return 0;
    }
    
    double target = (double)(P_gov - C) * Q_gov;
    // Now iterate P from C to P_upper
    // Determine P_upper
    int P_max = points[n-1].P;
    double Q_max = points[n-1].Q;
    int P_upper = P_max;
    if(D >0){
        P_upper += (int)(Q_max / D) + 100;
    }
    else{
        P_upper += 1000;
    }
    if(P_gov > P_upper){
        P_upper = P_gov;
    }
    if(P_upper < P_gov){
        P_upper = P_gov;
    }
    if(P_upper < C){
        P_upper = C;
    }
    // To prevent overflow, cap P_upper
    if(P_upper > 200000) P_upper = 200000;
    
    // Precompute sorted points
    // Already sorted
    // Iterate P from C to P_upper
    double min_s_max = 1e18;
    for(int P = C; P <= P_upper; P++){
        // Compute Q(P)
        double Q_P;
        if(P < points[0].P){
            Q_P = 0;
        }
        else {
            // Find interval
            int j;
            for(j=0; j<n-1; j++){
                if(P >= points[j].P && P <= points[j+1].P){
                    if(points[j+1].P == points[j].P){
                        Q_P = points[j].Q;
                    }
                    else{
                        double slope = (double)(points[j+1].Q - points[j].Q)/(points[j+1].P - points[j].P);
                        Q_P = points[j].Q + slope * (P - points[j].P);
                    }
                    break;
                }
            }
            if(j == n-1){
                // Above last P
                Q_P = Q_max - D * (P - P_max);
            }
        }
        if(Q_P <=0){
            continue;
        }
        double s_max = ((double)(P_gov - C) * Q_gov - (double)(P - C) * Q_P) / Q_gov;
        if(s_max < min_s_max){
            min_s_max = s_max;
        }
    }
    
    // Find s
    int s;
    if(min_s_max >= 0){
        s = 0;
    }
    else{
        s = (int)floor(min_s_max);
    }
    
    // Verify
    int valid =1;
    for(int P = C; P <= P_upper; P++){
        // Compute Q(P)
        double Q_P;
        if(P < points[0].P){
            Q_P = 0;
        }
        else {
            // Find interval
            int j;
            for(j=0; j<n-1; j++){
                if(P >= points[j].P && P <= points[j+1].P){
                    if(points[j+1].P == points[j].P){
                        Q_P = points[j].Q;
                    }
                    else{
                        double slope = (double)(points[j+1].Q - points[j].Q)/(points[j+1].P - points[j].P);
                        Q_P = points[j].Q + slope * (P - points[j].P);
                    }
                    break;
                }
            }
            if(j == n-1){
                // Above last P
                Q_P = Q_max - D * (P - P_max);
            }
        }
        if(Q_P <=0){
            continue;
        }
        double profit_gov = (P_gov - C - s) * Q_gov;
        double profit_P = (P - C) * Q_P;
        if(profit_gov < profit_P - 1e-6){
            valid =0;
            break;
        }
    }
    
    if(valid){
        printf("%d", s);
    }
    else{
        printf("NO SOLUTION");
    }
}