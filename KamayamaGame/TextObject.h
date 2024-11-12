#pragma once
#include "GameObject.h"
#include <Windows.h>

#include <string>

class TextObject :
    public GameObject
{
private:
    std::wstring text;
    HFONT hFont;
public:
    TextObject(std::wstring objectName, std::wstring text);
    ~TextObject();

    virtual void render(HDC)const override;
    void setText(const std::wstring& text);
};

