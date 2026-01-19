This project uses vcpkg to manage dependencies. Ensure SDL3 is installed via: vcpkg install sdl3.

This is a fish boids simulation based on boids alghorythm developed by Craig Reynolds.
The program works by creating 'sea' with many fishes (default 500) which influence to each other by gathering into groups.

![boids_1](https://github.com/user-attachments/assets/1a9f9e53-1710-4a63-b290-dedbb2668867)

<br><br>

UI includes basic sliders and font created by myself without additional libraries etc.

![boids_2](https://github.com/user-attachments/assets/5c3af9da-159c-4e00-a5b1-c0fc644eab90)
<br><br>

Sliders allow you to adjust many variables. Here's a closer look at how each one works.
1. TRACK DIST - set the radius from whitch fishes start following others
2. CLOSE DIST - set the radius from whitch fishes start to avoid others
3. MOVE SHIFT - if fish dont follow others, it moves in scope of its direction +- MOVE SHIFT [in degrees]. For example, if fish current direction is 37 degrees and MOVE SHIFT = 20, in next iterion fish will be in the scope from 17 tp 57 degrees.
4. VIEW OFFSET – Fish have a range of vision in which they can see others. This corresponds to the fish's direction +- VIEW OFFSET. Works as in the example above. If VIEW OFFSET = 180, fish can see all fish around them; if VIEW OFFSET = 0, fish can only see fish directly in front of them.
5. NOISE FACTOR - set the number of fishes which fish must follow, to be fully following. For example, if NOISE FACTOR = 10, if fish see 10 fishes, its direction depends on other fishes in 100%, but if fish see only 6 other fishes, its direction depend in 6/10 on other fishes and in 4/10 on rand moving (MOVE SHIFT) 
