#include <Nebula.h>
#include <Nebula_EntryPoint.h>

#include "ProjectLayer.h"

class ProjectApplication : public Nebula::Application {
public:
	ProjectApplication(Nebula::ApplicationCommandLineArgs args) : Application("New Nebula Project", args) {
		PushLayer(new ProjectLayer());
	}

	~ProjectApplication() { }
};

namespace Nebula {
	Application* CreateApplication(ApplicationCommandLineArgs args) {
		return new ProjectApplication(args);
	}
}