#include "hackathonapp.h"

/* Process lane departure warning system */
void processLaneDeparture(FILE* fp)
{
    float lane_width, car_width, left_sensor_distance, right_sensor_distance;
    fp = readLaneDepartureFile(fp, &lane_width, &car_width, &left_sensor_distance, &right_sensor_distance);
    int result = determineLaneDeparture(lane_width, car_width, left_sensor_distance, right_sensor_distance);
    // printf("Lane Departure: %d\n", result);
}

/* Process tyre pressure monitoring system */
void processTyrePressure() 
{
    int record_num = rand() % 25 + 1;
    struct Tyre tyre = readTyreMonitorRecord("files/TPMonitor.dat", record_num);
    unsigned char result = monitorTyrePressure(tyre);
    // printf("Tyre Pressure: %u\n", result);
}

/* Process blind spot detection system */
void processBlindSpot(FILE* fp)
{
    unsigned long int time_side;
    float threshold;
    fp = readBlindSpotDetectionFile(fp, &time_side, &threshold);
    uint8_t result = activateBlindSpot(time_side, threshold);
    // printf("Blind Spot: %u\n", result);
}

/* Process airbag actuator system */
void processAirbag(FILE* fp)
{
    struct Airbag airbag;
    fp = readAirbagActuatorFile(fp, &airbag);
    int result = activateAirbags(airbag);
    // printf("Airbag: %d\n", result);
}

/* Process reverse camera categorization system */
void processReverseCamera(FILE* lookup_fp, FILE* reverse_fp)
{
    struct Category categories[3];
    int cat_count = readLookupTable("files/lookup_table.txt", categories);
    unsigned long int time_taken;
    reverse_fp = readReverseCategoryFile(reverse_fp, &time_taken);
    const char* result = classifyObjectsWhileReversing(categories, cat_count, time_taken);
    // printf("Reverse Camera: %s\n", result);
}

/* Process driving range estimator system */
void processDrivingRange(FILE* fp)
{
    struct CarFuel carFuel;
    fp = readDrivingRangeEstimatorFile(fp, &carFuel);
    int result = calculateDrivingRange(carFuel);
    // printf("Driving Range: %d\n", result);
}

int main()
{
    FILE* lane_fp = fopen("files/LaneDeparture.txt", "r");
    FILE* blindspot_fp = fopen("files/BSDetection.txt", "r");
    FILE* airbag_fp = fopen("files/ABActuator.txt", "r");
    FILE* reverse_fp = fopen("files/ReverseData.txt", "r");
    FILE* lookup_fp = fopen("files/lookup_table.txt", "r");
    FILE* dre_fp = fopen("files/DREstimator.txt", "r");

    initTermios(0);
    while (!kbhit())
    {
        processLaneDeparture(lane_fp);
        processTyrePressure();
        processBlindSpot(blindspot_fp);
        processAirbag(airbag_fp);
        processReverseCamera(lookup_fp, reverse_fp);
        processDrivingRange(dre_fp);
    }
    
    /* Close all opened files */
    fclose(lane_fp);
    fclose(blindspot_fp);
    fclose(airbag_fp);
    fclose(reverse_fp);
    fclose(lookup_fp);
    fclose(dre_fp);

    resetTermios();
    return 0;
}