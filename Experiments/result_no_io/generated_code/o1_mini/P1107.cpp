#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fast IO
#define BUF_SIZE 1 << 25
char input_buffer[33554432];
size_t input_pos = 0, input_len = 0;

int readInt() {
    while (input_pos < input_len && (input_buffer[input_pos] < '0' || input_buffer[input_pos] > '9') && input_buffer[input_pos] != '-') {
        input_pos++;
    }
    int sign = 1, num = 0;
    if (input_pos < input_len && input_buffer[input_pos] == '-') {
        sign = -1;
        input_pos++;
    }
    while (input_pos < input_len && input_buffer[input_pos] >= '0' && input_buffer[input_pos] <= '9') {
        num = num * 10 + (input_buffer[input_pos++] - '0');
    }
    return sign * num;
}

int main(){
    // Read all input
    input_len = fread(input_buffer, 1, sizeof(input_buffer), stdin);
    
    // Read N, H, Delta
    int N = readInt();
    int H = readInt();
    int Delta = readInt();
    
    // Allocate has_fruit as a 1D array
    // has_fruit[i * (H+1) + h] = 1 if tree i has fruit at height h
    char *has_fruit = (char*)calloc((long long)N * (H+1), sizeof(char));
    if(has_fruit == NULL){
        return 1;
    }
    
    for(int i=0;i<N;i++){
        int Ni = readInt();
        for(int j=0; j<Ni; j++){
            int T = readInt();
            if(T >=1 && T <= H){
                has_fruit[(long long)i * (H+1) + T] = 1;
            }
        }
    }
    
    // Allocate dp_current and dp_new
    int *dp_current = (int*)calloc(N, sizeof(int));
    int *dp_new_arr = (int*)calloc(N, sizeof(int));
    if(dp_current == NULL || dp_new_arr == NULL){
        free(has_fruit);
        return 1;
    }
    
    // Allocate max_all
    int *max_all = (int*)calloc((H+2), sizeof(int));
    if(max_all == NULL){
        free(has_fruit);
        free(dp_current);
        free(dp_new_arr);
        return 1;
    }
    
    // Iterate from h = H downto 1
    for(int h=H; h>=1; h--){
        int m = 0;
        for(int i=0; i<N; i++){
            int option1 = (h < H) ? dp_current[i] : 0;
            int option2 = (h + Delta <= H) ? max_all[h + Delta] : 0;
            int temp = (option1 > option2) ? option1 : option2;
            dp_new_arr[i] = has_fruit[(long long)i * (H+1) + h] + temp;
            if(dp_new_arr[i] > m){
                m = dp_new_arr[i];
            }
        }
        max_all[h] = m;
        // Swap dp_current and dp_new_arr
        int *temp_ptr = dp_current;
        dp_current = dp_new_arr;
        dp_new_arr = temp_ptr;
    }
    
    // The answer is max_all[H]
    printf("%d\n", max_all[1 <= H ? 1 : 0] >= 0 ? max_all[1 <= H ? 1 : 0] : 0); // Correct index
    
    // Free memory
    free(has_fruit);
    free(dp_current);
    free(dp_new_arr);
    free(max_all);
    
    return 0;
}