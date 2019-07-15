// MinecraftNativeCaller.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h>


HMODULE get_module();

DWORD_PTR get_func(DWORD_PTR base, DWORD_PTR offset);

extern "C" __declspec(dllexport) DWORD_PTR call_out(DWORD_PTR offset);
extern "C" __declspec(dllexport) void close_modules();

using Func = void(__stdcall *)();

HMODULE loadModule;

int main()
{
    std::cout << "Starting Server...\n";

	const DWORD_PTR main_offset = 0x00058B70;
	loadModule = get_module();
	if (loadModule == nullptr)
	{
		std::cout << "DLL not found.\n";
		return -1;
	}

	close_modules();

	const auto func = reinterpret_cast<Func>(call_out(main_offset));
	func();

	close_modules();
}

HMODULE get_module()
{
	// your 'bedrock_server.exe' path.
	return LoadLibraryA(R"(C:\Users\hiroki\Desktop\server\bedrock-server-1.12.0.28\bedrock_server.exe)");
}

void close_modules()
{
	FreeLibrary(loadModule);
}

DWORD_PTR get_func(DWORD_PTR base, const DWORD_PTR offset)
{
	return base + offset;
}

DWORD_PTR call_out(DWORD_PTR offset)
{
	if (loadModule != nullptr)
		return get_func(reinterpret_cast<DWORD_PTR>(get_module()), offset);
	else
		return 0;
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
