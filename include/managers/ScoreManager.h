#ifndef MANAGERS_SCOREMANAGER_H_
#define MANAGERS_SCOREMANAGER_H_

#include <cstdint>

namespace managers {

class ScoreManager {
private:
	std::uint32_t score_;
	float powerupMultiplier_;

	ScoreManager();
public:
	ScoreManager(const ScoreManager& /*original*/) = delete;
	ScoreManager& operator=(const ScoreManager& /*object*/) = delete;

	static ScoreManager& instance();
	virtual ~ScoreManager();

	void increaseScore(std::uint32_t addScore);
	void resetScore();
	void setMultiplier(float powerupMultiplier);
	std::uint32_t getScore();
	float getMultiplier();
};

}

#endif // !MANAGERS_SCOREMANAGER_H_
