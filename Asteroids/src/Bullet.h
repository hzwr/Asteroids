#include "GameEngine\EntitySystem\Actor.h"

class Bullet:
	public Actor
{
public:
	Bullet(class Game *game, Quaternion rotation);
	void UpdateActor(float deltaTime) override;

private:
	class ColliderComponent *mCollider;
	float mTimer;
};