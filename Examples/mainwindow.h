#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SidePanel;
class CollapsibleSplitter;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void actionToggled(bool enable);

private:
    Ui::MainWindow *ui;
    QStringList sections;
    CollapsibleSplitter *splitter;
    SidePanel *sidePanel;
    QWidget *cWidget;
};

#endif // MAINWINDOW_H
