#include "ControlButton.h"

ControlButton::ControlButton(const QString &data, QWidget *parent)
    :QPushButton(parent)
{
    setFixedSize(32, 32);
    setIcon(QIcon(QString(":/images/%1.png").arg(data)));
    setShortcut(QKeySequence(QString("Ctrl+") + data[0]));
    setToolTip(data + ": " + shortcut().toString());
}
