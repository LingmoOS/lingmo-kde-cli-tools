/* This file is part of the KDE project
   Copyright (C) 2003 Waldo Bastian <bastian@kde.org>
   Copyright (C) 2003 David Faure <faure@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License version 2 or at your option version 3 as published by
   the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef TYPESLISTITEM_H
#define TYPESLISTITEM_H

#include "mimetypedata.h"
#include <QTreeWidgetItem>

#include <QMimeType>
#include <QMimeDatabase>

// TODO different subclasses for mimetypes and groups?
class TypesListItem : public QTreeWidgetItem
{
public:
    /**
     * Create a filetype group
     */
    TypesListItem(QTreeWidget *parent, const QString &major);

    /**
     * Create a filetype item inside a group, for an existing mimetype
     */
    TypesListItem(TypesListItem *parent, QMimeType mimetype);

    /**
     * Create a filetype item inside a group, for a new mimetype
     */
    TypesListItem(TypesListItem *parent, const QString &newMimetype);

    ~TypesListItem() override;

    void setIcon(const QString &icon);

    QString name() const
    {
        return m_mimetypeData.name();
    }

    const MimeTypeData &mimeTypeData() const
    {
        return m_mimetypeData;
    }

    MimeTypeData &mimeTypeData()
    {
        return m_mimetypeData;
    }

    void loadIcon(bool forceReload = false);

private:
    MimeTypeData m_mimetypeData;
};

#endif
