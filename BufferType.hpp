#pragma once

#include "CppUTest/SimpleString.h"
#include "CppUTestExt/MockNamedValue.h"
#include <sstream>
#include <cstdint>

struct BufferType
{
    BufferType(uint16_t length) : mLength(length) {}
    BufferType(uint16_t length, const uint8_t* buffer) : mLength(length), mBuffer(buffer) {}

    bool isEqual(const BufferType* bufferType) const
    {
        if (mLength != bufferType->mLength)
        {
            return false;
        }

        // If either buffer is NULL, assume that buffer content does not need to be compared.
        if ((mBuffer == NULL) || (bufferType->mBuffer == NULL)) return true;

        bool allEqual = true;
        for (uint16_t i = 0; i < mLength; ++i)
        {
            if (mBuffer[i] != bufferType->mBuffer[i])
            {
                allEqual = false;
                break;
            }
        }
        return allEqual;
    }

    SimpleString getString() const
    {
        std::ostringstream ss;
        uint16_t tempCopyOFLength = mLength;
        ss << tempCopyOFLength << " byte buffer";
        // Note: An immediate print of mLength does not give a use after free notification.
        return SimpleString(ss.str().c_str());
    }

  private:
    uint16_t mLength;
    const uint8_t* mBuffer = NULL;
};

class BufferTypeComparator : public MockNamedValueComparator
{
    virtual bool isEqual(const void* object1, const void* object2)
    {
        const BufferType* bufferType1 = static_cast<const BufferType*>(object1);
        const BufferType* bufferType2 = static_cast<const BufferType*>(object2);
        if ((bufferType1 == NULL) || (bufferType2 == NULL)) return false;

        return bufferType1->isEqual(bufferType2);
    }
    virtual SimpleString valueToString(const void* object)
    {
        return static_cast<const BufferType*>(object)->getString();
    }
};
