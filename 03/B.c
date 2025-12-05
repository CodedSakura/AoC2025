
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* file_handle = fopen("input.txt", "r");
    if (file_handle == NULL) {
        printf("Failed to read input\n");
        return 1;
    }

    long long sum = 0;

    char bank[128];
    unsigned char line_index = 0;
    int character;
    while ((character = fgetc(file_handle)) != EOF) {
        bank[line_index++] = (char) character;
        if (character == '\n') {
            bank[line_index - 1] = '\0';
            line_index = 0;

            const size_t length = strlen(bank);
            char joltage[13] = {};

            size_t last_index = -1;
            for (int index = 0; index < 12; index++) {
                const size_t max_index = last_index + 1;
                // printf("%lu -> %lu\n", length - 11 + index, max_index);
                for (size_t i = length - 11 + index; i-- > max_index;) {
                    // printf("%s %d, [%lu] = %c >? %c\n", bank, index, i, bank[i], joltage[index]);
                    if (bank[i] >= joltage[index]) {
                        joltage[index] = bank[i];
                        last_index = i;
                    }
                }
            }

            sum += atoll(joltage);

            // printf("%s %s\n", bank, joltage);
        }
    }
    fclose(file_handle);

    printf("%lld\n", sum);
}
