#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_NAME 30

typedef struct {
    char in_name[MAX_NAME];
    char out_name[MAX_NAME];
    int number;
} FilePair;

int get_number(const char* filename) {
    int num = 0;
    for(int i = 0; filename[i]; i++) {
        if(filename[i] >= '0' && filename[i] <= '9') {
            num = num * 10 + (filename[i] - '0');
        }
    }
    return num;
}

int cmp(const void* a, const void* b) {
    FilePair fa = *(FilePair*)a;
    FilePair fb = *(FilePair*)b;
    if(fa.number != fb.number)
        return fa.number - fb.number;
    return 0;
}

int main(){
    char token1[MAX_NAME], token2[MAX_NAME];
    int res = scanf("%s", token1);
    if(res !=1) return 0;
    res = scanf("%s", token2);
    FilePair* files;
    int n;
    if(res == 1 && (strcmp(token1, "0") ==0 || strcmp(token1, "1") ==0)){
        // Case 2
        int start_num = token1[0] - '0';
        sscanf(token2, "%d", &n);
        files = (FilePair*)malloc(sizeof(FilePair)*n);
        for(int i=0;i<n;i++) {
            scanf("%s %s", files[i].in_name, files[i].out_name);
            files[i].number = get_number(files[i].in_name);
        }
        qsort(files, n, sizeof(FilePair), cmp);
        for(int i=0;i<n;i++) {
            int new_num = start_num + i;
            // Input file
            char prefix_in[MAX_NAME], ext_in[MAX_NAME];
            int pos = 0;
            while(files[i].in_name[pos] && !(files[i].in_name[pos]>='0' && files[i].in_name[pos]<='9')) pos++;
            strncpy(prefix_in, files[i].in_name, pos);
            prefix_in[pos] = '\0';
            char *dot = strchr(files[i].in_name, '.');
            if(dot){
                strcpy(ext_in, dot+1);
            }
            else{
                ext_in[0] = '\0';
            }
            char new_in[MAX_NAME];
            if(dot){
                sprintf(new_in, "%s%d.%s", prefix_in, new_num, ext_in);
            }
            else{
                sprintf(new_in, "%s%d", prefix_in, new_num);
            }
            // Output file
            char prefix_out[MAX_NAME], ext_out[MAX_NAME];
            pos = 0;
            while(files[i].out_name[pos] && !(files[i].out_name[pos]>='0' && files[i].out_name[pos]<='9')) pos++;
            strncpy(prefix_out, files[i].out_name, pos);
            prefix_out[pos] = '\0';
            dot = strchr(files[i].out_name, '.');
            if(dot){
                strcpy(ext_out, dot+1);
            }
            else{
                ext_out[0] = '\0';
            }
            char new_out[MAX_NAME];
            if(dot){
                sprintf(new_out, "%s%d.%s", prefix_out, new_num, ext_out);
            }
            else{
                sprintf(new_out, "%s%d", prefix_out, new_num);
            }
            printf("%s %s\n", new_in, new_out);
        }
    }
    else{
        // Case 1
        char target_in[MAX_NAME], target_out_ext[MAX_NAME];
        strcpy(target_in, token1);
        strcpy(target_out_ext, token2);
        scanf("%d", &n);
        files = (FilePair*)malloc(sizeof(FilePair)*n);
        for(int i=0;i<n;i++) {
            scanf("%s %s", files[i].in_name, files[i].out_name);
            files[i].number = get_number(files[i].in_name);
        }
        qsort(files, n, sizeof(FilePair), cmp);
        // Parse target_in
        char main_in[MAX_NAME], ext_in[MAX_NAME];
        int pos = 0;
        int len = strlen(target_in);
        while(pos < len && !(target_in[pos]>='0' && target_in[pos]<='9')) pos++;
        strncpy(main_in, target_in, pos);
        main_in[pos] = '\0';
        int num_start = 0;
        while(pos < len && target_in[pos]>='0' && target_in[pos]<='9') {
            num_start = num_start *10 + (target_in[pos]-'0');
            pos++;
        }
        if(target_in[pos] == '.'){
            strcpy(ext_in, target_in + pos +1);
        }
        else{
            ext_in[0] = '\0';
        }
        for(int i=0;i<n;i++) {
            int new_num = num_start + i;
            // New input file
            char new_in[MAX_NAME];
            if(ext_in[0]){
                sprintf(new_in, "%s%d.%s", main_in, new_num, ext_in);
            }
            else{
                sprintf(new_in, "%s%d", main_in, new_num);
            }
            // New output file
            // Parse original output main name and extension
            char orig_out_main[MAX_NAME], orig_out_ext[MAX_NAME];
            pos = 0;
            while(files[i].out_name[pos] && !(files[i].out_name[pos]>='0' && files[i].out_name[pos]<='9')) pos++;
            strncpy(orig_out_main, files[i].out_name, pos);
            orig_out_main[pos] = '\0';
            char *dot = strchr(files[i].out_name, '.');
            if(dot){
                strcpy(orig_out_ext, dot+1);
            }
            else{
                orig_out_ext[0] = '\0';
            }
            char new_out[MAX_NAME];
            if(orig_out_ext[0]){
                sprintf(new_out, "%s%d.%s", main_in, new_num, target_out_ext);
            }
            else{
                sprintf(new_out, "%s%d", main_in, new_num);
            }
            printf("%s %s\n", new_in, new_out);
        }
    }
    free(files);
    return 0;
}