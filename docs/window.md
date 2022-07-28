# Window
This module provides functions to manage a window.

## Events

### Window shown
```lua
function world2d.OnWindowShown()
    
end
```

### Window hidden
```lua
function world2d.OnWindowHidden()
    
end
```

### Window exposed
```lua
function world2d.OnWindowExposed()
    
end
```

### Window moved
```lua
function world2d.OnWindowMoved(x: number, y: number)
    
end
```

### Window resized
```lua
function world2d.OnWindowResized(w: number, h: number)
    
end
```

### Window's size changed
```lua
function world2d.OnWindowSizeChanged(w: number, h: number)

end
```

### Window minimized
```lua
function world2d.OnWindowMinimized()

end
```

### Window maximized
```lua
function world2d.OnWindowMaximized()

end
```

### Window restored
```lua
function world2d.OnWindowRestored()

end
```

### Mouse entered a window
```lua
function world2d.OnWindowMouseEnter()

end
```

### Mouse leaved a window
```lua
function world2d.OnWindowMouseLeave()

end
```

### Window gained a keyboard focus
```lua
function world2d.OnWindowKeyboardFocusGained()

end
```

### Window lost a keyboard focus
```lua
function world2d.OnWindowKeyboardFocusLost()

end
```

### Window closed
```lua
function world2d.OnWindowClose()

end
```

## Enums

``world2d.Window.MessageBoxType``
```lua
world2d.Window.MessageBoxType = {
    Error = 0, -- Error message box
    Warning = 1, -- Warning message box
    Information = 2 -- Information message box
}
```

``world2d.Window.FlashOperation``
```lua
world2d.Window.FlashOperation = {
    Cancel = 0, -- Cancel flashing
    Briefly = 1, -- Flash briefly to get user's attention
    UntilFocused = 2 -- Flash until window is focused
}
```

## Functions

### Setting window's position
```lua
world2d.Window.SetPosition(x: number, y: number)
```

### Setting window's size
```lua
world2d.Window.SetSize(w: number, h: number)
```

### Getting window's size
```lua
world2d.Window.GetSize(): number, number
```

### Setting window's title
```lua
world2d.Window.SetTitle(title: string)
```

### Getting window's title
```lua
world2d.Window.GetTitle(): string
```

### Setting window resizable
```lua
world2d.Window.SetResizable(resizable: boolean)
```

### Showing simple message box
```lua
world2d.Window.ShowSimpleMessageBox(messageBoxType: world2d.Window.MessageBoxType, title: string, message: string)
```

### Flashing a window
```lua
world2d.Window.Flash(flashOperation: world2d.Window.FlashOperation)
```

### Setting vertical synchronization
```lua
world2d.Window.SetVSync(vsync: boolean)
```

### Getting display size
```lua
world2d.Window.GetDisplaySize(): number, number
```