#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestRegistry.h"
#include "CppUTestExt/MockSupportPlugin.h"
#include "BufferType.hpp"

int main(int ac, char** av)
{
    MockSupportPlugin mockPlugin;
    BufferTypeComparator bufferTypeComparator;
    mockPlugin.installComparator("BufferType", bufferTypeComparator);
    TestRegistry::getCurrentRegistry()->installPlugin(&mockPlugin);
    return CommandLineTestRunner::RunAllTests(ac, av);
}
