function world2d.Init()
	ImGui = world2d.ImGui
	ImGui.Initialize()

	numbers = {}

	local threadfunc = function()
		for i = 1, 10 do
			table.insert(numbers, i)
			print("Pushed number "..i.." to the table")
			world2d.Timer.Delay(1000)
		end
	end

	thread = world2d.Threading.Thread.new(threadfunc, "Thread1")
	thread:Detach()
end

function world2d.Render()
	ImGui.Begin("Threading")

	ImGui.Text("Thread pushes numbers to the table.")
	ImGui.Text("Numbers: "..table.concat(numbers, ", "))

	ImGui.Separator()

	ImGui.Text("Thread name: "..thread.name)
	ImGui.Text("Thread ID: "..thread.id)

	ImGui.End()
end