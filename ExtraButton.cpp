#include "ExtraButton.h"

#include <QDesktopServices>
#include <QUrl>

ExtraButton::ExtraButton(QWidget *parent)
    : QPushButton(parent)
{
    connect(this, &QPushButton::clicked,
            this, &ExtraButton::run);
    setFixedHeight(32);
}

void ExtraButton::setCommand(const QString &command) { m_command = command; }

void ExtraButton::run()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_command));
}
