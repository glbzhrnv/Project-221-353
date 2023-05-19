#ifndef USERSTATEMODEL_HPP
#define USERSTATEMODEL_HPP

#include <string>

class UserStateModel
{
public:
    void create(std::string login, std::string password);

    void auth(std::string login, std::string password);
};

#endif // USERSTATEMODEL_HPP
