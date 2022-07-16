function world2d.Init()
	ImGui = world2d.ImGui
	ImGui.Initialize()

	joysticks = world2d.Joystick.GetJoysticks()
end

function world2d.OnJoystickButtonUp(joy, button)
	print("OnJoystickButtonUp", joy.name, button)
end

function world2d.OnJoystickButtonDown(joy, button)
	print("OnJoystickButtonDown", joy.name, button)
end

function world2d.OnJoystickAxisMotion(joy, axis, value)
	print("OnJoystickAxisMotion", joy.name, axis, value)
end

function world2d.OnJoystickAdded(joy)
	print("OnJoystickAdded", joy.name)
end

function world2d.OnJoystickRemoved(joy, deviceId)
	print("OnJoystickRemoved", deviceId)
end

function world2d.Render()
	ImGui.Begin("Joystick Debug")

	ImGui.Text("Numbers of joysticks: "..world2d.Joystick.NumJoysticks())

	for idx, joy in ipairs(joysticks) do
		ImGui.Separator()
		ImGui.Text("Joystick #"..idx)

		ImGui.Text("Name: "..joy.name)
		ImGui.Text("Number of axes: "..joy.numOfAxes)
		ImGui.Text("Number of buttons: "..joy.numOfButtons)
		ImGui.Text("Is attached: "..tostring(joy.isAttached))
	end

	ImGui.End()
end