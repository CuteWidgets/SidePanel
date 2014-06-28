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

#ifndef SIDEPANEL_GLOBAL_H
#define SIDEPANEL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SIDEPANEL_LIBRARY)
#  define SIDEPANELSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SIDEPANELSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SIDEPANEL_GLOBAL_H
