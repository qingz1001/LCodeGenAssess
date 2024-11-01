#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
} Cow;

int is_safe(int n, Cow cows[], int exclude) {
    for(int i = 0; i < n; i++) {
        if(i == exclude) continue;
        int can_move = 0;
        // Check North
        int blocked = 0;
        for(int r = cows[i].row -1; r >=1; r--){
            int found = 0;
            for(int j =0; j < n; j++) {
                if(j == exclude) continue;
                if(cows[j].row == r && cows[j].col == cows[i].col){
                    found =1;
                    break;
                }
            }
            if(found){
                blocked =1;
                break;
            }
        }
        if(!blocked){
            can_move =1;
        }
        // Check East
        blocked =0;
        if(!can_move){
            for(int c = cows[i].col +1; c <=50; c++){
                int found =0;
                for(int j =0; j < n; j++) {
                    if(j == exclude) continue;
                    if(cows[j].row == cows[i].row && cows[j].col == c){
                        found =1;
                        break;
                    }
                }
                if(found){
                    blocked =1;
                    break;
                }
            }
            if(!blocked){
                can_move =1;
            }
        }
        if(!can_move){
            return 0;
        }
    }
    return 1;
}

int main(){
    int r, c, n;
    scanf("%d %d", &r, &c);
    scanf("%d", &n);
    Cow cows[n];
    for(int i =0;i<n;i++){
        scanf("%d %d", &cows[i].row, &cows[i].col);
    }
    // Check initial
    if(is_safe(n, cows, -1)){
        printf("0\n");
        return 0;
    }
    // Check each removal
    int valid[n];
    for(int i=0;i<n;i++) valid[i]=0;
    for(int i=0;i<n;i++){
        if(is_safe(n, cows, i)){
            valid[i]=1;
        }
    }
    int count=0;
    for(int i=0;i<n;i++) if(valid[i]) count++;
    if(count ==0){
        printf("-1\n");
    }
    else{
        for(int i=0;i<n;i++) if(valid[i]) printf("%d\n", i+1);
    }
    return 0;
}