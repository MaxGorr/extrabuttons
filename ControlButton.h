#pragma once

#include <QPushButton>

class ControlButton : public QPushButton
{
    Q_OBJECT

public:
    ControlButton(const QString &data, QWidget *parent = nullptr);
};
