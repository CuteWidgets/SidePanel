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

#include "side_panel.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedLayout>

#include "side_bar.h"

#include <QAction>
#include <QSignalMapper>

#include <QDebug>

SidePanel::SidePanel(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QHBoxLayout),
    stackedLayout(new QStackedLayout),
    signalMapper(new QSignalMapper)
{
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    sideBar = new SideBar(this);

    mainLayout->addWidget(sideBar);
    mainLayout->addLayout(stackedLayout);
    setLayout(mainLayout);

    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(actionTriggered(QString)));
    setTheme(DARK);

    connect(sideBar, SIGNAL(panelVisibleChanged(bool)), this, SLOT(togglePanelVisible(bool)));
}

SidePanel::~SidePanel()
{
    qDeleteAll(hiddenWidgets);
    while (stackedLayout->count()) {
        QWidget *w = stackedLayout->takeAt(0)->widget();
        if (w) {
            delete w;
        }
    }
}

void SidePanel::addSection(const QString &name, const QIcon &icon, QWidget *contentWidget, int pos)
{
    QAction *act = new QAction(this);

    act->setData(name);
    act->setIcon(icon);
    if (pos == -1) {
        if (contentWidget) {
            stackedLayout->addWidget(contentWidget);
        }
        else {
            act->setEnabled(false);
        }
        actions << act;
        sideBar->addAction(act);
    }
    else {
        if (contentWidget) {
            stackedLayout->insertWidget(pos, contentWidget);
        }
        else {
            act->setEnabled(false);
        }
        actions.insert(pos, act);
        sideBar->insertAction(sideBar->actions().at(pos), act);
    }

    if(contentWidget) {
        contentWidget->setObjectName(name);
        contentWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
    }
    connect(act, SIGNAL(triggered()), signalMapper, SLOT(map()));
    signalMapper->setMapping(act, name);
}

void SidePanel::setWidget(const QString &sectionName, QWidget *contentWidget)
{

}

void SidePanel::activateSection(int index)
{
    sideBar->triggerAction(index);
}

void SidePanel::activateSection(const QString &name)
{
    sideBar->triggerAction(name);
}

void SidePanel::setSectionEnabled(const QString &name, bool sectEnabled)
{

    sideBar->setActionEnabled(name, sectEnabled);
    if (sideBar->currentActionName() != name || sectEnabled) {
        return;
    }
    //now activate the first enabled
    for (int i = 0; i < sideBar->actions().size(); ++i) {
        if (sideBar->actions().at(i)->isEnabled()) {
            activateSection(i);
            break;
        }
    }
}

void SidePanel::setTheme(SidePanel::Theme theme)
{
    m_theme = theme;
    switch (theme) {
    case ENV:
        sideBar->useDefaultPalette(true);
        break;
    case LIGHT:
        sideBar->useDefaultPalette(false);
        sideBar->setBgImage(QImage(":/panel_light.png"));
        break;
    case DARK:
        sideBar->useDefaultPalette(false);
        sideBar->setBgImage(QImage(":/panel_texture.png"));
        break;
    }
}

void SidePanel::setToggleable(bool toggleable)
{
    sideBar->setTogglerVisible(toggleable);
}

void SidePanel::actionTriggered(const QString &id)
{
//    qDebug() << "triggered" << id;
    if(QWidget *w = getWidgetByName(id)) {
        stackedLayout->setCurrentWidget(w);
        emit sectionActivated(id);
    }
}

void SidePanel::togglePanelVisible(bool visible)
{
//    qDebug() << "set visible" << visible;
    if(stackedLayout->count() == 0 && hiddenWidgets.size() == 0) {
        return;
    }
    if(!visible) {
        while(stackedLayout->itemAt(0)) {
//            qDebug() << "saving item";
            hiddenWidgets << stackedLayout->takeAt(0)->widget();
        }
    }
    else {
        while(hiddenWidgets.count()) {
//            qDebug() << "restoring item";
            stackedLayout->addWidget(hiddenWidgets.takeFirst());
        }
        activateSection(sideBar->currentIndex());
    }
    emit contentsVisibleToggled(visible);
    sideBar->setTogglerActive(visible);
}

QWidget *SidePanel::getWidgetByName(const QString &name) const
{
    QWidget *w = 0;
    for(int i = 0; i < stackedLayout->count(); ++i) {
        w = stackedLayout->itemAt(i)->widget();
        if(w) {
            if(w->objectName() == name) {
                return w;
            }
        }
    }
    return 0;
}
