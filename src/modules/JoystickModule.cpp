#include "world2d/modules/JoystickModule.h"
#include <algorithm>

world2d::JoystickModule::JoystickModule() : world2d::Module() {

}

world2d::JoystickModule::~JoystickModule() {
	FreeJoysticks();
}

bool world2d::JoystickModule::Initialize() {
	if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL joystick subsystem: %s", SDL_GetError());
		return false;
	}
	
	sol::state& lua { mEngine->GetLua() };

	sol::table luaWorld2dNamespace { lua.get<sol::table>("world2d") };
	sol::table luaJoystickNamespace { lua.create_table() };

	// ===== Structures =====
	luaJoystickNamespace.new_usertype<world2d::GameController>("Joystick",
		"name", sol::property([&](world2d::GameController* self) {
			return SDL_GameControllerName(self->joy);
		}),

		"numOfAxes", sol::property([&](world2d::GameController* self) {
			return SDL_JoystickNumAxes(SDL_GameControllerGetJoystick(self->joy));
		}),

		"numOfButtons", sol::property([&](world2d::GameController* self) {
			return SDL_JoystickNumButtons(SDL_GameControllerGetJoystick(self->joy));
		}),

		"isAttached", sol::property([&](world2d::GameController* self) {
			return static_cast<bool>(SDL_GameControllerGetAttached(self->joy));
		}),

		"IsButtonPressed", [&](world2d::GameController* self, const char* buttonstr) {
			SDL_GameControllerButton button = SDL_GameControllerGetButtonFromString(buttonstr);

			if (button == SDL_CONTROLLER_AXIS_INVALID) {
				luaL_error(lua.lua_state(), "Invalid button \"%s\"", buttonstr);
				return false;
			}

			return static_cast<bool>(SDL_GameControllerGetButton(self->joy, button));
		}
	);
	// ======================

	// ===== Functions =====
	luaJoystickNamespace.set_function("NumJoysticks", &SDL_NumJoysticks);

	luaJoystickNamespace.set_function("GetJoysticks", [&]() {
		LoadJoysticks();
		return mJoysticks;
	});
	// =====================

	luaWorld2dNamespace["Joystick"] = luaJoystickNamespace;
	return true;
}

void world2d::JoystickModule::OnEvent(SDL_Event& event) {
	sol::state& lua { mEngine->GetLua() };
	sol::table luaWorld2dNamespace { lua.get <sol::table>("world2d") };

	switch (event.type) {
		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERBUTTONUP: {
			world2d::GameController* controller = FindJoystick(event.cbutton.which);
			const char* funcName = (event.type == SDL_JOYBUTTONUP) ? "OnJoystickButtonUp" : "OnJoystickButtonDown";
			const char* button = SDL_GameControllerGetStringForButton(static_cast<SDL_GameControllerButton>(event.jbutton.button));

			luaWorld2dNamespace.get<sol::function>(funcName)(controller, button);
			break;
		}

		case SDL_CONTROLLERAXISMOTION: {
			world2d::GameController* controller = FindJoystick(event.caxis.which);
			const char* axis = SDL_GameControllerGetStringForAxis(static_cast<SDL_GameControllerAxis>(event.jaxis.axis));

			luaWorld2dNamespace.get<sol::function>("OnJoystickAxisMotion")(controller, axis, event.jaxis.value);
			break;
		}

		case SDL_CONTROLLERDEVICEADDED: {
			world2d::GameController* controller = AddJoystick(event.cdevice.which);
			luaWorld2dNamespace.get<sol::function>("OnJoystickAdded")(controller);
			break;
		}

		case SDL_CONTROLLERDEVICEREMOVED: {
			SDL_JoystickID deviceId = RemoveJoystick(event.cdevice.which);
			luaWorld2dNamespace.get<sol::function>("OnJoystickRemoved")(deviceId);
			break;
		}
	}
}

const char* world2d::JoystickModule::GetName() {
	return "JoystickModule";
}

world2d::GameController* world2d::JoystickModule::AddJoystick(int deviceIndex) {
	SDL_GameController* joy = SDL_GameControllerOpen(deviceIndex);
	world2d::GameController* controller = new world2d::GameController { deviceIndex, joy };
	mJoysticks.push_back(controller);
	return controller;
}

world2d::GameController* world2d::JoystickModule::FindJoystick(SDL_JoystickID deviceId) {
	std::vector<world2d::GameController*>::iterator controller = std::find_if(mJoysticks.begin(), mJoysticks.end(), [&](world2d::GameController* controller) {
		return SDL_JoystickGetDeviceInstanceID(controller->index) == deviceId;
	});
	return *controller;
}

int world2d::JoystickModule::RemoveJoystick(world2d::GameController* controller) {
	if (SDL_GameControllerGetAttached(controller->joy)) {
		SDL_GameControllerClose(controller->joy);
	}

	int controllerIndex = controller->index;

	mJoysticks.erase(std::find(mJoysticks.begin(), mJoysticks.end(), controller));
	delete controller;

	return controllerIndex;
}

int world2d::JoystickModule::RemoveJoystick(SDL_JoystickID deviceId) {
	std::vector<world2d::GameController*>::iterator controller = std::find_if(mJoysticks.begin(), mJoysticks.end(), [&](world2d::GameController* controller) {
		return SDL_JoystickGetDeviceInstanceID(controller->index) == deviceId;
	});

	return RemoveJoystick(*controller);
}

void world2d::JoystickModule::LoadJoysticks() {
	if (mJoysticks.size() > 0) {
		FreeJoysticks();
	}

	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		AddJoystick(i);
	}
}

void world2d::JoystickModule::FreeJoysticks() {
	for (world2d::GameController* controller : mJoysticks) {
		RemoveJoystick(controller);
	}
}

world2d::JoystickModule* world2d::JoystickModule::Get() {
	static JoystickModule currentModule;
	return &currentModule;
}