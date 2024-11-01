#include <stdio.h>
#include <limits.h>

int main(){
    int n, d;
    scanf("%d %d", &n, &d);
    int comb = 1 << d;
    long max_val[16];
    long min_val[16];
    for(int c=0; c<comb; c++){
        max_val[c] = LONG_MIN;
        min_val[c] = LONG_MAX;
    }
    int coords[4];
    for(int i=0; i<n; i++){
        for(int k=0; k<d; k++) scanf("%d", &coords[k]);
        for(int c=0; c<comb; c++){
            long f = 0;
            for(int k=0; k<d; k++){
                if(c & (1<<k)) f += coords[k];
                else f -= coords[k];
            }
            if(f > max_val[c]) max_val[c] = f;
            if(f < min_val[c]) min_val[c] = f;
        }
    }
    long result = 0;
    for(int c=0; c<comb; c++){
        long diff = max_val[c] - min_val[c];
        if(diff > result) result = diff;
    }
    printf("%ld", result);
    return 0;
}