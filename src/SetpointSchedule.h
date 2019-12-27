#ifndef SETPOINT_SCHEDULE_H
#define SETPOINT_SCHEDULE_H

#include "SetpointScheduleEnums.h"
#include "ScheduleLinkedList.h"

class SetpointSchedule {

    public:
    SetpointSchedule(const ScheduleType type, const SlotTypes slotsPerHour);
    ~SetpointSchedule();

    float getActiveSetpoint(DaysOfTheWeek day, int hours, int minutes);
    void setSetpointInSchedule(DaysOfTheWeek day, int hours, int minutes, float& setpoint);

    private:
    void generateSchedule(const SlotTypes slotsPerHour);
    bool isWeekday(const DaysOfTheWeek day) const;
    ScheduleSetpoint* findSetpoint(const DaysOfTheWeek day, const unsigned int hours, const unsigned int minutes);
    HourSchedule* generate24h(const SlotTypes slotsPerHour);
    ScheduleSetpoint* generateSlots(const SlotTypes slotsPerHour);
    ScheduleType m_scheduleType;

    // Always points to the start of the schedule
    DaySchedule* m_daySchedule;
};

#endif
