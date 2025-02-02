/*  This file is part of the KDE project
    Copyright (C) 2000 - 2008 David Faure <faure@kde.org>
    Copyright (C) 2008 Urs Wolfer <uwolfer @ kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License or ( at
    your option ) version 3 or, at the discretion of KDE e.V. ( which shall
    act as a proxy as in section 14 of the GPLv3 ), any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; see the file COPYING.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef FILETYPESVIEW_H
#define FILETYPESVIEW_H

#include <QList>
#include <QMap>
#include <QLabel>
#include <QStackedWidget>

#include <KSharedConfig>
#include <KCModule>

#include "typeslistitem.h"

class QLabel;
class QTreeWidget;
class QTreeWidgetItem;
class QPushButton;
class KLineEdit;
class FileTypeDetails;
class FileGroupDetails;
class QStackedWidget;

class FileTypesView : public KCModule
{
    Q_OBJECT
public:
    FileTypesView(QWidget *parent, const QVariantList &args);
    ~FileTypesView() override;

    void load() override;
    void save() override;
    void defaults() override;

protected Q_SLOTS:
    void addType();
    void removeType();
    void updateDisplay(QTreeWidgetItem *);
    void slotDoubleClicked(QTreeWidgetItem *);
    void slotFilter(const QString &patternFilter);
    void setDirty(bool state);

    void slotDatabaseChanged(const QStringList &changedResources);
    void slotEmbedMajor(const QString &major, bool &embed);

private:
    void readFileTypes();
    void updateRemoveButton(TypesListItem *item);

private:
    QTreeWidget *typesLV;
    QPushButton *m_removeTypeB;

    QStackedWidget *m_widgetStack;
    FileTypeDetails *m_details;
    FileGroupDetails *m_groupDetails;
    QLabel *m_emptyWidget;

    KLineEdit *patternFilterLE;
    QStringList removedList;
    bool m_dirty;
    bool m_removeButtonSaysRevert;
    QMap<QString, TypesListItem *> m_majorMap; // groups
    QList<TypesListItem *> m_itemList;

    KSharedConfig::Ptr m_fileTypesConfig;
};

// helper class for loading the icon on request instead of preloading lots of probably
// unused icons which takes quite a lot of time
class TypesListTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TypesListTreeWidget(QWidget *parent)
        : QTreeWidget(parent)
    {
    }

protected:
    void drawRow(QPainter *painter, const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override
    {
        static_cast<TypesListItem *>(itemFromIndex(index))->loadIcon();

        QTreeWidget::drawRow(painter, option, index);
    }
};

#endif
