# Threading
This module provides threading access.

## Structures

### Thread
``world2d.Threading.Thread``

#### Creating a thread
``function world2d.Threading.Thread.new(callback: function, threadName: string)``

#### Thread's name
``world2d.Threading.Thread.name: string``

#### Thread's callback
``world2d.Threading.Thread.func: function``

#### Thread's ID
``world2d.Threading.Thread.id: number``

#### Waiting for thread to finish
``function world2d.Threading.Thread:Wait()``

#### Detaching a thread
``function world2d.Threading.Thread:Detach()``

## Functions

### Get current thread's ID
```lua
world2d.Threading.GetCurrentThreadID(): number
```

### Set current thread's priority
```lua
world2d.Threading.SetCurrentThreadPriority(priority: string)
```

Priorities: Low, Normal, High, TimeCritical