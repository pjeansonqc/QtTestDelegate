#include "propertyModel.h"
#include <QDoubleSpinBox>

PropertyModel::PropertyModel(QObject *parent) : QAbstractItemModel(parent)
{
   // Add properties to the list
   Property property;
   property.name = "Period";
   property.value = QVariant(0.0);
   properties.append(property);

   property.name = "Count";
   property.value = QVariant(int(0));
   properties.append(property);

   property.name = "Enabled";
   property.value = QVariant(false);
   properties.append(property);

   property.name = "Name";
   property.value = QVariant("Claudia");
   properties.append(property);
}

PropertyModel::~PropertyModel() {}

QVariant PropertyModel::data(const QModelIndex &index, int role) const
{
   if (!index.isValid())
      return QVariant();

   if (role == Qt::DisplayRole || role == Qt::EditRole)
   {
      if (index.column() == 0)
      {
         if (index.row() < properties.size())
            return properties[index.row()].name;
      }
      else if (index.column() == 1)
      {
         if (index.row() < properties.size())
         {
            if (properties[index.row()].name == "mPeriod")
            {
               // Return the value of mPeriod
               return properties[index.row()].value;
            }
            else
            {
               // Return other property values as regular QVariant
               return QVariant::fromValue(properties[index.row()].value);
            }
         }
      }
   }

   return QVariant();
}

bool PropertyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
   if (!index.isValid())
      return false;

   if (role == Qt::EditRole && index.column() == 1)
   {
      if (index.row() < properties.size())
      {
         properties[index.row()].value = value;
         emit dataChanged(index, index);
         return true;
      }
   }

   return false;
}

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
   if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
   {
      if (section == 0)
         return "Property";
      else if (section == 1)
         return "Value";
   }

   return QVariant();
}

QModelIndex PropertyModel::index(int row, int column, const QModelIndex &parent) const
{
   if (!hasIndex(row, column, parent))
      return QModelIndex();

   if (!parent.isValid())
   {
      if (row < properties.size())
         return createIndex(row, column);
   }

   return QModelIndex();
}

QModelIndex PropertyModel::parent(const QModelIndex &index) const
{
   Q_UNUSED(index)
   return QModelIndex();
}

int PropertyModel::rowCount(const QModelIndex &parent) const
{
   if (parent.isValid())
      return 0;

   return properties.size();
}

int PropertyModel::columnCount(const QModelIndex &parent) const
{
   Q_UNUSED(parent)
   return 2;
}
