#include <stdio.h>

typedef struct {
    long long A;
    long long B;
} Pear;

int main(){
    int N;
    scanf("%d", &N);
    
    long long C1, C2, C3;
    scanf("%lld %lld %lld", &C1, &C2, &C3);
    
    Pear pears[N];
    for(int i=0;i<N;i++){
        scanf("%lld %lld", &pears[i].A, &pears[i].B);
    }
    
    int max_count = 1;
    for(int j=0; j<N; j++){
        long long A0 = pears[j].A;
        long long B0 = pears[j].B;
        int count = 0;
        for(int i=0; i<N; i++){
            if(pears[i].A >= A0 && pears[i].B >= B0){
                long long diffA = pears[i].A - A0;
                long long diffB = pears[i].B - B0;
                long long temp = C1 * diffA + C2 * diffB;
                if(temp <= C3){
                    count++;
                }
            }
        }
        if(count > max_count){
            max_count = count;
        }
    }
    
    printf("%d\n", max_count);
    return 0;
}