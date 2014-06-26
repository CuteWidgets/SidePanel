#ifndef SPLITTER_HANDLE_H
#define SPLITTER_HANDLE_H

#include <QSplitterHandle>

class SplitterHandle : public QSplitterHandle
{
    Q_OBJECT
public:
    explicit SplitterHandle(Qt::Orientation orientation, QSplitter *parent = 0);
public slots:
    void setActive(bool active);
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    bool m_active;
};

#endif // SPLITTER_HANDLE_H
