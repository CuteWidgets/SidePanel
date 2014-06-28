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

#ifndef SIDE_PANEL_H
#define SIDE_PANEL_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QVBoxLayout;
class QStackedLayout;
template <class T> class QList;
class QSignalMapper;
QT_END_NAMESPACE

class SideBar;
class ContentHeader;

class SidePanel : public QWidget
{
    Q_OBJECT
public:
    enum Theme { ENV = 0, LIGHT, DARK };
    explicit SidePanel(QWidget *parent = 0);
    ~SidePanel();
    void addSection(const QString &name, const QIcon &icon, QWidget *contentWidget = 0, int pos = -1);
    void setWidget(const QString &sectionName, QWidget *contentWidget);
    void activateSection(int index);
    void activateSection(const QString &name);
    void setSectionEnabled(const QString &name, bool sectEnabled = true);
    void setTheme(Theme theme);
    void setToggleable(bool toggleable);

signals:
    void contentsVisibleToggled(bool visible);
    void sectionActivated(const QString &sectName);
public slots:
    void actionTriggered(const QString &id);
    void togglePanelVisible(bool visible);
private:
    QWidget *getWidgetByName(const QString &name) const;

    QHBoxLayout *mainLayout;
    QStackedLayout *stackedLayout;
    SideBar *sideBar;

    QList<QAction *> actions;
    QList<QWidget*> hiddenWidgets;
    QSignalMapper *signalMapper;

    Theme m_theme;
};

#endif // SIDE_PANEL_H
