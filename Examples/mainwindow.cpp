#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "collapsible_splitter.h"
#include "side_panel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sections << "brown" << "red" << "blue" << "green" << "yellow";

    sidePanel = new SidePanel;

    QList<QAction*> actions;
    foreach (QString color, sections) {
        QWidget *contentWidget = new QWidget;
        contentWidget->setStyleSheet(QString("background-color: %1;").arg(color));
        //for testing we can set minimum width to contained widgets
        contentWidget->setMinimumWidth(100);
        sidePanel->addSection(color, QIcon(QString(":/%1.png").arg(color)), contentWidget);

        QAction *act = new QAction(QIcon(QString(":/%1.png").arg(color)), color, this);
        act->setCheckable(true);
        act->setChecked(true);
        connect(act, SIGNAL(toggled(bool)), this, SLOT(actionToggled(bool)));
        actions << act;
    }
    ui->menuSections->addActions(actions);

    cWidget = new QWidget;
    cWidget->setStyleSheet("background-color: gold;");

    splitter = new CollapsibleSplitter(this);
    setCentralWidget(splitter);
    splitter->addWidget(sidePanel);
    splitter->addWidget(cWidget);

    connect(sidePanel, SIGNAL(contentsVisibleToggled(bool)), splitter, SLOT(toggleCollapse(bool)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionToggled(bool enable)
{
    QAction *act = qobject_cast<QAction*>(sender());
    sidePanel->setSectionEnabled(act->text(), enable);
}
