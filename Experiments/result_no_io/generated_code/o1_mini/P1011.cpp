#include <stdio.h>

int main(){
    int a, n, m, x;
    scanf("%d %d %d %d", &a, &n, &m, &x);
    
    if(n ==1){
        printf("%d\n", a);
        return 0;
    }

    int on[21] = {0};
    int found = 0;
    int k;
    for(k=0; k<=m; k++){
        on[1] = a;
        on[2] = k;
        for(int j=3; j<=n-1; j++){
            on[j] = on[j-1] + on[j-2];
        }
        if(on[n-1] == m - a){
            found =1;
            break;
        }
    }

    // Assuming the input guarantees a solution
    int on_train_after[21] = {0};
    for(int j=1; j<=n; j++){
        if(j ==1){
            on_train_after[j] = a;
        }
        else if(j ==2){
            // off[j] = on[j]
            on_train_after[j] = a;
        }
        else if(j <n){
            // off[j] = on[j-1]
            on_train_after[j] = on_train_after[j-1] + on[j] - on[j-1];
        }
        else{
            // j ==n
            on_train_after[j] =0;
        }
    }

    printf("%d\n", on_train_after[x]);
    return 0;
}