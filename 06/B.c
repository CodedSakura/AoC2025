#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* file_handle = fopen("input.txt", "r");
    if (file_handle == NULL) {
        printf("Failed to read input\n");
        return 1;
    }

    char worksheet[8][4096];
    size_t column_max = 0, current_column = 0, row_max = 0;
    int character;
    while ((character = fgetc(file_handle)) != EOF) {
        if (character == '\n') {
            column_max = current_column > column_max ? current_column : column_max;
            worksheet[row_max][current_column] = '\0';
            row_max++;
            current_column = 0;
            continue;
        }
        worksheet[row_max][current_column++] = (char) character;
    }
    fclose(file_handle);

    long long sum = 0;
    char data[12];
    size_t data_index = 0;
    int numbers[8];
    size_t numbers_index = 0;
    for (int col = (int) column_max - 1; col >= 0; --col) {
        for (int row = 0; row < row_max - 1; ++row) {
            if (worksheet[row][col] == '\0' || worksheet[row][col] == ' ') {
                continue;
            }
            data[data_index++] = worksheet[row][col];
        }
        data[data_index] = '\0';
        data_index = 0;
        numbers[numbers_index++] = atoi(data);
        if (worksheet[row_max - 1][col] == '*' || worksheet[row_max - 1][col] == '+') {
            if (worksheet[row_max - 1][col] == '*') {
                long long total = 1;
                for (int n = 0; n < numbers_index; ++n) {
                    total *= numbers[n];
                }
                sum += total;
            } else {
                long long total = 0;
                for (int n = 0; n < numbers_index; ++n) {
                    total += numbers[n];
                }
                sum += total;
            }
            col--;
            numbers_index = 0;
        }
    }
    printf("%lld\n", sum);
}
