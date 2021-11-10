
#include <NucleoH7_freeRTOS/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h>
#include <Os/TaskId.hpp>

namespace Os
{
    TaskId::TaskId(void)
    {
        TaskStatus_t taskStatus;
        vTaskGetInfo( NULL, &taskStatus,pdFALSE, eDeleted);
        id = taskStatus.xTaskNumber;
    }
    TaskId::~TaskId(void)
    {
    }
    bool TaskId::operator==(const TaskId& T) const
    {
        return (id == T.id);
    }
    bool TaskId::operator!=(const TaskId& T) const
    {
        return (id != T.id); 
    }
    TaskIdRepr TaskId::getRepr(void) const
    {
        return this->id;
    }
}
