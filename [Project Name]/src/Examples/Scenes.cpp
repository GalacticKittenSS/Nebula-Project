#include "../ProjectLayer.h"

/*
	THIS EXAMPLE SHOWCASES USING NEBULA STORM AS A LEVEL EDITOR
					------------------
	TO USE THIS EXAMPLE MAKE SURE TO ONLY LINK THIS FILE
				IN THE "Examples" FOLDER.
*/

class PlayerMovement : public Nebula::ScriptableEntity {
protected:
	void Update() override 
	{
		Nebula::TransformComponent& transform = GetComponent<Nebula::TransformComponent>();
		
		// Move Player Left and Right
		if (Nebula::Input::IsKeyPressed(NB_D))
			transform.Translation.x += speed;
		else if (Nebula::Input::IsKeyPressed(NB_A))
			transform.Translation.x -= speed;

		Nebula::UpdateChildrenAndTransform(GetCurrentEntity());
	}
private:
	float speed = 0.1f;
};

class ObjectMovement : public Nebula::ScriptableEntity {
protected:
	void Update() override
	{
		auto& transform = GetComponent<Nebula::TransformComponent>();
		
		// Move objects down
		transform.Translation.y -= gravity * Nebula::Time::DeltaTime();
		Nebula::UpdateChildrenAndTransform(GetCurrentEntity());
		
		// Delete Object if offscreen
		if (transform.Translation.y < -20.0f)
		{
			DestroyObject(this);
			NB_TRACE("DESTROYED OBJECT");
		}
	}
private:
	float gravity = 4.5f;
};

class SpawnEntities : public Nebula::ScriptableEntity {
public:
	Nebula::Entity ObjTemplate;
protected:
	void Start() override
	{
		// Calculate Min and Max Bounds based on Object Transform
		Nebula::mat4 transform = GetComponent<Nebula::WorldTransformComponent>().Transform;
		min = transform * Nebula::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
		max = transform * Nebula::vec4( 0.5f,  0.5f, 0.0f, 1.0f);

		// Set Cooldown. This will spawn them once every 0.6 seconds
		cooldownReset = 0.6f;
		cooldown = cooldownReset;
	}

	void Update() override
	{
		cooldown -= Nebula::Time::DeltaTime();

		if (cooldown > 0)
			return;

		cooldown = cooldownReset;
		SpawnNewObject();
	}

	void SpawnNewObject() {
		// Get A Random X and Y based on the bounds
		float x = CalculateRandom(min.x, max.x, 100.0f);
		float y = CalculateRandom(min.y, max.y, 100.0f);

		// Duplicate the Template
		Nebula::Entity entity = GetActiveScene()->DuplicateEntity(ObjTemplate);
		
		// Update the Translation with the Random X and Y
		entity.GetComponent<Nebula::TransformComponent>().Translation = { x, y, 0.0f };
		Nebula::UpdateChildrenAndTransform(entity);
		
		// Add a script to update the object
		entity.AddComponent<Nebula::NativeScriptComponent>().Bind<ObjectMovement>();

		NB_TRACE("NEW ENTITY CREATED AT: {0}, {1}", x, y);
	}

	float CalculateRandom(float min, float max, int32_t accuracy)
	{
		// Random can only take integers
		// By Multiplying by 10/100/1000 e.c.t
		// We Gan get better accuracy on the decimals

		int32_t minI = min * accuracy;
		int32_t maxI = max * accuracy;
		float random;

		// Random Can Only Take Positive Numbers 
		// So We may need to adjust some numbers

		// If Both are negative
		if (min < 0 && max < 0) 
			random = -Nebula::Rand(-minI, -maxI);
		
		// If Min is Negative
		else if (min < 0)
		{
			minI = 0;
			maxI -= min * accuracy;
			random  = Nebula::Rand(minI, maxI);
			random += min * accuracy;
		}

		// Both are Positive
		else
			random = Nebula::Rand(minI, maxI);
		
		// Return random to normal range
		return random / accuracy;
	}
private:
	Nebula::vec2 min, max;
	float cooldown;
	float cooldownReset;
};

static Nebula::Entity GetEntityWithTag(std::string tag, Nebula::Ref<Nebula::Scene> Scene) {
	for (auto& entityID : Scene->GetAllEntitiesWith<Nebula::TagComponent>()) {
		Nebula::Entity entity{ entityID, Scene.get() };
		if (entity.GetComponent<Nebula::TagComponent>().Tag == tag)
			return entity;
	}

	NB_ERROR("Could Not Find Entity with name {0}", tag);
	return Nebula::Entity{};
}

/// This will called First
/// Initialize any variables here
void ProjectLayer::Attach() {
	// Sets the background colour
	Nebula::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1.0f });

	// Create A Blanks Scene
	Scene = Nebula::CreateRef<Nebula::Scene>();
	
	// Deserialize File onto Scene
	Nebula::SceneSerializer SceneSerializer(Scene);
	SceneSerializer.Deserialize("Resources/scenes/ExampleOne.nebula");

	// Start Scene
	Scene->OnRuntimeStart();

	// Get Neccessary Entities
	Nebula::Entity player = GetEntityWithTag("Player", Scene);
	Nebula::Entity box = GetEntityWithTag("Bounding Box", Scene);
	Nebula::Entity obj = GetEntityWithTag("Object", Scene);
	
	// If we can't find any we can't continue
	if (!player || !box || !obj)
		return;

	// Add a Native script component to the Player
	player.AddComponent<Nebula::NativeScriptComponent>().Bind<PlayerMovement>();

	// Add a Native script component to the Player
	box.AddComponent<Nebula::NativeScriptComponent>().Bind<SpawnEntities>();
	
	// We Can Only use instance by initializeing it using updateRuntime;
	Scene->UpdateRuntime();

	// Set Object Template
	SpawnEntities* spawner = (SpawnEntities*)(box.GetComponent<Nebula::NativeScriptComponent>().Instance);
	spawner->ObjTemplate = obj;
}

/// This will called Last
/// Destroy any variables here
void ProjectLayer::Detach() {
	Scene->OnRuntimeStop();
}

///  Called Once Per Frame
///  Use to Update any variables
void ProjectLayer::Update(Nebula::Timestep ts) {
	Scene->UpdateRuntime();
}

/// Clalled Once Per Frame
/// Use to Render onto Screen
void ProjectLayer::Render() {
	Nebula::RenderCommand::Clear();
	Scene->RenderRuntime();
}

/// Use to Render Any ImGui items
void ProjectLayer::ImGuiRender() { }

/// Called on any Event such as window resize
void ProjectLayer::OnEvent(Nebula::Event& e) {
	Nebula::Dispatcher(e).Dispatch<Nebula::WindowResizeEvent>(BIND_EVENT(ProjectLayer::OnWindowResize));
}

/// Will be Called When Window is Resized.
/// Must be initialised using 
///         "dispatcher.Dispatch<Nebula::WindowResizeEvent>(BIND_EVENT(ProjectLayer::OnWindowResize));"
/// in ProjectLayer::OnEvent
bool ProjectLayer::OnWindowResize(Nebula::WindowResizeEvent& e) {
	Scene->OnViewportResize((uint32_t)e.GetWidth(), (uint32_t)e.GetHeight());
	return true;
}