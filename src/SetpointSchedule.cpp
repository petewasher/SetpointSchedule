#include "SetpointSchedule.h"
#include <float.h>

//---------------------------------------------------------------------------
SetpointSchedule::SetpointSchedule(const ScheduleType type, const SlotTypes slotsPerHour) : m_scheduleType(type),
                                                                                            m_daySchedule(0x0)
{
    generateSchedule(slotsPerHour);
}

//---------------------------------------------------------------------------
SetpointSchedule::~SetpointSchedule()
{
}

//---------------------------------------------------------------------------
void SetpointSchedule::generateSchedule(const SlotTypes slotsPerHour)
{
    m_daySchedule = new DaySchedule();

    switch (m_scheduleType)
    {
    case ScheduleType_1Day:
        // Link the list to the start
        m_daySchedule->next = m_daySchedule;
        break;

    case ScheduleType_WeekdayWeekend:
        break;

    case ScheduleType_7Day:
        break;

    default:
        // Disaster!
        break;
    }
}

//---------------------------------------------------------------------------
bool SetpointSchedule::isWeekday(const DaysOfTheWeek day) const
{
    if ((int)day > (int)DaysOfTheWeek_Friday)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//---------------------------------------------------------------------------
float SetpointSchedule::getActiveSetpoint(DaysOfTheWeek day, int hours, int minutes)
{
    if (m_daySchedule)
    {
        DaySchedule *days = m_daySchedule;

        switch (m_scheduleType)
        {
        case ScheduleType_7Day:
            // Find the day in the list:
            while (days->Day != day)
            {
                days = days->next;
            }
            break;

        case ScheduleType_WeekdayWeekend:
            // Find either the first or second day depending which list 'day' is in:
            if (!isWeekday(day))
            {
                days = days->next;
            }
            break;

        case ScheduleType_1Day:
        default:
            // Use the first day - do nothing
            break;
        }

        // Now we have the right day, find the right hour:
    }
    else
    {
        // Whoops - no days yet
        return 0.0;
    }
}

//---------------------------------------------------------------------------
ScheduleSetpoint* SetpointSchedule::findSetpoint(const DaysOfTheWeek day, const unsigned int hours, const unsigned int minutes)
{
    ScheduleSetpoint *retVal = 0x0;
    DaySchedule *days = m_daySchedule;

    switch (m_scheduleType)
    {
    case ScheduleType_7Day:
        // Find the day in the list:
        while (days->Day != day)
        {
            days = days->next;
        }
        break;

    case ScheduleType_WeekdayWeekend:
        // Find either the first or second day depending which list 'day' is in:
        if (!isWeekday(day))
        {
            days = days->next;
        }
        break;

    case ScheduleType_1Day:
    default:
        // Use the first day - do nothing
        break;
    }

    // Hopefully we got something?
    if (days && (hours < 24))
    {
        // Get the hours
        HourSchedule *pHour = days->Hours;

        // Hours is 0-24, so wind through...
        while (pHour->HourIndex != hours)
        {
            pHour = pHour->next;
        }

        if (pHour)
        {
            // Find the minutes we need
            switch (days->SlotsPerHour)
            {
            case SlotTypes_One:
                retVal = pHour->Schedules;
                break;

            case SlotTypes_Two:
                if (minutes < 30)
                {
                    retVal = pHour->Schedules;
                }
                else
                {
                    retVal = pHour->Schedules->next;
                }
                break;

            case SlotTypes_Three:
                if (minutes < 20)
                {
                    retVal = pHour->Schedules;
                }
                else if ((minutes > 20) && (minutes < 40))
                {
                    retVal = pHour->Schedules->next;
                }
                else
                {
                    retVal = pHour->Schedules->next->next;
                }
                break;
            }
        }
    }

    return retVal;
}

//---------------------------------------------------------------------------
void SetpointSchedule::setSetpointInSchedule(DaysOfTheWeek day, int hours, int minutes, float &setpoint)
{
    if (m_daySchedule)
    {
        struct ScheduleSetpoint *theSetpoint = findSetpoint(day, hours, minutes);
        theSetpoint->SetPoint = setpoint;
    }
    else
    {
        // Whoops - no days yet!!
    }
}
