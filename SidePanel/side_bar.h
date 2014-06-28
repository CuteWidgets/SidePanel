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

#ifndef SIDE_BAR_H
#define SIDE_BAR_H

#include <QWidget>

class SideBar : public QWidget
{
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = 0);
    void triggerAction(int index);
    void triggerAction(const QString &name);
    int currentIndex();
    const QString currentActionName();
    void setActionEnabled(const QString &name, bool actEnabled = true);
    void useDefaultPalette(bool use);
    void setBgImage(const QImage &img);
    void setTogglerActive(bool active);
    void setTogglerVisible(bool tVisible);

signals:
    void panelVisibleChanged(bool visible);
public slots:

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void leaveEvent(QEvent *event);

private:
    int indexAt(const QPoint &position);
    QRect getVTogglerRect();
    bool isActionEnabled(int index);

    int m_currentActionIndex;
    int m_currentHoveredIndex;

    int fxdWidth;
    int iconMargins;
    int itemWidth;
    int itemHeight;
    int offset;
    int spacing;
    int margin;
    int vTogglerWidth;
    int vTogglerHeight;

    bool m_useEnvPalette;

    bool m_panelVisible;
    bool m_vTogglerHovered;
    bool m_togglerVisible;

    QImage bgImage;
public:
    QSize sizeHint() const;
};

#endif // SIDE_BAR_H
