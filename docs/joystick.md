# Joystick
This module provides joystick access.

## Structures

### Joystick
!> This structure can't be created manually.

``world2d.Joystick``

## Name of the joystick
``world2d.Joystick.name: string``

## Number of axes
``world2d.Joystick.numOfAxes: number``

## Number of buttons
``world2d.Joystick.numOfButtons: number``

## Is joystick attached
``world2d.Joystick.isAttached: boolean``

## Is joystick button pressed
``function world2d.Joystick:IsButtonPressed(button: string)``

## Events

### Joystick button is pressed up
```lua
function world2d.OnJoystickButtonUp(joystick: world2d.Joystick, button: string)

end
```

### Joystick button is pressed down
```lua
function world2d.OnJoystickButtonDown(jostick: world2d.Joystick, button: string)

end
```

### Joystick axis motion
```lua
function world2d.OnJoystickAxisMotion(joystick: world2d.Joystick, axis: string, value: number)

end
```

### Joystick added
```lua
function world2d.OnJoystickAdded(joystick: world2d.Joystick)

end
```

### Joystick removed
```lua
function world2d.OnJoystickRemoved(deviceId: number)

end
```

## Functions

### Getting all joysticks
```lua
world2d.Joystick.GetJoysticks(): {world2d.Joystick}
```

### Getting total amount of joysticks
```lua
world2d.Joystick.NumJoysticks(): number
```