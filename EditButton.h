#pragma once

#include "ControlButton.h"

class EditButton : public ControlButton
{
    Q_OBJECT

public:
    EditButton(QWidget *parent = nullptr);

public slots:
    void onClicked();
};
