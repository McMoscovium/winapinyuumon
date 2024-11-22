#include "PlayResultState.h"

#include "CompareNormSubState.h"
#include "TextObject.h"
#include "Stage.h"
#include "Pitcher.h"
#include <string>


PlayResultState::PlayResultState(Game& game, Result& result, Stage* stage) :
	GameState(game),
	result(result)
{
	OutputDebugString(L"Entering PlayResultState\n");

	//GameObject��݂���
	gameObjectManager.addFront<PictureObject>("KEKKAHAPPYOU", L".//assets//���ʔ��\.bmp", SIZE{ 1152,720 });
	gameObjectManager.addFront<PictureObject>("KEKKAHAPPYOU2", L".//assets//���ʔ��\2.bmp", SIZE{ 1152,720 });
	
	//appendObject({�o�b�^�[�摜�I�u�W�F�N�g�ւ̃|�C���^�[});//�o�b�^�[�摜

	Pitcher* pitcher = stage->getPitcher();
	gameObjectManager.addFront<TextObject>("PITCHERNAME", pitcher->getName());
	gameObjectManager.addFront<TextObject>("BALLS", std::to_wstring(stage->getTrials()));
	gameObjectManager.addFront<TextObject>("NORM", std::to_wstring(stage->getNorm()));
	gameObjectManager.addFront<TextObject>("RUNS", std::to_wstring(result.getRuns()));
	gameObjectManager.addFront<TextObject>("RUNSTREAK", std::to_wstring(result.getMaxSuccessiveRuns()));
	gameObjectManager.addFront<TextObject>("MAX_DISTANCE", std::to_wstring(result.getMaxDistance()));
	gameObjectManager.addFront<TextObject>("DISTANCE_SUM", std::to_wstring(result.getDistanceSum()));
	gameObjectManager.addFront<TextObject>("BONUS_POINT", L"0");
	gameObjectManager.addFront<PictureObject>("CLEAR", L".//assets//�N���A.bmp", SIZE{ 273,78 });
	gameObjectManager.addFront<PictureObject>("FAILURE", L".//assets//�����ς�.bmp", SIZE{ 273,78 });
	gameObjectManager.addFront<PictureObject>("NEXT", L".//assets//����.bmp", SIZE{ 115,49 });
	PictureObject& toStageList = gameObjectManager.addFront<PictureObject>("TO_STAGELIST", L".//assets//�X�e�[�W�I����.bmp", SIZE{ 401,66 });

	//�ʒu�ݒ�
	gameObjectManager.getObject<PictureObject>("PITCHERNAME").setObjectPosition({ 312,224 });
	gameObjectManager.getObject<TextObject>("BALLS").setObjectPosition({ 606,330 });
	gameObjectManager.getObject<TextObject>("NORM").setObjectPosition({ 606,393 });
	gameObjectManager.getObject<TextObject>("RUNS").setObjectPosition({ 741,514 });
	gameObjectManager.getObject<PictureObject>("NEXT").setObjectPosition({ 920,623 });
	toStageList.setObjectPosition({ 718,643 });

	//substate������
	changeSubState(new CompareNormSubState(*this));
}

PlayResultState::~PlayResultState()
{
	//�|�C���^�^�̃����o��������delete
}

void PlayResultState::update(Game& game)
{
	if (currentSubState)currentSubState->update(game);
}

const Result& PlayResultState::getResult() const
{
	return result;
}
