# Tweening
This module provides tweening feature. It will help you to make smooth animations.

## Structures

### Tween
``world2d.Tweening.Tween``

#### Creating a tween
``world2d.Tweening.Tween.new(data: table | userdata, easingStyle: world2d.Tweening.EasingStyle, easingDirection: world2d.Tweening.EasingDirection, duration: number, properties: table)``

#### Playing a tween
``world2d.Tweening.Tween:Play()``

#### Pausing a tween
``world2d.Tweening.Tween:Pause()``

## Enums

!> Some easing styles don't work as intented.

``world2d.Tweening.EasingStyle``
```lua
world2d.Tweening.EasingStyle = {
    Linear = 0,

    Quadratic = 1,
    Cubic = 2,
    Quartic = 3,
    Quintic = 4,
    Sextic = 5,
    Septic = 6,
    Octic = 7,

    Back = 8,
    Bounce = 9,
    Circle = 10,
    Elastic = 11,
    Exponent2 = 12,
    Sine = 13,
    ExponentE = 14,
    Log10 = 15,
    SquareRoot = 16
}
```

``world2d.Tweening.EasingDirection``
```lua
world2d.Tweening.EasingDirection = {
    In = 0,
    InOut = 1,
    Out = 2
}
```

## Examples
```lua
function world2d.Init()
    rectpos = {
        x = 20,
        y = 20
    }

    newrectpos = {
        x = 120,
        y = 120
    }

    -- The first argument can be either table or userdata (aka. structure)
    -- After tween is finished, the position will be (120, 120)

    tween = world2d.Tweening.Tween.new(rectpos, world2d.Tweening.EasingStyle.Quadratic, world2d.Tweening.EasingDirection.Out, 10, newrectpos)

    tween:Play() -- Start the tween
end

function world2d.Render()
    world2d.Graphics.SetDrawColor(127, 127, 127, 255)
    world2d.Graphics.Clear()

    world2d.Graphics.SetDrawColor(255, 255, 255, 255)
    world2d.Graphics.DrawRect(world2d.Graphics.DrawMode.Fill, rectpos.x, rectpos.y, 100, 100)
end
```