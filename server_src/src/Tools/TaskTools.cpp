#include <QSqlDatabase>
#include <QJsonDocument>
#include <QJsonObject>
#include "Enum/FSMTypeEnum.hpp"
#include "Model/TaskModel.hpp"
#include "Task/MealySolve.hpp"
#include "Task/MealySuperposition.hpp"
#include "Task/MooreSolve.hpp"
#include "Task/MooreSuperposition.hpp"
#include "Tools/TaskTools.hpp"

taskData TaskTools::create(ENUM::FSMTypeEnum type)
{
    QJsonObject data;
    std::string request = "01010101";
    std::string solution;

    switch (type) {
        case ENUM::MEALY_SOLVE:
            data = MealySolve::gen(request, solution);
            break;
        case ENUM::MEALY_SUPER:
            data = MealySuperposition::gen(request, solution);
            break;
        case ENUM::MEALY_TO_MOORE:
            break;
        case ENUM::MOORE_SOLVE:
            data = MooreSolve::gen(request, solution);
            break;
        case ENUM::MOORE_SUPER:
            data = MooreSuperposition::gen(request, solution);
            break;
    }

    return {
        .id = 0,
        .type = type,
        .data = QJsonDocument(data).toJson(QJsonDocument::Compact).toStdString(),
        .solution = solution,
        .is_solved = true
    };
}
