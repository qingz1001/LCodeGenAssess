#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_CURRENCIES 30
#define INF 1e20
#define MAX_NAME_LENGTH 31

int main(){
    int n, m, case_num=1;
    char currency_names[MAX_CURRENCIES][MAX_NAME_LENGTH];
    double f[MAX_CURRENCIES][MAX_CURRENCIES];
    char src[MAX_NAME_LENGTH], dest[MAX_NAME_LENGTH];
    double rate;
    
    while(scanf("%d", &n) == 1){
        if(n == 0) break;
        
        // Read currency names
        for(int i=0;i<n;i++){
            scanf("%s", currency_names[i]);
        }
        
        // Initialize matrix
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i == j){
                    f[i][j] = 0.0;
                }
                else{
                    f[i][j] = INF;
                }
            }
        }
        
        // Read m exchange rates
        scanf("%d", &m);
        for(int i=0;i<m;i++){
            scanf("%s %lf %s", src, &rate, dest);
            int from = -1, to = -1;
            for(int k=0;k<n;k++){
                if(strcmp(src, currency_names[k]) == 0){
                    from = k;
                }
                if(strcmp(dest, currency_names[k]) == 0){
                    to = k;
                }
                if(from != -1 && to != -1){
                    break;
                }
            }
            if(from != -1 && to != -1){
                double w = -log(rate);
                if(w < f[from][to]){
                    f[from][to] = w;
                }
            }
        }
        
        // Floyd-Warshall
        for(int k=0;k<n;k++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(f[i][k] + f[k][j] < f[i][j]){
                        f[i][j] = f[i][k] + f[k][j];
                    }
                }
            }
        }
        
        // Check for negative cycles
        int arbitrage = 0;
        for(int i=0;i<n;i++){
            if(f[i][i] < -1e-8){
                arbitrage = 1;
                break;
            }
        }
        
        // Output
        printf("Case %d: %s\n", case_num, arbitrage ? "Yes" : "No");
        case_num++;
    }
    
    return 0;
}