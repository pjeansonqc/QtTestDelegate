#include "propertyModel.h"
#include "propertyItem.h"

#include <QDoubleSpinBox>
#include <QStringList>

PropertyModel::PropertyModel(QObject *parent) : QAbstractItemModel(parent)
{
   mRootItem = new PropertyItem({"Title", "Summary"});
   //   setupModelData(parent.split('\n'), rootItem);
}

PropertyModel::~PropertyModel()
{
   delete mRootItem;
}

QVariant PropertyModel::data(const QModelIndex &index, int role) const
{
   if (!index.isValid())
      return QVariant();

   if (role != Qt::DisplayRole)
      return QVariant();

   PropertyItem *item = static_cast<PropertyItem *>(index.internalPointer());

   return item->data(index.column());
}

// bool PropertyModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (!index.isValid())
//       return false;

//   if (role == Qt::EditRole && index.column() == 1)
//   {
//      if (index.row() < properties.size())
//      {
//         properties[index.row()].value = value;
//         emit dataChanged(index, index);
//         return true;
//      }
//   }

//   return false;
//}

Qt::ItemFlags PropertyModel::flags(const QModelIndex &index) const
{
   if (!index.isValid())
      return Qt::NoItemFlags;

   Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

   if (index.column() == 1)
      flags |= Qt::ItemIsEditable;

   return flags;
}

QVariant PropertyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
      return mRootItem->data(section);

   return QVariant();
}

QModelIndex PropertyModel::index(int row, int column, const QModelIndex &parent) const
{
   if (!hasIndex(row, column, parent))
      return QModelIndex();

   PropertyItem *parentItem;

   if (!parent.isValid())
      parentItem = mRootItem;
   else
      parentItem = static_cast<PropertyItem *>(parent.internalPointer());

   PropertyItem *childItem = parentItem->child(row);
   if (childItem)
      return createIndex(row, column, childItem);
   return QModelIndex();
}

QModelIndex PropertyModel::parent(const QModelIndex &index) const
{
   if (!index.isValid())
      return QModelIndex();

   PropertyItem *childItem = static_cast<PropertyItem *>(index.internalPointer());
   PropertyItem *parentItem = childItem->parentItem();

   if (parentItem == mRootItem)
      return QModelIndex();

   return createIndex(parentItem->row(), 0, parentItem);
}

int PropertyModel::rowCount(const QModelIndex &parent) const
{
   PropertyItem *parentItem;
   if (parent.column() > 0)
      return 0;

   if (!parent.isValid())
      parentItem = mRootItem;
   else
      parentItem = static_cast<PropertyItem *>(parent.internalPointer());

   return parentItem->childCount();
}

int PropertyModel::columnCount(const QModelIndex &parent) const
{
   if (parent.isValid())
      return static_cast<PropertyItem *>(parent.internalPointer())->columnCount();
   return mRootItem->columnCount();
}

bool stringToInt(QString inString, int &outValue)
{
   bool isOk = false;
   outValue = inString.toInt(&isOk);
   return isOk;
}

bool stringToDouble(QString inString, double &outValue)
{
   bool isOk = false;
   outValue = inString.toDouble(&isOk);
   return isOk;
}

void PropertyModel::setupModelData(const QStringList &lines)
{
   QVector<PropertyItem *> parents;
   QVector<int> indentations;
   parents << mRootItem;
   indentations << 0;

   int number = 0;

   while (number < lines.count())
   {
      int position = 0;
      while (position < lines[number].length())
      {
         if (lines[number].at(position) != ' ')
            break;
         position++;
      }

      const QString lineData = lines[number].mid(position).trimmed();

      if (!lineData.isEmpty())
      {
         // Read the column data from the rest of the line.
         const QStringList columnStrings = lineData.split(QLatin1Char('\t'), Qt::SkipEmptyParts);
         QVector<QVariant> columnData;
         columnData.reserve(columnStrings.count());
         for (const QString &columnString : columnStrings)
         {
            int intValue = 0;
            double doubleValue = 0.0;
            if (stringToInt(columnString, intValue))
            {
               columnData << intValue;
            }
            else if (stringToDouble(columnString, doubleValue))
            {
               columnData << doubleValue;
            }
            else
            {
               columnData << columnString;
            }

            if (position > indentations.last())
            {
               // The last child of the current parent is now the new parent
               // unless the current parent has no children.

               if (parents.last()->childCount() > 0)
               {
                  parents << parents.last()->child(parents.last()->childCount() - 1);
                  indentations << position;
               }
            }
            else
            {
               while (position < indentations.last() && parents.count() > 0)
               {
                  parents.pop_back();
                  indentations.pop_back();
               }
            }

            // Append a new item to the current parent's list of children.
            parents.last()->appendChild(new PropertyItem(columnData, parents.last()));
         }
         ++number;
      }
   }
}
