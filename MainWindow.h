#pragma once

#include <QMainWindow>

class QVBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void build();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void onDataParsed(QString title, QString command);
    void onDataParsingFinished();
    void onReloadButtonClicked();

signals:
    void requestForData();

private:
    int m_btnCounter = 0;
    QVBoxLayout *m_mainLayout = nullptr;
};
