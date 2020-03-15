#pragma once

#include <QPushButton>

class ExtraButton : public QPushButton
{
    Q_OBJECT

public:
    ExtraButton(QWidget *parent = nullptr);

    void run();

    void setCommand(const QString &command);

private:
    QString m_command;
};
