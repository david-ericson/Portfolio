#include "PlayerManager.h"
#include "LightManager.h"
#include <glm\gtx\transform.hpp>
#include <Windows.h>

QList<Player*> players;
QList<PlayerPanel*> panels;
float playerVel = 15.0f;
float forwardVel = 20.0f;
float playerSpec = 30.0f;
glm::vec3 playerAmb(.1f,.1f,.1f);
float wallLoc = 7.0f;
int	CURRENT_TEAM_NUMBER = 0;

PlayerScore::PlayerScore(glm::vec3 color, int teamNum)
{
	EntityManager::addEntity(this);
	render = new RenderableComponent(this, "Plane.bin", "HUDVertexShader.glsl", "TextFragmentShader.glsl", "pebbles.png");
	addComponent(render);
	score = 0;
	color = (teamNum == 0)?glm::vec3(255.0f, 56.0f,56.0f):glm::vec3(0,153.0f,255.0f);
	text = new TextComponent(this, .1f, render->graphic->getTexture(), &score, TextComponent::followInt, 1, color);
	render->transform.scale = glm::vec3(.4f, 1.0f, .2f);
	render->transform.rotate.x = 270.0f;
	glm::vec3 pos = (teamNum == 0)?glm::vec3(-.7f,.9f, -.98f):glm::vec3(1.0f,.9f,-.98f);
	render->transform.position = pos;
	addComponent(text);
}

PlayerScore::~PlayerScore(){}

void Player::initialize(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	isMovingBackward = false;
	isMovingForward = false;
	score = 0;
	EntityManager::addEntity(this);
	teamNum = CURRENT_TEAM_NUMBER++%2;
	
	teamColor = (teamNum == 0)?glm::vec4(1.0f,0,0,1.0f):glm::vec4(0,0,1.0f,1.0f);
	score = new PlayerScore(glm::vec3(teamColor), teamNum);

	left = glm::vec3(-1.0f,0,0);
	render = new RenderableComponent(this, "AirHockeyPaddle.bin", "NormalMapVertexShader.glsl", "NormalMapFragmentShader.glsl");
	GeneralGLWindow::addLightingUniforms(render, LightManager::getLight(0), &playerSpec, &playerAmb, &teamColor);
	render->transform.position = pos;
	render->transform.position.y = render->graphic->bounds.y/2 - 2;
	render->transform.rotate = rot;
	render->transform.scale = scale;
	render->update();
	if(teamNum == 0)
	{
		leftKey = 65;
		rightKey = 68;
		hitKey = 87;
	}
	else if(teamNum == 1)
	{
		leftKey = 37;
		rightKey = 39;
		hitKey = 38;
	}
	left = glm::vec3(glm::rotate(rot.y, glm::vec3(0,1.0f,0))*glm::vec4(left,0));
	addComponent(render);
	physics = new PhysicsComponent(this, &render->transform.position);
	physics->mass = 2.0f;
	input = new InputComponent(this);
	input->addInput(leftKey, fastdelegate::MakeDelegate(this, &Player::moveLeft), fastdelegate::MakeDelegate(this, &Player::slowDown));
	input->addInput(rightKey, fastdelegate::MakeDelegate(this, &Player::moveRight), fastdelegate::MakeDelegate(this, &Player::slowDown));
	input->addInput(hitKey, fastdelegate::MakeDelegate(this, &Player::moveForward));
	startPoint = pos;
	addComponent(physics);
	addComponent(input);
	render->graphic->addFramebufferID(0);
	render->graphic->addFramebufferID(1);
	/*if(panels.size() == 0)
	{
		panels.push_back(new PlayerPanel(teamNum));
	}*/
}

void Player::moveLeft()
{
	physics->setAcc(left*playerVel*.25f, 30.0f);
	physics->velocity.x = (glm::abs(physics->velocity.x) < glm::abs(left.x*playerVel) || physics->velocity.x * left.x < 0)?(left*playerVel).x:physics->velocity.x;
}

void Player::moveRight()
{
	physics->setAcc((-left*playerVel*.25f), 30.0f);
	physics->velocity.x = (glm::abs(physics->velocity.x) < glm::abs(left.x*playerVel) || physics->velocity.x * left.x < 0)?(-1.0f*left*playerVel).x:physics->velocity.x;
}

void Player::moveForward()
{
	if(!isMovingForward)
	{
		glm::vec3 forward = glm::vec3(-left.z, 0, left.x);
		if(physics->isDecellerating)
		{
			physics->isDecellerating = false;
			physics->acceleration = glm::vec3();
		}
		physics->velocity += forward*forwardVel;
		isMovingForward = true;
	}
}

void Player::slowDown()
{
	if(!GetAsyncKeyState(leftKey) && !GetAsyncKeyState(rightKey) && !isMovingForward)
	{
		physics->setAcc(glm::vec3(playerVel*6.0f,0,0), 30.0f, true);
	}
}

void Player::update()
{
	if(isMovingForward && glm::abs(render->transform.position.z - startPoint.z) >= 3.0f && !isMovingBackward)
	{
		isMovingBackward = true;
		render->transform.position.z = left.x*3.0f+startPoint.z;
		physics->velocity.z = -left.x*forwardVel;
	}
	else if(isMovingBackward && isMovingForward && glm::dot(glm::vec3(0,0,left.x), glm::vec3(0,0,render->transform.position.z-startPoint.z)) < 0)
	{
		render->transform.position.z = startPoint.z;
		isMovingBackward = false;
		isMovingForward = false;
		physics->velocity.z = 0;
	}
	if(render->transform.position.x+render->graphic->bounds.x/2+.5f>wallLoc)
	{
		render->transform.position.x = wallLoc-render->graphic->bounds.x/2-.5f;
		physics->acceleration.x = 0;
		physics->velocity.x = 0;
	}
	else if(render->transform.position.x-render->graphic->bounds.x/2-.5f<-wallLoc)
	{
		render->transform.position.x = -wallLoc+render->graphic->bounds.x/2+.5f;
		physics->acceleration.x = 0;
		physics->velocity.x = 0;
	}
}

Player::~Player()
{
	delete score;
}

PlayerPanel::PlayerPanel(int teamNum)
{
	GeneralGLWindow::addPass(512, 512, (teamNum == 1)? GeneralGLWindow::addCamera(glm::vec3(0,9.5f, -11.0f), glm::vec3(0, -1.5f, 1.0f)):nullptr);
	EntityManager::addEntity(this);
	render = new RenderableComponent(this, "Plane2.bin", "HUDVertexShader.glsl", "TextureFragmentShader.glsl", "checkerboard.png");
	render->transform.position.z = -.97f;
	render->graphic->setTexture(GeneralGLWindow::addFrameBufferTexture(GL_RGBA));
	glm::vec3 pos = (teamNum == 0)?glm::vec3(-.5f, 0, -.97f):glm::vec3(.5f,0,-.97f);
	render->transform.position = pos;
	render->transform.scale = glm::vec3(1.0f, 1.0f, 2.0f);
	render->transform.rotate.x = 90.0f;
	addComponent(render);
}

void PlayerManager::createPlayer(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	Player* player = new Player;
	player->initialize(pos, rot, scale);
	players.push_back(player);
}

QList<Player*> PlayerManager::getPlayers()
{
	return players;
}

void PlayerManager::shutdown()
{
	while(players.size() > 0)
	{
		delete players.first();
		players.removeFirst();
	}
	while(panels.size() > 0)
	{
		delete panels.first();
		panels.removeFirst();
	}
}

void PlayerManager::resetGame()
{
	for(int i=0; i<players.size(); i++)
	{
		players[i]->score->score = 0;
	}
}

void PlayerManager::update()
{
	for(int i=0; i<players.size(); i++)
	{
		players[i]->update();
	}
	if(GetAsyncKeyState(VK_SPACE))
	{
		resetGame();
	}
}
