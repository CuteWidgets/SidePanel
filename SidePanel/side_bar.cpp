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

#include "side_bar.h"
#include <QPainter>
#include <QAction>
#include <QMouseEvent>
#include <QDebug>

SideBar::SideBar(QWidget *parent) :
    QWidget(parent),
    m_currentActionIndex(-1),
    m_useEnvPalette(false),
    m_currentHoveredIndex(-1),
    m_panelVisible(true),
    m_vTogglerHovered(false),
    m_togglerVisible(true)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setFixedWidth(fxdWidth);
    setMouseTracking(true);
}

void SideBar::mousePressEvent(QMouseEvent *event)
{
    int ind = indexAt(event->pos());
    if( ind != -1) {
        triggerAction(ind);
        update();
        return;
    }
    if (!m_togglerVisible) {
        return;
    }
    QRect togglerRect = getVTogglerRect();
    if (togglerRect.contains(event->pos())) {
//        m_panelVisible = !m_panelVisible;
        emit panelVisibleChanged(m_panelVisible = !m_panelVisible);
//        update();
    }
}

void SideBar::mouseMoveEvent(QMouseEvent *event)
{
    int ind = indexAt(event->pos());
    if( ind != -1) {
        if (isActionEnabled(ind)) {
            m_currentHoveredIndex = ind;
            update();
            return;
        }
    }
    m_currentHoveredIndex = -1;
    if (!m_togglerVisible) {
        update();
        return;
    }
    QRect togglerRect = getVTogglerRect();
    m_vTogglerHovered = togglerRect.contains(event->pos());
    update();
}

//void SideBar::mouseMoveEvent(QMouseEvent *)
//{

//}

void SideBar::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::black);

    QFont fontText(p.font());
    fontText.setPixelSize(10);
    fontText.setFamily("Helvetica Neue");
    fontText.setBold(true);
    p.setFont(fontText);

    QFontMetrics fm(fontText);

    QBrush fBrush;
    if (m_useEnvPalette) {
        fBrush = palette().window();
    }
    else {
        if (bgImage.isNull()) {
            bgImage = QImage(124, 178, QImage::Format_ARGB32);
            bgImage.fill(palette().window().color());
        }
        fBrush.setTextureImage(bgImage);
    }
    p.fillRect(event->rect(), fBrush);
    p.setPen(QColor(20, 20, 20));
    p.drawLine(event->rect().topRight(), event->rect().bottomRight());
    p.drawLine(event->rect().bottomLeft(), event->rect().bottomRight());

    int itemCount = actions().size();

    if(itemCount) {
        p.save();
        p.setOpacity(0.6);
        p.setPen(Qt::black);
        p.drawLine(0, offset - 1, itemWidth, offset - 1);
        p.setPen(Qt::white);
        p.setOpacity(0.2);
        p.drawLine(0, offset + itemCount * itemHeight, itemWidth, offset + itemCount * itemHeight);
        p.restore();
    }

    for (int i = 0; i < actions().size(); ++i) {
        p.save();
        p.translate(0, offset + i * (spacing + itemHeight));
        if(i == m_currentActionIndex) {
            p.setOpacity(0.3);
            p.fillRect(0, 0, itemWidth, itemHeight, Qt::black);
        }
        else {
            p.setPen(Qt::white);
            p.setOpacity(0.2);
            p.drawLine(0, 0, itemWidth, 0);
        }

        if (m_currentHoveredIndex == i) {
            p.setOpacity(0.2);
            p.fillRect(0, 0, itemWidth, itemHeight, Qt::white);
        }

        p.setPen(Qt::black);
        p.setOpacity(0.6);
        p.drawLine(0, itemHeight - 1, itemWidth, itemHeight - 1);

        p.setOpacity(1.0);
        QRect iconRect(0, 0, itemWidth / 2, itemHeight / 2);
        iconRect.moveTo(itemWidth / 4, itemHeight / 8);
        QIcon::Mode iconMode;
        if (!actions().at(i)->isEnabled()) {
            iconMode = QIcon::Disabled;
        }
        else {
            if (i == m_currentActionIndex) {
                iconMode = QIcon::Active;
            }
            else {
                iconMode = QIcon::Normal;
            }
        }
        actions().at(i)->icon().paint(&p, iconRect, Qt::AlignCenter, iconMode);

        QString txt = fm.elidedText(actions().at(i)->data().toString(), Qt::ElideRight, itemWidth - 3);
        QRect textRect = fm.boundingRect(txt).adjusted(0, 0, 1, 0);
        textRect.moveCenter(QPoint(itemWidth / 2, 3 * (itemHeight / 4)));
        p.drawText(textRect, txt);
//        p.fillRect(textRect, QBrush(QColor(255, 0, 0, 100)));
        textRect.moveTop(textRect.top() - 1);
        p.setPen(Qt::white);
        p.drawText(textRect, txt);
        p.restore();
    }

    if (!m_togglerVisible) {
        return;
    }

    QIcon vTogglerIcon;
    vTogglerIcon.addFile(":/panel_visible.png", QSize(vTogglerWidth, vTogglerHeight));
    vTogglerIcon.addFile(":/panel_hidden.png", QSize(vTogglerWidth, vTogglerHeight), QIcon::Disabled);

    QRect togglerRect = getVTogglerRect();
//    if (m_vTogglerHovered) {
//        p.save();
//        p.setOpacity(0.2);
//        p.fillRect(togglerRect, Qt::white);
////        p.translate(togglerRect.topLeft());
////        vTogglerIcon.paint(&p, 0, 0, );
//        p.restore();
//    }

//    if (m_panelVisible) {
//        vTogglerIcon.paint(&p, togglerRect, Qt::AlignCenter, QIcon::Normal);
//    }
//    else {
//        vTogglerIcon.paint(&p, togglerRect, Qt::AlignCenter, QIcon::Disabled);
//    }
    QString imgUri = m_panelVisible ? ":/panel_visible.png" : ":/panel_hidden.png";
    p.drawImage(togglerRect, QImage(imgUri).scaled(vTogglerWidth, vTogglerHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

}

void SideBar::leaveEvent(QEvent *event)
{
    m_currentHoveredIndex = -1;
    update();
}

int SideBar::indexAt(const QPoint &position)
{
    if(position.y() < offset) {
        return -1;
    }
    int yOffset = (position.y() - offset) % (spacing + itemHeight);
    int index = yOffset > itemHeight ? -1 : (position.y() - offset) / (spacing + itemHeight);
    if(index >= actions().count()) {
        return -1;
    }
    return index;
}

QRect SideBar::getVTogglerRect()
{
    int x_ = (width() - vTogglerWidth) / 2;
    int y_ = height() - iconMargins - vTogglerHeight;
    return QRect(x_, y_, vTogglerWidth, vTogglerHeight);
}

bool SideBar::isActionEnabled(int index)
{
    return actions().at(index)->isEnabled();
}

QSize SideBar::sizeHint() const
{
    return QSize(fxdWidth, 0);
}

void SideBar::triggerAction(int index)
{
    if (!isActionEnabled(index)) {
        return;
    }
    actions().at(index)->trigger();
    m_currentActionIndex = index;
}

void SideBar::triggerAction(const QString &name)
{
    for (int i = 0; i < actions().size(); ++i) {
        if (actions().at(i)->data().toString() == name) {
            if (actions().at(i)->isEnabled()) {
                actions().at(i)->trigger();
                m_currentActionIndex = i;
                return;
            }
        }
    }
}

int SideBar::currentIndex()
{
    return m_currentActionIndex;
}

const QString SideBar::currentActionName()
{
//    return actions().at(currentIndex())->data().toString();
    QAction *act = actions().value(currentIndex());
    return act ? act->data().toString() : "";
}

void SideBar::setActionEnabled(const QString &name, bool actEnabled)
{
    foreach (QAction *act, actions()) {
        if (act->data().toString() == name) {
            act->setEnabled(actEnabled);
        }
    }
    update();
}

void SideBar::useDefaultPalette(bool use)
{
    m_useEnvPalette = use;
}

void SideBar::setBgImage(const QImage &img)
{
    bgImage = img;
}

void SideBar::setTogglerActive(bool active)
{
    m_panelVisible = active;
    update();
}

void SideBar::setTogglerVisible(bool tVisible)
{
    m_togglerVisible = tVisible;
}
