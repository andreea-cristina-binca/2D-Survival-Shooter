#include "lab_m1/tema1/tema1.h"

using namespace std;
using namespace m1;


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	logicSpace.x = 0;       // logic x
	logicSpace.y = 0;       // logic y
	logicSpace.width = 15;   // logic width
	logicSpace.height = 15;  // logic height

	player.setPosition(logicSpace.width / 2, logicSpace.height / 2);
	player.setParameters(0, 20, 1);

	fireRate = 0.5;
	timeToFire = 0;

	spawnEnemy = 3;
	timeToSpawn = 1.5;

	GenerateObstacles();

	healthMax = 6.0f;
	scoreMax = 6.0f;
	healthScale = 6.0f;
	scoreScale = 0.0f;

	spawnPickUp = 10;
	timePickUp = 10;

	fasterFireTime = 0;
	doubleScoreTime = 0;
	multiplier = 1;

	gameOver = false;

	// Mesh for map
	CreateMap();

	// Meshes for player
	CreatePlayer();

	// Mesh for enemies
	CreateEnemy();

	// Mesh for obstacles
	CreateObstacle();

	// Mesh for projectiles
	CreateProjectile();

	// Mesh for health bar and score bar
	CreateBars();

	// Mesh for pick-ups
	CreatePickUps();
}


void Tema1::CreateMap()
{
	Mesh* map = object2D::CreateSquare("map",
		glm::vec3(0.0f, 0.0f, 0.0f),
		4 * logicSpace.width,
		glm::vec3(0.6f, 0.6f, 0.6f),
		true);
	AddMeshToList(map);

	Mesh* mapOutline = object2D::CreateSquare("mapOutline",
		glm::vec3(0.0f, 0.0f, 0.1f),
		4 * logicSpace.width,
		glm::vec3(0.0f, 0.0f, 0.0f),
		false);
	AddMeshToList(mapOutline);

	Mesh* border = object2D::CreateSquare("border",
		glm::vec3(0.0f, 0.0f, 0.0f),
		4 * logicSpace.width,
		glm::vec3(0.1f, 0.0f, 0.8f),
		true);
	AddMeshToList(border);
}


void Tema1::CreatePlayer()
{
	Mesh* circle = object2D::CreateCircle("circle",
		glm::vec3(0.0f, 0.0f, 0.9f),
		1,
		50,
		glm::vec3(1.0f, 0.8f, 0.1f),
		true);
	AddMeshToList(circle);

	Mesh* circleOutline = object2D::CreateCircle("circleOutline",
		glm::vec3(0.0f, 0.0f, 0.8f),
		1,
		50,
		glm::vec3(0.0f, 0.0f, 0.0f));
	AddMeshToList(circleOutline);

	Mesh* circleHand = object2D::CreateCircle("circleHand",
		glm::vec3(0.0f, 0.0f, 1.1f),
		1,
		50,
		glm::vec3(1.0f, 0.8f, 0.1f),
		true);
	AddMeshToList(circleHand);

	Mesh* circleHandOutline = object2D::CreateCircle("circleHandOutline",
		glm::vec3(0.0f, 0.0f, 1.0f),
		1,
		50,
		glm::vec3(0.0f, 0.0f, 0.0f));
	AddMeshToList(circleHandOutline);
}


void Tema1::CreateEnemy()
{
	Mesh* enemy = object2D::CreateSquare("enemy",
		glm::vec3(0.0f, 0.0f, 0.4f),
		1,
		glm::vec3(0.8f, 0.0f, 0.2f),
		true);
	AddMeshToList(enemy);

	Mesh* enemyOutline = object2D::CreateSquare("enemyOutline",
		glm::vec3(0.0f, 0.0f, 0.5f),
		1,
		glm::vec3(0.0f, 0.0f, 0.0f),
		false);
	AddMeshToList(enemyOutline);

	Mesh* enemyHand = object2D::CreateSquare("enemyHand",
		glm::vec3(0.0f, 0.0f, 0.6f),
		1,
		glm::vec3(0.8f, 0.0f, 0.2f),
		true);
	AddMeshToList(enemyHand);

	Mesh* enemyHandOutline = object2D::CreateSquare("enemyHandOutline",
		glm::vec3(0.0f, 0.0f, 0.7f),
		1,
		glm::vec3(0.0f, 0.0f, 0.0f),
		false);
	AddMeshToList(enemyHandOutline);
}


void Tema1::CreateObstacle()
{
	Mesh* obstacle = object2D::CreateSquare("obstacle",
		glm::vec3(0.0f, 0.0f, 0.2f),
		1,
		glm::vec3(0.5f, 0.8f, 0.0f),
		true);
	AddMeshToList(obstacle);

	Mesh* obstacleOutline = object2D::CreateSquare("obstacleOutline",
		glm::vec3(0.0f, 0.0f, 0.3f),
		1,
		glm::vec3(0.0f, 0.0f, 0.0f),
		false);
	AddMeshToList(obstacleOutline);
}


void Tema1::CreateProjectile()
{
	Mesh* bullet = object2D::CreateSquare("bullet",
		glm::vec3(0.0f, 0.0f, 0.3f),
		1,
		glm::vec3(0.0f, 0.0f, 0.0f),
		true);
	AddMeshToList(bullet);
}


void Tema1::CreateBars()
{
	// Health bar
	Mesh* health = object2D::CreateSquare("health",
		glm::vec3(0.0f, 0.0f, 1.5f),
		1,
		glm::vec3(0.7f, 0.1f, 0.1f),
		true);
	AddMeshToList(health);

	Mesh* healthOutline = object2D::CreateSquare("healthOutline",
		glm::vec3(0.0f, 0.0f, 1.5f),
		1,
		glm::vec3(0.7f, 0.1f, 0.1f),
		false);
	AddMeshToList(healthOutline);

	// Score bar
	Mesh* score = object2D::CreateSquare("score",
		glm::vec3(0.0f, 0.0f, 1.5f),
		1,
		glm::vec3(0.3f, 0.8f, 0.8f),
		true);
	AddMeshToList(score);

	Mesh* scoreOutline = object2D::CreateSquare("scoreOutline",
		glm::vec3(0.0f, 0.0f, 1.5f),
		1,
		glm::vec3(0.3f, 0.8f, 0.8f),
		false);
	AddMeshToList(scoreOutline);
}


void Tema1::CreatePickUps()
{
	// Mesh for heal pick-up
	Mesh* heal = object2D::CreateSquare("heal",
		glm::vec3(0.0f, 0.0f, 0.5f),
		1,
		glm::vec3(0.7f, 0.1f, 0.1f),
		true);
	AddMeshToList(heal);

	// Mesh for extra fire rate pick-up
	Mesh* firerate = object2D::CreateSquare("firerate",
		glm::vec3(0.0f, 0.0f, 0.5f),
		1,
		glm::vec3(0.9f, 0.3f, 0.0f),
		true);
	AddMeshToList(firerate);

	// Mesh for score multiplier pick-up
	Mesh* multiplier = object2D::CreateSquare("multiplier",
		glm::vec3(0.0f, 0.0f, 0.5f),
		1,
		glm::vec3(0.3f, 0.8f, 0.8f),
		true);
	AddMeshToList(multiplier);

	// Mesh for outlines
	Mesh* pickupOutline = object2D::CreateSquare("pickupOutline",
		glm::vec3(0.0f, 0.0f, 0.6f),
		1,
		glm::vec3(0.0f, 0.0f, 0.0f),
		false);
	AddMeshToList(pickupOutline);

	// Mesh for symbols
	Mesh* pickupSymbol = object2D::CreateSquare("pickupSymbol",
		glm::vec3(0.0f, 0.0f, 0.6f),
		1,
		glm::vec3(1.0f, 1.0f, 1.0f),
		true);
	AddMeshToList(pickupSymbol);
}


void Tema1::GenerateObstacles()
{
	Obstacle ob1;
	ob1.setPosition(0.0f, 30.0f);
	ob1.setScale(30.0f, 3.0f);
	obstacles.push_back(ob1);

	Obstacle ob2;
	ob2.setPosition(25.0f, 10.0f);
	ob2.setScale(1.0f, 6.5f);
	obstacles.push_back(ob2);

	Obstacle ob3;
	ob3.setPosition(15.0f, 15.0f);
	ob3.setScale(5.0f, 5.0f);
	obstacles.push_back(ob3);

	Obstacle ob4;
	ob4.setPosition(-21.0f, 13.0f);
	ob4.setScale(8.0f, 2.5f);
	obstacles.push_back(ob4);

	Obstacle ob5;
	ob5.setPosition(-13.0f, 21.0f);
	ob5.setScale(3.0f, 4.5f);
	obstacles.push_back(ob5);

	Obstacle ob6;
	ob6.setPosition(-25.0f, 25.0f);
	ob6.setScale(3.0f, 3.0f);
	obstacles.push_back(ob6);

	Obstacle ob7;
	ob7.setPosition(0.0f, 18.0f);
	ob7.setScale(1.0f, 10.f);
	obstacles.push_back(ob7);

	Obstacle ob8;
	ob8.setPosition(-5.0f, 5.0f);
	ob8.setScale(2.0f, 5.0f);
	obstacles.push_back(ob8);

	Obstacle ob9;
	ob9.setPosition(-15.0f, -15.0f);
	ob9.setScale(10.0f, 10.0f);
	obstacles.push_back(ob9);

	Obstacle ob10;
	ob10.setPosition(0.0f, -7.0f);
	ob10.setScale(5.0f, 6.0f);
	obstacles.push_back(ob10);

	Obstacle ob11;
	ob11.setPosition(-20.0f, 0.0f);
	ob11.setScale(5.0f, 6.0f);
	obstacles.push_back(ob11);

	Obstacle ob12;
	ob12.setPosition(5.0f, -25.0f);
	ob12.setScale(20.0f, 1.0f);
	obstacles.push_back(ob12);

	Obstacle ob13;
	ob13.setPosition(15.0f, -13.0f);
	ob13.setScale(4.0f, 7.0f);
	obstacles.push_back(ob13);

	Obstacle ob14;
	ob14.setPosition(17.0f, 0.0f);
	ob14.setScale(6.0f, 3.0f);
	obstacles.push_back(ob14);

	Obstacle ob15;
	ob15.setPosition(20.0f, -30.0f);
	ob15.setScale(2.0f, 5.0f);
	obstacles.push_back(ob15);

	Obstacle ob16;
	ob16.setPosition(-15.0f, -30.0f);
	ob16.setScale(5.0f, 5.0f);
	obstacles.push_back(ob16);
}


glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
	float sx, sy, tx, ty, smin;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	if (sx < sy)
		smin = sx;
	else
		smin = sy;
	tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
	ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

	return glm::transpose(glm::mat3(
		smin, 0.0f, tx,
		0.0f, smin, ty,
		0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	GetSceneCamera()->Update();
}


void Tema1::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Tema1::ProjectileUpdate(float deltaTimeSeconds)
{
	// Calculate projectiles trajectories
	auto it = projectiles.begin();
	while (it != projectiles.end()) {
		bool go = true;
		if (it->distance) {
			it->positionX += it->speed * deltaTimeSeconds * cos(it->rotation);
			it->positionY += it->speed * deltaTimeSeconds * sin(it->rotation);
			it->distance--;

			// Check collision with enemy
			auto en = enemies.begin();
			while (en != enemies.end() && go) {
				if (abs(it->positionX - en->positionX) < 0.4f + en->dimension * en->scaleX / 2 &&
					abs(it->positionY - en->positionY) < 0.2f + en->dimension * en->scaleY / 2) {
					en = enemies.erase(en);
					go = false;
					scoreScale += multiplier * 0.5f;
				}
				else
					en++;
			}

			// Check collision with obstacles
			for (const Obstacle& ob : obstacles) {
				if (abs(it->positionX - ob.positionX) < 0.4f + ob.dimension * ob.scaleX / 2 &&
					abs(it->positionY - ob.positionY) < 0.2f + ob.dimension * ob.scaleY / 2)
					go = false;
			}

			// Check collision with map edges
			if (it->positionY + 0.4f > 2.0f * logicSpace.width * 1.25f ||
				it->positionY - 0.4f < -2.0f * logicSpace.width * 1.25f ||
				it->positionX - 0.8f < -2.0f * logicSpace.width ||
				it->positionX + 0.8f > 2.0f * logicSpace.width)
				go = false;
		}
		else
			go = false;

		if (go)
			it++;
		else
			it = projectiles.erase(it);
	}
	timeToFire -= deltaTimeSeconds;
}


void Tema1::EnemyUpdate(float deltaTimeSeconds)
{
	// Spawn enemies
	if (timeToSpawn <= 0.0f) {
		float x = (float)(-25 + rand() % (25 - (-25)));
		float y = (float)(-30 + rand() % (30 - (-30)));
		float r = atan2(player.positionY - y, player.positionX - x);
		float d = 1.0f;
		float s = (float)(10 + rand() % (15 - 10));

		Character enemy;
		enemy.setPosition(x, y);
		enemy.setParameters(r, s, d);
		enemy.setScale(1.5f, 1.5f);

		enemies.push_back(enemy);
		timeToSpawn = spawnEnemy;
	}
	else
		timeToSpawn -= deltaTimeSeconds;

	// Move enemies
	auto en = enemies.begin();
	while (en != enemies.end()) {
		en->positionX += en->speed * deltaTimeSeconds * cos(en->rotation);
		en->positionY += en->speed * deltaTimeSeconds * sin(en->rotation);
		en->rotation = atan2(player.positionY - en->positionY, player.positionX - en->positionX);

		// Check collision with map edges
		if (en->positionY + en->dimension / 2 > 2.0f * logicSpace.width * 1.25f ||
			en->positionY - en->dimension / 2 < -2.0f * logicSpace.width * 1.25f ||
			en->positionX - en->dimension / 2 < -2.0f * logicSpace.width ||
			en->positionX + en->dimension / 2 > 2.0f * logicSpace.width) {
			en->positionX -= en->speed * deltaTimeSeconds * cos(en->rotation);
			en->positionY -= en->speed * deltaTimeSeconds * sin(en->rotation);
		}

		// Check collision with player
		if (abs(player.positionX - en->positionX) < player.dimension + en->dimension * en->scaleX / 2 &&
			abs(player.positionY - en->positionY) < player.dimension + en->dimension * en->scaleY / 2) {
			en = enemies.erase(en);
			healthScale -= 0.5f;
		}
		else
			en++;
	}
}


void Tema1::PickUpUpdate(float deltaTimeSeconds)
{
	// Spawn pick-ups
	if (timePickUp <= 0.0f) {
		bool go = false;
		float x = 0, y = 0;

		// Generate position that isn't inside an obstacle
		while (go == false) {
			x = (float)(-25 + rand() % (25 - (-25)));
			y = (float)(-30 + rand() % (30 - (-30)));

			go = true;
			for (const Obstacle& ob : obstacles) {
				if (abs(x - ob.positionX) < 0.5f + ob.dimension * ob.scaleX / 2 &&
					abs(y - ob.positionY) < 0.5f + ob.dimension * ob.scaleY / 2)
					go = false;

			}
		}

		float prob = (float)(1 + rand() % (100 - 1));
		int t;
		if (prob <= 30)
			t = 1;
		else if (prob <= 40)
			t = 2;
		else if (prob <= 70)
			t = 3;
		else
			t = 4;

		PickUp pick(x, y, t);
		pickUps.push_back(pick);

		timePickUp = spawnPickUp;
	}
	else
		timePickUp -= deltaTimeSeconds;

	// Verify if pick-up is to be used
	auto pick = pickUps.begin();
	while (pick != pickUps.end()) {
		// Check collision with player
		if (abs(player.positionX - pick->positionX) < player.dimension + 0.5f &&
			abs(player.positionY - pick->positionY) < player.dimension + 0.5f) {
			switch (pick->type) {
			case 1:
				// increase a bit of health
				healthScale += 0.5f;
				break;
			case 2:
				// increase health to full
				healthScale = healthMax;
				break;
			case 3:
				// increase fire rate for some time
				fasterFireTime = 10;
				fireRate = 0.2f;
				break;
			case 4:
				// double the score when hitting enemies for some time
				doubleScoreTime = 10;
				multiplier = 2;
				break;
			default:
				break;
			}

			pick = pickUps.erase(pick);
		}
		else
			pick++;
	}

	// Verify active pick-ups
	if (fasterFireTime <= 0)
		fireRate = 0.5f;
	else
		fasterFireTime -= deltaTimeSeconds;

	if (doubleScoreTime <= 0)
		multiplier = 1;
	else
		doubleScoreTime -= deltaTimeSeconds;
}

void Tema1::VerifyGameState()
{
	if (healthScale == 0.0f) {
		cout << "-------------" << endl;
		cout << "| YOU LOST! |" << endl;
		cout << "| GAME OVER |" << endl;
		cout << "-------------" << endl;
		gameOver = true;
	}

	if (scoreScale == scoreMax) {
		cout << "------------" << endl;
		cout << "| YOU WON! |" << endl;
		cout << "| GOOD JOB |" << endl;
		cout << "------------" << endl;
		gameOver = true;
	}
}


void Tema1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	// Sets the screen area where to draw
	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
	SetViewportArea(viewSpace, glm::vec3(0), true);

	// Compute uniform 2D visualization matrix
	visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);

	// Calclate projectile trajectories and check for collisions
	ProjectileUpdate(deltaTimeSeconds);

	// Spawn, move enemies and check for collisions
	EnemyUpdate(deltaTimeSeconds);

	// Spawn pick-ups
	PickUpUpdate(deltaTimeSeconds);

	// Verify if the game is over
	VerifyGameState();

	if (gameOver) {
		window->Close();
	}

	// Render the scene
	DrawScene(visMatrix);

	// Initialize minimap
	LogicSpace new_ls;
	new_ls.x = -2.0f * logicSpace.width * 1.05f;
	new_ls.y = -2.0f * logicSpace.height * 1.25f * 1.05f;
	new_ls.width = 4.0f * logicSpace.width * 1.05f;
	new_ls.height = 4.0f * logicSpace.height * 1.25f * 1.05f;

	viewSpace = ViewportSpace(0, 0, resolution.x / 5.1, resolution.y / 2.3);
	SetViewportArea(viewSpace, glm::vec3(0), true);

	visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2DUnif(new_ls, viewSpace);

	// Render the minimap
	DrawMinimap(visMatrix);
}


void Tema1::FrameEnd()
{
}


void Tema1::RenderMap(const glm::mat3& visMatrix)
{
	modelMatrix = visMatrix;

	// Render map
	modelMatrix *= transform2D::Scale(1.0f, 1.25f);
	RenderMesh2D(meshes["map"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["mapOutline"], shaders["VertexColor"], modelMatrix);

	modelMatrix *= transform2D::Scale(1.05f, 1.05f);
	RenderMesh2D(meshes["border"], shaders["VertexColor"], modelMatrix);
}


void Tema1::RenderPlayer(const glm::mat3& visMatrix)
{
	glm::mat3 originalMatrix;

	modelMatrix = visMatrix;

	// Render player piece by piece
	modelMatrix *= transform2D::Translate(player.positionX, player.positionY);
	modelMatrix *= transform2D::Rotate(player.rotation);
	originalMatrix = modelMatrix;
	modelMatrix *= transform2D::Scale(0.8f, 0.8f);
	RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

	modelMatrix = originalMatrix;
	modelMatrix *= transform2D::Scale(0.85f, 0.85f);
	RenderMesh2D(meshes["circleOutline"], shaders["VertexColor"], modelMatrix);

	modelMatrix = originalMatrix;
	modelMatrix *= transform2D::Translate(0.7f, 0.6f);
	modelMatrix *= transform2D::Scale(0.3f, 0.3f);
	RenderMesh2D(meshes["circleHand"], shaders["VertexColor"], modelMatrix);

	modelMatrix = originalMatrix;
	modelMatrix *= transform2D::Translate(0.7f, 0.6f);
	modelMatrix *= transform2D::Scale(0.35f, 0.35f);
	RenderMesh2D(meshes["circleHandOutline"], shaders["VertexColor"], modelMatrix);

	modelMatrix = originalMatrix;
	modelMatrix *= transform2D::Translate(0.7f, -0.6f);
	modelMatrix *= transform2D::Scale(0.3f, 0.3f);
	RenderMesh2D(meshes["circleHand"], shaders["VertexColor"], modelMatrix);

	modelMatrix = originalMatrix;
	modelMatrix *= transform2D::Translate(0.7f, -0.6f);
	modelMatrix *= transform2D::Scale(0.35f, 0.35f);
	RenderMesh2D(meshes["circleHandOutline"], shaders["VertexColor"], modelMatrix);

}


void Tema1::RenderEnemy(const glm::mat3& visMatrix)
{
	for (const Character& enemy : enemies) {
		glm::mat3 originalMatrix;

		modelMatrix = visMatrix;

		// Render enemy piece by piece
		modelMatrix *= transform2D::Translate(enemy.positionX, enemy.positionY);
		modelMatrix *= transform2D::Rotate(enemy.rotation);
		originalMatrix = modelMatrix;
		modelMatrix *= transform2D::Scale(1.5f, 1.5f);
		RenderMesh2D(meshes["enemy"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["enemyOutline"], shaders["VertexColor"], modelMatrix);

		modelMatrix = originalMatrix;
		modelMatrix *= transform2D::Translate(0.8f, 0.6f);
		modelMatrix *= transform2D::Scale(0.6f, 0.6f);
		RenderMesh2D(meshes["enemyHand"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["enemyHandOutline"], shaders["VertexColor"], modelMatrix);

		modelMatrix = originalMatrix;
		modelMatrix *= transform2D::Translate(0.8f, -0.6f);
		modelMatrix *= transform2D::Scale(0.6f, 0.6f);
		RenderMesh2D(meshes["enemyHand"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["enemyHandOutline"], shaders["VertexColor"], modelMatrix);
	}
}


void Tema1::RenderObstacle(const glm::mat3& visMatrix)
{
	for (const Obstacle& ob : obstacles) {
		modelMatrix = visMatrix;
		modelMatrix *= transform2D::Translate(ob.positionX, ob.positionY);
		modelMatrix *= transform2D::Scale(ob.scaleX, ob.scaleY);
		RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["obstacleOutline"], shaders["VertexColor"], modelMatrix);
	}
}


void Tema1::RenderProjectile(const glm::mat3& visMatrix)
{
	for (const Projectile& bullet : projectiles) {
		modelMatrix = visMatrix;
		modelMatrix *= transform2D::Translate(bullet.positionX, bullet.positionY);
		modelMatrix *= transform2D::Rotate(bullet.rotation);
		modelMatrix *= transform2D::Scale(0.8f, 0.4f);
		RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
	}
}


void Tema1::RenderBars(const glm::mat3& visMatrix)
{
	// Render health bar
	modelMatrix = visMatrix;
	modelMatrix *= transform2D::Translate(player.positionX + 8.0f + (healthMax - healthScale) / 2, player.positionY + 6.0f);
	modelMatrix *= transform2D::Scale(healthScale, 1.5f);
	RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);
	modelMatrix = visMatrix;
	modelMatrix *= transform2D::Translate(player.positionX + 8.0f, player.positionY + 6.0f);
	modelMatrix *= transform2D::Scale(healthMax, 1.5f);
	RenderMesh2D(meshes["healthOutline"], shaders["VertexColor"], modelMatrix);

	// Render score bar
	modelMatrix = visMatrix;
	modelMatrix *= transform2D::Translate(player.positionX - 8.0f - (scoreMax - scoreScale) / 2, player.positionY + 6.0f);
	modelMatrix *= transform2D::Scale(scoreScale, 1.5f);
	RenderMesh2D(meshes["score"], shaders["VertexColor"], modelMatrix);
	modelMatrix = visMatrix;
	modelMatrix *= transform2D::Translate(player.positionX - 8.0f, player.positionY + 6.0f);
	modelMatrix *= transform2D::Scale(scoreMax, 1.5f);
	RenderMesh2D(meshes["scoreOutline"], shaders["VertexColor"], modelMatrix);
}


void Tema1::RenderPickUps(const glm::mat3& visMatrix)
{
	for (const PickUp& pick : pickUps) {

		switch (pick.type) {
		case 1:
			// Render heal pick-up
			modelMatrix = visMatrix;
			modelMatrix *= transform2D::Translate(pick.positionX, pick.positionY);
			RenderMesh2D(meshes["heal"], shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["pickupOutline"], shaders["VertexColor"], modelMatrix);
			modelMatrix *= transform2D::Scale(0.1f, 0.5f);
			RenderMesh2D(meshes["pickupSymbol"], shaders["VertexColor"], modelMatrix);
			modelMatrix *= transform2D::Scale(1.0f / 0.1f, 1.0f / 0.5f);
			modelMatrix *= transform2D::Scale(0.5f, 0.1f);
			RenderMesh2D(meshes["pickupSymbol"], shaders["VertexColor"], modelMatrix);
			break;
		case 2:
			// Render mega heal pick-up
			modelMatrix = visMatrix;
			modelMatrix *= transform2D::Translate(pick.positionX, pick.positionY);
			RenderMesh2D(meshes["heal"], shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["pickupOutline"], shaders["VertexColor"], modelMatrix);
			modelMatrix *= transform2D::Scale(0.3f, 0.1f);
			RenderMesh2D(meshes["pickupSymbol"], shaders["VertexColor"], modelMatrix);
			modelMatrix *= transform2D::Scale(1.0f / 0.3f, 1.0f / 0.1f);
			modelMatrix *= transform2D::Translate(-0.2f, 0);
			modelMatrix *= transform2D::Scale(0.1f, 0.5f);
			RenderMesh2D(meshes["pickupSymbol"], shaders["VertexColor"], modelMatrix);
			modelMatrix *= transform2D::Scale(1.0f / 0.1f, 1.0f / 0.5f);
			modelMatrix *= transform2D::Translate(0.4f, 0);
			modelMatrix *= transform2D::Scale(0.1f, 0.5f);
			RenderMesh2D(meshes["pickupSymbol"], shaders["VertexColor"], modelMatrix);
			break;
		case 3:
			// Render fire rate pick-up
			modelMatrix = visMatrix;
			modelMatrix *= transform2D::Translate(pick.positionX, pick.positionY);
			RenderMesh2D(meshes["firerate"], shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["pickupOutline"], shaders["VertexColor"], modelMatrix);
			modelMatrix *= transform2D::Scale(0.4f, 0.1f);
			RenderMesh2D(meshes["pickupSymbol"], shaders["VertexColor"], modelMatrix);
			break;
		case 4:
			// Render multiplier pick-up
			modelMatrix = visMatrix;
			modelMatrix *= transform2D::Translate(pick.positionX, pick.positionY);
			RenderMesh2D(meshes["multiplier"], shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["pickupOutline"], shaders["VertexColor"], modelMatrix);
			modelMatrix *= transform2D::Rotate(AI_MATH_PI / 4);
			modelMatrix *= transform2D::Scale(0.5f, 0.1f);
			RenderMesh2D(meshes["pickupSymbol"], shaders["VertexColor"], modelMatrix);
			modelMatrix *= transform2D::Scale(1.0f / 0.5f, 1.0f / 0.1f);
			modelMatrix *= transform2D::Rotate(-AI_MATH_PI / 2);
			modelMatrix *= transform2D::Scale(0.5f, 0.1f);
			RenderMesh2D(meshes["pickupSymbol"], shaders["VertexColor"], modelMatrix);
			break;
		default:
			break;
		}
	}
}


void Tema1::DrawScene(glm::mat3 visMatrix)
{
	// Render map
	RenderMap(visMatrix);

	// Render player
	RenderPlayer(visMatrix);

	// Render enemy
	RenderEnemy(visMatrix);

	// Render obstacles
	RenderObstacle(visMatrix);

	// Render projectiles
	RenderProjectile(visMatrix);

	// Render health and score bars
	RenderBars(visMatrix);

	// Render pick-ups
	RenderPickUps(visMatrix);
}


void Tema1::DrawMinimap(glm::mat3 visMatrix)
{
	// Render map
	RenderMap(visMatrix);

	// Render player
	RenderPlayer(visMatrix);

	// Render enemy
	RenderEnemy(visMatrix);

	// Render obstacles
	RenderObstacle(visMatrix);

	// Render pick-ups
	RenderPickUps(visMatrix);
}


void Tema1::PlayerCollisionsUp(float deltaTime) {
	bool go = true;

	if (player.positionY + player.dimension + player.speed * deltaTime > 2.0f * logicSpace.width * 1.25f)
		go = false;

	for (const Obstacle& ob : obstacles) {
		if (abs(player.positionX - ob.positionX) < player.dimension + ob.dimension * ob.scaleX / 2 &&
			abs(player.positionY + player.speed * deltaTime - ob.positionY) < player.dimension + ob.dimension * ob.scaleY / 2)
			go = false;
	}

	if (go) {
		logicSpace.y += player.speed * deltaTime;
		player.positionY += player.speed * deltaTime;
	}
}


void Tema1::PlayerCollisionsDown(float deltaTime) {
	bool go = true;

	if (player.positionY - player.dimension - player.speed * deltaTime < -2.0f * logicSpace.width * 1.25f)
		go = false;

	for (const Obstacle& ob : obstacles) {
		if (abs(player.positionX - ob.positionX) < player.dimension + ob.dimension * ob.scaleX / 2 &&
			abs(player.positionY - player.speed * deltaTime - ob.positionY) < player.dimension + ob.dimension * ob.scaleY / 2)
			go = false;
	}

	if (go) {
		logicSpace.y -= player.speed * deltaTime;
		player.positionY -= player.speed * deltaTime;
	}
}


void Tema1::PlayerCollisionsLeft(float deltaTime) {
	bool go = true;

	if (player.positionX - player.dimension - player.speed * deltaTime < -2.0f * logicSpace.width)
		go = false;

	for (const Obstacle& ob : obstacles) {
		if (abs(player.positionX - player.speed * deltaTime - ob.positionX) < player.dimension + ob.dimension * ob.scaleX / 2 &&
			abs(player.positionY - ob.positionY) < player.dimension + ob.dimension * ob.scaleY / 2)
			go = false;
	}

	if (go) {
		logicSpace.x -= player.speed * deltaTime;
		player.positionX -= player.speed * deltaTime;
	}
}


void Tema1::PlayerCollisionsRight(float deltaTime) {
	bool go = true;

	if (player.positionX + player.dimension + player.speed * deltaTime > 2.0f * logicSpace.width)
		go = false;

	for (const Obstacle& ob : obstacles) {
		if (abs(player.positionX + player.speed * deltaTime - ob.positionX) < player.dimension + ob.dimension * ob.scaleX / 2 &&
			abs(player.positionY - ob.positionY) < player.dimension + ob.dimension * ob.scaleY / 2)
			go = false;
	}

	if (go) {
		logicSpace.x += player.speed * deltaTime;
		player.positionX += player.speed * deltaTime;
	}
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	// Move the logic window
	if (window->KeyHold(GLFW_KEY_W)) {
		PlayerCollisionsUp(deltaTime);
	}
	if (window->KeyHold(GLFW_KEY_A)) {
		PlayerCollisionsLeft(deltaTime);
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		PlayerCollisionsDown(deltaTime);
	}
	if (window->KeyHold(GLFW_KEY_D)) {
		PlayerCollisionsRight(deltaTime);
	}
}


void Tema1::OnKeyPress(int key, int mods)
{
}


void Tema1::OnKeyRelease(int key, int mods)
{
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	player.rotation = -atan2((float)mouseY - ((float)window->GetResolution().y / 2),
		(float)mouseX - ((float)window->GetResolution().x / 2));
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (timeToFire <= 0) {
		Projectile bullet(player.positionX, player.positionY, player.rotation, 30, 20);
		projectiles.push_back(bullet);
		timeToFire = fireRate;
	}
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
