#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "BufferType.hpp"
#include <cstring>
#include <memory>

extern "C" {
    void callExternalInterface(int times, uint16_t bufferSize, uint8_t* buffer);

    void sendBuffer(uint16_t bufferSize, uint8_t* buffer)
    {
        BufferType bufferType(bufferSize, buffer);
        mock().actualCall("sendBuffer").withParameterOfType("BufferType", "bufferType", &bufferType);
    }
}

TEST_GROUP(SimpleTestGroup)
{
    std::unique_ptr<BufferType> mBufferType;
    static const uint16_t mSize = 123;
    uint8_t mBuffer[mSize];

    void teardown()
    {
        bool makeItFail = true;
        if (!makeItFail)
        {
            // This is needed to work around a lifetime issue where the mockSupport plugin
            //     only checks expectations after the test case (along with the data) is already destroyed.
            mock().checkExpectations();
        }
    }
};

TEST(SimpleTestGroup, CallsZeroTimes)
{
    // Arrange
    const uint16_t size = 123;
    uint8_t buffer[size];
    memset(buffer, 0xAA, size);

    // Act
    callExternalInterface(0, size, buffer);

    // Implicit assert by MockSupportPlugin.
}

TEST(SimpleTestGroup, CallsOneTimes)
{
    // Arrange
    const uint16_t size = 123;
    uint8_t buffer[size];
    memset(buffer, 0xAA, size);
    mBufferType = std::make_unique<BufferType>(size, buffer);
    mock().expectOneCall("sendBuffer").withParameterOfType("BufferType", "bufferType", mBufferType.get());

    // Act
    callExternalInterface(1, size, buffer);

    // Implicit assert by MockSupportPlugin.
}

TEST(SimpleTestGroup, CallsTwoTimes)
{
    // Arrange
    const uint16_t size = 123;
    uint8_t buffer[size];
    memset(buffer, 0xAA, size);
    memset(mBuffer, 0xAA, mSize);
    mBufferType = std::make_unique<BufferType>(size, mBuffer);

    mock().expectNCalls(2, "sendBuffer").withParameterOfType("BufferType", "bufferType", mBufferType.get());

    // Act
    callExternalInterface(3, size, buffer);

     // Implicit assert by MockSupportPlugin.
}
