#include "../include/ProcessorCore.hpp"
#include "./include/ProcessorStorageCore.hpp"

ProcessorCore::ProcessorCore(
    ProcessorStorageCore* parentStorage,
    ProcessorCore* parentProcessor
): parentStorage(parentStorage), parentProcessor(parentProcessor)
{
}

ProcessorCore::~ProcessorCore()
{
}
