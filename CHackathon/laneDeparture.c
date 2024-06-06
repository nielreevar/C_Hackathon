#include "hackathonapp.h"
#include <math.h>

FILE* readLaneDepartureFile(FILE* fp, float* f1, float* f2, float* f3, float* f4)
{
    /* Read data from the database and validate its integrity */
    if (fscanf(fp, "%f %f %f %f", f1, f2, f3, f4) == 4)
    {
        return fp;
    }
    return NULL;
}

int determineLaneDeparture(
    float lane_width,
    float car_width,
    float left_sensor_distance,
    float right_sensor_distance)
{
    /* Validate lane width and car width */
    if (lane_width <= car_width)
    {
        return -1;
    }

    /* Calculate adjusted threshold */
    float adjusted_threshold = (lane_width - car_width) / 2;

    /* Calculate deviation from mean position */
    float deviation = fabs(left_sensor_distance - right_sensor_distance);

    /* Determine if the car is within the lane or deviating */
    if (deviation <= adjusted_threshold)
    {
        return 0; /* Car is within the lane */
    }
    else
    {
        return 1; /* Car is deviating */
    }
}