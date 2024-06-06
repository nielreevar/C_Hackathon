[10:59 AM] Senthilkumar, Matheshwara (M.)
#include "hackathonapp.h"
 
#define SPEED_OF_RADIO_WAVES_KM_SEC 300000.0
#define KM_TO_FEET 3280.84
 
int readLookupTable(const char* filename, struct Category* ct)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        return 0;
    }
    int i = 0;
    while (fscanf(file, "%s %d %d", ct[i].name, &ct[i].lower_limit, &ct[i].upper_limit) != EOF) {
        i++;
    }
 
    fclose(file);
    return i;
}
 
FILE* readReverseCategoryFile(FILE* fp, unsigned long int* time_taken)
{
    // Read data from the database and validate its integrity
    if (fscanf(fp, "%lu", time_taken))
    {
        return fp;
    }
    else
    {
        return NULL;
    }
}
 
const char* classifyObjectsWhileReversing(struct Category* ct, int cat_count, unsigned long int time_taken)
{  
    const float SPEED_OF_RADIO_WAVES_FT_NS = (SPEED_OF_RADIO_WAVES_KM_SEC * KM_TO_FEET) / 1e9;
    if (time_taken <= 0) {
        // Invalid time
        return "";
    }
    //to calculate distance in feet
    float distance_ft = (SPEED_OF_RADIO_WAVES_FT_NS * time_taken) / 2.0;
 
    for (int i = 0; i < cat_count; i++) {
        if (distance_ft > ct[i].lower_limit && distance_ft <= ct[i].upper_limit) {
            return ct[i].name;
        }
    }
 
    return "White";
}