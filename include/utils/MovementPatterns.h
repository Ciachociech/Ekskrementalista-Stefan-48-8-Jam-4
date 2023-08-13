#ifndef MOVEMENTPATTERNS_H_
#define MOVEMENTPATTERNS_H_

inline void playerBulletCenterMovement(float& x, float& y) {
    x = 0.f;
    y = -9.f;
}

inline void playerBulletLeftMovement(float& x, float& y) {
    x = -1.f;
    y = -9.f;
}

inline void playerBulletRightMovement(float& x, float& y) {
    x = 1.f;
    y = -9.f;
}

inline void powerupSlowMovement(float& x, float& y) {
    x = 0.f;
    y = 1.f;
}

inline void powerupFastMovement(float& x, float& y) {
    x = 0.f;
    y = 2.f;
}

inline void bossKretkaMovement(float& x, float& y) {
    x = 4.f;
    y = 0.f;
}

inline void enemySmallMovement(float& x, float& y) {
    x = 0.f;
    y = 9.f;
}

inline void enemyMediumMovement(float& x, float& y) {
    x = 0.f;
    y = 6.f;
}

inline void enemyBigMovement(float& x, float& y) {
    x = 0.f;
    y = 3.f;
}

#endif // !MOVEMENTPATTERNS_H_
