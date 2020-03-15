#include "VariablesManager.h"

#include <QDebug>
#include <QMap>
#include <QProcessEnvironment>
#include <QRegularExpression>

namespace {
    QMap<QString, QString> g_variableMap;
    QRegularExpression g_varRx("\\$\\{(.+?)\\}"); // ${..}
}

void VariablesManager::addVariable(const QString &name, const QString &value)
{
    qDebug() << name << "=" << value << "is inserted!";
    g_variableMap.insert(name, value);
}

void VariablesManager::clear()
{
    g_variableMap.clear();
}

QString VariablesManager::getVariable(const QString &name)
{
    auto result = g_variableMap.value(name, "");
    if (!result.isEmpty()) {
        return result;
    }
    return QProcessEnvironment::systemEnvironment().value(name, "");
}

QString VariablesManager::replace(const QString &arg)
{
    QString result = arg;
    while (true) {
        auto match = g_varRx.match(result);
        if (!match.hasMatch()) {
            break;
        }
        QString var = getVariable(match.captured(1));
        result.replace(match.captured(0), var);
    }
    qDebug() << arg << "is replaced by" << result;
    return result;
}
