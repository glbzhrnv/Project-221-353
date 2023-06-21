#ifndef USERSTATEMODEL_HPP
#define USERSTATEMODEL_HPP

#include <string>
#include "Enum/UserAuthStateEnum.hpp"
#include "Model/UserModel.hpp"

namespace Model {

/**
 * @brief Класс, хранящий в себе текущее состяние пользователя
 */
class UserStateModel
{
public:
    /**
     * @brief Обновляет состояние авторизации
     * @param value - Идентификатор состяния
     */
    void authStatusSet(ENUM::UserAuthStateEnum value);

    /**
     * @brief Получение текущего состояния авторизации
     * @return Идентификатор состояния
     */
    ENUM::UserAuthStateEnum authStatusGet();

    /**
     * @brief Устанавливает учётные данные пользователя
     * @param value - Учётные данные
     */
    void dataSet(Model::UserModel::userData value);

    /**
     * @brief Возвращает текущие учётные данные пользователя
     * @return Указатель на учётные данные
     */
    Model::UserModel::userData* dataGet();

protected:
    /**
     * @brief Текущий состояние авторизации
     */
    ENUM::UserAuthStateEnum authStatus = ENUM::NO_AUTH;

    /**
     * @brief Данные состояния пользователя
     */
    Model::UserModel::userData userData = {};
};

}

#endif // USERSTATEMODEL_HPP
