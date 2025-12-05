
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1489 - too low, but same as someone else's
int main() {
    FILE* file_handle = fopen("input.txt", "r");
    if (file_handle == NULL) {
        printf("Failed to read input\n");
        return 1;
    }

    long long fresh_ranges[256][2];
    long long ingredients[1024];
    char data[32];
    size_t data_index = 0;
    size_t range_max = 0, ingredient_max = 0;
    bool processing_ranges = true;
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
                processing_ranges = false;
                continue;
            }
            last_was_newline = true;
            if (processing_ranges) {
                data[data_index] = '\0';
                fresh_ranges[range_max][1] = atoll(data);
                range_max++;
                data_index = 0;
                continue;
            }
            data[data_index] = '\0';
            ingredients[ingredient_max] = atoll(data);
            ingredient_max++;
            data_index = 0;
            continue;
        }
        data[data_index++] = (char) character;
        last_was_newline = false;
    }
    fclose(file_handle);

    int fresh = 0;
    for (size_t i = 0; i < ingredient_max; i++) {
        // printf("%lld\n", ingredients[i]);
        for (size_t range = 0; range < range_max; range++) {
            if (fresh_ranges[range][0] <= ingredients[i] && ingredients[i] <= fresh_ranges[range][1]) {
                fresh++;
                break;
            }
        }
    }
    printf("%d\n", fresh);
}
