#include "TextObject.h"

TextObject::TextObject(const std::string& objectName, const std::wstring& text):
	GameObject(objectName),
	text(text),
	hFont(CreateFontW(60, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial")))
{
}

TextObject::~TextObject()
{
	DeleteObject(hFont);
}

void TextObject::render(HDC hdc)const
{
	SetBkMode(hdc, TRANSPARENT);//îwåiÇìßñæÇ…Ç∑ÇÈ
	HGDIOBJ oldObj = SelectObject(hdc, hFont);
	TextOut(hdc, getPositionX(), getPositionY(), text.c_str(), (unsigned int)text.size());
	SelectObject(hdc, oldObj);
	
}

void TextObject::setText(const std::wstring& text)
{
	TextObject::text = text;
}

void TextObject::setFont(LPCWSTR fontName)
{
	if (HFONT newFont = CreateFontW(100, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY, VARIABLE_PITCH, fontName)) {
		//çÏê¨ê¨å˜
		DeleteObject(hFont);
		hFont = newFont;
		return;
	}
	//çÏê¨é∏îs
	OutputDebugString(L"ÉtÉHÉìÉgÇÃïœçXÇ…é∏îs\n");
}


