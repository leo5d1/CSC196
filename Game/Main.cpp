#include "Player.h"
#include "Enemy.h"
#include "Engine.h"
#include "SpaceShooter.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	c14::InitializeMemory();

	c14::SetFilePath("../Assets");

	// initialize systems
	c14::g_renderer.Initialize();
	c14::g_inputSystem.Initialize();
	c14::g_audio.Initialize();

	// add audio
	c14::g_audio.AddAudio("laser", "laser.wav");
	c14::g_audio.AddAudio("explosion", "Explosion.wav");

	// create window
	c14::g_renderer.CreateWindow("Neumont", 800, 600);
	c14::g_renderer.setClearColor(c14::Color{ 0, 0, 0, 0 });

	{
		// create game
		SpaceShooter game;
		game.Initialize();

		bool quit = false;
		while (!quit)
		{
			//update (engine)
			c14::g_time.Tick();
			c14::g_inputSystem.Update();
			c14::g_audio.Update();

			if (c14::g_inputSystem.GetKeyDown(c14::key_escape)) { quit = true; }

			game.Update();

			// renderer
			c14::g_renderer.BeginFrame();

			game.Draw(c14::g_renderer);

			c14::g_renderer.EndFrame();
		}
	}

	c14::g_audio.Shutdown();
	c14::g_renderer.Shutdown();
}