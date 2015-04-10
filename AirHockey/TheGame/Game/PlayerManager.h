#include "ComponentSystem\RenderableComponent.h"
#include "ComponentSystem\PhysicsComponent.h"
#include "ComponentSystem\InputComponent.h"
#include "ComponentSystem\TextComponent.h"

#pragma once
struct PlayerScore : public EntityManager::Entity
{
	RenderableComponent* render;
	TextComponent* text;
	int score;
	PlayerScore(glm::vec3 color, int teamNum);
	~PlayerScore();
};
struct Player : public EntityManager::Entity
{
	PlayerScore* score;
	RenderableComponent* render;
	PhysicsComponent* physics;
	InputComponent* input;
	int teamNum;
	int leftKey;
	int rightKey;
	int hitKey;
	bool isMovingForward;
	bool isMovingBackward;
	glm::vec3 left;
	glm::vec3 startPoint;
	glm::vec4 teamColor;
	void initialize(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	void moveLeft();
	void moveRight();
	void moveForward();
	void slowDown();
	void update();
	~Player();
};
struct PlayerPanel : EntityManager::Entity
{
	RenderableComponent* render;
	PlayerPanel(int teamNum);
};
class PlayerManager
{
public:
	static void createPlayer(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	static QList<Player*> getPlayers();
	static void shutdown();
	static void resetGame();
	static void update();
};

