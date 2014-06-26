#include "collapsible_splitter.h"
#include "splitter_handle.h"

CollapsibleSplitter::CollapsibleSplitter(QWidget *parent) :
    QSplitter(parent)
{
    setHandleWidth(2);
    setChildrenCollapsible(false);
}

void CollapsibleSplitter::collapse()
{
    stateSave = saveState();
    int totalWidth = 0;
    for (int i = 0; i < sizes().count(); ++i) {
        totalWidth += sizes().at(i);
    }
    QList<int> szs;
//    szs.append(adjSize);
//    szs.append(totalWidth - adjSize);
    szs.append(0);
    szs.append(10000);//rarito rarito
//    qDebug() << "szs" << szs;
//    qDebug() << "totalSize" << rect().size();
    setSizes(szs);
}

bool CollapsibleSplitter::restoreState()
{
    return QSplitter::restoreState(stateSave);
}

QSplitterHandle *CollapsibleSplitter::createHandle()
{
    m_handle = new SplitterHandle(orientation(), this);
    return m_handle;
}

void CollapsibleSplitter::toggleCollapse(bool firstVisible)
{
    if (!firstVisible) {
        collapse();
    }
    else {
        restoreState();
    }
    if(SplitterHandle *hndl = qobject_cast<SplitterHandle*>(m_handle)) {
        hndl->setActive(firstVisible);
    }
}
