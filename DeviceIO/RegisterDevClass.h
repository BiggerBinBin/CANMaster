#ifndef REGISTERDEVCLASS_H
#define REGISTERDEVCLASS_H
#include "ReflectClass.h"
#include "peakCAN.h"
class RegisterDevReflect
{
public:
    static void RegisterReflect()
    {
        CReflectClass<DeviceIO>::registerClass<peakCAN>();
    }
};

#endif // REGISTERDEVCLASS_H
