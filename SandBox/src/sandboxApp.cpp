#include <Fuji.h>

class SandBox : public Fuji::Application
{
public:
	SandBox()
	{

	}

	~SandBox()
	{

	}
};

Fuji::Application* Fuji::CreateApplication()
{
	return new SandBox();
}