#include "../ProjectLayer.h"

/*
	THIS EXAMPLE SHOWCASES FRAMEBUFFER AND IMGUI DOCKING
					------------------
	TO USE THIS EXAMPLE MAKE SURE TO ONLY LINK THIS FILE
				IN THE "Examples" FOLDER.
*/

/// This will called First
/// Initialize any variables here
void ProjectLayer::Attach() {
	// A Framebuffer must be initialised using Specifications
	Nebula::FrameBufferSpecification specs;

	// When Rendering by default It uses a Colour (RGBA8) and Depth attachment
	specs.Attachments = { Nebula::FramebufferTextureFormat::RGBA8, Nebula::FramebufferTextureFormat::Depth };
	specs.Height = 900; specs.Width = 1600; // Window Width / Height

	// Using Framebuffer::Create returns a Ref (std::shared_ptr)
	Viewport = Nebula::FrameBuffer::Create(specs);

	// Sets the background colour
	Nebula::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1.0f });
}

/// This will called Last
/// Destroy any variables here
void ProjectLayer::Detach() {

}

///  Called Once Per Frame
///  Use to Update any variables
void ProjectLayer::Update(Nebula::Timestep ts) {
	// Resize Framebuffer Based On ImGui
	Nebula::FrameBufferSpecification spec = Viewport->GetFrameBufferSpecifications();
	
	// If framebuffer is not the size of available space in imgui
	if (ViewportSize.x > 0.0f && ViewportSize.y > 0.0f && (spec.Width != ViewportSize.x || spec.Height != ViewportSize.y))
		// Resize the framebuffer to the available space
		Viewport->Resize((uint32_t)ViewportSize.x, (uint32_t)ViewportSize.y);
}

/// Clalled Once Per Frame
/// Use to Render onto Screen
void ProjectLayer::Render() {
	// Bind the framebuffer, to Start Rendering to it
	Viewport->Bind();

	// Clears the Screen
	Nebula::RenderCommand::Clear();

	// Render a Quad
	Nebula::Renderer2D::BeginScene(Camera); // Must always start with begin scene.
	Nebula::Renderer2D::Draw(NB_QUAD, Nebula::mat4(1.0f), Nebula::vec4(1.0f)); // Render the quad at pos (0, 0) with white colour
	Nebula::Renderer2D::EndScene(); // Must always end the scene to render

	// Don't forget to unbind the buffer once your done!
	Viewport->Unbind();
}

/// Use to Render Any ImGui items
void ProjectLayer::ImGuiRender() {
	// Set Window Size to Viewport Size
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	// Window Flags for 
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	// No Window Padding or Border to Docked Windows
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	// Create Window for Dockspace
	ImGui::Begin("Project Dockspace", nullptr, window_flags);
	ImGui::PopStyleVar(3);

	// Begin Dockspace on Window created Above
	ImGui::DockSpace(ImGui::GetID("Project Dockspace"), ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

	ImGui::ShowDemoWindow();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Viewport");
	ImGui::PopStyleVar();

	// Get Viewport Size based on Available Content Region
	ViewportSize.x = ImGui::GetContentRegionAvail().x;
	ViewportSize.y = ImGui::GetContentRegionAvail().y;

	// Render Image
	ImGui::Image((void*)Viewport->GetColourAttachmentRendererID(), ImGui::GetContentRegionAvail(), ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	ImGui::End();

	ImGui::End();
}

/// Called on any Event such as window resize
void ProjectLayer::OnEvent(Nebula::Event& e) {

}

/// Will be Called When Window is Resized.
/// Must be initialised using 
///         "dispatcher.Dispatch<Nebula::WindowResizeEvent>(BIND_EVENT(ProjectLayer::OnWindowResize));"
/// in ProjectLayer::OnEvent
bool ProjectLayer::OnWindowResize(Nebula::WindowResizeEvent& e) {
	return false;
}