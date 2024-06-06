#include "hackathonapp.h"
#include<math.h>

#define ACCEL_G 9.81

FILE* readAirbagActuatorFile(FILE* fp, struct Airbag* ab)
{   
    /* Read data from the database and validate its integrity */
    if (fscanf(fp, "%f %f %f %f %f",
           &(ab->start_time),
           &(ab->init_speed),
           &(ab->end_time),
           &(ab->final_speed),
           &(ab->gforce)) == 5)
    {
        return fp;
    }
    else
    {
        return NULL;
    }
}

int activateAirbags(struct Airbag ab)
{
    float gforce_act;
    //conversion of kmph to m/s
    ab.init_speed= ab.init_speed * (5.0/18.0);
    ab.final_speed = ab.final_speed * (5.0/18.0);

    //calculation of actual gforce
    //9.81 is acceleration due to gravity   
    gforce_act = ((fabs(ab.final_speed - ab.init_speed))/(ab.end_time - ab.start_time))/ACCEL_G;

    if(gforce_act > ab.gforce)
    {
        return 1;
    }

    return 0;
}
