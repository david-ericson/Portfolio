#pragma once
#include "Matrix3D.h"
#include "Matrix2D.h"
#include "Engine.h"
#include "GameObject.h"
#include "Bullets.h"
#include "ParticleEffect.h"
#include "Profiler.h"
#include "Timer.h"
#include "Core.h"

static ParticleEffect thrusterTrail[] = {
	ParticleEffect(2, Vector2D(-50,0), 100, 0, 0, RGB(85,131 ,207)),
	ParticleEffect(2, Vector2D(-50,0), 100, 0, 0, RGB(85,131,207))
};

static Vector2D shipPoints[] = { 
	Vector2D(-15.0f,-20.0f), Vector2D(-15.0f,0.0f), Vector2D(-5.0f,0.0f), Vector2D(0.0f,-15.0f),
	Vector2D(5.0f,0.0f), Vector2D(15.0f,0.0f), Vector2D(15.0f,-20.0f), Vector2D(25.0f,-10.0f),
	Vector2D(25.0f,10.0f), Vector2D(15.0f,20.0f), Vector2D(-15.0f,20.0f), Vector2D(-25.0f,10.0f),
	Vector2D(-25.0f,-10.0f)};

static Vector2D turret[] = {
	Vector2D(-2.0f, -2.0f), Vector2D(-2.0f, 2.0f), 
	Vector2D(25.0f, 2.0f), Vector2D(25.0f, -2.0f)};

static const int maxVelocity = 15;
static const int maxMode = 3;
static const int maxBulletCount = 10;
static const int turretLength = 25;
static const int numParticles = 50;
static const float rotateAmount = .09f;
static const float fireRate = .15f;

static const int numShipLines = sizeof(shipPoints)/sizeof(*shipPoints);
static const int numberTurretPoints = sizeof(turret)/sizeof(*turret);
static const int numberParticlEffects = sizeof(thrusterTrail)/sizeof(*thrusterTrail);

class Spaceship: public GameObject
{
	Vector2D originalPosition;
	bool fueling, alive;
public:
	Vector2D* turretPoints;
	Bullets* bullets;
	int numBulletPoints;
	float angle;
	float timeFromLastShot;
	int numTurretPoints;
	int mode;
	Spaceship(Vector2D start);
	~Spaceship();
	void Draw (Core::Graphics& graphics);
	void DrawTurret (Core::Graphics& graphics, Matrix3D turretTransform);
	void DrawBullets(Core::Graphics& graphics);
	void DrawInstruction (Core::Graphics& graphics);
	void update(float dt, const int SCREEN_HEIGHT, const int SCREEN_WIDTH, Vector2D*);
	void findVelocity(bool up, bool down, float dt);
	void wrapping(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
	void bouncing(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
	void hitWall(Vector2D start, Vector2D finish, Vector2D newVelocity);
	void wallBounce(Vector2D perpWall);
	void setLife(bool life);
	void resetShip();
	void checkButtons(bool up, bool down, float dt);
	bool isFueling();
	void checkForFueling(Vector2D* fuelingStation);
	Matrix3D turretRotation(Vector2D mouse);
};