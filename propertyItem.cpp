
#include "propertyItem.h"

//! [0]
PropertyItem::PropertyItem(const QVector<QVariant> &data, PropertyItem *parent) : m_itemData(data), m_parentItem(parent) {}
//! [0]

//! [1]
PropertyItem::~PropertyItem()
{
   qDeleteAll(m_childItems);
}
//! [1]

//! [2]
void PropertyItem::appendChild(PropertyItem *item)
{
   m_childItems.append(item);
}
//! [2]

//! [3]
PropertyItem *PropertyItem::child(int row)
{
   if (row < 0 || row >= m_childItems.size())
      return nullptr;
   return m_childItems.at(row);
}
//! [3]

//! [4]
int PropertyItem::childCount() const
{
   return m_childItems.count();
}
//! [4]

//! [5]
int PropertyItem::columnCount() const
{
   return m_itemData.count();
}
//! [5]

//! [6]
QVariant PropertyItem::data(int column) const
{
   if (column < 0 || column >= m_itemData.size())
      return QVariant();
   return m_itemData.at(column);
}
//! [6]

//! [7]
PropertyItem *PropertyItem::parentItem()
{
   return m_parentItem;
}
//! [7]

//! [8]
int PropertyItem::row() const
{
   if (m_parentItem)
      return m_parentItem->m_childItems.indexOf(const_cast<PropertyItem *>(this));

   return 0;
}
//! [8]
