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

#include "splitter_handle.h"

#include <QPainter>
#include <QPaintEvent>

SplitterHandle::SplitterHandle(Qt::Orientation orientation, QSplitter *parent) :
    QSplitterHandle(orientation, parent),
    m_active(true)
{
    setMask(QRegion(contentsRect()));
    setAttribute(Qt::WA_MouseNoMask, true);
}

void SplitterHandle::setActive(bool active)
{
    setCursor((m_active = active) ? Qt::SplitHCursor : Qt::ArrowCursor);
}

void SplitterHandle::resizeEvent(QResizeEvent *event)
{
    if (orientation() == Qt::Horizontal)
        setContentsMargins(2, 0, 2, 0);
    else
        setContentsMargins(0, 2, 0, 2);
    setMask(QRegion(contentsRect()));
    QSplitterHandle::resizeEvent(event);
}

void SplitterHandle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::black);
}

void SplitterHandle::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_active) {
        event->ignore();
        return;
    }
    QSplitterHandle::mouseMoveEvent(event);
}

void SplitterHandle::mousePressEvent(QMouseEvent *event)
{
    if(!m_active) {
        event->ignore();
        return;
    }
    QSplitterHandle::mousePressEvent(event);
}
