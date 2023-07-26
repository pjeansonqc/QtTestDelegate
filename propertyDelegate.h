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

inline void PropertyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   qDebug() << "row, column: (" << index.row() << "," << index.column() << ")";
   if (index.column() == 1)
   {
      QVariant value = index.data(Qt::DisplayRole);
      QString text;
      QVariant::Type varType = value.type();
      switch (static_cast<QMetaType::Type>(varType))
      {
      case QMetaType::Double:
      case QMetaType::Float:
      {
         text = QString::number(value.toDouble());
      }
      break;
      case QMetaType::Int:
      {
         text = QString::number(value.toInt());
      }
      break;
      case QMetaType::Bool:
      {
         text = value.toBool() ? "True" : "False";
      }
      break;
      default:
      {
         qDebug() << "typeName  :" << value.typeName();
         qDebug() << "     type :" << value.type();
         qDebug() << " userType :" << value.userType();
         int userType = value.userType();
         if (userType == qMetaTypeId<ChoiceModel>())
         {
            ChoiceModel model = value.value<ChoiceModel>();
            text = model.getSelectedChoice();
         }
         else
         {
            text = value.isValid() ? value.toString() : ".";
         }
      }
      }
      QStyleOptionViewItem opt = option;
      initStyleOption(&opt, index);

      QStyledItemDelegate::paint(painter, opt, index);

      QRect textRect = opt.rect;
      painter->eraseRect(textRect);
      painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, text);
      return;
   }
   QStyledItemDelegate::paint(painter, option, index);
}


inline QWidget *PropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   qDebug() << "row, column: (" << index.row() << "," << index.column() << ")";

   if (index.column() == 1)
   {
      QVariant value = index.data(Qt::EditRole);
      QVariant::Type varType = value.type();
      switch (static_cast<QMetaType::Type>(varType))
      {
      case QMetaType::Double:
      case QMetaType::Float:
      {
         QDoubleSpinBox *spinBox = new QDoubleSpinBox(parent);
         spinBox->setDecimals(2);
         spinBox->setSingleStep(0.1);
         spinBox->setFrame(false);
         spinBox->setValue(value.toDouble());
         return spinBox;
      }
      case QMetaType::Int:
      {
         QSpinBox *spinBox = new QSpinBox(parent);
         spinBox->setFrame(false);
         spinBox->setValue(value.toInt());
         return spinBox;
      }
      case QMetaType::Bool:
      {
         QCheckBox *checkBox = new QCheckBox(parent);
         checkBox->setChecked(value.toBool());
         return checkBox;
      }
      case QMetaType::QStringList:
      {
         QComboBox *comboBox = new QComboBox(parent);
         comboBox->addItems(value.toStringList());
         return comboBox;
      }
      default:
         qDebug() << "typeName  :" << value.typeName();
         qDebug() << "     type :" << value.type();
         qDebug() << " userType :" << value.userType();
         int userType = value.userType();
         if (userType == qMetaTypeId<ChoiceModel>())
         {
            QComboBox *comboBox = new QComboBox(parent);
            return comboBox;
         }
      } // switch (static_cast<QMetaType::Type>(varType))
   }    // if (index.column() == 1)
   return QStyledItemDelegate::createEditor(parent, option, index);
}


inline void PropertyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
   qDebug() << "row, column: (" << index.row() << "," << index.column() << ")";
   QVariant value = index.model()->data(index, Qt::EditRole);
   if (QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox *>(editor))
   {
      spinBox->setValue(value.toDouble());
   }
   else if (QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor))
   {
      spinBox->setValue(value.toInt());
   }
   else if (QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor))
   {
      checkBox->setChecked(value.toBool());
   }
   else if (QComboBox *comboBox = qobject_cast<QComboBox *>(editor))
   {
      ChoiceModel model = value.value<ChoiceModel>();
      comboBox->addItems(model.getChoiceList());
      comboBox->setCurrentIndex(model.getSelection());
   }

   else
   {
      QStyledItemDelegate::setEditorData(editor, index);
   }
}

inline void PropertyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
   qDebug() << "row, column: (" << index.row() << "," << index.column() << ")";
   if (QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox *>(editor))
   {
      model->setData(index, spinBox->value(), Qt::EditRole);
   }
   else if (QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor))
   {
      model->setData(index, spinBox->value(), Qt::EditRole);
   }
   else if (QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor))
   {
      model->setData(index, checkBox->isChecked(), Qt::EditRole);
   }
   else if (QComboBox *comboBox = qobject_cast<QComboBox *>(editor))
   {
      model->setData(index, comboBox->currentIndex());
   }
   else
   {
      QStyledItemDelegate::setModelData(editor, model, index);
   }
}

inline void PropertyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   Q_UNUSED(index);
   editor->setGeometry(option.rect);
}
