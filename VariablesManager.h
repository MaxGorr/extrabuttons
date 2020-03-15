#pragma once

#include <QString>

class VariablesManager
{
public:
    static void addVariable(const QString &name, const QString &value);

    static void clear();

    static QString getVariable(const QString &name);

    static QString replace(const QString &arg);
};
