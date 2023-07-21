#pragma once
#include <QtDebug>
//  qDebug() << "index.column()" << index.column();
// qDebug() << "index.data()" << index.data();
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QPainter>
#include <QStyledItemDelegate>

class PropertyDelegate : public QStyledItemDelegate
{
 public:
   void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
   QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
   void setEditorData(QWidget *editor, const QModelIndex &index) const override;
   void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
   void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

void PropertyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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
         QDoubleSpinBox spinBox;
         spinBox.setDecimals(2);
         spinBox.setSingleStep(0.1);
         spinBox.setFrame(false);
         spinBox.setValue(value.toDouble());
         text = spinBox.textFromValue(value.toDouble());
      }
      break;
      case QMetaType::Int:
      {
         QSpinBox spinBox;
         spinBox.setFrame(false);
         spinBox.setValue(value.toInt());
         text = spinBox.text();
      }
      break;
      case QMetaType::Bool:
      {
         text = value.toBool() ? "True" : "False";
      }
      break;
      default:
      {
         text = value.toString();
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
      default:
         qWarning() << "PropertyDelegate::createEditor Unknown type";
         break;
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
