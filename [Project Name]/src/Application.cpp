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

// Inorder to start using the application, 
// you must return your app in the following function
namespace Nebula {
	Application* CreateApplication(ApplicationCommandLineArgs args) {
		// You will need 
		ApplicationSpecification spec;
		spec.CommandLineArgs = args;
		spec.Name = "New Nebula Project";
		
		// This is the application that handles window class automatically.
		Application* app = new Application(spec);
		
		// Pushing a layer will activate that layer and 
		// will call basic functions associated with the layer
		app->PushLayer(new ProjectLayer());

		// If you want to layer to be rendered last even if you push one after
		// Use PushOverlay. This can be useful for rendering on top or dealing with events
		/*
			PushOverlay(new ProjectLayer());
		*/

		// If you no longer want to call the class functions, pop the layer
		// You will need a pointer to the layer to do so.
		/*
			PopLayer(Layer);
		*/

		return app;
	}
}