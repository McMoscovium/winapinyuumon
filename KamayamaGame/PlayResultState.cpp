#include "PlayResultState.h"

#include "CompareNormSubState.h"
#include "TextObject.h"
#include "Pitcher.h"

#include <string>


PlayResultState::PlayResultState(Game& game, Result& result,Pitcher* pitcher):
	GameState(game),
	result(result)
{
	OutputDebugString(L"Entering PlayResultState\n");

	//GameObject��݂���
	appendObject(L"PICTURE_KEKKAHAPPYOU", L".//assets//���ʔ��\.bmp", { 1152,720 });//�w�i
	//appendObject({�o�b�^�[�摜�I�u�W�F�N�g�ւ̃|�C���^�[});//�o�b�^�[�摜

	std::wstring pitcherName = pitcher->getName();
	appendObject(new TextObject(L"TEXT_PITCHERNAME", pitcherName));//�s�b�`���[��
	

	appendObject(new TextObject(L"TEXT_BALLS", L"1oku"));//����
	appendObject(new TextObject(L"TEXT_NORM", L"1oku"));//�m���}
	std::wstring runs = std::to_wstring(result.getRuns());
	appendObject(new TextObject(L"TEXT_RUNS", runs));//�z�[��������
	appendObject(L"PICTURE_CLEAR", L".//assets//�N���A.bmp", { 273,78 });
	appendObject(L"PICTURE_FAILURE", L".//assets//�����ς�.bmp", { 273,78 });
	appendObject(L"BUTTON_NEXT", L".//assets//����.bmp", { 115,49 });

	//�ʒu�ݒ�
	getGameObject(L"TEXT_PITCHERNAME").setObjectPosition({ 312,224 });
	getGameObject(L"TEXT_BALLS").setObjectPosition({ 606,330 });
	getGameObject(L"TEXT_NORM").setObjectPosition({ 606,393 });
	getGameObject(L"TEXT_RUNS").setObjectPosition({ 741,514 });
	getGameObject(L"BUTTON_NEXT").setObjectPosition({ 920,623 });

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
