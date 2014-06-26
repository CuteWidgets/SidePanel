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
