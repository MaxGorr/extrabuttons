#include "Path.h"

#include <QDir>
#include <QFile>
#include <QStandardPaths>

namespace {
    const QString BUTTONS_FILE = "config.xml";
    const QString GEOMETRY_FILE = "settings.dat";
    const QString LOCK_FILE = "extrabuttons.lock";
}

Path & Path::instance()
{
    static Path path;
    return path;
}

Path::Path()
{
    build(m_buttonsFile, BUTTONS_FILE);
    build(m_geometryFile, GEOMETRY_FILE);
    m_lockFile = QDir::cleanPath(QDir::tempPath() + QDir::separator() + LOCK_FILE);
}

void Path::build(QString &fileNameDst, const QString &fileNameSrc)
{
    QString writable = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QDir writableDir(writable);
    writableDir.mkdir(".");
    fileNameDst = QDir::cleanPath(writable + QDir::separator() + fileNameSrc);
}
