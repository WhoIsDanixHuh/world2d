local function EnumValueToString(enum, value)
    for k, v in pairs(enum) do
        if v == value then
            return k
        end
    end

    return "Unknown"
end

function world2d.Init()
    ImGui = world2d.ImGui
    ImGui.Initialize()

    tbl = {
        x = 20,
        y = 20
    }

    properties = {
        x = 120,
        y = 120
    }

    easingStyle = world2d.Tweening.EasingStyle.Linear
    easingDirection = world2d.Tweening.EasingDirection.Out

    t = ImGui.Int.new(5)

    tween = nil
end

function world2d.Render()
    world2d.Graphics.SetDrawColor(127, 127, 127, 255)
    world2d.Graphics.Clear()

    world2d.Graphics.SetDrawColor(255, 255, 255, 255)
    world2d.Graphics.DrawRect(world2d.Graphics.DrawMode.Fill, tbl.x, tbl.y, 120, 120)

    ImGui.Begin("Tween")

    ImGui.Text(string.format("data = {x = %f, y = %f}", tbl.x, tbl.y))
    ImGui.Text(string.format("properties = {x = %f, y = %f}", properties.x, properties.y))

    ImGui.Separator()

    ImGui.Text("Current tween: "..tostring(tween))

    ImGui.Text("Current EasingStyle: "..EnumValueToString(world2d.Tweening.EasingStyle, easingStyle))
    ImGui.BeginListBox("EasingStyle")

    for k, v in pairs(world2d.Tweening.EasingStyle) do
        local selected = (v == easingStyle)

        if ImGui.Selectable(k, selected) then
            easingStyle = v
        end
    end

    ImGui.EndListBox()

    ImGui.Text("Current EasingDirection: "..EnumValueToString(world2d.Tweening.EasingDirection, easingDirection))
    ImGui.BeginListBox("EasingDirection")

    for k, v in pairs(world2d.Tweening.EasingDirection) do
        local selected = (v == easingDirection)

        if ImGui.Selectable(k, selected) then
            easingDirection = v
        end
    end

    ImGui.EndListBox()

    ImGui.InputInt("Duration", t)

    if ImGui.Button("Create") then
        tween = world2d.Tweening.Tween.new(tbl, easingStyle, easingDirection, t.value, properties)
    end

    if ImGui.Button("Play") then
        tween:Play()
    end

    if ImGui.Button("Pause") then
        tween:Pause()
    end

    if ImGui.Button("Reset") then
        tbl.x = 0
        tbl.y = 0
    end

    ImGui.End()
end