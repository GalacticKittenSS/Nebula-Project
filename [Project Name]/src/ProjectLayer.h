#pragma once

#include <Nebula.h>

/*
	THE MAIN IMPLEMENTATION WILL
	BE DONE USING LAYERS LIKE THIS ONE
*/

// ProjectLayer can be called whatever you like,
// But must be derived from Nebula::Layer
class ProjectLayer : public Nebula::Layer {
public:
	/// Can be Used to Initialize variables
	/// Where possible, use Attach instead 
	ProjectLayer() : Layer("Project Layer") { }

	/// Can be Used to Destroy variables
	/// Where possible, use Detach instead 
	~ProjectLayer() = default;

	/// This will called First
	/// Initialize any variables here
	void Attach() override;

	/// This will called Last
	/// Destroy any variables here
	void Detach() override;

	///  Called Once Per Frame
	///  Use to Update any variables
	void Update(Nebula::Timestep ts) override;

	/// Clalled Once Per Frame
	/// Use to Render onto Screen
	void Render() override;

	/// Use to Render ImGui
	void ImGuiRender() override;

	/// Called on any Event such as window resize
	void OnEvent(Nebula::Event& e) override;
private:
	/// Will be Called When Window is Resized.
	bool OnWindowResize(Nebula::WindowResizeEvent& e);
private:
	// Viewport if Using ImGui Dockspace
	Nebula::Ref<Nebula::FrameBuffer> Viewport;
	Nebula::vec2 ViewportSize = { 1600, 900 };

	// Orthagraphic Camera used for Rendering
	// Must be initialised here as it has no default constructor
	Nebula::OrthographicCamera Camera = { -16.0f, 16.0f, -9.0f, 9.0f };
};