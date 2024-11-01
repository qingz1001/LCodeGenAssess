#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LIGHTS 2000000
#define BYTE_SIZE 8

int main(){
    int n;
    scanf("%d", &n);
    // Calculate number of bytes needed
    int num_bytes = (MAX_LIGHTS + BYTE_SIZE -1)/BYTE_SIZE;
    unsigned char *lights = (unsigned char*)calloc(num_bytes, sizeof(unsigned char));
    if(!lights){
        return 1;
    }
    double a;
    int t;
    unsigned long long a_int;
    unsigned long long k_a;
    unsigned long long l;
    unsigned long long max_l = 0;
    for(int i=0;i<n;i++){
        scanf("%lf %d", &a, &t);
        a_int = (unsigned long long)(a * 1000000.0 + 1e-3);
        for(int k=1; k<=t; k++){
            k_a = ((unsigned long long)k) * a_int;
            l = k_a / 1000000;
            if(l >=1 && l <= MAX_LIGHTS){
                unsigned long long idx = (l-1)/BYTE_SIZE;
                int bit = (l-1)%BYTE_SIZE;
                lights[idx] ^= (1 << bit);
                if(l > max_l){
                    max_l = l;
                }
            }
        }
    }
    for(unsigned long long l=1; l<=max_l; l++){
        unsigned long long idx = (l-1)/BYTE_SIZE;
        int bit = (l-1)%BYTE_SIZE;
        if(lights[idx] & (1 << bit)){
            printf("%llu\n", l);
            free(lights);
            return 0;
        }
    }
    free(lights);
    return 0;
}