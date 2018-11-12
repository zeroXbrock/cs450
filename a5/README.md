# Vertex & Fragment Shaders
Uses vertex shader to draw shape & fragment shader to draw on the shape's surface.

### Explanation

**Concept:** OpenGL (from the main program `pattern.cpp`) builds a glutSolidSphere and applies the pattern drawn by the shaders to it à la the `Pattern->Use()` function. Variables are sent to the shaders using 
`Pattern->SetUniformVariable(...)` function calls.

1. The vertex shader applies normalization and (per-vertex) lighting as well as any additional transformations to the object.
2. Per-vertex texture coordinates (s,t) are passed to the fragment shader through the rasterizer.
3. The fragment shader draws a fun pattern on the object originally drawn by the vertex shader using the texture coordinates (s,t); this is represented by vec2 `vST`, which is set by the vertex shader.

### Just The Tips
Vertex vs. Fragment:
> A vertex is a part of a calculated shape which has not been rendered yet. A fragment is effectively a pixel [to be]. Fragments are the pixelated versions of vertices.

`uniform` variables
> `SetUniformVariable(...)` is called in `Display()` which means it's being updated every frame. This is how you get animations/controls into your shaders.

Pro dev tip:
> Get a GLSL linter for VS Code to highlight dat syntax. And get VS Code if you don't have it.
> Also if you use a Mac, build on a Linux system bc Mac's OpenGL is wack.