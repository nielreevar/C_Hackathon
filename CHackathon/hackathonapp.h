#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/select.h>

int determineLaneDeparture(float, float, float, float);
FILE* readLaneDepartureFile(FILE*, float*, float*, float*, float*);

# pragma pack(1)
struct Tyre
{
    uint8_t front_pressure;
    uint8_t rear_pressure;
    unsigned int threshold;
};

struct Tyre readTyreMonitorRecord(const char*, int);
unsigned char monitorTyrePressure(struct Tyre);

FILE* readBlindSpotDetectionFile(FILE*, unsigned long int*, float*);
uint8_t activateBlindSpot(unsigned long int, float);

struct Airbag
{
    float start_time;
    float end_time;
    float init_speed;
    float final_speed;
    float gforce;
};

FILE* readAirbagActuatorFile(FILE*, struct Airbag*);
int activateAirbags(struct Airbag);

struct Category
{
    char name[100];
    int lower_limit;
    int upper_limit;
};

int readLookupTable(const char*, struct Category*);
FILE* readReverseCategoryFile(FILE*, unsigned long int*);
const char* classifyObjectsWhileReversing(struct Category*, int, unsigned long int);

struct CarFuel
{
    float fuel_cap;
    float fuel_level;
    float kmpl;
    float engine_rpm;
};

FILE* readDrivingRangeEstimatorFile(FILE*, struct CarFuel*);
int calculateDrivingRange(struct CarFuel);

void initTermios(int);
void resetTermios();
int kbhit();