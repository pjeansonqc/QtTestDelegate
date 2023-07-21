#ifndef PROPERTYITEM_H
#define PROPERTYITEM_H

#include <QVariant>
#include <QVector>

class PropertyItem
{
 public:
   explicit PropertyItem(const QVector<QVariant> &data, PropertyItem *parent = nullptr);
   ~PropertyItem();

   //   void appendChild(PropertyItem *child);

   PropertyItem *child(int number);
   int childCount() const;
   int columnCount() const;
   QVariant data(int column) const;
   int row() const;
   bool insertChildren(int position, int count, int columns);
   bool insertColumns(int position, int columns);
   PropertyItem *parent();
   bool removeChildren(int position, int count);
   bool removeColumns(int position, int columns);
   int childNumber() const;
   bool setData(int column, const QVariant &value);

 private:
   QVector<PropertyItem *> m_childItems;
   QVector<QVariant> m_itemData;
   PropertyItem *m_parentItem;
};
//! [0]

#endif // PROPERTYITEM_H
