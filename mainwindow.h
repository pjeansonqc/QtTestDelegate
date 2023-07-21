#pragma once

#include <QMainWindow>

class PropertyModel;
class PropertyItemDelegate;

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
   Q_OBJECT

 public:
   MainWindow(QWidget *parent = nullptr);

 public slots:
   void updateActions();

 private slots:
   void insertChild();
   bool insertColumn();
   void insertRow();
   bool removeColumn();
   void removeRow();

 private:
   Ui::MainWindow *ui;

   PropertyModel *model = nullptr;
};
