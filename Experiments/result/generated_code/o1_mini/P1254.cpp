#include <stdio.h>
#include <stdlib.h>

#define MAX_N 8
#define MAX_ASSIGNMENTS 1000000

typedef struct {
    int sectors[MAX_N];
} Assignment;

Assignment assignments[MAX_ASSIGNMENTS];
int assign_count = 0;
int max_i = 0;

int compute_max_i(int sectors[], int n) {
    unsigned long long mask1 = 0;
    unsigned long long mask2 = 0;

    for(int j = 0; j < n; j++) {
        int sum = 0;
        for(int l = 0; l < n; l++) {
            int idx = (j + l) % n;
            sum += sectors[idx];
            if(sum >=1 && sum <=64){
                mask1 |= (1ULL << (sum -1));
            }
            else if(sum >=65 && sum <=128){
                mask2 |= (1ULL << (sum -65));
            }
        }
    }

    int i = 1;
    while(i <= 128){
        if(i <= 64){
            if( (mask1 & (1ULL << (i-1))) == 0 ) break;
        }
        else{
            if( (mask2 & (1ULL << (i-65))) == 0 ) break;
        }
        i++;
    }
    return i-1;
}

void backtrack(int sectors[], int pos, int n){
    if(pos == n){
        int current_i = compute_max_i(sectors, n);
        if(current_i > max_i){
            max_i = current_i;
            assign_count = 0;
            if(assign_count < MAX_ASSIGNMENTS){
                for(int k = 0; k < n; k++) assignments[assign_count].sectors[k] = sectors[k];
                assign_count++;
            }
        }
        else if(current_i == max_i){
            if(assign_count < MAX_ASSIGNMENTS){
                for(int k = 0; k < n; k++) assignments[assign_count].sectors[k] = sectors[k];
                assign_count++;
            }
        }
        return;
    }

    for(int val =1; val <=20; val++){
        sectors[pos] = val;
        backtrack(sectors, pos+1, n);
    }
}

int main(){
    int n;
    if(scanf("%d", &n)!=1){
        return 0;
    }
    if(n <1 || n >8){
        return 0;
    }

    int sectors[MAX_N];
    for(int i=0; i<MAX_N; i++) sectors[i] =1;
    sectors[0] =1;

    backtrack(sectors, 1, n);

    printf("%d\n", max_i);
    for(int a=0; a<assign_count; a++){
        for(int k=0; k<n; k++){
            printf("%d", assignments[a].sectors[k]);
            if(k != n-1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}