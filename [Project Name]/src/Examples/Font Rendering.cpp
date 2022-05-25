#include "../ProjectLayer.h"

/*
	THIS EXAMPLE SHOWCASES FONT CREATION AND TEXT RENDERING
					------------------
	TO USE THIS EXAMPLE MAKE SURE TO ONLY LINK THIS FILE
				IN THE "Examples" FOLDER.
*/

/// This will called First
/// Initialize any variables here
void ProjectLayer::Attach() {
	// Sets the background colour
	Nebula::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1.0f });

	// Create A Font Using FontManager
	// This allows you to access the font at any time
	Nebula::FontManager::Add(new Nebula::Font("OpenSans", "Resources/fonts/OpenSans/Regular.ttf", 86.0f));
	Nebula::FontManager::Add(new Nebula::Font("Roboto",		"Resources/fonts/Roboto/Regular.ttf", 86.0f));
}

/// This will called Last
/// Destroy any variables here
void ProjectLayer::Detach() {
	//Make Sure to Delete/Clean the Fonts in the FontManager
	Nebula::FontManager::Clean();
}

///  Called Once Per Frame
///  Use to Update any variables
void ProjectLayer::Update(Nebula::Timestep ts) {

}

/// Clalled Once Per Frame
/// Use to Render onto Screen
void ProjectLayer::Render() {
	// Clears the Screen
	Nebula::RenderCommand::Clear();

	// Rendering
	Nebula::Renderer2D::BeginScene(Camera); // Must always start with begin scene.
	Nebula::Renderer2D::DrawString("This is some text", Nebula::FontManager::Get("OpenSans"), 
		Nebula::mat4(1.0f), Nebula::vec4(1.0f)); // Render the Text starting at pos (0, 0) with white colour
	Nebula::Renderer2D::EndScene(); // Must always end the scene to render
}

/// Use to Render Any ImGui items
void ProjectLayer::ImGuiRender() {

}

/// Called on any Event such as window resize
void ProjectLayer::OnEvent(Nebula::Event& e) {

}

/// Will be Called When Window is Resized.
/// Must be initialised using 
///         "dispatcher.Dispatch<Nebula::WindowResizeEvent>(BIND_EVENT(ProjectLayer::OnWindowResize));"
/// in ProjectLayer::OnEvent
bool ProjectLayer::OnWindowResize(Nebula::WindowResizeEvent& e) {
	return true;
}