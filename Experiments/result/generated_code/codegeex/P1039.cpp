#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_M 20
#define MAX_P 100
#define MAX_NAME_LEN 50
#define MAX_STATEMENT_LEN 250

typedef struct {
    char name[MAX_NAME_LEN];
    int is_guilty;
    int is_alibi;
} Person;

typedef struct {
    char speaker[MAX_NAME_LEN];
    char statement[MAX_STATEMENT_LEN];
} Statement;

Person people[MAX_M];
Statement statements[MAX_P];
int num_people, num_liars, num_statements;

int parse_input() {
    if (scanf("%d %d %d", &num_people, &num_liars, &num_statements) != 3) {
        return 0;
    }

    for (int i = 0; i < num_people; i++) {
        scanf("%s", people[i].name);
        people[i].is_guilty = -1;
        people[i].is_alibi = -1;
    }

    for (int i = 0; i < num_statements; i++) {
        scanf("%s", statements[i].speaker);
        scanf("%s", statements[i].statement);
    }

    return 1;
}

void mark_guilty(char *name) {
    for (int i = 0; i < num_people; i++) {
        if (strcmp(people[i].name, name) == 0) {
            people[i].is_guilty = 1;
            break;
        }
    }
}

void mark_alibi(char *name) {
    for (int i = 0; i < num_people; i++) {
        if (strcmp(people[i].name, name) == 0) {
            people[i].is_alibi = 1;
            break;
        }
    }
}

int evaluate_statements() {
    for (int i = 0; i < num_statements; i++) {
        char *speaker = statements[i].speaker;
        char *statement = statements[i].statement;

        if (strncmp(statement, "I am guilty.", 12) == 0) {
            if (strcmp(speaker, "I") == 0) {
                mark_guilty(speaker);
            } else {
                return 0;
            }
        } else if (strncmp(statement, "I am not guilty.", 16) == 0) {
            if (strcmp(speaker, "I") == 0) {
                mark_alibi(speaker);
            } else {
                return 0;
            }
        } else if (strncmp(statement, " is guilty.", 11) == 0) {
            char guilty_name[MAX_NAME_LEN];
            sscanf(statement, "%s is guilty.", guilty_name);
            if (strcmp(speaker, guilty_name) == 0) {
                return 0;
            } else {
                mark_guilty(guilty_name);
            }
        } else if (strncmp(statement, " is not guilty.", 16) == 0) {
            char alibi_name[MAX_NAME_LEN];
            sscanf(statement, "%s is not guilty.", alibi_name);
            if (strcmp(speaker, alibi_name) == 0) {
                return 0;
            } else {
                mark_alibi(alibi_name);
            }
        } else if (strncmp(statement, "Today is ", 9) == 0) {
            // Ignore date statements
        } else {
            // Ignore other statements
        }
    }

    return 1;
}

int count_liars() {
    int count = 0;
    for (int i = 0; i < num_people; i++) {
        if (people[i].is_guilty == 1 && people[i].is_alibi == 1) {
            count++;
        }
    }
    return count;
}

int main() {
    if (!parse_input()) {
        printf("Impossible\n");
        return 0;
    }

    if (evaluate_statements()) {
        int num_guilty = 0;
        char guilty_name[MAX_NAME_LEN];
        for (int i = 0; i < num_people; i++) {
            if (people[i].is_guilty == 1 && people[i].is_alibi != 1) {
                num_guilty++;
                strcpy(guilty_name, people[i].name);
            }
        }

        if (num_guilty == 1) {
            printf("%s\n", guilty_name);
        } else if (num_guilty > 1) {
            printf("Cannot Determine\n");
        } else {
            printf("Impossible\n");
        }
    } else {
        printf("Impossible\n");
    }

    return 0;
}