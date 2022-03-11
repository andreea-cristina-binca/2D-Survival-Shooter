#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema1/projectile.h"
#include "lab_m1/tema1/character.h"
#include "lab_m1/tema1/obstacle.h"
#include "lab_m1/tema1/pickup.h"
#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"

#include <vector>
#include <iostream>


namespace m1
{
	class Tema1 : public gfxc::SimpleScene
	{
	public:
		struct ViewportSpace
		{
			ViewportSpace() : x(0), y(0), width(1), height(1) {}
			ViewportSpace(int x, int y, int width, int height)
				: x(x), y(y), width(width), height(height) {}
			int x;
			int y;
			int width;
			int height;
		};

		struct LogicSpace
		{
			LogicSpace() : x(0), y(0), width(1), height(1) {}
			LogicSpace(float x, float y, float width, float height)
				: x(x), y(y), width(width), height(height) {}
			float x;
			float y;
			float width;
			float height;
		};

	public:
		Tema1();
		~Tema1();

		void Init() override;
		void CreateMap();
		void CreatePlayer();
		void CreateEnemy();
		void CreateObstacle();
		void CreateProjectile();
		void CreateBars();
		void CreatePickUps();
		void GenerateObstacles();

	private:
		void FrameStart() override;
		void ProjectileUpdate(float deltaTimeSeconds);
		void EnemyUpdate(float deltaTimeSeconds);
		void PickUpUpdate(float deltaTimeSeconds);
		void VerifyGameState();
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMap(const glm::mat3& visMatrix);
		void RenderPlayer(const glm::mat3& visMatrix);
		void RenderEnemy(const glm::mat3& visMatrix);
		void RenderObstacle(const glm::mat3& visMatrix);
		void RenderProjectile(const glm::mat3& visMatrix);
		void RenderBars(const glm::mat3& visMatrix);
		void RenderPickUps(const glm::mat3& visMatrix);
		void DrawScene(glm::mat3 visMatrix);
		void DrawMinimap(glm::mat3 visMatrix);

		void PlayerCollisionsUp(float deltaTime);
		void PlayerCollisionsDown(float deltaTime);
		void PlayerCollisionsLeft(float deltaTime);
		void PlayerCollisionsRight(float deltaTime);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

		glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

		void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

	protected:
		ViewportSpace viewSpace;
		LogicSpace logicSpace;
		glm::mat3 modelMatrix, visMatrix;

		Character player;

		float fireRate, timeToFire;
		std::vector<Projectile> projectiles;

		float spawnEnemy, timeToSpawn;
		std::vector<Character> enemies;

		std::vector<Obstacle> obstacles;

		float healthMax, scoreMax;
		float healthScale, scoreScale;

		float spawnPickUp, timePickUp;
		std::vector<PickUp> pickUps;
		float fasterFireTime, doubleScoreTime, multiplier;

		bool gameOver;
	};
}   // namespace m1
