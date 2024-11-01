#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_B 26
#define MAX_L 26
#define MAX_D 1000
#define MAX_WORD_LEN 10

// Global variables to store the best result
int best_unique_count = -1;
int best_partition[MAX_B];

// Function to compare two unsigned long longs for qsort
int cmp_ull(const void *a, const void *b){
    unsigned long long ua = *(unsigned long long*)a;
    unsigned long long ub = *(unsigned long long*)b;
    if(ua < ub){
        return -1;
    }
    else if(ua > ub){
        return 1;
    }
    else{
        return 0;
    }
}

// Function to check if current partition is better than the best partition
int is_better(int curr_partition[], int best_partition_local[], int B){
    for(int i=0; i<B; i++){
        if(curr_partition[i] > best_partition_local[i]) return 1;
        if(curr_partition[i] < best_partition_local[i]) return 0;
    }
    return 0;
}

// Function to process a partition and return the number of unique word sequences
int process_partition(int B, int L, int partition_sizes[], unsigned char words_letters[][MAX_WORD_LEN], int words_lengths[], int D, unsigned long long codes[]){
    int letter_to_button[MAX_L];
    int start = 0;
    for(int i=0; i<B; i++){
        int size = partition_sizes[i];
        for(int j=start; j<start + size; j++){
            letter_to_button[j] = i +1;
        }
        start += size;
    }
    // Map each word to a unique code based on button assignments
    for(int i=0; i<D; i++){
        unsigned long long code = 0;
        for(int j=0; j<words_lengths[i]; j++){
            code = code * 100 + letter_to_button[ words_letters[i][j] ];
        }
        codes[i] = code;
    }
    // Sort the codes
    qsort(codes, D, sizeof(unsigned long long), cmp_ull);
    // Count unique codes
    int unique_count =0;
    if(D >=1 ){
        if (D ==1 || codes[0] != codes[1]) unique_count++;
    }
    for(int i=1; i < D -1; i++){
        if( codes[i] != codes[i-1] && codes[i] != codes[i+1] ){
            unique_count++;
        }
    }
    if(D >=2 ){
        if(codes[D-1] != codes[D-2]){
            unique_count++;
        }
    }
    return unique_count;
}

// Recursive backtrack function to generate partitions
void backtrack(int button, int start, int partition_sizes[], int B, int L, unsigned char words_letters[][MAX_WORD_LEN], int words_lengths[], int D){
    if(button == B){
        int size = L - start;
        if(size <1) return;
        partition_sizes[button-1] = size;
        // Process this partition
        unsigned long long codes[MAX_D];
        int unique_count = process_partition(B, L, partition_sizes, words_letters, words_lengths, D, codes);
        if(unique_count > best_unique_count){
            best_unique_count = unique_count;
            for(int i=0; i<B; i++) best_partition[i] = partition_sizes[i];
        }
        else if(unique_count == best_unique_count){
            if(is_better(partition_sizes, best_partition, B)){
                for(int i=0; i<B; i++) best_partition[i] = partition_sizes[i];
            }
        }
        return;
    }
    else{
        // Assign at least one letter to this button
        // and leave enough letters for the remaining buttons
        for(int end = start +1; end <= L - (B - button); end++){
            int size = end - start;
            partition_sizes[button -1] = size;
            backtrack(button +1, end, partition_sizes, B, L, words_letters, words_lengths, D);
        }
    }
}

int main(){
    int B, L;
    scanf("%d %d", &B, &L);
    int D;
    scanf("%d", &D);
    unsigned char words_letters[MAX_D][MAX_WORD_LEN];
    int words_lengths[MAX_D];
    char temp_word[MAX_WORD_LEN +1];
    for(int i=0; i<D; i++){
        scanf("%s", temp_word);
        int len = strlen(temp_word);
        words_lengths[i] = len;
        for(int j=0; j<len; j++){
            words_letters[i][j] = temp_word[j] - 'A';
        }
    }
    // Initialize partition_sizes
    int partition_sizes[MAX_B];
    memset(partition_sizes, 0, sizeof(partition_sizes));
    // Initialize best_partition with smallest possible
    memset(best_partition, 0, sizeof(best_partition));
    // Start backtracking
    backtrack(1, 0, partition_sizes, B, L, words_letters, words_lengths, D);
    // Output the result
    printf("%d\n", best_unique_count);
    // Assign letters based on best_partition and print
    int current_start =0;
    for(int i=0; i<B; i++){
        int size = best_partition[i];
        for(int j=0; j<size; j++){
            char c = 'A' + current_start + j;
            printf("%c", c);
        }
        printf("\n");
        current_start += size;
    }
    return 0;
}