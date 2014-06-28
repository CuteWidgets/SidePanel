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
