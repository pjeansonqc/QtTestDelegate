#pragma once

#include <QMetaType>
#include <QStringList>

class ChoiceModel
{
 public:
   ChoiceModel(const QStringList &inChoices = {""}, int inSelection = 0) : mChoiceList(inChoices), mSelection(inSelection) {}
   int getSelection();
   void setSelection(int inSelection);

   const QStringList &getChoiceList() const;
   void setChoiceList(const QStringList &inChoiceList);

   QString getSelectedChoice();

 private: // methods
 private:
   QStringList mChoiceList;
   int mSelection = 0;
};
Q_DECLARE_METATYPE(ChoiceModel)

inline const QStringList &ChoiceModel::getChoiceList() const
{
   return mChoiceList;
}


inline void ChoiceModel::setChoiceList(const QStringList &inChoiceList)
{
   mChoiceList = inChoiceList;
}

inline QString ChoiceModel::getSelectedChoice()
{
   if (mSelection < 0 || mSelection >= mChoiceList.size())
   {
      mSelection = 0;
   }
   return mChoiceList[mSelection];
}

inline int ChoiceModel::getSelection()
{
   return mSelection;
}

inline void ChoiceModel::setSelection(int inSelection)
{
   if (inSelection < 0 || inSelection >= mChoiceList.size())
   {
      mSelection = 0;
   }
   else
   {
      mSelection = inSelection;
   }
}
