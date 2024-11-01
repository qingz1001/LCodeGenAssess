#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char type;
    int p;
    int q;
} cmd;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Allocate memory for army positions
    int *x = (int*)malloc(sizeof(int) * n);
    int *y = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        scanf("%d %d", &x[i], &y[i]);
    }
    
    // Allocate memory for commands
    cmd *cmds = (cmd*)malloc(sizeof(cmd) * m);
    for(int i = 0; i < m; i++){
        char c;
        scanf(" %c", &c);
        cmds[i].type = c;
        if(c == 'm'){
            scanf("%d %d", &cmds[i].p, &cmds[i].q);
        }
        else{
            cmds[i].p = 0;
            cmds[i].q = 0;
        }
    }
    
    // Initialize transformation parameters
    long long s_x = 1, s_y = 1;
    long long t_x = 0, t_y = 0;
    
    // Process commands in reverse order
    for(int i = m-1; i >= 0; i--){
        if(cmds[i].type == 'm'){
            t_x += cmds[i].p;
            t_y += cmds[i].q;
        }
        else if(cmds[i].type == 'x'){
            s_x *= -1;
            t_x *= -1;
        }
        else if(cmds[i].type == 'y'){
            s_y *= -1;
            t_y *= -1;
        }
    }
    
    // Apply transformations to each army position and print
    for(int i = 0; i < n; i++){
        long long final_x = s_x * (long long)x[i] + t_x;
        long long final_y = s_y * (long long)y[i] + t_y;
        printf("%lld %lld\n", final_x, final_y);
    }
    
    // Free allocated memory
    free(x);
    free(y);
    free(cmds);
    
    return 0;
}