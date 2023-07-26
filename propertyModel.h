#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QString>
#include <QVariant>

class PropertyItem;

class PropertyModel : public QAbstractItemModel
{
   Q_OBJECT

 public:
   PropertyModel(const QStringList &headers, const QString &data, QObject *parent = nullptr);
   ~PropertyModel();

   void initModel(const QStringList &headers);
   QVariant data(const QModelIndex &index, int role) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

   QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
   QModelIndex parent(const QModelIndex &index) const override;
   int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   int columnCount(const QModelIndex &parent = QModelIndex()) const override;

   Qt::ItemFlags flags(const QModelIndex &index) const override;
   bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
   bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

   bool insertColumns(int position, int columns, const QModelIndex &parent = QModelIndex()) override;
   bool removeColumns(int position, int columns, const QModelIndex &parent = QModelIndex()) override;
   bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
   bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;

 private:
   void setupModelData(const QStringList &lines, PropertyItem *parent);
   PropertyItem *getItem(const QModelIndex &index) const;

 public:
   PropertyItem *mRootItem = nullptr;
};
