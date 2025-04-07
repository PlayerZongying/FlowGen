# Engine Document

# Graphics

1. Mesh & Obj Loader: 

There is a Mesh Class to store position, uv, and normal information which the ObjLoader can deliver. The ObjLoader supports uv, normal, and trianglization. The ObjLoader can also serialize and deserialize mesh data to reduce loading time,

2. Texture

The Texture class uses `stb_image.h` to load a jpg or png as a texture.

3. Shader

The Shader class could load vertex and fragment shaders through the file path to create an OpenGL shader program.

4. Resource Handler

The created meshes, textures, and shaders will be stored in ResourceHandler for further use instead of instanting again.

4. Virtual Object

The VirtualObject contains mesh, texture, shader, transform, for rendering, name for display in the UI, and collider for physics simulation.

6. Light and Light Manager

There are four light types. Every light has attributes such as `LightType`(none, directional, point, and spot),  `position`, `direction`, `intensity`, `length`, `angle`, `ambient`, `diffuse`, and `specular`.

LightManager will instantiate 9 lights. But by default, the light type is none, which means the default light will be ignored by the rendering pipeline.

“Turn on” a light by setting the LightType to either `directional`, `point`, or `spot`.

“Turn off” a light by setting the LightType to `none`. 

Currently only lights[0] support shadow mapping for the `spot` light.

# Physics

1. Collider & Collision

Collider has attributes such as transform, velocity, mass, etc.

Collider Has child classes BoxCollider and SphereCollider.
When two colliders collide, collision will be returned, with the two collider pointers and the collision point (position).

2. Ray & RayHit

Ray has attributes such as origin and direction.

When a ray hit a collider, a RayHit will be returned, with the hit collider pointer, hit point (position), and distance.

3. FlowPhysics

Has a physics simulate function to run in the main function loop, checking collisions and ray hits, to move the colliders as well as the virtual objects.

# UI

1. Object Hierarchy

Listing the rendered virtual objects. Can adjust their transform, mesh, textures, shader, and name.

There is a button to create a new virtual object (a cube by default), and a button to delete the selected virtual object.

There is a UI down below to save and load levels, currently only save and load the transform of the virtual objects.

2. Light viewer

Listing all 9 lights and their property, which can also be adjusted.

3. Physics Simulation

There is a blue button to toggle physics simulation.