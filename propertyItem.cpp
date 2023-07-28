
#include "propertyItem.h"
#include "choiceModel.h"

PropertyItem::PropertyItem(const QVector<QVariant> &data, PropertyItem *parent) : m_itemData(data), m_parentItem(parent) {}
PropertyItem::~PropertyItem()
{
   qDeleteAll(m_childItems);
}

PropertyItem *PropertyItem::child(int number)
{
   if (number < 0 || number >= m_childItems.size())
      return nullptr;
   return m_childItems.at(number);
}

int PropertyItem::childCount() const
{
   return m_childItems.count();
}

int PropertyItem::childNumber() const
{
   if (m_parentItem)
      return m_parentItem->m_childItems.indexOf(const_cast<PropertyItem *>(this));
   return 0;
}

int PropertyItem::columnCount() const
{
   return m_itemData.count();
}

QVariant PropertyItem::data(int column) const
{
   if (column < 0 || column >= m_itemData.size())
      return QVariant();
   return m_itemData.at(column);
}

bool PropertyItem::insertChildren(int position, int count, int columns)
{
   if (position < 0 || position > m_childItems.size())
      return false;

   for (int row = 0; row < count; ++row)
   {
      QVector<QVariant> data(columns);
      PropertyItem *item = new PropertyItem(data, this);
      m_childItems.insert(position, item);
   }

   return true;
}

bool PropertyItem::insertColumns(int position, int columns)
{
   if (position < 0 || position > m_itemData.size())
      return false;

   for (int column = 0; column < columns; ++column)
      m_itemData.insert(position, QVariant());

   for (PropertyItem *child : qAsConst(m_childItems))
      child->insertColumns(position, columns);

   return true;
}
PropertyItem *PropertyItem::parent()
{
   return m_parentItem;
}

bool PropertyItem::removeChildren(int position, int count)
{
   if (position < 0 || position + count > m_childItems.size())
      return false;

   for (int row = 0; row < count; ++row)
      delete m_childItems.takeAt(position);

   return true;
}

bool PropertyItem::removeColumns(int position, int columns)
{
   if (position < 0 || position + columns > m_itemData.size())
      return false;

   for (int column = 0; column < columns; ++column)
      m_itemData.remove(position);

   for (PropertyItem *child : qAsConst(m_childItems))
      child->removeColumns(position, columns);

   return true;
}

bool PropertyItem::setData(int column, const QVariant &value)
{
   if (column < 0 || column >= m_itemData.size())
      return false;

   if (m_itemData[column].userType() == qMetaTypeId<ChoiceModel>())
   {
      ChoiceModel choice = m_itemData[column].value<ChoiceModel>();
      choice.setSelection(value.toInt());
      QVariant var;
      var.setValue<ChoiceModel>(choice);
      m_itemData[column] = var;
   }
   else
   {
      m_itemData[column] = value;
   }
   return true;
}


bool PropertyItem::appendChildren(const QString &inPropertyName, const QVariant &value, QObject *inObject)
{
   bool status = true;
   insertChildren(childCount(), 1, 2);
   status &= child(childCount() - 1)->setData(0, inPropertyName);
   status &= child(childCount() - 1)->setData(1, value);
   child(childCount() - 1)->setObject(inObject);
   return status;
}

PropertyItem *PropertyItem::addNode(const QString &inNodeName)
{
   insertChildren(childCount(), 1, columnCount());
   child(childCount() - 1)->setData(0, inNodeName);
   return (child(childCount() - 1));
}

QObject *PropertyItem::getObject() const
{
   return mObject;
}

void PropertyItem::setObject(QObject *inObject)
{
   mObject = inObject;
}

const QString &PropertyItem::getName() const
{
   return mName;
}

void PropertyItem::setName(const QString &inName)
{
   mName = inName;
}
