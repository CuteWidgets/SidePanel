/****************************************************************************
* Copyright (C) 2011-2014 Rayner Pupo Gomez
*
* GNU Lesser General Public License Usage
* This file may be used under the terms of the GNU Lesser
* General Public License version 2.1 as published by the Free Software
* Foundation and appearing in the file LICENSE.LGPL included in the
* packaging of this file.  Please review the following information to
* ensure the GNU Lesser General Public License version 2.1 requirements
* will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "collapsible_splitter.h"
#include "side_panel.h"
#include <QMessageBox>
#include <QScopedPointer>
#include <QTimer>

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

    sidePanel->activateSection(sections.first());

    connect(sidePanel, SIGNAL(contentsVisibleToggled(bool)), splitter, SLOT(toggleCollapse(bool)));

    QTimer::singleShot(200, this, SLOT(showTips()));
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

void MainWindow::showTips()
{
    QScopedPointer<QMessageBox> msgBox(new QMessageBox);
    msgBox->setText(tr("You can resize the side panel, enable/disable sections\n"
                       "on \"sections\" menu and play with the side bar.\n"
                       "Have fun."));
    msgBox->exec();
}
