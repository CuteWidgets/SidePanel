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
