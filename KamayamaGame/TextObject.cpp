#include "TextObject.h"

TextObject::TextObject(std::wstring objectName, std::wstring text):
	GameObject(objectName),
	text(text),
	hFont(CreateFontW(100, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("HGçsèëëÃ")))
{
}

TextObject::~TextObject()
{
	DeleteObject(hFont);
}

void TextObject::render(HDC hdc)const
{
	//SetBkMode(hdc, TRANSPARENT);//îwåiÇìßñæÇ…Ç∑ÇÈ
	SelectObject(hdc, hFont);
	TextOut(hdc, getPositionX(), getPositionY(), text.c_str(), text.size());
}

void TextObject::setText(const std::wstring& text)
{
	TextObject::text = text;
}
