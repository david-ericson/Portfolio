#include "Puck.h"
#include "LightManager.h"
#include "PlayerManager.h"

float specExp = 50.0f;
glm::vec3 ambColor(.1f,.1f,.1f);
float blueZScore = 10.0f;
float redZScore = -10.0f;
float servDist = 1.75f;
glm::vec4 puckColor(.1f,.1f,.1f,1.0f);

void Puck::initialize(glm::vec3 start)
{
	EntityManager::addEntity(this);
	render = new RenderableComponent(this, "AirHockeyPuck.bin", "NormalMapVertexShader.glsl", "NormalMapFragmentShader.glsl", "white.png");
	GeneralGLWindow::addLightingUniforms(render, LightManager::getLight(0), &specExp, &ambColor, &puckColor);
	physics = new PhysicsComponent(this, &render->transform.position);
	physics->velocity = glm::vec3(0,0,-5.0f);
	physics->maxVelocity = 30.0f;
	physics->minVelocity = 2.0f;
	render->transform.position = start;
	render->transform.position.y = render->graphic->bounds.y/2-2;
	render->transform.scale = glm::vec3(.85f, 1.0f, .85f);
	render->graphic->addFramebufferID(0);
	render->graphic->addFramebufferID(1);
	addComponent(render);
	addComponent(physics);
	server = nullptr;
}

void Puck::update()
{
	if(server)
	{
		render->transform.position.x = server->render->transform.position.x;
		render->transform.position.z = server->left.x * servDist + server->startPoint.z + server->left.x*render->graphic->bounds.z/2;
		if(glm::length(physics->velocity) > 0)
		{
			server = nullptr;
			physics->minVelocity = 2.0f;
		}
	}
	QList<Player*> players = PlayerManager::getPlayers();
	for(int i=0; i<players.size(); i++)
	{
		checkCollision(players[i]);
		if(players[i]->teamNum == 0 && render->transform.position.z < redZScore)
		{
			players[i]->score->score++;
			physics->velocity = glm::vec3();
			physics->minVelocity = 0;
			server = players[1];
			server->render->transform.position = glm::vec3(server->startPoint.x, server->render->transform.position.y, server->startPoint.z);
		}
		else if(players[i]->teamNum == 1 && render->transform.position.z > blueZScore)
		{
			server = players[0];
			physics->velocity = glm::vec3();
			physics->minVelocity = 0;
			players[i]->score->score++;
			server->render->transform.position = glm::vec3(server->startPoint.x, server->render->transform.position.y, server->startPoint.z);
		}
	}
}

void Puck::checkCollision(Player* player)
{
	glm::vec3 posToCheck1(render->transform.position.x, 0, render->transform.position.z);
	glm::vec3 posToCheck2(player->render->transform.position.x, 0, player->render->transform.position.z);
	if(glm::distance(posToCheck1, posToCheck2) <= player->render->graphic->bounds.x/2+render->graphic->bounds.x/2)
	{
		glm::vec3 contactNormal = glm::normalize(posToCheck1-posToCheck2);
		glm::vec3 relativeVelocity = physics->velocity - player->physics->velocity;
		float separatingVel = glm::dot(relativeVelocity, contactNormal);
		if(separatingVel > 0)
			return;
		float newSepVel = -separatingVel;
		float deltaVelocity = newSepVel - separatingVel;
		float totalInverseMass = 1/physics->mass + 1/player->physics->mass;
		float impulse = deltaVelocity / totalInverseMass;
		glm::vec3 impulsePerIMass = contactNormal * impulse;
		physics->velocity = physics->velocity + impulsePerIMass * (1/physics->mass);
	}
}

Puck::~Puck()
{
}
