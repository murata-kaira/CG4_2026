#include "Particle.h"
#include <cassert>
#include <algorithm>
#include <math/MathUtility.h>


using namespace MathUtility;

void Particle::Initialize(Model* model, Vector3 position, Vector3 velocity) {

	assert(model);
	model_ = model;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// 色設定
	objectColor_.Initialize();
	color_ = {1, 1, 0, 1};
	velocity_ = velocity;

	//大きさ
	worldTransform_.scale_ = {0.2f, 0.2f, 0.2f};

}

void Particle::Update() {

	// 円運動の更新

	worldTransform_.translation_ += velocity_;

	worldTransform_.UpdateMatrix();

	objectColor_.SetColor(color_);

	//終了なら何もしない
	if (isFinished_) {
		return;
	}
	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	// 存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了扱いにする
		isFinished_ = true;
	}

	//フェード処理
	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);


}

void Particle::Draw(Camera& camera) {

	model_->Draw(worldTransform_, camera ,&objectColor_);

}
