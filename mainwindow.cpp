#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "propertyDelegate.h"
#include "propertyItem.h"
#include "propertyModel.h"

typedef QVector<QVariant> VarianList;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   // Create an instance of the custom model
   model = new PropertyModel(this);
   {
      PropertyItem *p2p = new PropertyItem(VarianList({"Point to Point"}), model->mRootItem);
      model->mRootItem->appendChild(p2p);
      PropertyItem *tol = new PropertyItem(VarianList() << "Tolerance" << 0.1, p2p);
      p2p->appendChild(tol);
      PropertyItem *zone = new PropertyItem(VarianList() << "Zones" << 10, p2p);
      p2p->appendChild(zone);
      PropertyItem *model = new PropertyItem(VarianList() << "Model"
                                                          << "testmodel",
                                             p2p);
      p2p->appendChild(model);
   }
   {
      QVector<QVariant> list;
      list << "Point to Plane" << 0.0f;
      PropertyItem *item = new PropertyItem(list, model->mRootItem);
      model->mRootItem->appendChild(item);
   }


   ui->treeView->setModel(model);

   // Set the delegate for column 1
   delegate = new PropertyDelegate;
   ui->treeView->setItemDelegateForColumn(1, delegate);
   //   ui->treeView->setItemDelegateForColumn(0, delegate);
}

MainWindow::~MainWindow()
{
   delete ui;
}
