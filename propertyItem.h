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
   bool appendChildren(const QString &inPropertyName, const QVariant &value, QObject *inObject);
   PropertyItem *addNode(const QString &inNodeName);

   QObject *getObject() const;
   void setObject(QObject *inObject);

   const QString &getName() const;
   void setName(const QString &inName);

 private:
   QVector<PropertyItem *> m_childItems;
   QVector<QVariant> m_itemData;
   QString mName = "";
   QObject *mObject = nullptr;
   PropertyItem *m_parentItem;
};

#endif // PROPERTYITEM_H
