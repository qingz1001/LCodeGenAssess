#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int idx;
    int val; // 0 for B, 1 for R
} Fixed;

typedef struct {
    double p1;
    double *p;
    double *q;
} Game;

int main(){
    int n, m;
    char type[21];
    scanf("%d %d %s", &n, &m, type);
    
    Game game;
    game.p = (double*)malloc((n+2) * sizeof(double));
    game.q = (double*)malloc((n+2) * sizeof(double));
    
    scanf("%lf", &game.p1);
    for(int i=2;i<=n;i++){
        scanf("%lf %lf", &game.p[i], &game.q[i]);
    }
    
    // Use an array to store fixed information
    int *fixed = (int*)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++) fixed[i] = -1; // -1 means not fixed
    
    // To store the operations
    char op[10];
    int idx, c;
    
    // Precompute expectations without any fixed information
    // Here, for simplicity, we compute full expectation each time
    // But since n and m are large, this is not efficient
    // However, due to problem constraints, we proceed
    
    for(int op_num=0; op_num<m; op_num++){
        scanf("%s", op);
        if(strcmp(op, "add")==0){
            scanf("%d %d", &idx, &c);
            fixed[idx] = c;
        }
        else{
            scanf("%d", &idx);
            fixed[idx] = -1;
        }
        
        // Now compute the expectation
        // We need to iterate from 1 to n, considering fixed points
        // Keep track of previous fixed or not
        double E = 0.0;
        double prevR = -1.0, prevB = -1.0;
        if(fixed[1] == 1){
            E += 1.0;
            prevR = 1.0;
            prevB = 0.0;
        }
        else if(fixed[1] == 0){
            prevR = 0.0;
            prevB = 1.0;
        }
        else{
            prevR = game.p1;
            prevB = 1.0 - game.p1;
            E += game.p1;
        }
        
        for(int i=2;i<=n;i++){
            if(fixed[i] == 1){
                if(prevR >=0){
                    E +=1.0;
                    prevR =1.0;
                    prevB =0.0;
                }
                else{
                    E +=1.0 * prevR;
                    prevR =1.0;
                    prevB =0.0;
                }
            }
            else if(fixed[i] ==0){
                if(prevR >=0){
                    prevR =0.0;
                    prevB =1.0;
                }
                else{
                    prevR =0.0;
                    prevB =1.0;
                }
            }
            else{
                if(prevR >=0){
                    E += game.p[i];
                    double newR = game.p[i];
                    double newB = 1.0 - game.p[i];
                    prevR = newR;
                    prevB = newB;
                }
                else{
                    double currP = prevR * game.p[i] + prevB * game.q[i];
                    E += prevR * game.p[i] + prevB * game.q[i];
                    double newR = (prevR * game.p[i] * 1.0 + prevB * game.q[i] * 1.0) / currP;
                    double newB = 1.0 - newR;
                    prevR = newR;
                    prevB = newB;
                }
            }
        }
        printf("%.6lf\n", E);
    }
    
    free(game.p);
    free(game.q);
    free(fixed);
    return 0;
}