#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

class PropertyModel;
class PropertyDelegate;

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
   ~MainWindow();

 private:
   Ui::MainWindow *ui;

   PropertyModel *model = nullptr;
   PropertyDelegate *delegate = nullptr;
};
#endif // MAINWINDOW_H
