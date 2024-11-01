#include <stdio.h>
#include <limits.h>

int main(){
    int n, d;
    scanf("%d %d", &n, &d);
    int maxC = 1 << d;
    int max_s[16];
    int min_s[16];
    for(int s=0; s<maxC; s++){
        max_s[s] = INT_MIN;
        min_s[s] = INT_MAX;
    }
    int coord[4];
    for(int i=0; i<n; i++){
        for(int k=0; k<d; k++) scanf("%d", &coord[k]);
        for(int s=0; s<maxC; s++){
            int val = 0;
            for(int k=0; k<d; k++) val += (s & (1<<k)) ? coord[k] : -coord[k];
            if(val > max_s[s]) max_s[s] = val;
            if(val < min_s[s]) min_s[s] = val;
        }
    }
    int max_dist = 0;
    for(int s=0; s<maxC; s++){
        int diff = max_s[s] - min_s[s];
        if(diff > max_dist) max_dist = diff;
    }
    printf("%d", max_dist);
    return 0;
}