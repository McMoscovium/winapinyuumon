#pragma once
class Result
{
private:
	const int norm;
	int runs = 0;
	int maxSuccessiveRuns = 0;
	int successiveRuns = 0;
	int maxDistance = 0;
	int distanceSum = 0;
	int score = 0;

	//runs��1�𑫂�
	void addRun();
	//�򋗗����󂯎��AmaxDistnce�Ɣ�r���čX�V
	void updateMaxDistance(int dist);
	//successiveRuns�𑝂₷
	void addSuccessiveRuns();
	//seuccessiveRuns��0�ɂ���
	void resetSuccessiveRuns();
	//maxSuccessiveRuns���X�V
	void updateMaxSuccessiveRuns();
	//distanceSum�Ɏ󂯎���������Z
	void addDistanceSum(int dist);
	//�򋗗�����X�R�A���v�Z
	int calculateScore(int dist)const;
	//�X�R�A�����Z
	void addScore(int score);
public:
	Result(int norm) :
		norm(norm) {}
	//�򋗗��ƁA�z�[���������ۂ����󂯎��A�ϐ����X�V
	void update(int dist, bool isRun);
	//�m���}�ƌ��ʂ���N���A���ǂ����Ԃ�
	bool isClear()const;

	//
	int getRuns()const;
	//
	int getMaxSuccessiveRuns()const;
	//
	int getMaxDistance()const;
	//
	int getDistanceSum()const;
};

