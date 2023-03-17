#ifndef PROCESSORCORE_HPP
#define PROCESSORCORE_HPP

#include <QtGlobal>
#include "./ProcessorStorageCore.hpp"

class ProcessorCore
{
public:
    ProcessorCore(
        ProcessorStorageCore* parentStorage = nullptr,
        ProcessorCore* parentProcessor = nullptr
    );
    ~ProcessorCore();
    virtual int requestProcess(QByteArray* data) = 0;
private:
    ProcessorStorageCore* parentStorage = nullptr;
    ProcessorCore* parentProcessor = nullptr;
};
#endif // PROCESSORCORE_HPP
