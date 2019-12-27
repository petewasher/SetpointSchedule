#ifndef SETPOINT_SCHEDULE_ENUMS
#define SETPOINT_SCHEDULE_ENUMS

enum ScheduleType {
    ScheduleType_7Day,
    ScheduleType_WeekdayWeekend,
    ScheduleType_1Day
};

enum DaysOfTheWeek {
    DaysOfTheWeek_Monday,
    DaysOfTheWeek_Tuesday,
    DaysOfTheWeek_Wednesday,
    DaysOfTheWeek_Thursday,
    DaysOfTheWeek_Friday,
    DaysOfTheWeek_Saturday,
    DaysOfTheWeek_Sunday,
};

enum SlotTypes {
    // Setpoint per hour
    SlotTypes_One,

    // Setpoint every 1/2 hour
    SlotTypes_Two,

    // Setpoint every 1/3 hour
    SlotTypes_Three
};

#endif