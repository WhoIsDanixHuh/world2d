function world2d.Init()
    ImGui = world2d.ImGui
    ImGui.Initialize()

    toolActive = ImGui.Bool.new(true)
    color = ImGui.FloatArray4.new()
end

function world2d.Render()
    world2d.Graphics.SetDrawColor(color[1] * 255, color[2] * 255, color[3] * 255, color[4] * 255)
    world2d.Graphics.Clear()

    if toolActive.value ~= true then
        return
    end

    ImGui.Begin("My First Tool", toolActive, ImGui.WindowFlags.MenuBar)

    if ImGui.BeginMenuBar() then
        if ImGui.BeginMenu("File") then
            if ImGui.MenuItem("Open..", "Ctrl+O") then
                -- Do stuff
            end

            if ImGui.MenuItem("Save", "Ctrl+S") then
                -- Do stuff
            end

            if ImGui.MenuItem("Close", "Ctrl+W") then
                toolActive.value = false
            end

            ImGui.EndMenu()
        end

        ImGui.EndMenuBar()
    end

    ImGui.ColorEdit4("Color", color)

    local values = {0.2, 0.1, 1.0, 0.5, 0.9, 2.2}
    ImGui.PlotLines("Frame Times", values)

    ImGui.TextColored(ImGui.Vec4.new(1, 1, 0, 1), "Important Stuff")
    ImGui.BeginChild("Scrolling")

    for n = 1, 50 do
        ImGui.Text(string.format("%04d: Some text", n))
    end

    ImGui.EndChild()
    ImGui.End()
end