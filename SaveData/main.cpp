#include "./SaveData.h"

#include <iostream>


using namespace std;



void test() {
	SaveData saveData;
	SaveDataManager saveDataManager;



	saveData.initScore();

	cout << "saveData: initialized" << endl;
	saveData.print();
	cout << endl;

	saveData.setScore(200);
	saveData.setCheated(true);
	cout << "saveData: changed" << endl;
	saveData.print();
	cout << endl;

	cout << "begin to save" << endl;
	saveDataManager.save(saveData);
	cout << "saved" << endl << endl;


	cout << "begin to load" << endl;
	saveDataManager.load(saveData);
	cout << "loaded" << endl << endl;

	saveData.print();
}

int main() {
	test();
	return 0;
}