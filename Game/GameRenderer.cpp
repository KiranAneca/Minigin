#include "GameRenderer.h"
#include "Renderer.h"

#include <SDL.h>
#include "SceneManager.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

void GameRenderer::Init(SDL_Window* window)
{
	Renderer::GetInstance().Init(window);
}

void GameRenderer::Render() const
{
	Renderer::GetInstance().Render();
}

void GameRenderer::RenderUI(Application* app) const
{
	
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(Renderer::GetInstance().GetWindow());
	ImGui::NewFrame();

	if (ImGui::Button("1 Player"))
	{
		app->LoadGameSinglePlayer();
		SceneManager::GetInstance().SetSceneActive(true, "GameSceneSingle");
		SceneManager::GetInstance().SetSceneActive(false, "MainMenu");
		SceneManager::GetInstance().DeleteScene("GameSceneMulti");
	}
	if (ImGui::Button("2 Player"))
	{
		app->LoadGameMultiplayer();
		SceneManager::GetInstance().SetSceneActive(true, "GameSceneMulti");
		SceneManager::GetInstance().SetSceneActive(false, "MainMenu");
		SceneManager::GetInstance().DeleteScene("GameSceneSingle");
	}

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(Renderer::GetInstance().GetSDLRenderer());
}

void GameRenderer::Destroy()
{
	Renderer::GetInstance().Destroy();
}

void GameRenderer::RenderTexture(const Texture2D& texture, float x, float y) const
{
	Renderer::GetInstance().RenderTexture(texture, x, y);
}

void GameRenderer::RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const
{
	Renderer::GetInstance().RenderTexture(texture, x, y, width, height);
}

void GameRenderer::RenderTexture(const Texture2D& texture, float x, float y, Rect srcRect) const
{
	Renderer::GetInstance().RenderTexture(texture, x, y, srcRect);
}
