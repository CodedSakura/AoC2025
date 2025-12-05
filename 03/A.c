
#include <stdio.h>
#include <string.h>

int main() {
    FILE* file_handle = fopen("input.txt", "r");
    if (file_handle == NULL) {
        printf("Failed to read input\n");
        return 1;
    }

    int sum = 0;

    char bank[128];
    unsigned char line_index = 0;
    int character;
    while ((character = fgetc(file_handle)) != EOF) {
        bank[line_index++] = (char) character;
        if (character == '\n') {
            bank[line_index - 1] = '\0';
            line_index = 0;

            const size_t length = strlen(bank);

            char max = 0;
            size_t max_index = -1;
            for (size_t i = length - 1; i-- > 0;) {
                if (bank[i] >= max) {
                    max = bank[i];
                    max_index = i;
                }
            }
            char next = 0;
            for (size_t i = max_index + 1; i < length; i++) {
                if (bank[i] > next) {
                    next = bank[i];
                }
            }

            const int value = (max - '0') * 10 + next - '0';
            sum += value;

            // printf("%s %d\n", bank, value);
        }
    }
    fclose(file_handle);

    printf("%d\n", sum);
}
