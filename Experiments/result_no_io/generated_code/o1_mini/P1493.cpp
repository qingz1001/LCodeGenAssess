#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long A;
    long long B;
    long long S;
} Pear;

int main(){
    int N;
    scanf("%d", &N);
    long long C1, C2, C3;
    scanf("%lld %lld %lld", &C1, &C2, &C3);
    Pear pears[N];
    for(int i=0;i<N;i++){
        scanf("%lld %lld", &pears[i].A, &pears[i].B);
        pears[i].S = C1 * pears[i].A + C2 * pears[i].B;
    }
    long long max_count = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            long long A0 = pears[i].A;
            long long B0 = pears[j].B;
            long long D = C3 + C1 * A0 + C2 * B0;
            long long count = 0;
            for(int k=0;k<N;k++){
                if(pears[k].A >= A0 && pears[k].B >= B0 && (C1 * (pears[k].A - A0) + C2 * (pears[k].B - B0)) <= C3){
                    count++;
                }
            }
            if(count > max_count){
                max_count = count;
            }
        }
    }
    printf("%lld\n", max_count);
}