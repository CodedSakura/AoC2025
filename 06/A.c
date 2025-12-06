#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* file_handle = fopen("input.txt", "r");
    if (file_handle == NULL) {
        printf("Failed to read input\n");
        return 1;
    }

    int worksheet[8][1024];
    size_t column_max = 0, current_column = 0, row_max = 0;
    char data[12];
    size_t data_index = 0;
    int character;
    bool last_was_space = true;
    while ((character = fgetc(file_handle)) != EOF) {
        if (character == ' ') {
            if (last_was_space) {
                continue;
            }
            data[data_index] = '\0';
            if (data[0] == '*' || data[0] == '+') {
                worksheet[row_max][current_column] = (unsigned char) data[0];
            } else {
                worksheet[row_max][current_column] = atoi(data);
            }
            current_column++;
            data_index = 0;
            last_was_space = true;
            continue;
        }
        if (character == '\n') {
            column_max = current_column + 1;
            if (last_was_space) {
                row_max++;
                current_column = 0;
                continue;
            }
            data[data_index] = '\0';
            if (data[0] == '*' || data[0] == '+') {
                worksheet[row_max][current_column] = (unsigned char) data[0];
            } else {
                worksheet[row_max][current_column] = atoi(data);
            }
            data_index = 0;
            row_max++;
            current_column = 0;
            last_was_space = true;
            continue;
        }
        data[data_index++] = (char) character;
        last_was_space = false;
    }
    fclose(file_handle);

    long long sum = 0;
    for (size_t col = 0; col < column_max; col++) {
        const char op = (char) worksheet[row_max - 1][col];
        long long total = op == '+' ? 0 : 1;
        // printf("%c ", op);
        for (size_t row = 0; row < row_max - 1; row++) {
            // printf("%d ", worksheet[row][col]);
            if (op == '+') {
                total += worksheet[row][col];
            } else {
                total *= worksheet[row][col];
            }
        }
        sum += total;
        // printf("= %lld\n", total);
    }
    printf("%lld\n", sum);
}
