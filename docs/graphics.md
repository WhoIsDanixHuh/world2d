# Graphics
Graphics is the main module in world2d. It provides you with useful structures and functions to render anything you want.

## Structures

### Texture
``world2d.Graphics.Texture``

#### Creating a texture
``function world2d.Graphics.Texture.new(pathToImage: string)``

#### Getting texture's width
``world2d.Graphics.Texture.w: number``

#### Getting texture's height
``world2d.Graphics.Texture.h: number``

#### Drawing a texture
``world2d.Graphics.Texture:Draw()``

``world2d.Graphics.Texture:Draw(x: number, y: number)``

``world2d.Graphics.Texture:Draw(x: number, y: number, w: number, h: number)``

### Sprite
``world2d.Graphics.Sprite``

#### Creating a sprite from image
``world2d.Graphics.Sprite.new(pathToImage: string)``

``world2d.Graphics.Sprite.new(pathToImage: string, x: number)``

``world2d.Graphics.Sprite.new(pathToImage: string, x: number, y: number)``

``world2d.Graphics.Sprite.new(pathToImage: string, x: number, y: number, w: number)``

``world2d.Graphics.Sprite.new(pathToImage: string, x: number, y: number, w: number, h: number)``

#### Creating a sprite from existing texture

!> Currently doesn't work. Don't use these constructors.

``world2d.Graphics.Sprite.new(texture: world2d.Graphics.Texture)``

``world2d.Graphics.Sprite.new(texture: world2d.Graphics.Texture, x: number)``

``world2d.Graphics.Sprite.new(texture: world2d.Graphics.Texture, x: number, y: number)``

``world2d.Graphics.Sprite.new(texture: world2d.Graphics.Texture, x: number, y: number, w: number)``

``world2d.Graphics.Sprite.new(texture: world2d.Graphics.Texture, x: number, y: number, w: number, h: number)``

#### Sprite's texture
``world2d.Graphics.Sprite.texture: world2d.Graphics.Texture``

#### Sprite's X position
``world2d.Graphics.Sprite.x: number``

#### Sprite's Y position
``world2d.Graphics.Sprite.y: number``

#### Sprite's width
``world2d.Graphics.Sprite.w: number``

#### Sprite's height
``world2d.Graphics.Sprite.h: number``

#### Drawing a sprite
``function world2d.Graphics.Sprite:Draw()``

#### Checking if sprite is colliding with another sprite
``function world2d.Graphics.Sprite:IsCollidingWith(target: world2d.Graphics.Sprite)``

### Font
``world2d.Graphics.Font``

#### Creating a font
``function world2d.Graphics.Font.new(pathToTTFfont: string, fontSize: number)``

#### Getting text size
``function world2d.Graphics.Font:GetTextSize(text: string): number``

#### Drawing text with a font
``function world2d.Graphics.Font:Draw(text: string, x: number, y: number)``

``function world2d.Graphics.Font:Draw(text: string, x: number, y: number, w: number, h: number)``

## Events

### Initialization
Use this event to initialize your stuff.

```lua
function world2d.Init()
    -- Some initialization
end
```

### Updating
This event is called every frame. Use it to update your stuff.

```lua
function world2d.Update(deltaTime: number)
    -- Updating...
end
```

### Rendering
This event is called every frame. Use it to render your stuff.

```lua
function world2d.Render()
    -- Rendering...
end
```

## Enums

``world2d.Graphics.DrawMode``
```lua
world2d.Graphics.DrawMode = {
    Fill = 0, -- Fill entire primitive
    Line = 1 -- Outline primitive
}
```

## Functions

### Setting draw color
Sets the drawing color. This color is used to render primitives and clearing the screen.

```lua
world2d.Graphics.SetDrawColor(r: number, g: number, b: number, a: number)
```

### Getting draw color
```lua
world2d.Graphics.GetDrawColor(): number, number, number, number
```

### Clearing the screen
```lua
world2d.Graphics.Clear()
```

### Drawing a line
```lua
world2d.Graphics.DrawLine(x1: number, y1: number, x2: number, y2: number)
```

### Drawing a point
```lua
world2d.Graphics.DrawPoint(x: number, y: number)
```

### Drawing a rect
```lua
world2d.Graphics.DrawRect(drawMode: world2d.Graphics.DrawMode, x: number, y: number, w: number, h: number)
```

### Drawing a circle
```lua
world2d.Graphics.DrawCircle(drawMode: world2d.Graphics.DrawMode, x0: number, y0: number, radius: number)
```