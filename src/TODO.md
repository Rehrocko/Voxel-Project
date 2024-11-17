This is how the structure of the game will look (hopefully)

# Frame Begins:

We begin by running through a list of all loaded chunks (loaded will be calculated via a method described later)

From this list of loaded chunks we cull the ones outside of view.
To find if the given point is within the view or not we check to see if the given point is within the viewport
In order to see if the point is within the viewport we apply multiple transformations to it.
We take the chunk then we apply several matrices on top of it. First being the model matrix (essentially what will be the center of the chunk),
then we apply the view matrix, then we apply the projection matrix, now that all this transformation is done, we can check to see if the
resulting coordinate is within thet -1.0 -> 1.0 range (I would give it a 0.2 extra range, then change that from there)
An issue that may pop up is chunks being deleted near the edge of the screen, in which you would increase the dead zone.

!! Do some experimentation to see if we can do without the last projection matrix transformation for optimization !!

**One final addition, if a chunk is blocked by another chunk, how we will do this, I don't know...**

Now that we have done a rough cull on all of the chunks we can move on to rendering each chunk, each chunk with be (probably) 32x32x32,
we basically copy down what TanTan has done, so we would loop through all of the voxels within our working chunk, load that into a big ol'
binary array, and also load in the neighboring chunks borders. Then we continue copying TanTan.

After we have rendered our chunk we can move onto to more of the game logic. I won't write that down in this commit as it is getting late.

This should provide a basic starting point for the game logic to go off of.

## How will we find these chunks?

Each chunk will be defined at a specific ChunkPos, an IVec3 that, when given a certain value, like (3, 2, 1), loops through each loaded chunk
to see if there is one that has the position (3, 2, 1)
!! Warning !! This may be terribly inefficent, however, this is all I could think of at 10:33 PM, another solution I had was to hash positions,
I.E make (3, 2, 1) an integer like 78590234, however, I believe this is already how an IVec3 works so I doubt it would optimize...
We want a way to also convert voxel coord to chunk pos, so that a voxel at (534, 123, 52) lines up to chunk (16, 3, 1), or something like that,
this may entirely be unnecessary I don't know yet.

# Currently working on

- Create voxel class
- Create some way to color the voxels and get depth