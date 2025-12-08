#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define min3(a,b,c) (((a)<(b))?(min(a,c)):(min(b,c)))

typedef struct {
    int x, y, z;
} junction_box_t;
typedef struct {
    size_t a, b;
    long long distance;
} connection_t;

#define CON_COUNT 1000


// 13072 - too low
int main() {
    FILE* file_handle = fopen("input.txt", "r");
    if (file_handle == NULL) {
        printf("Failed to read input\n");
        return 1;
    }

    junction_box_t boxes[1024];
    char data[12];
    size_t data_index = 0;
    size_t box_index = 0;
    bool processing_x = true;
    int character;
    while ((character = fgetc(file_handle)) != EOF) {
        if (character == '\n') {
            data[data_index] = '\0';
            boxes[box_index++].z = atoi(data);
            data_index = 0;
            processing_x = true;
            continue;
        }
        if (character == ',') {
            data[data_index] = '\0';
            if (processing_x) {
                boxes[box_index].x = atoi(data);
                processing_x = false;
            } else {
                boxes[box_index].y = atoi(data);
            }
            data_index = 0;
            continue;
        }
        data[data_index++] = (char) character;
    }
    fclose(file_handle);

    connection_t connections[CON_COUNT];
    for (int i = 0; i < box_index; i++) {
        for (int j = i + 1; j < box_index; j++) {
            const auto box1 = boxes[i];
            const auto box2 = boxes[j];
            const long long distance2 = (long long) (box1.x - box2.x) * (long long) (box1.x - box2.x)
                    + (long long) (box1.y - box2.y) * (long long) (box1.y - box2.y)
                    + (long long) (box1.z - box2.z) * (long long) (box1.z - box2.z);
            for (int c = 0; c < CON_COUNT; c++) {
                if (connections[c].a == 0 && connections[c].b == 0) {
                    connections[c].a = i;
                    connections[c].b = j;
                    connections[c].distance = distance2;
                    break;
                }
                if (connections[c].distance > distance2) {
                    if (c < CON_COUNT - 1) {
                        connection_t old[CON_COUNT];
                        memcpy(old, connections, CON_COUNT * sizeof(connection_t));
                        memcpy(&connections[c+1], &old[c], (CON_COUNT - c) * sizeof(connection_t));
                    }
                    connections[c].a = i;
                    connections[c].b = j;
                    connections[c].distance = distance2;
                    break;
                }
            }
        }
    }

    int circuits[1024] = {[0 ... 1023] = 1024};
    for (int i = 0; i < CON_COUNT; i++) {
        const int circuit_a = circuits[connections[i].a];
        const int circuit_b = circuits[connections[i].b];
        const int circuit = min3(circuit_a, circuit_b, i);
        circuits[connections[i].a] = circuit;
        circuits[connections[i].b] = circuit;
        if (circuit_a != 1024 && circuit != circuit_a) {
            // set all net_a to net
            for (int j = 0; j < 1024; ++j) {
                if (circuits[j] == circuit_a) {
                    circuits[j] = circuit;
                }
            }
        }
        if (circuit_b != 1024 && circuit != circuit_b) {
            // set all net_b to net
            for (int j = 0; j < 1024; ++j) {
                if (circuits[j] == circuit_b) {
                    circuits[j] = circuit;
                }
            }
        }
    }

    int circuit_sizes[1024] = {};
    for (int i = 0; i < box_index; i++) {
        if (circuits[i] != 1024) {
            circuit_sizes[circuits[i]]++;
        }
    }

    int largest_circuits[3] = {};
    for (int i = 0; i < box_index; i++) {
        for (int n = 0; n < 3; n++) {
            if (largest_circuits[n] == 0) {
                largest_circuits[n] = circuit_sizes[i];
                break;
            }
            if (circuit_sizes[i] > largest_circuits[n]) {
                if (n < 2) {
                    int old[3];
                    memcpy(old, largest_circuits, 3 * sizeof(int));
                    memcpy(&largest_circuits[n+1], &old[n], (3 - n) * sizeof(int));
                }
                largest_circuits[n] = circuit_sizes[i];
                break;
            }
        }
    }

    long long product = 1;
    for (int i = 0; i < 3; i++) {
        product *= largest_circuits[i];
    }

    printf("%lld\n", product);
}
