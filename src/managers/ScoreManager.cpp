#include "managers/ScoreManager.h"

namespace managers {

ScoreManager::ScoreManager() : score_(0), powerupMultiplier_(1) {}

ScoreManager& ScoreManager::instance() {
	static ScoreManager scoreManager;
	return scoreManager;
}

ScoreManager::~ScoreManager() {}

void ScoreManager::increaseScore(std::uint32_t addScore) { this->score_ += addScore; }

void ScoreManager::resetScore() { this->score_ = 0; }

void ScoreManager::setMultiplier(float powerupMultiplier) { this->powerupMultiplier_ = powerupMultiplier; }

std::uint32_t ScoreManager::getScore() { return this->score_; }

float ScoreManager::getMultiplier() { return this->powerupMultiplier_; }

}