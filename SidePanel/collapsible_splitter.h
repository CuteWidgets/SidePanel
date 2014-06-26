#ifndef COLLAPSIBLE_SPLITTER_H
#define COLLAPSIBLE_SPLITTER_H

#include <QSplitter>
class QSplitterHandle;

class CollapsibleSplitter : public QSplitter
{
    Q_OBJECT
public:
    explicit CollapsibleSplitter(QWidget *parent = 0);
    void collapse();
    bool restoreState();

protected:
    QSplitterHandle *createHandle();
signals:

public slots:
    void toggleCollapse(bool firstVisible);
private:
    QByteArray stateSave;
    QSplitterHandle *m_handle;
};

#endif // COLLAPSIBLE_SPLITTER_H
