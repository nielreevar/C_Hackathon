#include "hackathonapp.h"
#define SPEED 300000000
FILE* readBlindSpotDetectionFile(FILE* fp, unsigned long int* time_side, float* threshold)
{
/* Read data from the database and validate its integrity */
    if (fscanf(fp, "%lu %f", time_side, threshold) == 2)
    {
        return fp;
    }
    else
    {
        return NULL;
    }
}

uint8_t activateBlindSpot(unsigned long int time_side, float threshold)
{
    unsigned long int  side = (time_side & 1) ? 1 : 0; //if side =0 -> left if side =1 -> right
    unsigned long int time_ns =  (time_side >> 1);

    double distance = (SPEED*(time_ns / 1e9))/2;

    if((distance <= threshold) && (side == 0)) //left return 1
    {
        return 1;
    }
    else if((distance <= threshold) && (side == 1)) //right return 2
    {
        return 2;
    }
    else  // blind spot not detected -> 0
    {
        return 0;
    }
}