#include <Windows.h>
#include "KamataEngine.h"
#include "TitleScene.h"
#include "GameScene.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KamataEngine::Initialize(L"CG4_LE3D_ムラタ_カイラ");

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// タイトルシーンのインスタンス生成
	TitleScene* titleScene = new TitleScene();
	// タイトルシーンの初期化
	titleScene->Initialize();

	// ゲームシーンのポインタ
	GameScene* gameScene = nullptr;

	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		// タイトルシーンの処理
		if (titleScene) {
			// タイトルシーンの更新
			titleScene->Update();

			// 描画開始
			dxCommon->PreDraw();

			// タイトルシーンの描画
			titleScene->Draw();

			// 描画終了
			dxCommon->PostDraw();

			// タイトルシーン終了チェック
			if (titleScene->IsFinished()) {
				// タイトルシーンの解放
				delete titleScene;
				titleScene = nullptr;

				// ゲームシーンのインスタンス生成
				gameScene = new GameScene();
				// ゲームシーンの初期化
				gameScene->Initialize();
			}
		}
		// ゲームシーンの処理
		else if (gameScene) {
			// ゲームシーンの更新
			gameScene->Update();

			// 描画開始
			dxCommon->PreDraw();

			// ゲームシーンの描画
			gameScene->Draw();

			// 描画終了
			dxCommon->PostDraw();
		}
	}

	// シーンの解放
	delete titleScene;
	delete gameScene;

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}
