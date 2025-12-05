
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long llpow(const int base, const int exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int main() {
    FILE* file_handle = fopen("input.txt", "r");
    if (file_handle == NULL) {
        printf("Failed to read input\n");
        return 1;
    }

    long sum = 0;

    int character;
    char raw_start[12];
    char raw_end[12];
    bool processing_start = true;
    size_t index = 0;
    while ((character = fgetc(file_handle)) != EOF) {
        if (character == '-') {
            processing_start = false;
            raw_start[index] = '\0';
            index = 0;
            continue;
        }
        if (character == ',' || character == '\n') {
            processing_start = true;
            raw_end[index] = '\0';
            index = 0;

            const long long start = atoll(raw_start);
            const long long end = atoll(raw_end);

            char raw_number[12];
            for (long long i = start; i <= end; i++) {
                sprintf(raw_number, "%lld", i);
                const size_t length = strlen(raw_number);
                for (size_t j = 1; j <= length / 2; j++) {
                    if (length % j != 0) {
                        continue;
                    }
                    bool valid = true;
                    char c = '\0';
                    for (size_t k = 0; valid && k < j; k++) {
                        c = raw_number[k];
                        for (size_t l = 0; l < length; l += j) {
                            if (c != raw_number[l + k]) {
                                valid = false;
                                break;
                            }
                        }
                    }
                    if (valid) {
                        // printf("%lld\n", i);
                        sum += i;
                        break;
                    }
                }
            }

            // printf("got range from %lld to %lld\n", start, end);
            continue;
        }
        if (processing_start) {
            raw_start[index] = (char) character;
        } else {
            raw_end[index] = (char) character;
        }
        index++;
    }


    fclose(file_handle);

    printf("%ld", sum);
}
