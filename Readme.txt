https://github.com/KiranAneca/Minigin

- All the gameobjects are build up out of components.
- All components come from a basecomponent base class.
- Most things interact using the observer pattern.
- Commands can be bound using a custom command and a button or controller input.
- The UI is drawn from a Gamerenderer class, this class calls the base render (the rendering of the gameobject), but adds the UI made for the specific game.