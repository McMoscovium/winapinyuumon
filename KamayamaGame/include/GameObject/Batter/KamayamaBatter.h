#pragma once
#include "GameObject/Batter/Batter.h"


class SaveData;

class KamayamaBatter :
    public Batter
{
private:
public:
    KamayamaBatter(HINSTANCE hInstance, const SaveData& dataSet);
    ~KamayamaBatter() = default;
};

