#include "hackathonapp.h"

struct Tyre readTyreMonitorRecord(const char* filename, int record_num) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    struct Tyre tyre;
    fseek(file, (record_num - 1) * sizeof(struct Tyre), SEEK_SET);
    fread(&tyre, sizeof(struct Tyre), 1, file);
    fclose(file);

    return tyre;
}

unsigned char monitorTyrePressure(struct Tyre ty) {
    unsigned char tyrePressureFlags = 0;
    int lowPressureCount = 0;

    unsigned long int front_left_pressure = (ty.front_pressure & 0x0F);
    unsigned long int front_right_pressure = ((ty.front_pressure >> 4) & 0x0F);
    unsigned long int rear_left_pressure = ((ty.rear_pressure & 0x0F) & 0x0F);
    unsigned long int rear_right_pressure = ((ty.rear_pressure >> 4) & 0x0F);

    unsigned long int front_left_threshold = (ty.threshold & 0xFF);
    unsigned long int front_right_threshold = ((ty.threshold >> 8) & 0xFF);
    unsigned long int rear_left_threshold = ((ty.threshold >> 16) & 0xFF);
    unsigned long int rear_right_threshold = ((ty.threshold >> 24) & 0xFF);

    // Check front right tyre pressure
    if (front_right_pressure < front_right_threshold)
    {
        tyrePressureFlags |= (1 << 0); // FR
        lowPressureCount++;
    }
    // Check front left tyre pressure
    if (front_left_pressure < front_left_threshold)
    {
        tyrePressureFlags |= (1 << 1); // FL
        lowPressureCount++;
    }
    // Check rear right tyre pressure
    if (rear_right_pressure < rear_right_threshold)
    {
        tyrePressureFlags |= (1 << 2); // RR
        lowPressureCount++;
    }
    // Check rear left tyre pressure
    if (rear_left_pressure < rear_left_threshold)
    {
        tyrePressureFlags |= (1 << 3); // RL
        lowPressureCount++;
    }

    // Set warning flag if more than two tyres have low pressure
    if (lowPressureCount > 2)
    {
        tyrePressureFlags |= (1 << 5); // W
    }

    return tyrePressureFlags;
}