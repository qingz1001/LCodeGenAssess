#include <stdio.h>
#include <string.h>

int main(){
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);
    
    int visited[A+1][B+1];
    memset(visited, 0, sizeof(visited));
    
    // Queue implementation
    int queue_a[A+1 * B+1];
    int queue_b[A+1 * B+1];
    int head =0, tail=0;
    
    // Initialize
    queue_a[tail] =0;
    queue_b[tail] =0;
    tail++;
    visited[0][0] =1;
    
    // Result array
    int possible[21] = {0};
    
    while(head < tail){
        int current_a = queue_a[head];
        int current_b = queue_b[head];
        int current_c = C - current_a - current_b;
        if(current_a ==0){
            if(current_c >=0 && current_c <=20){
                possible[current_c]=1;
            }
        }
        // Define pours
        int amounts[3] = {current_a, current_b, current_c};
        int caps[3] = {A, B, C};
        for(int from=0; from<3; from++){
            for(int to=0; to<3; to++){
                if(from == to) continue;
                if(amounts[from] ==0) continue;
                // Calculate pour amount
                int pour = amounts[from];
                if(amounts[from] + amounts[to] > caps[to]){
                    pour = caps[to] - amounts[to];
                }
                if(pour ==0) continue;
                // New amounts
                int new_a = current_a, new_b = current_b;
                if(from ==0){
                    new_a -= pour;
                }
                else if(from ==1){
                    new_b -= pour;
                }
                else{
                    // c is not stored, but c = C - a -b
                }
                
                if(to ==0){
                    new_a += pour;
                }
                else if(to ==1){
                    new_b += pour;
                }
                else{
                    // c = C - new_a - new_b
                }
                
                // Check and add to queue
                if(new_a >=0 && new_a <=A && new_b >=0 && new_b <=B && !visited[new_a][new_b]){
                    visited[new_a][new_b]=1;
                    queue_a[tail] = new_a;
                    queue_b[tail] = new_b;
                    tail++;
                }
            }
        }
        head++;
    }
    
    // Print results
    int first =1;
    for(int i=0;i<=C;i++) {
        if(possible[i]){
            if(!first){
                printf(" ");
            }
            printf("%d", i);
            first =0;
        }
    }
    printf("\n");
    return 0;
}