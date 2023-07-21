#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QVector>

class PropertyItem
{
 public:
   explicit PropertyItem(const QVector<QVariant> &data, PropertyItem *parentItem = nullptr);
   ~PropertyItem();

   void appendChild(PropertyItem *child);

   PropertyItem *child(int row);
   int childCount() const;
   int columnCount() const;
   QVariant data(int column) const;
   int row() const;
   PropertyItem *parentItem();

 private:
   QVector<PropertyItem *> m_childItems;
   QVector<QVariant> m_itemData;
   PropertyItem *m_parentItem;
};


#endif // TREEITEM_H
