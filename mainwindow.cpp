#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "choiceModel.h"
#include "pointToPointParameters.h"
#include "propertyDelegate.h"
#include "propertyItem.h"
#include "propertyModel.h"
#include "registrationParameters.h"
#include "registrationWidget.h"
#include "workingLimitsParameters.h"

typedef QVector<QVariant> VarianLBist;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), mRegistrationWidgetPtr(new RegistrationWidget(this))
{
   qRegisterMetaType<ChoiceModel>("ChoiceModel");
   ui->setupUi(this);


   ui->scrollArea->setWidget(mRegistrationWidgetPtr);
   mRegistrationWidgetPtr->onSetAlgorithmList({"Point to Point", "Point to Plane", "GoICP"});
   mRegistrationWidgetPtr->onSetAlgorithmSelection(0);


   QObject *registrationParametersPtr = new RegistrationParameters();
   registrationParametersPtr->setParent(this);
   QObject *workingLimitsParametersPtr = new WorkingLimitsParameters();
   workingLimitsParametersPtr->setParent(registrationParametersPtr);
   QObject *pointToPointParameters = new PointToPointParameters();
   pointToPointParameters->setParent(workingLimitsParametersPtr);

   mRegistrationWidgetPtr->onSetObject(registrationParametersPtr);


   connect(ui->exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

   //   connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::updateActions);

   //   connect(ui->actionsMenu, &QMenu::aboutToShow, this, &MainWindow::updateActions);
   //   connect(ui->insertRowAction, &QAction::triggered, this, &MainWindow::insertRow);
   //   connect(ui->insertColumnAction, &QAction::triggered, this, &MainWindow::insertColumn);
   //   connect(ui->removeRowAction, &QAction::triggered, this, &MainWindow::removeRow);
   //   connect(ui->removeColumnAction, &QAction::triggered, this, &MainWindow::removeColumn);
   //   connect(ui->insertChildAction, &QAction::triggered, this, &MainWindow::insertChild);

   //   updateActions();
}

MainWindow::~MainWindow()
{
   //   if (mRegistrationWidgetPtr)
   //   {
   //      delete mRegistrationWidgetPtr;
   //      mRegistrationWidgetPtr = nullptr;
   //   }
}

// void MainWindow::insertChild()
//{
//    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
//    QAbstractItemModel *model = ui->treeView->model();

//   if (model->columnCount(index) == 0)
//   {
//      if (!model->insertColumn(0, index))
//         return;
//   }

//   if (!model->insertRow(0, index))
//      return;

//   for (int column = 0; column < model->columnCount(index); ++column)
//   {
//      const QModelIndex child = model->index(0, column, index);
//      model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
//      if (!model->headerData(column, Qt::Horizontal).isValid())
//         model->setHeaderData(column, Qt::Horizontal, QVariant(tr("[No header]")), Qt::EditRole);
//   }

//   ui->treeView->selectionModel()->setCurrentIndex(model->index(0, 0, index), QItemSelectionModel::ClearAndSelect);
//   updateActions();
//}

// bool MainWindow::insertColumn()
//{
//    QAbstractItemModel *model = ui->treeView->model();
//    int column = ui->treeView->selectionModel()->currentIndex().column();

//   // Insert a column in the parent item.
//   bool changed = model->insertColumn(column + 1);
//   if (changed)
//      model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);

//   updateActions();

//   return changed;
//}

// void MainWindow::insertRow()
//{
//    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
//    QAbstractItemModel *model = ui->treeView->model();

//   if (!model->insertRow(index.row() + 1, index.parent()))
//      return;

//   updateActions();

//   for (int column = 0; column < model->columnCount(index.parent()); ++column)
//   {
//      const QModelIndex child = model->index(index.row() + 1, column, index.parent());
//      model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
//   }
//}

// bool MainWindow::removeColumn()
//{
//    QAbstractItemModel *model = ui->treeView->model();
//    const int column = ui->treeView->selectionModel()->currentIndex().column();

//   // Insert columns in each child of the parent item.
//   const bool changed = model->removeColumn(column);
//   if (changed)
//      updateActions();

//   return changed;
//}

// void MainWindow::removeRow()
//{
//    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
//    QAbstractItemModel *model = ui->treeView->model();
//    if (model->removeRow(index.row(), index.parent()))
//       updateActions();
// }

// void MainWindow::updateActions()
//{
//    const bool hasSelection = !ui->treeView->selectionModel()->selection().isEmpty();
//    ui->removeRowAction->setEnabled(hasSelection);
//    ui->removeColumnAction->setEnabled(hasSelection);

//   const bool hasCurrent = ui->treeView->selectionModel()->currentIndex().isValid();
//   ui->insertRowAction->setEnabled(hasCurrent);
//   ui->insertColumnAction->setEnabled(hasCurrent);

//   if (hasCurrent)
//   {
//      ui->treeView->closePersistentEditor(ui->treeView->selectionModel()->currentIndex());

//      const int row = ui->treeView->selectionModel()->currentIndex().row();
//      const int column = ui->treeView->selectionModel()->currentIndex().column();
//      if (ui->treeView->selectionModel()->currentIndex().parent().isValid())
//         statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
//      else
//         statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
//   }
//}
