#ifndef USERMODEL_HPP
#define USERMODEL_HPP

#include <string>

namespace Model {

/**
 * @brief Класс, предоставляющий возможность управлять учётными записями пользователя
 */
class UserModel
{
public:
    inline static const std::string LOGIN_REGEX = "^\\w{3,20}$";
    inline static const std::string PASSWORD_REGEX = "^\\w{8,64}$";

    /**
     * @brief Даныне пользователя
     */
    struct userData {
        int32_t id;
        std::string login;
        std::string password;
        bool is_teacher;
    };

    /**
     * @brief Проверяет существование пользователя
     * @param login - Логин
     * @return Результат проверки
     */
    static bool isExists(std::string login);

    /**
     * @brief Создаёт пользователя
     * @param login - Логин
     * @param password - Пароль
     * @return Данные пользователя
     */
    static Model::UserModel::userData create(std::string login, std::string password);

    /**
     * @brief Извлекает данные пользователя в соответсвтии с логином
     * @param login - Логин
     * @param data - Указатель на хранилище данных
     * @return Результат извлечения
     */
    static bool extract(std::string login, userData &data);
};

}

#endif // USERMODEL_HPP
