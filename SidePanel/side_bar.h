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

    const int fxdWidth = 64;
    const int iconMargins = 4;
    const int itemWidth = fxdWidth;
    const int itemHeight = itemWidth;
    const int offset = 20;
    const int spacing = 0;
    const int margin = 2;
    const int vTogglerWidth = 25;
    const int vTogglerHeight = vTogglerWidth;

    bool m_useEnvPalette;

    bool m_panelVisible;
    bool m_vTogglerHovered;
    bool m_togglerVisible;

    QImage bgImage;
public:
    QSize sizeHint() const;
};

#endif // SIDE_BAR_H
