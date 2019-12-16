#ifndef SETPOINT_SCHEDULE_H
#define SETPOINT_SCHEDULE_H

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

const DaysOfTheWeek Weekdays[] = {
    DaysOfTheWeek_Monday,
    DaysOfTheWeek_Tuesday,
    DaysOfTheWeek_Wednesday,
    DaysOfTheWeek_Thursday,
    DaysOfTheWeek_Friday,
};

const DaysOfTheWeek Weekend[] = {
    DaysOfTheWeek_Saturday,
    DaysOfTheWeek_Sunday,
};

typedef struct DaySchedule {

} DaySchedule;

typedef struct HourSchedule {

} HourSchedule;

typedef struct ScheduleSetpoint {
    float SetPoint;
    struct ScheduleSetpoint* next;

} ScheduleSetpoint;

class SetpointSchedule {

    public:
    SetpointSchedule(ScheduleType type, int slotsPerHour);
    ~SetpointSchedule();

    float getActiveSetpoint(DaysOfTheWeek day, int hours, int minutes);
    void setSetpointInSchedule(DaysOfTheWeek day, int hours, int minutes, float setpoint);

    private:
    ScheduleType m_scheduleType;
    DaySchedule* m_daySchedule;

};

#endif
