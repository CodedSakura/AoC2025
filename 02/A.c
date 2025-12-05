
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

            size_t start_len = strlen(raw_start);
            const size_t end_len = strlen(raw_end);

            long long start = atoll(raw_start);
            long long end = atoll(raw_end);

            if (start_len != end_len) {
                if (start_len % 2 == 0) {
                    end = end - end % llpow(10, (int) start_len) - 1;
                } else {
                    start = llpow(10, (int) end_len - 1);
                    start_len++;
                }
            }

            if (start_len % 2 != 0) {
                // printf("odd range (%s-%s)\n", raw_start, raw_end);
                continue;
            }

            const long long mid = llpow(10, (int) start_len / 2);

            for (long long i = start; i <= end; i++) {
                const long long head = i / mid;
                const long long tail = i % mid;
                if (head == tail) {
                    // printf("found %lld\n", i);
                    sum += i;
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
