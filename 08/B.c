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

int compare_connection(const void *a, const void *b) {
    const auto c1 = (const connection_t *)a;
    const auto c2 = (const connection_t *)b;
    if (c1->distance < c2->distance) return -1;
    if (c1->distance > c2->distance) return 1;
    return 0;
}

// took forever, but got the right answer
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

    connection_t *connections = malloc(sizeof(connection_t) * 1024 * 512);
    size_t connection_index = 0;
    for (int i = 0; i < box_index; i++) {
        for (int j = i + 1; j < box_index; j++) {
            const auto box1 = boxes[i];
            const auto box2 = boxes[j];
            const long long distance2 = (long long) (box1.x - box2.x) * (long long) (box1.x - box2.x)
                    + (long long) (box1.y - box2.y) * (long long) (box1.y - box2.y)
                    + (long long) (box1.z - box2.z) * (long long) (box1.z - box2.z);
            connections[connection_index].a = i;
            connections[connection_index].b = j;
            connections[connection_index].distance = distance2;
            connection_index++;
        }
    }

    qsort(connections, connection_index, sizeof(connection_t), compare_connection);

    int circuits[1024] = {[0 ... 1023] = 1024};
    for (int i = 0; i < connection_index; i++) {
        const int circuit_a = circuits[connections[i].a];
        const int circuit_b = circuits[connections[i].b];
        const int circuit = min3(circuit_a, circuit_b, i);
        circuits[connections[i].a] = circuit;
        circuits[connections[i].b] = circuit;
        if (circuit_a != 1024 && circuit != circuit_a) {
            // set all net_a to net
            for (int j = 0; j < box_index; ++j) {
                if (circuits[j] == circuit_a) {
                    circuits[j] = circuit;
                }
            }
        }
        if (circuit_b != 1024 && circuit != circuit_b) {
            // set all net_b to net
            for (int j = 0; j < box_index; ++j) {
                if (circuits[j] == circuit_b) {
                    circuits[j] = circuit;
                }
            }
        }
        bool all_same = true;
        for (int j = 1; j < box_index; j++) {
            if (circuits[0] != circuits[j]) {
                all_same = false;
                break;
            }
        }
        if (all_same) {
            const junction_box_t box_a = boxes[connections[i].a];
            const junction_box_t box_b = boxes[connections[i].b];
            printf("%lld\n", (long long) box_a.x * (long long) box_b.x);
            break;
        }
    }

    free(connections);
}
