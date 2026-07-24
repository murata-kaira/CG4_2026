#include "GameScene.h"
#include <math/MathUtility.h>
#include <random>

using namespace KamataEngine;
using namespace MathUtility;

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

// デストラクタ
GameScene::~GameScene() {
	// エフェクト
	for (Effect* effect : effects_) {
		delete effect;
	}
	effects_.clear();

	delete modelParticle_;
	delete stage_;
	delete player_;
	delete modelPlayer_;
	delete graph_;

	for (Particle* particle : particles_) {
		delete particle;
	}
	particles_.clear();
}

// 初期化
void GameScene::Initialize() {
	// 乱数の初期化
	srand((unsigned)time(NULL));

	// 3Dモデルデータ生成
	modelEffect_ = Model::CreateFromOBJ("plane");
	modelParticle_ = Model::CreateSphere(4, 4);

	textureHandleStage_ = TextureManager::Load("stage/stage.png");
	textureHandleGraph_ = TextureManager::Load("white1x1.png");


	// 3Dモデルの生成
	modelPlayer_ = Model::CreateFromOBJ("player");

	// カメラの初期化
	camera_.translation_ = {0, 0, -20};
	camera_.Initialize();

	stage_ = new Stage();
	stage_->Initialize(textureHandleStage_);

	player_ = new Player();
	player_->Initialize(modelPlayer_);

	graph_ = new Graph();
	graph_->Initialize(textureHandleGraph_);

}

// 更新
void GameScene::Update() {

	stage_->Update();
	player_->Update();
	graph_->Update(hp_);

	// エフェクト発生
	if (rand() % 5 == 0) {
		Vector3 position = {distribution(randomEngine), distribution(randomEngine), 0};
		position = position * 10;
		EffectBorn(position);
	}

	// パーティクル発生
	if (rand() % 20 == 0) {
		Vector3 position = {distribution(randomEngine) * 30.0f, distribution(randomEngine) * 20.0f, 0};
		ParticleBorn(position);
	}

	// エフェクト更新
	// effect_->Update();
	for (Effect* effect : effects_) {
		effect->Update();
	}

	// デスフラグの立ったエフェクトを削除
	effects_.remove_if([](Effect* effect) {
		if (effect->IsFinished()) {
			delete effect;
			return true;
		}
		return false;
	});

	// パーティクル更新
	for (Particle* particle : particles_) {
		particle->Update();
	}

	// 終了フラグの立ったパーティクルを削除
	particles_.remove_if([](Particle* particle) {
		if (particle->IsFinished()) {
			delete particle;
			return true;
		}
		return false;
	});
}

// 描画
void GameScene::Draw() {
	// DirectXCommon インスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 2Dスプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// 背景描画
	stage_->Draw();
	graph_->Draw();

	// 2Dスプライト描画後処理
	Sprite::PostDraw();


	// 3Dモデル描画前処理
	dxCommon->ClearDepthBuffer();

	Model::PreDraw();

	// エフェクト描画
	for (Effect* effect : effects_) {
		effect->Draw(camera_);
	}

	// パーティクル描画
	for (Particle* particle : particles_) {
		particle->Draw(camera_);
	}

	player_->Draw(camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();
}

// エフェクト発生
void GameScene::EffectBorn(Vector3 position) {
	Vector3 color = {abs(distribution(randomEngine)), abs(distribution(randomEngine)), abs(distribution(randomEngine))};
	for (int32_t i = 0; i < 15; i++) {
		Effect* effect = new Effect();
		float rotate = distribution(randomEngine) * 3.14f;
		float size = 1.0f + abs(distribution(randomEngine)) * 4;
		effect->Initialize(modelEffect_, rotate, size, position, color);
		effects_.push_back(effect);
	}
}

// パーティクル発生
void GameScene::ParticleBorn(Vector3 position) {
	// パーティクルの生成
	for (int i = 0; i < 100; i++) {

		// 生成
		Particle* particle = new Particle();
		// 移動量
		Vector3 velocity = {distribution(randomEngine), distribution(randomEngine), 0};
		// 初期化
		particle->Initialize(modelParticle_, position, velocity);
		// リストに追加
		particles_.push_back(particle);
		Normalize(velocity);
		velocity *= distribution(randomEngine);
		velocity *= 0.1f;
	}
}
