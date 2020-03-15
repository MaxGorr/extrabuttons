#include "EditButton.h"

#include "Path.h"

#include <QDesktopServices>
#include <QUrl>

EditButton::EditButton(QWidget *parent)
    : ControlButton("Edit", parent)
{
    connect(this, &QPushButton::clicked, this, &EditButton::onClicked);
}

void EditButton::onClicked()
{
    QDesktopServices::openUrl(
        QUrl::fromLocalFile(
            Path::instance().buttonsSettings()));
}
