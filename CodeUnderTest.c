#include "ExternalInterface.h"
#include <stdint.h>

void callExternalInterface(int times, uint16_t bufferSize, uint8_t* buffer)
{
    if (times > 0)
    {
        sendBuffer(bufferSize, buffer);
    }
}
