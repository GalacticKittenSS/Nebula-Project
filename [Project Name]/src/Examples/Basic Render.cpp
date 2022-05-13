#include "../ProjectLayer.h"

/*
	THIS EXAMPLE SHOWCASES BASIC RENDERING AND EVENTS
					------------------
	TO USE THIS EXAMPLE MAKE SURE TO ONLY LINK THIS FILE
				IN THE "Examples" FOLDER.
*/

/// This will called First
/// Initialize any variables here
void ProjectLayer::Attach() {

}

/// This will called Last
/// Destroy any variables here
void ProjectLayer::Detach() {
	
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

	// Sets the background colour
	Nebula::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1.0f });

	// Render a Quad
	Nebula::Renderer2D::BeginScene(Camera);
	Nebula::Renderer2D::Draw(NB_QUAD, Nebula::mat4(1.0f), Nebula::vec4(1.0f));
	Nebula::Renderer2D::EndScene();
}

/// Use to Render Any ImGui items
void ProjectLayer::ImGuiRender() {

}

/// Called on any Event
void ProjectLayer::OnEvent(Nebula::Event& e) {
	// Create Event Dispatcher
	Nebula::Dispatcher dispatcher(e);

	// Use Dispatch to call a function with a specific event type
	// Format: dispatcher.Dispatch<Event Type>(function)
	dispatcher.Dispatch<Nebula::WindowResizeEvent>([&](Nebula::WindowResizeEvent& e) {
		NB_TRACE("Window was Resized: {0}, {1}", e.GetWidth(), e.GetHeight());

		// Must Return a boolean. 
		// True  = Will NOT call OnWindowResize equivalent in the next layer
		// False = Will call OnWindowResize equivalent in the next layer
		return false;
	});

	// You can also use BIND_EVENT(function) to use a class function
	// This function does not need to be public
	dispatcher.Dispatch<Nebula::WindowResizeEvent>(BIND_EVENT(ProjectLayer::OnWindowResize));
}

/// Will be Called When Window is Resized.
/// Must be initialised using 
///         "dispatcher.Dispatch<Nebula::WindowResizeEvent>(BIND_EVENT(ProjectLayer::OnWindowResize));"
/// in ProjectLayer::OnEvent
bool ProjectLayer::OnWindowResize(Nebula::WindowResizeEvent& e) {
	NB_TRACE("Window was Resized: {0}, {1} | Used ProjectLayer::OnWindowResize(Nebula::WindowResizeEvent& e)", 
		e.GetWidth(), e.GetHeight());

	// Must Return a boolean. 
	// True  = Will NOT call OnWindowResize equivalent in the next layer
	// False = Will call OnWindowResize equivalent in the next layer
	return true;
}