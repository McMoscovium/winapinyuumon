#pragma once

#include <Windows.h>

class Window;

/// <summary>
/// 仮想ウィンドウ。これにゲーム状態を描画してWindowクラスにデータを送り、実際のウィンドウに描画してもらう。
/// </summary>
class VirtualWindow
{
public:
	VirtualWindow(Window* window);//windowと互換性を持つ仮想ウィンドウ（バックバッファ）クラスを作成
	~VirtualWindow();
private:
	HDC hdcBackBuffer = nullptr;//バックバッファ用メモリデバイスコンテスト
	HBITMAP hBackBuffer = nullptr;//バックバッファ用ビットマップ（メモリデバイスコンテキストはビットマップ上に描画する。）
};