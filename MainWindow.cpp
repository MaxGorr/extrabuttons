#include "MainWindow.h"

#include "EditButton.h"
#include "ExtraButton.h"
#include "Path.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>

#ifdef _WIN32
#include <Windows.h>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) { }

MainWindow::~MainWindow() { }

void MainWindow::build()
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    m_mainLayout = new QVBoxLayout;
    central->setLayout(m_mainLayout);

    QFrame *frame = new QFrame();
    frame->setFrameShape(QFrame::HLine);
    m_mainLayout->addWidget(frame);

    QHBoxLayout *sublayout = new QHBoxLayout;
    m_mainLayout->addLayout(sublayout);
    sublayout->addWidget(new EditButton(this));
    auto reloadBtn = new ControlButton("Reload", this);
    connect(reloadBtn, &ControlButton::clicked, this, &MainWindow::onReloadButtonClicked);
    sublayout->addWidget(reloadBtn);
    auto quitBtn = new ControlButton("Minimize", this);
    connect(quitBtn, &ControlButton::clicked, this, &MainWindow::showMinimized);
    sublayout->addWidget(quitBtn);

    Qt::WindowFlags flags = Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint;
    setWindowFlags(flags);
#ifdef _WIN32
    SetForegroundWindow((HWND)winId());
#endif
    setFixedWidth(120);
    central->setFixedWidth(120);

    QFile geomFile(Path::instance().geometrySettings());
    if (geomFile.open(QIODevice::ReadOnly)) {
        QByteArray data = geomFile.readAll();
        restoreGeometry(data);
        geomFile.close();
    }

    emit requestForData();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QFile geomFile(Path::instance().geometrySettings());
    if (geomFile.open(QIODevice::WriteOnly)) {
        geomFile.write(saveGeometry());
        geomFile.close();
    }
    QMainWindow::closeEvent(event);
}

void MainWindow::onDataParsed(QString title, QString command)
{
    ExtraButton *btn = new ExtraButton(this);
    btn->setText(title);
    btn->setCommand(command);
    m_mainLayout->insertWidget(m_btnCounter, btn);
    if (!m_btnCounter) {
        btn->setFocus();
    }
    ++m_btnCounter;
}

void MainWindow::onDataParsingFinished()
{
    int height = m_btnCounter * 36 + 56;
    centralWidget()->setFixedHeight(height);
    setFixedHeight(height);
}

void MainWindow::onReloadButtonClicked()
{
    for (; m_btnCounter > 0; --m_btnCounter) {
        auto item = m_mainLayout->takeAt(0);
        if (item) {
            auto w = item->widget();
            m_mainLayout->removeWidget(w);
            delete w;
        }
    }
    emit requestForData();
}
