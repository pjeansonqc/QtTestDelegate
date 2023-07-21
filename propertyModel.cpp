#include "propertyModel.h"
#include "propertyItem.h"

#include <QDoubleSpinBox>
#include <QStringList>

PropertyModel::PropertyModel(const QStringList &headers, const QString &data, QObject *parent) : QAbstractItemModel(parent)
{
   QVector<QVariant> rootData;
   for (const QString &header : headers)
      rootData << header;

   mRootItem = new PropertyItem(rootData);
}

PropertyModel::~PropertyModel()
{
   delete mRootItem;
}

int PropertyModel::columnCount(const QModelIndex &parent) const
{
   Q_UNUSED(parent);
   return mRootItem->columnCount();
}

QVariant PropertyModel::data(const QModelIndex &index, int role) const
{
   if (!index.isValid())
      return QVariant();

   if (role != Qt::DisplayRole && role != Qt::EditRole)
      return QVariant();

   PropertyItem *item = getItem(index);

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

   return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

PropertyItem *PropertyModel::getItem(const QModelIndex &index) const
{
   if (index.isValid())
   {
      PropertyItem *item = static_cast<PropertyItem *>(index.internalPointer());
      if (item)
         return item;
   }
   return mRootItem;
}

QVariant PropertyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
      return mRootItem->data(section);

   return QVariant();
}

QModelIndex PropertyModel::index(int row, int column, const QModelIndex &parent) const
{
   if (parent.isValid() && parent.column() != 0)
      return QModelIndex();

   PropertyItem *parentItem = getItem(parent);
   if (!parentItem)
      return QModelIndex();

   PropertyItem *childItem = parentItem->child(row);
   if (childItem)
      return createIndex(row, column, childItem);
   return QModelIndex();
}

bool PropertyModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
   beginInsertColumns(parent, position, position + columns - 1);
   const bool success = mRootItem->insertColumns(position, columns);
   endInsertColumns();

   return success;
}

bool PropertyModel::insertRows(int position, int rows, const QModelIndex &parent)
{
   PropertyItem *parentItem = getItem(parent);
   if (!parentItem)
      return false;

   beginInsertRows(parent, position, position + rows - 1);
   const bool success = parentItem->insertChildren(position, rows, mRootItem->columnCount());
   endInsertRows();

   return success;
}

QModelIndex PropertyModel::parent(const QModelIndex &index) const
{
   if (!index.isValid())
      return QModelIndex();

   PropertyItem *childItem = getItem(index);
   PropertyItem *parentItem = childItem ? childItem->parent() : nullptr;

   if (parentItem == mRootItem || !parentItem)
      return QModelIndex();

   return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool PropertyModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
   beginRemoveColumns(parent, position, position + columns - 1);
   const bool success = mRootItem->removeColumns(position, columns);
   endRemoveColumns();

   if (mRootItem->columnCount() == 0)
      removeRows(0, rowCount());

   return success;
}

bool PropertyModel::removeRows(int position, int rows, const QModelIndex &parent)
{
   PropertyItem *parentItem = getItem(parent);
   if (!parentItem)
      return false;

   beginRemoveRows(parent, position, position + rows - 1);
   const bool success = parentItem->removeChildren(position, rows);
   endRemoveRows();

   return success;
}

int PropertyModel::rowCount(const QModelIndex &parent) const
{
   const PropertyItem *parentItem = getItem(parent);

   return parentItem ? parentItem->childCount() : 0;
}

bool PropertyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
   if (role != Qt::EditRole)
      return false;

   PropertyItem *item = getItem(index);
   bool result = item->setData(index.column(), value);

   if (result)
      emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

   return result;
}

bool PropertyModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
   if (role != Qt::EditRole || orientation != Qt::Horizontal)
      return false;

   const bool result = mRootItem->setData(section, value);

   if (result)
      emit headerDataChanged(orientation, section, section);

   return result;
}

void PropertyModel::setupModelData(const QStringList &lines, PropertyItem *parent)
{
   QVector<PropertyItem *> parents;
   QVector<int> indentations;
   parents << parent;
   indentations << 0;

   int number = 0;

   while (number < lines.count())
   {
      int position = 0;
      while (position < lines[number].length())
      {
         if (lines[number].at(position) != ' ')
            break;
         ++position;
      }

      const QString lineData = lines[number].mid(position).trimmed();

      if (!lineData.isEmpty())
      {
         // Read the column data from the rest of the line.
         const QStringList columnStrings = lineData.split(QLatin1Char('\t'), Qt::SkipEmptyParts);
         QVector<QVariant> columnData;
         columnData.reserve(columnStrings.size());
         for (const QString &columnString : columnStrings)
            columnData << columnString;

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
         PropertyItem *parent = parents.last();
         parent->insertChildren(parent->childCount(), 1, mRootItem->columnCount());
         for (int column = 0; column < columnData.size(); ++column)
            parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
      }
      ++number;
   }
}
