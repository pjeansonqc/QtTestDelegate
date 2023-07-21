#pragma once

#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QStyledItemDelegate>

class PropertyItemDelegate : public QStyledItemDelegate
{
   Q_OBJECT

 public:
   explicit PropertyItemDelegate(QObject *parent = nullptr);

   QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

   void setEditorData(QWidget *editor, const QModelIndex &index) const override;
   void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

   void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

inline PropertyItemDelegate::PropertyItemDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

inline QWidget *PropertyItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   Q_UNUSED(option);

   QVariant data = index.data(Qt::DisplayRole);

   if (data.type() == QVariant::Int)
   {
      // If the data is an integer, use a QLineEdit for editing
      QLineEdit *lineEdit = new QLineEdit(parent);
      lineEdit->setValidator(new QIntValidator(lineEdit));
      return lineEdit;
   }
   else if (data.type() == QVariant::Double)
   {
      // If the data is a double, use a QDoubleSpinBox for editing
      QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox(parent);
      doubleSpinBox->setDecimals(2); // Set the number of decimal places
      return doubleSpinBox;
   }
   else
   {
      // For other data types, use the default editor (QLineEdit)
      return QStyledItemDelegate::createEditor(parent, option, index);
   }
}

inline void PropertyItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
   QVariant data = index.data(Qt::DisplayRole);

   if (data.type() == QVariant::Int)
   {
      // If the data is an integer, set the value in the QLineEdit
      QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
      if (lineEdit)
         lineEdit->setText(QString::number(data.toInt()));
   }
   else if (data.type() == QVariant::Double)
   {
      // If the data is a double, set the value in the QDoubleSpinBox
      QDoubleSpinBox *doubleSpinBox = qobject_cast<QDoubleSpinBox *>(editor);
      if (doubleSpinBox)
         doubleSpinBox->setValue(data.toDouble());
   }
   else
   {
      // For other data types, use the default editor (QLineEdit)
      QStyledItemDelegate::setEditorData(editor, index);
   }
}

inline void PropertyItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
   QVariant data = index.data(Qt::DisplayRole);

   if (data.type() == QVariant::Int)
   {
      // If the data is an integer, get the value from the QLineEdit
      QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
      if (lineEdit)
         model->setData(index, lineEdit->text().toInt(), Qt::EditRole);
   }
   else if (data.type() == QVariant::Double)
   {
      // If the data is a double, get the value from the QDoubleSpinBox
      QDoubleSpinBox *doubleSpinBox = qobject_cast<QDoubleSpinBox *>(editor);
      if (doubleSpinBox)
         model->setData(index, doubleSpinBox->value(), Qt::EditRole);
   }
   else
   {
      // For other data types, use the default editor (QLineEdit)
      QStyledItemDelegate::setModelData(editor, model, index);
   }
}

inline void PropertyItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   Q_UNUSED(index);
   editor->setGeometry(option.rect);
}
