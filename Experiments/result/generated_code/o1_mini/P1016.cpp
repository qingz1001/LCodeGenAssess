#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double D;
    double P;
} Station;

int cmp(const void *a, const void *b){
    Station *s1 = (Station *)a;
    Station *s2 = (Station *)b;
    if (s1->D < s2->D) return -1;
    else if (s1->D > s2->D) return 1;
    else return 0;
}

int main(){
    double D1, C, D2, P;
    int N;
    scanf("%lf %lf %lf %lf %d", &D1, &C, &D2, &P, &N);
    Station stations[N+1];
    for(int i=0;i<N;i++) {
        scanf("%lf %lf", &stations[i].D, &stations[i].P);
    }
    stations[N].D = D1;
    stations[N].P = 0.0;
    qsort(stations, N+1, sizeof(Station), cmp);
    if(stations[0].D != 0.0){
        Station temp;
        temp.D = 0.0;
        temp.P = P;
        for(int i=N;i>0;i--){
            stations[i] = stations[i-1];
        }
        stations[0] = temp;
        N++;
    }
    double total = 0.0;
    double tank = 0.0;
    double maxDist = C * D2;
    for(int i=0;i<N;i++){
        double dist = stations[i+1].D - stations[i].D;
        if(dist > maxDist){
            printf("No Solution");
            return 0;
        }
        int j = -1;
        double minP = stations[i].P;
        for(int k=i+1; k<=N && stations[k].D - stations[i].D <= maxDist; k++){
            if(stations[k].P < minP){
                minP = stations[k].P;
                j = k;
                break;
            }
        }
        if(j == -1){
            j = i+1;
            for(int k=i+1; k<=N && stations[k].D - stations[i].D <= maxDist; k++){
                if(stations[k].P < stations[j].P){
                    j = k;
                }
            }
            total += (C - tank) * stations[i].P;
            tank = C - (stations[j].D - stations[i].D)/D2;
        }
        else{
            double needed = (stations[j].D - stations[i].D)/D2;
            if(needed > tank){
                total += (needed - tank) * stations[i].P;
                tank = 0.0;
            }
            else{
                tank -= needed;
            }
        }
    }
    printf("%.2lf", total);
    return 0;
}