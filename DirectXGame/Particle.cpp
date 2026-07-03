#include "Particle.h"
#include <cassert>


void Particle::Initialize(Model* model) {

assert(model);
model_ = model;

// ワールド変換の初期化
worldTransform_.Initialize();


}

void Particle::Update() {

	worldTransform_.TransferMatrix();

}

void Particle::Draw(Camera& camera) {

	model_->Draw(worldTransform_, camera);


}


