//  This file is part of the KDE libraries
//
//  Copyright (C) 2003,2007 Oswald Buddenhagen <ossi@kde.org>
//
//  Rewritten for QT4 by e_k <e_k at users.sourceforge.net>, Copyright (C)2008
//  Forked for Baulk - Copyright (C) 2008-2009 - Jacob Alexander <haata at users.sf.net>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  any later version, including version 3 of the License.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef kpty_p_h
#define kpty_p_h

#include "kpty.h"

#include <QtCore/QByteArray>

struct KPtyPrivate {
    Q_DECLARE_PUBLIC(KPty)

    KPtyPrivate();
    bool chownpty(bool grant);

    int masterFd;
    int slaveFd;

    QByteArray ttyName;

    KPty *q_ptr;
};

#endif

