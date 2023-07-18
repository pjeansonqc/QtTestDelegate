#pragma once

#include <QAbstractItemModel>
#include <QString>

class PropertyModel : public QAbstractItemModel
{
   Q_OBJECT

 public:
   explicit PropertyModel(QObject *parent = nullptr);
   ~PropertyModel() override;

   QVariant data(const QModelIndex &index, int role) const override;
   bool setData(const QModelIndex &index, const QVariant &value, int role) override;
   Qt::ItemFlags flags(const QModelIndex &index) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
   QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
   QModelIndex parent(const QModelIndex &index) const override;
   int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   int columnCount(const QModelIndex &parent = QModelIndex()) const override;

 private:
   struct Property
   {
      QString name;
      QVariant value;
   };

   QList<Property> properties;
};