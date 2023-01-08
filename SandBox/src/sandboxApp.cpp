#include <Fuji.h>

class SandBox : public Fuji::Application
{
public:
	SandBox()
	{
		F_LOG_INFO("Application started");
	}

	~SandBox()
	{

	}
};

Fuji::Application* Fuji::CreateApplication()
{
	return new SandBox();
}
