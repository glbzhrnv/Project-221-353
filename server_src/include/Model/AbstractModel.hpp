#ifndef ABSTRACTMODEL_HPP
#define ABSTRACTMODEL_HPP

#include <sys/types.h>
#include <string>
#include <map>

typedef struct {

    char regex[];
} PropertyDesciption;

class AbstractModel
{
protected:
    const std::map<std::string, PropertyDesciption> schema;
};

#endif // ABSTRACTMODEL_HPP
