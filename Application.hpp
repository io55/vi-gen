#ifndef _Window_HPP
#define _Window_HPP

struct Application {
	Application()          = default;
	virtual ~Application() = default;

	Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;

	virtual void run() = 0;
};

#endif