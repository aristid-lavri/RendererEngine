#include "ExampleLayer.h"
#include <glm/gtc/type_ptr.hpp>	

#include <thread>

using namespace Z_Engine::Rendering::Renderers;
using namespace Z_Engine::Rendering::Cameras;
using namespace Z_Engine::Rendering::Shaders;
using namespace Z_Engine::Rendering::Buffers;
using namespace Z_Engine::Window;
using namespace Z_Engine::Core;
using namespace Z_Engine::Inputs;

using namespace Z_Engine::Managers;
using namespace Z_Engine::Rendering::Textures;
using namespace Z_Engine::Controllers;

namespace Sandbox::Layers {
	
	void ExampleLayer::Initialize() {

		m_texture_manager.reset(new Z_Engine::Managers::TextureManager());
		
													   
		m_texture_manager->Load("src/Assets/Images/free_image.png");
		m_texture_manager->Load("src/Assets/Images/Checkerboard_2.png");
		m_texture_manager->Load("src/Assets/Images/Crate.png");
		m_texture_manager->Load("src/Assets/Images/Flying_Mario.png");
		m_texture_manager->Load("src/Assets/Images/mario_and_sonic.png");

		m_texture_manager->Add("custom", 1, 1);

		m_camera_controller.reset(new OrthographicCameraController(GetAttachedWindow(), true));
		m_renderer.reset(new GraphicRenderer2D());
		
		m_camera_controller->Initialize();
		m_renderer->Initialize();
		
		m_rect_1_pos = {-0.7, 0.7};
	}

	void ExampleLayer::Update(Z_Engine::Core::TimeStep dt) {
		m_camera_controller->Update(dt);

		if(IDevice::As<Z_Engine::Inputs::Keyboard>()->IsKeyPressed(Z_ENGINE_KEY_J)) {
			//m_rect_1_pos.y -= 0.1f * dt;
			m_rect_1_pos.x -= 0.1f * dt;
		}

		if (IDevice::As<Z_Engine::Inputs::Keyboard>()->IsKeyPressed(Z_ENGINE_KEY_F)) {
			//m_rect_1_pos.y += 0.1f * dt;
			m_rect_1_pos.x += 0.1f * dt;
		}

		if (IDevice::As<Z_Engine::Inputs::Keyboard>()->IsKeyPressed(Z_ENGINE_KEY_B)) {
			m_rect_1_pos.y += 0.1f * dt;
			//m_rect_1_pos.x += 0.1f * dt;
		}
		if (IDevice::As<Z_Engine::Inputs::Keyboard>()->IsKeyPressed(Z_ENGINE_KEY_Y)) {
			m_rect_1_pos.y -= 0.1f * dt;
			//m_rect_1_pos.x += 0.1f * dt;
		}
	}

	bool ExampleLayer::OnEvent(Z_Engine::Event::CoreEvent& e) {
		m_camera_controller->OnEvent(e);
		return false;
	}

	void ExampleLayer::ImGuiRender()
	{
		/*ImGui::Begin("Editor");
		ImGui::DragFloat2("Rectangle_one", glm::value_ptr(m_rect_1_pos), .5f);
		ImGui::DragFloat2("Rectangle_two", glm::value_ptr(m_rect_2_pos), .05f);
		ImGui::DragFloat2("Rectangle_three", glm::value_ptr(m_rect_3_pos), .5f);
		ImGui::End();*/
	}

	void ExampleLayer::Render() {

		static float angle = 0.0f;
		++angle;

		  //if(angle >= 360.f) angle = 0.0f;

		RendererCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		RendererCommand::Clear();


		m_renderer->BeginScene(m_camera_controller->GetCamera());

		for (float x = 0.0f; x < 2.f; x += 0.17f) {
			for (float y = 0.0f; y < 2.f; y += 0.12f) {
				m_renderer->DrawRect({ x , y }, { 0.1f, 0.1f }, { angle * x , angle * y , (angle * x * y) }, glm::radians(angle) * 10);
			}
		}


		for (float x = 2.0f; x < 4.f; x += 0.17f) {
			for (float y = 0.0f; y < 4.f; y += 0.12f) {
				m_renderer->DrawTriangle({ x , y }, { 0.1f, 0.1f }, { angle * x , angle , (20 * x * y) }, -glm::radians(angle) * 10);
			}
		}
		
		m_renderer->EndScene();

		
	}

}