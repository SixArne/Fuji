#pragma once

#ifdef FU_PLATFORM_WINDOWS

/************************************************************************/
/* Tells the compiler to look for a external function
/************************************************************************/
extern Fuji::Application* Fuji::CreateApplication();

/************************************************************************/
/* Main function will be in the engine
/************************************************************************/
int main(int argc, char** argv)
{
	Fuji::Log::Init();
	F_LOG_CORE_WARN("Initialized");
	F_LOG_INFO("Var={0}", 4);

	auto app = Fuji::CreateApplication();
	app->Run();

	delete app;
}

#endif