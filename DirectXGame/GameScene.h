#pragma once

#include "KamataEngine.h"
#include "Effect.h"
#include "Particle.h"
#include "Stage.h"
#include "Player.h"
#include "Graph.h"
#include "Number.h"




using namespace KamataEngine;

// ゲームシーン
class GameScene
{
public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	

	// 3Dモデル 
	Model* modelEffect_ = nullptr;
	Model* modelParticle_ = nullptr;

	//テクスチャー
	uint32_t textureHandleStage_ = 0;
	uint32_t textureHandleGraph_ = 0;
	uint32_t textureHandleNumber_ = 0;

		
	// エフェクト
	std::list<Effect*> effects_;

	// パーティクル
	std::list<Particle*> particles_;

	// エフェクト発生
	void EffectBorn(Vector3 position);

	// パーティクル発生
	void ParticleBorn(Vector3 position);


	
	// 3Dモデル
	KamataEngine::Model* modelPlayer_ = nullptr;
	// カメラ
	KamataEngine::Camera camera_; 
	// クラス
	Player* player_ = nullptr;
	Stage* stage_ = nullptr;
	Graph* graph_ = nullptr;
	Number* number_ = nullptr;

	// HP
	int hp_ = 200;
	// score
	int gameScore_ = 0;

};

