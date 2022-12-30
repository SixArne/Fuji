#pragma once

#ifdef FU_PLATFORM_WINDOWS

extern Fuji::Application* Fuji::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Fuji::CreateApplication();
	app->Run();

	delete app;
}

#endif