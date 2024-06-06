#include "hackathonapp.h"

FILE* readDrivingRangeEstimatorFile(FILE* fp, struct CarFuel* cf)
{
    if (fscanf(fp, "%f %f %f %f", &cf->fuel_cap, &cf->fuel_level, &cf->kmpl, &cf->engine_rpm) == 4)
    {
        return fp; // Return NULL if fscanf fails to read four values
    }
    return NULL; // Return the file pointer if successful
}

float get_rpm_multiplier(float engine_rpm) {
    if (engine_rpm < 2000) {
        return 1.0;
    } else if (engine_rpm >= 2000 && engine_rpm < 3200) {
        return 1.2;
    } else {
        return 1.5;
    }
}

int calculateDrivingRange(struct CarFuel cf)
{
    // Validating the inputs
    if (cf.fuel_cap <= 0 || cf.fuel_level <= 0 || cf.fuel_level > 100 || cf.kmpl <= 0 || cf.engine_rpm <= 0) {
        return -1;
    }

    // Determine the RPM-based multiplier
    float consumption_multiplier = get_rpm_multiplier(cf.engine_rpm);
    
    // Calculate the available fuel in liters bodmas
    float usable_fuel = (cf.fuel_level * cf.fuel_cap ) / 100.0 ;
    
    // Calculate the driving range in kilometers
    float  driving_range = (usable_fuel * cf.kmpl) / consumption_multiplier;
    
    return (int)driving_range;
}
