#pragma once

#include "choiceModel.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPainter>
#include <QStringList>
#include <QStyledItemDelegate>
#include <QtDebug>


class PropertyDelegate : public QStyledItemDelegate
{
 public:
   void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
   QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
   void setEditorData(QWidget *editor, const QModelIndex &index) const override;
   void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
   void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};












