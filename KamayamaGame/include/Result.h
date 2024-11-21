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

	//runsに1を足す
	void addRun();
	//飛距離を受け取り、maxDistnceと比較して更新
	void updateMaxDistance(int dist);
	//successiveRunsを増やす
	void addSuccessiveRuns();
	//seuccessiveRunsを0にする
	void resetSuccessiveRuns();
	//maxSuccessiveRunsを更新
	void updateMaxSuccessiveRuns();
	//distanceSumに受け取った数を可算
	void addDistanceSum(int dist);
	//飛距離からスコアを計算
	int calculateScore(int dist)const;
	//スコアを加算
	void addScore(int score);
public:
	Result(int norm) :
		norm(norm) {}
	//飛距離と、ホームランか否かを受け取り、変数を更新
	void update(int dist, bool isRun);
	//ノルマと結果からクリアかどうか返す
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

