#ifndef PROCESSORCORE_HPP
#define PROCESSORCORE_HPP

#include <QtGlobal>
#include <QJsonObject>
#include "./ProcessorStorageCore.hpp"

class ProcessorCore
{
public:
    ProcessorCore(
        ProcessorStorageCore* parentStorage = nullptr,
        ProcessorCore* parentProcessor = nullptr
    );
    ~ProcessorCore();
    virtual int requestProcess(QJsonObject* data) = 0;
private:
    ProcessorStorageCore* parentStorage = nullptr;
    ProcessorCore* parentProcessor = nullptr;
};
#endif // PROCESSORCORE_HPP
