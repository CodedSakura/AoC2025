
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* file_handle = fopen("input.txt", "r");
    if (file_handle == NULL) {
        printf("Failed to read input\n");
        return 1;
    }

    long long fresh_ranges[256][2];
    char data[32];
    size_t data_index = 0;
    size_t range_max = 0;
    bool last_was_newline = false;
    int character;
    while ((character = fgetc(file_handle)) != EOF) {
        if (character == '-') {
            data[data_index] = '\0';
            fresh_ranges[range_max][0] = atoll(data);
            data_index = 0;
            continue;
        }
        if (character == '\n') {
            if (last_was_newline) {
                break;
            }
            last_was_newline = true;
            data[data_index] = '\0';
            fresh_ranges[range_max][1] = atoll(data);
            range_max++;
            data_index = 0;
            continue;
        }
        data[data_index++] = (char) character;
        last_was_newline = false;
    }
    fclose(file_handle);

    for (size_t a = 0; a < range_max; a++) {
        for (size_t b = 0; b < range_max; b++) {
            if (fresh_ranges[b][1] == 0 || a == b) {
                continue;
            }
            if (fresh_ranges[b][0] <= fresh_ranges[a][1] && fresh_ranges[a][1] <= fresh_ranges[b][1]) {
                if (fresh_ranges[b][0] > fresh_ranges[a][0]) {
                    fresh_ranges[b][0] = fresh_ranges[a][0];
                }
                fresh_ranges[a][0] = 0;
                fresh_ranges[a][1] = 0;
            }
        }
    }

    long long sum = 0;
    for (size_t a = 0; a < range_max; a++) {
        if (fresh_ranges[a][1] == 0) {
            continue;
        }
        sum += fresh_ranges[a][1] - fresh_ranges[a][0] + 1;
    }

    printf("%lld\n", sum);
}
