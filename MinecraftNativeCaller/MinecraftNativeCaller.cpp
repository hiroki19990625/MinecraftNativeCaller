// MinecraftNativeCaller.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h>


HMODULE get_module();

DWORD_PTR get_func(DWORD_PTR base, DWORD_PTR offset);

//extern "C" __declspec(dllexport) 

typedef void (*UnExportedFunc)();

int main()
{
    std::cout << "Starting Server...\n";

	const DWORD_PTR main_offset = 0x00057B70;
	const auto hMod = get_module();
	if (hMod == nullptr)
	{
		std::cout << "DLL not found.\n";
		return -1;
	}

	const auto func = reinterpret_cast<UnExportedFunc>(get_func(reinterpret_cast<DWORD_PTR>(hMod), main_offset));
	func();
}

HMODULE get_module()
{
	return LoadLibraryA("C:\\Users\\hiroki\\Desktop\\server\\MinecraftNativeCaller\\x64\\Debug\\bedrock_server.exe");
}

DWORD_PTR get_func(DWORD_PTR base, const DWORD_PTR offset)
{
	return base + offset;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
