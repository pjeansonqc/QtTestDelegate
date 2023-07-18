#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "propertyDelegate.h"
#include "propertyModel.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   // Create an instance of the custom model
   model = new PropertyModel(this);

   ui->tableView->setModel(model);

   // Set the delegate for column 1
   delegate = new PropertyDelegate;
   ui->tableView->setItemDelegateForColumn(1, delegate);
}

MainWindow::~MainWindow()
{
   delete ui;
}
