#pragma once

#include <QString>

class Path
{
private:
    Path();

public:
    static Path & instance();

    QString buttonsSettings() const { return m_buttonsFile; }
    QString geometrySettings() const { return m_geometryFile; }
    QString lockFile() const { return m_lockFile; }

private:
    void build(QString &fileNameDst, const QString &fileNameSrc);

private:
    QString m_buttonsFile;
    QString m_geometryFile;
    QString m_lockFile;
};
