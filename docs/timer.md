# Timer
Timer will help you to time your actions. It also provides you with data like FPS.

## Functions

### Stopping a thread for certain amount of time

!> Using this function in main thread will freeze entire thread, which means world2d will stop responding for a certain time. Prefer using the function in separate thread.

```lua
world2d.Timer.Delay(ms: number)
```

### Getting current FPS
```lua
world2d.Timer.GetFPS(): number
```