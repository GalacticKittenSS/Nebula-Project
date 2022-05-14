#include <Nebula.h>
#include <Nebula_EntryPoint.h>

#include "ProjectLayer.h"
/*
	THIS CLASS IS PURELY TO HANDLE
	THE PUSHING/POPPING OF THESE LAYERS
			-----------
	YOU CAN USE THIS CLASS TO DO IMPLEMENTATIONS
	HOWEVER IT IS RECOMMENDED YOU USE LAYERS
	INSTEAD
*/

// This is the application that handles window class automatically.
// The name can be different, however must derive from Nebula::Application
class ProjectApplication : public Nebula::Application {
public:
	ProjectApplication(Nebula::ApplicationCommandLineArgs args) : Application("New Nebula Project", args) {
				/// TO CREATE A LAYER
		
		// Pushing a layer will activate that layer and 
		// will call basic functions associated with the layer
		PushLayer(new ProjectLayer());
		
						// OR
		// You can use a variable to initialize and push a layer
		// This can be useful if you want to pop or delete a layer
		Layer = new ProjectLayer();
		PushOverlay(Layer);

		// If you no longer want to call the class functions, pop the layer
		// You will need a pointer to the layer to do so.
		PopLayer(Layer);

		// If you want to layer to be rendered last even if you push one after
		// Use PushOverlay. This can be useful for rendering on top or dealing with events
		//PushOverlay(new ProjectLayer());
	}

	~ProjectApplication() { }
private:
	// This layer does not need to be deleted.
	// It is automatically done
	ProjectLayer* Layer;
};

// Inorder to start using the application, 
// you must return your custom app in the following function
namespace Nebula {
	Application* CreateApplication(ApplicationCommandLineArgs args) {
		return new ProjectApplication(args);
	}
}