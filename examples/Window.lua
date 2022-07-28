function world2d.Init()
    local events = {
        "OnWindowShown",
        "OnWindowHidden",
        "OnWindowExposed",
        "OnWindowMoved",
        "OnWindowRezised",
        "OnWindowSizeChanged",
        "OnWindowMinimized",
        "OnWindowMaximized",
        "OnWindowRestored",
        "OnWindowMouseEnter",
        "OnWindowMouseLeave",
        "OnWindowKeyboardFocusGained",
        "OnWindowKeyboardFocusLost",
        "OnWindowClose"
    }

    for _, event in ipairs(events) do
        world2d[event] = function(...)
            print(event, ...)
        end
    end
end