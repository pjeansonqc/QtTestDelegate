#include "choiceModel.h"

const QStringList &ChoiceModel::getChoiceList() const
{
    return mChoiceList;
}

void ChoiceModel::setChoiceList(const QStringList &inChoiceList)
{
    mChoiceList = inChoiceList;
}

QString ChoiceModel::getSelectedChoice()
{
    if (mSelection < 0 || mSelection >= mChoiceList.size())
    {
        mSelection = 0;
    }
    return mChoiceList[mSelection];
}

int ChoiceModel::getSelection()
{
    return mSelection;
}

void ChoiceModel::setSelection(int inSelection)
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
