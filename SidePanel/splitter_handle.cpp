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
