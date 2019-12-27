#ifndef SCHEDULE_LINKED_LIST
#define SCHEDULE_LINKED_LIST

#include "SetpointScheduleEnums.h"

// Holds the setpoints within an hour
class ScheduleSetpoint
{
    public:
    // The setpoint at this schedule point
    float SetPoint;

    // The setpoint index, dependant on 
    // Divisions from the DaySchedule:
    // setpointIndex = [0:Divisions-1], which 
    // represent 60 minutes / Divisions worth of
    // time. 
    unsigned short setpointIndex;

    // The next schedule setpoint
    ScheduleSetpoint *next;

};

// Holds each hour within a day
class HourSchedule
{
public:
    // The set of schedules for this hour
    ScheduleSetpoint *Schedules;

    // The hour we are scheduling
    unsigned short HourIndex;

    // The next hour
    HourSchedule *next;
};

// Holds the schedule for a day
class DaySchedule
{
    public:
    // The day we are scheduling
    DaysOfTheWeek Day;

    // How many slots are the hours divided into?
    SlotTypes SlotsPerHour;

    // Hours in the day
    HourSchedule *Hours;

    // Next day in the list
    DaySchedule *next;
};

#endif
