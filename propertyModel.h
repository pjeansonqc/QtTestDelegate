#pragma once

#include <QAbstractItemModel>
#include <QString>

class PropertyItem;

class PropertyModel : public QAbstractItemModel
{
   Q_OBJECT

 public:
   explicit PropertyModel(QObject *parent = nullptr);
   ~PropertyModel() override;

   QVariant data(const QModelIndex &index, int role) const override;
   Qt::ItemFlags flags(const QModelIndex &index) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
   QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
   QModelIndex parent(const QModelIndex &index) const override;
   int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   int columnCount(const QModelIndex &parent = QModelIndex()) const override;

   void setupModelData(const QStringList &lines);

   PropertyItem *mRootItem;
};
