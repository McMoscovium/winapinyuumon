#include "CutIn.h"

#include "AfterMeetSubState.h"

void CutIn::enter(Game& game)
{
	timer.setRecord();
	PictureObject& cutIn = gameObjectManager.getObject<PictureObject>("CUTIN");
	PictureObject& cutInStr = gameObjectManager.getObject<PictureObject>("CUTIN_STRING");
	cutIn.setObjectPosition({ 0,300 });
	cutInStr.setObjectPosition({ 200,381 });
	cutInStr.appear();
	cutIn.appear();
}

void CutIn::update(Game& game)
{
	timer.update();
	if (timer.span() > 1500) {
		//1500ms経過で次のsubstateへ
		owner.changeSubState(new AfterMeetSubState(owner, hitStopTime));
		return;
	}

	PictureObject& cutIn = gameObjectManager.getObject<PictureObject>("CUTIN");
	PictureObject& cutInStr = gameObjectManager.getObject<PictureObject>("CUTIN_STRING");
	//カットインを少し移動
	POINT cutIncurrent = cutIn.getPosition();
	POINT cutInnext = { cutIncurrent.x - 5,cutIncurrent.y };
	cutIn.setObjectPosition(cutInnext);

	POINT cutInStrCurrent = cutInStr.getPosition();
	POINT cutInStrNext = { cutInStrCurrent.x - 10,cutInStrCurrent.y };
	cutInStr.setObjectPosition(cutInStrNext);
}

void CutIn::exit(Game& game)
{
	PictureObject& cutIn = gameObjectManager.getObject<PictureObject>("CUTIN");
	PictureObject& cutInStr = gameObjectManager.getObject<PictureObject>("CUTIN_STRING");
	cutIn.hide();
	cutInStr.hide();
}
