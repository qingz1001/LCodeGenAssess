#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    int *a = (int*)malloc(n * m * sizeof(int));
    for(int i=0; i<n*m; i++) {
        scanf("%d", &a[i]);
    }
    int *count = (int*)calloc(k, sizeof(int));
    char *day_present = (char*)malloc(k * sizeof(char));
    for(int j=0; j<m; j++){
        memset(day_present, 0, k * sizeof(char));
        for(int i=0; i<n; i++){
            int d = a[i*m + j];
            if(d >=1 && d <=k){
                day_present[d-1] = 1;
            }
        }
        for(int d=0; d<k; d++) {
            if(day_present[d]) count[d]++;
        }
    }
    for(int d=0; d<k; d++){
        if(d >0) printf(" ");
        printf("%d", count[d]);
    }
    printf("\n");
    free(a);
    free(count);
    free(day_present);
    return 0;
}