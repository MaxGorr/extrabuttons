#pragma once

#include <QObject>
#include <QString>

class Parser : public QObject
{
    Q_OBJECT

public:
    Parser(QObject *parent = nullptr);

public slots:
    void fromFile();

signals:
    void dataParsed(QString title, QString command);
    void dataParsingFinished();
};
