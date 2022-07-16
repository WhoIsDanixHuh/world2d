#ifndef WORLD2D_MODULES_JOYSTICKMODULE_H
#define WORLD2D_MODULES_JOYSTICKMODULE_H

#include "world2d/Module.h"
#include "world2d/lua/structures/GameController.h"
#include <vector>

namespace world2d {
	class JoystickModule : public world2d::Module {
	private:
		std::vector<world2d::GameController*> mJoysticks;

	public:
		JoystickModule();
		~JoystickModule();
		JoystickModule(const JoystickModule&) = delete;

		bool Initialize() override;
		void OnEvent(SDL_Event& event) override;

		world2d::GameController* AddJoystick(int deviceIndex);
		world2d::GameController* FindJoystick(SDL_JoystickID deviceId);
		int RemoveJoystick(world2d::GameController* controller);
		int RemoveJoystick(SDL_JoystickID deviceId);

		void LoadJoysticks();
		void FreeJoysticks();
		
		static JoystickModule* Get();
	};
}

#endif