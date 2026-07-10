#pragma once

#include "KamataEngine.h"
#include "Effect.h"
#include "Particle.h"

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
	// カメラ
	Camera camera_;

	// 3Dモデル 
	Model* modelEffect_ = nullptr;
	Model* modelParticle_ = nullptr;


	// エフェクト
	std::list<Effect*> effects_;

	// パーティクル
	std::list<Particle*> particles_;

	// エフェクト発生
	void EffectBorn(Vector3 position);

	// パーティクル発生
	void ParticleBorn(Vector3 position);

};

