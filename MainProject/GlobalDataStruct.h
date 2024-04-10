#ifndef GLOBALDATASTRUCT_H
#define GLOBALDATASTRUCT_H
struct DeviceParameter
{
    short devType;
    short devChannel;
    short baudRate;
    short devModel;
    DeviceParameter()
    {
        devType = 0;
        devChannel = 0;
        baudRate = 0;
        devModel = 0;
    }
};

#endif // GLOBALDATASTRUCT_H
