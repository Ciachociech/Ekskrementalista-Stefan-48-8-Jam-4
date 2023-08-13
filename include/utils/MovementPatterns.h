#ifndef MOVEMENTPATTERNS_H_
#define MOVEMENTPATTERNS_H_

void playerBulletMovement(float& x, float& y) {
    x = 0.f;
    y = -9.f;
}

void enemyEmptyMovement(float& x, float& y) {
    x = 0.f;
    y = 0.f;
}

void bossKretkaMovement(float& x, float& y) {
    x = 4.f;
    y = 0.f;
}

#endif // !MOVEMENTPATTERNS_H_
