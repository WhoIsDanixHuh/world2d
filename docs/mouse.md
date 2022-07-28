# Mouse
This module provides mouse access.

## Events

### Mouse is pressed
```lua
function world2d.OnMousePressed(x: number, y: number, buttonName: string)

end
```

### Mouse is released
```lua
function world2d.OnMouseReleased(x: number, y: number, buttonName: string)

end
```

### Mouse motion
```lua
function world2d.OnMouseMotion(x: number, y: number, xrel: number, yrel: number)

end
```

### Mouse wheel motion
```lua
function world2d.OnMouseWheelMotion(x: number, y: number, direction: string, preciseX: number, preciseY: number)

end
```

## Functions

### Getting mouse coordinates
```lua
world2d.Mouse.GetCoordinates(): number, number
```