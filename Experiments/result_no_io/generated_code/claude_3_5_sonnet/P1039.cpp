#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PEOPLE 20
#define MAX_STATEMENTS 100
#define MAX_NAME_LENGTH 20
#define MAX_STATEMENT_LENGTH 250

char names[MAX_PEOPLE][MAX_NAME_LENGTH + 1];
char statements[MAX_STATEMENTS][MAX_STATEMENT_LENGTH + 1];
char speaker[MAX_STATEMENTS][MAX_NAME_LENGTH + 1];
int M, N, P;

int find_name(char *name) {
    for (int i = 0; i < M; i++) {
        if (strcmp(names[i], name) == 0) return i;
    }
    return -1;
}

int is_valid_day(char *day) {
    char *valid_days[] = {"MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY"};
    for (int i = 0; i < 7; i++) {
        if (strcmp(day, valid_days[i]) == 0) return 1;
    }
    return 0;
}

int check_consistency(int suspect, int liars) {
    int liar_count = 0;
    for (int i = 0; i < P; i++) {
        int speaker_id = find_name(speaker[i]);
        int is_liar = (liar_count < liars) ? 1 : 0;
        
        if (strstr(statements[i], "I am guilty")) {
            if ((speaker_id == suspect) != is_liar) return 0;
        } else if (strstr(statements[i], "I am not guilty")) {
            if ((speaker_id != suspect) != is_liar) return 0;
        } else if (strstr(statements[i], "is guilty")) {
            char name[MAX_NAME_LENGTH + 1];
            sscanf(statements[i], "%s is guilty", name);
            int accused = find_name(name);
            if ((accused == suspect) != is_liar) return 0;
        } else if (strstr(statements[i], "is not guilty")) {
            char name[MAX_NAME_LENGTH + 1];
            sscanf(statements[i], "%s is not guilty", name);
            int accused = find_name(name);
            if ((accused != suspect) != is_liar) return 0;
        } else if (strstr(statements[i], "Today is")) {
            char day[10];
            sscanf(statements[i], "Today is %s", day);
            if (!is_valid_day(day)) return 0;
        }
        
        if (is_liar) liar_count++;
    }
    return liar_count == liars;
}

int main() {
    scanf("%d %d %d", &M, &N, &P);
    
    for (int i = 0; i < M; i++) {
        scanf("%s", names[i]);
    }
    
    for (int i = 0; i < P; i++) {
        scanf("%s : %[^\n]", speaker[i], statements[i]);
    }
    
    int suspect_count = 0;
    int last_suspect = -1;
    
    for (int i = 0; i < M; i++) {
        if (check_consistency(i, N)) {
            suspect_count++;
            last_suspect = i;
        }
    }
    
    if (suspect_count == 0) {
        printf("Impossible\n");
    } else if (suspect_count == 1) {
        printf("%s\n", names[last_suspect]);
    } else {
        printf("Cannot Determine\n");
    }
    
    return 0;
}