function world2d.Init()
    ImGui = world2d.ImGui
    ImGui.Initialize()

    audio = world2d.Audio.new("./examples/sounds/music.mp3")
    audio:Play()

    buttonSize = ImGui.Vec2.new(100, 20)

    volume = ImGui.Float.new(audio.volume)
    pitch = ImGui.Float.new(audio.pitch)
    isLooping = ImGui.Bool.new(audio.isLooping)
end

function world2d.Update()
    audio.volume = volume.value
    audio.pitch = pitch.value
    audio.isLooping = isLooping.value
end

function world2d.Render()
    world2d.Graphics.SetDrawColor(127, 127, 127, 255)
    world2d.Graphics.Clear()

    ImGui.Begin("Audio")
    
    if ImGui.Button("Play", buttonSize) then
        audio:Play()
    end

    if ImGui.Button("Pause", buttonSize) then
        audio:Pause()
    end

    if ImGui.Button("Stop", buttonSize) then
        audio:Stop()
    end

    ImGui.Separator()

    ImGui.Text("IsPlaying: "..tostring(audio.isPlaying))

    ImGui.InputFloat("Volume", volume)
    ImGui.InputFloat("Pitch", pitch)
    ImGui.Checkbox("IsLooping", isLooping)

    ImGui.End()
end