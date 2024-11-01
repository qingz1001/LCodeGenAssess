#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_M 20
#define MAX_P 100
#define MAX_NAME_LEN 20
#define MAX_STATEMENT_LEN 250

typedef struct {
    char name[MAX_NAME_LEN];
    char statement[MAX_STATEMENT_LEN];
} Statement;

char names[MAX_M][MAX_NAME_LEN];
Statement statements[MAX_P];
int M, N, P;

bool is_guilty[MAX_M];
bool is_liar[MAX_M];

bool is_day_valid(char *day) {
    const char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int i = 0; i < 7; i++) {
        if (strcmp(day, days[i]) == 0) {
            return true;
        }
    }
    return false;
}

int find_name_index(char *name) {
    for (int i = 0; i < M; i++) {
        if (strcmp(name, names[i]) == 0) {
            return i;
        }
    }
    return -1;
}

bool parse_statement(char *statement, int speaker_index, int *guilty_index, char *day) {
    char temp[MAX_STATEMENT_LEN];
    strcpy(temp, statement);
    char *token = strtok(temp, " ");
    if (strcmp(token, "I") == 0) {
        token = strtok(NULL, " ");
        if (strcmp(token, "am") == 0) {
            token = strtok(NULL, " ");
            if (strcmp(token, "guilty.") == 0) {
                *guilty_index = speaker_index;
                return true;
            } else if (strcmp(token, "not") == 0) {
                token = strtok(NULL, " ");
                if (strcmp(token, "guilty.") == 0) {
                    *guilty_index = -1;
                    return true;
                }
            }
        }
    } else if (strcmp(token, "Today") == 0) {
        token = strtok(NULL, " ");
        if (strcmp(token, "is") == 0) {
            token = strtok(NULL, " ");
            if (is_day_valid(token)) {
                strcpy(day, token);
                return true;
            }
        }
    } else {
        int index = find_name_index(token);
        if (index != -1) {
            token = strtok(NULL, " ");
            if (strcmp(token, "is") == 0) {
                token = strtok(NULL, " ");
                if (strcmp(token, "guilty.") == 0) {
                    *guilty_index = index;
                    return true;
                } else if (strcmp(token, "not") == 0) {
                    token = strtok(NULL, " ");
                    if (strcmp(token, "guilty.") == 0) {
                        *guilty_index = -1;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool validate_statements(int guilty_index, char *day) {
    int liar_count = 0;
    for (int i = 0; i < P; i++) {
        int speaker_index = find_name_index(statements[i].name);
        int statement_guilty_index = -2;
        char statement_day[MAX_NAME_LEN];
        bool valid = parse_statement(statements[i].statement, speaker_index, &statement_guilty_index, statement_day);
        if (valid) {
            if (statement_guilty_index == guilty_index) {
                if (is_liar[speaker_index]) {
                    return false;
                }
            } else if (statement_guilty_index == -1) {
                if (!is_liar[speaker_index]) {
                    return false;
                }
            } else if (strcmp(statement_day, day) == 0) {
                if (is_liar[speaker_index]) {
                    return false;
                }
            } else {
                if (!is_liar[speaker_index]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    scanf("%d %d %d", &M, &N, &P);
    for (int i = 0; i < M; i++) {
        scanf("%s", names[i]);
    }
    for (int i = 0; i < P; i++) {
        scanf("%s: %[^\n]", statements[i].name, statements[i].statement);
    }

    int possible_guilty_count = 0;
    int possible_guilty_index = -1;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < 7; j++) {
            char day[MAX_NAME_LEN];
            strcpy(day, "Monday");
            for (int k = 0; k < j; k++) {
                strcpy(day, "Tuesday");
            }
            for (int k = 0; k < j; k++) {
                strcpy(day, "Wednesday");
            }
            for (int k = 0; k < j; k++) {
                strcpy(day, "Thursday");
            }
            for (int k = 0; k < j; k++) {
                strcpy(day, "Friday");
            }
            for (int k = 0; k < j; k++) {
                strcpy(day, "Saturday");
            }
            for (int k = 0; k < j; k++) {
                strcpy(day, "Sunday");
            }

            memset(is_guilty, false, sizeof(is_guilty));
            memset(is_liar, false, sizeof(is_liar));
            is_guilty[i] = true;
            for (int k = 0; k < N; k++) {
                is_liar[k] = true;
            }

            if (validate_statements(i, day)) {
                possible_guilty_count++;
                possible_guilty_index = i;
            }
        }
    }

    if (possible_guilty_count == 1) {
        printf("%s\n", names[possible_guilty_index]);
    } else if (possible_guilty_count > 1) {
        printf("Cannot Determine\n");
    } else {
        printf("Impossible\n");
    }

    return 0;
}