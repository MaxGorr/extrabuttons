#include "MainWindow.h"

#include "Parser.h"
#include "Path.h"

#include <QApplication>
#include <QLockFile>
#include <QMessageBox>
#include <QProxyStyle>

class ShortcutStyle : public QProxyStyle
{
public:
    int styleHint(StyleHint hint, const QStyleOption *option = 0,
                  const QWidget *widget = 0,
                  QStyleHintReturn *returnData = 0) const override
    {
        if (hint == QStyle::SH_UnderlineShortcut) {
            return 1;
        }
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLockFile lockFile(Path::instance().lockFile());
    if (!lockFile.tryLock(100)) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Already launched!");
        return msgBox.exec();
    }
    a.setStyle(new ShortcutStyle());
    MainWindow w;
    Parser p;
    QObject::connect(&p, &Parser::dataParsed, &w, &MainWindow::onDataParsed);
    QObject::connect(&p, &Parser::dataParsingFinished, &w, &MainWindow::onDataParsingFinished);
    QObject::connect(&w, &MainWindow::requestForData, &p, &Parser::fromFile);
    w.build();
    w.show();

    return a.exec();
}
