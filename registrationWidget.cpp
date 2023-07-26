#include "registrationWidget.h"
#include "choiceModel.h"
#include "propertyDelegate.h"
#include "propertyItem.h"
#include "propertyModel.h"
#include "registrationParameters.h"
#include "ui_registrationWidget.h"


RegistrationWidget::RegistrationWidget(QWidget *parent) : QWidget(parent), mUiPtr(new Ui::RegistrationWidget), mPropertyModelPtr()
{
   mUiPtr->setupUi(this);

   // Create an instance of the custom model
   mHeaders.append({"Title", "Description"});

   mPropertyModelPtr = new PropertyModel(mHeaders, "", parent);
   mPropertyModelPtr->initModel(mHeaders);
   mUiPtr->treeView->setModel(mPropertyModelPtr);
   auto delegate = new PropertyDelegate;
   mUiPtr->treeView->setItemDelegate(delegate);
}

RegistrationWidget::~RegistrationWidget() {}

void RegistrationWidget::onSetAlgorithmList(const QStringList &inAlgorithmList)
{
   mAlgorithmList = inAlgorithmList;
   mUiPtr->algorithmListComboBox->addItems(mAlgorithmList);
}

void RegistrationWidget::onSetAlgorithmSelection(int inIndex)
{
   if (inIndex < mAlgorithmList.size())
   {
      mUiPtr->algorithmListComboBox->setCurrentIndex(inIndex);
   }
}

void RegistrationWidget::resizeContent()
{
   for (int column = 0; column < mPropertyModelPtr->columnCount(); ++column)
      mUiPtr->treeView->resizeColumnToContents(column);
}

void RegistrationWidget::onSetObject(QObject *inObject)
{
   mPropertyModelPtr->initModel(mHeaders);
   auto rootItem = mPropertyModelPtr->mRootItem;
   setObjectInNode(inObject, rootItem);
}

void RegistrationWidget::setObjectInNode(QObject *inObject, PropertyItem *inItem)
{
   auto objectItem = inItem->addNode(inObject->objectName());
   auto properties = inObject->dynamicPropertyNames();
   for (auto prop : properties)
   {
      QVariant qvar = inObject->property(prop);
      objectItem->appendChildren(prop, qvar);
   }
   auto objectList = inObject->children();
   for (auto child : objectList)
   {
      setObjectInNode(child, objectItem);
   }
   resizeContent();
}

void RegistrationWidget::initGui() {}

void RegistrationWidget::on_algorithmListComboBox_currentIndexChanged(const QString &inAlgorithm)
{
   emit signalAlgorithmChanged(inAlgorithm);
}

void RegistrationWidget::on_algorithmListComboBox_currentIndexChanged(int index)
{
   emit signalAlgorithmChanged(index);
}
