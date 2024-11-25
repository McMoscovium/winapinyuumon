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
	SetBkMode(hdc, TRANSPARENT);//�w�i�𓧖��ɂ���
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
		//�쐬����
		DeleteObject(hFont);
		hFont = newFont;
		return;
	}
	//�쐬���s
	OutputDebugString(L"�t�H���g�̕ύX�Ɏ��s\n");
}


