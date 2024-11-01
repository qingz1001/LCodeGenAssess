#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRINGS 10000
#define MAX_LENGTH 400
#define MAX_QUEUE 100000
#define MAX_INPUT 20
#define MAX_S_LENGTH 21

typedef struct {
    char str[MAX_LENGTH + 1];
    int count;
} Visited;

// Comparator for qsort for strings array
int cmp_input_strings(const void *a, const void *b) {
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;
    return strcmp(s1, s2);
}

// Comparator for qsort for current level strings
int cmp_current_level(const void *a, const void *b) {
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;
    return strcmp(s1, s2);
}

// Function to find a string in the visited array
int find_string(Visited *visited, int visited_count, char *s) {
    for(int i = 0; i < visited_count; i++) {
        if(strcmp(visited[i].str, s) == 0)
            return i;
    }
    return -1;
}

int main(){
    int n;
    scanf("%d", &n);
    char input_strings[MAX_INPUT][MAX_S_LENGTH];
    char *ptr_strings[MAX_INPUT];
    for(int i=0;i<n;i++) {
        scanf("%s", input_strings[i]);
        ptr_strings[i] = input_strings[i];
    }

    // Sort input strings lex
    qsort(ptr_strings, n, sizeof(char*), cmp_input_strings);

    // Initialize visited with empty string
    Visited visited_arr[MAX_STRINGS];
    int visited_count = 0;
    strcpy(visited_arr[visited_count].str, "");
    visited_arr[visited_count].count = 1;
    visited_count++;

    // Initialize queue
    int queue[MAX_QUEUE];
    int head = 0, tail = 0;
    queue[tail++] = 0;

    // Initialize answer
    char answer[MAX_LENGTH +1];
    answer[0] = '\0';
    int answer_found = 0;

    while(head < tail){
        int level_size = tail - head;
        if(level_size <=0) break;

        // Collect current level strings
        char *current_level[level_size];
        for(int i=0; i<level_size; i++) {
            current_level[i] = visited_arr[queue[head + i]].str;
        }

        // Sort current level strings lex
        qsort(current_level, level_size, sizeof(char*), cmp_current_level);

        // Process each string in current level
        for(int i=0; i<level_size; i++){
            // Find the index of current_level[i]
            int idx = find_string(visited_arr, visited_count, current_level[i]);
            if(idx == -1) continue;

            // For each input string
            for(int j=0; j<n; j++){
                char new_str[MAX_LENGTH +1];
                strcpy(new_str, visited_arr[idx].str);
                strcat(new_str, ptr_strings[j]);

                // Check if new_str is already visited
                int found = find_string(visited_arr, visited_count, new_str);
                if(found != -1){
                    visited_arr[found].count++;
                    if(visited_arr[found].count == 2){
                        if(!answer_found){
                            strcpy(answer, new_str);
                            answer_found = 1;
                        }
                        else{
                            int len_new = strlen(new_str);
                            int len_ans = strlen(answer);
                            if(len_new < len_ans){
                                strcpy(answer, new_str);
                            }
                            else if(len_new == len_ans && strcmp(new_str, answer) < 0){
                                strcpy(answer, new_str);
                            }
                        }
                    }
                }
                else{
                    // Add new_str to visited and enqueue
                    if(visited_count >= MAX_STRINGS){
                        // Exceeded maximum visited strings
                        continue;
                    }
                    strcpy(visited_arr[visited_count].str, new_str);
                    visited_arr[visited_count].count = 1;
                    queue[tail++] = visited_count;
                    visited_count++;
                }

                // If answer found and it's the smallest possible in this level, stop
                if(answer_found){
                    // Since we are processing in lex order within the level, the first found is the lex smallest
                    break;
                }
            }
            if(answer_found){
                break;
            }
        }
        head += level_size;
        if(answer_found){
            break;
        }
    }

    printf("%lu\n%s\n", strlen(answer), answer);
    return 0;
}