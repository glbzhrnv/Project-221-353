#ifndef GENERALPROCESSOR_HPP
#define GENERALPROCESSOR_HPP

#include <map>
#include <QtGlobal>
#include "../ProcessorStorageCore.hpp"
#include "../ProcessorCore.hpp"

class GeneralProcessor: public ProcessorCore
{
public:
    int requestProcess(QByteArray* data);
private:
    std::map<quint64, ProcessorStorageCore*> storageMap;
    std::map<quint64, ProcessorCore*> processorMap;
};

#endif // GENERALPROCESSOR_HPP
