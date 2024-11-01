#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char in_prefix[25];
    char in_suffix[25];
    char out_prefix[25];
    char out_suffix[25];
    int original_num;
} file_pair;

int compare(const void *a, const void *b){
    file_pair *fa = (file_pair*)a;
    file_pair *fb = (file_pair*)b;
    if(fa->original_num != fb->original_num){
        return fa->original_num - fb->original_num;
    }
    return 0;
}

void extract_parts(const char *filename, char *prefix, char *suffix, int *num){
    int len = strlen(filename);
    int i = 0;
    while(i < len && !isdigit(filename[i])) i++;
    while(i < len && !isdigit(filename[i])) i++;
    int start = -1, end = -1;
    for(int j=0; j<len; j++){
        if(isdigit(filename[j])){
            if(start == -1) start = j;
            end = j;
        }
    }
    if(start == -1){
        strcpy(prefix, filename);
        suffix[0] = '\0';
        *num = 0;
        return;
    }
    strncpy(prefix, filename, start);
    prefix[start] = '\0';
    strncpy(suffix, filename + end + 1, len - end -1);
    suffix[len - end -1] = '\0';
    char num_str[15];
    strncpy(num_str, filename + start, end - start +1);
    num_str[end - start +1] = '\0';
    *num = atoi(num_str);
}

int main(){
    char first_line[50];
    fgets(first_line, sizeof(first_line), stdin);
    int is_case2 = 0;
    int start_num = 0;
    char target_in_format[25], target_out_ext[25];
    char target_prefix[25], target_suffix_in[25];
    char target_suffix_out[25];
    int target_start_num = 0;
    if(first_line[0]=='0'||first_line[0]=='1'){
        is_case2 = 1;
        start_num = first_line[0]-'0';
    }
    else{
        is_case2 = 0;
        sscanf(first_line, "%s %s", target_in_format, target_out_ext);
        // Parse target_in_format
        extract_parts(target_in_format, target_prefix, target_suffix_in, &target_start_num);
    }
    // Read all file pairs
    file_pair *files = NULL;
    int n = 0;
    // Read until EOF
    char in_file[25], out_file[25];
    while(scanf("%s %s", in_file, out_file)!=EOF){
        files = realloc(files, sizeof(file_pair)*(n+1));
        // Extract parts
        extract_parts(in_file, files[n].in_prefix, files[n].in_suffix, &files[n].original_num);
        extract_parts(out_file, files[n].out_prefix, files[n].out_suffix, &files[n].original_num);
        files[n].original_num = 0;
        // Extract number from in_file
        int num1, num2;
        extract_parts(in_file, files[n].in_prefix, files[n].in_suffix, &num1);
        extract_parts(out_file, files[n].out_prefix, files[n].out_suffix, &num2);
        // Assuming numbers are same
        files[n].original_num = num1;
        n++;
    }
    // Sort the files based on original_num
    qsort(files, n, sizeof(file_pair), compare);
    if(is_case2){
        // Case 2: keep prefix and suffix, change number
        int current_num = start_num;
        for(int i=0;i<n;i++){
            printf("%s%d%s %s%d%s\n", files[i].in_prefix, current_num, files[i].in_suffix, files[i].out_prefix, current_num, files[i].out_suffix);
            current_num++;
        }
    }
    else{
        // Case1: use target_prefix and target_suffix_in, target_out_ext
        int current_num = target_start_num;
        for(int i=0;i<n;i++){
            printf("%s%d.%s %s%d.%s\n", target_prefix, current_num, target_suffix_in, target_prefix, current_num, target_out_ext);
            current_num++;
        }
    }
    free(files);
    return 0;
}