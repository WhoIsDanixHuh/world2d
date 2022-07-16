-- This file will be compiled if path wasn't specified
-- You can change this file as you want

function world2d.Init()
    world2d.Window.SetTitle("world2d Application")

    ImGui = world2d.ImGui
    ImGui.Initialize()

    debug_dt = 0
    bg_color = ImGui.FloatArray4.new(0.3, 0.5, 0.4, 1)

    local wx, wy = world2d.Window.GetSize()
    window_width = ImGui.Int.new(wx)
    window_height = ImGui.Int.new(wy)
    dw, dh = world2d.Window.GetDisplaySize()

    windows = {
        {func = ImGui.ShowDemoWindow, title = "Show Demo Window", bool = ImGui.Bool.new(false)},
        {func = ImGui.ShowAboutWindow, title = "Show About Window", bool = ImGui.Bool.new(false)},
        {func = ImGui.ShowMetricsWindow, title = "Show Metrics Window", bool = ImGui.Bool.new(false)},
        {func = ImGui.ShowStyleSelector, title = "Show Style Selector", bool = ImGui.Bool.new(false)},
        {func = ImGui.ShowFontSelector, title = "Show Font Selector", bool = ImGui.Bool.new(false)},
        {func = ImGui.ShowUserGuide, title = "Show User Guide", bool = ImGui.Bool.new(false)},
    }
end

function world2d.Update(dt)
    debug_dt = dt
end

function world2d.Render()
    world2d.Graphics.SetDrawColor(bg_color[1] * 255, bg_color[2] * 255, bg_color[3] * 255, bg_color[4] * 255)
    world2d.Graphics.Clear()

    ImGui.Begin("Welcome to world2d!")

    ImGui.Text("Platform: "..world2d.GetPlatform())
    ImGui.Text("world2d Version: "..world2d.Version)
    ImGui.Text("ImGui Version: "..ImGui.Version)
    ImGui.Text("Lua Version: ".._VERSION)
    ImGui.Text("Delta time: "..debug_dt)

    ImGui.Separator()

    ImGui.ColorEdit4("Background Color", bg_color)

    ImGui.Separator()

    ImGui.Text(string.format("Display size: (%i, %i)", dw, dh))

    ImGui.SliderInt("Window Width", window_width, 0, dw)
    ImGui.SliderInt("Window Height", window_height, 0, dh)

    if ImGui.Button("Set Window Size") then
        world2d.Window.SetSize(window_width.value, window_height.value)
    end

    ImGui.Separator()

    for _, window in ipairs(windows) do
        ImGui.Checkbox(window.title, window.bool)

        if window.bool.value == true then
            window.func(window.bool)
        end
    end

    ImGui.End()
end