This project uses vcpkg to manage dependencies. Ensure SDL3 is installed via: vcpkg install sdl3.

This is a fish boids simulation based on boids alghorythm developed by Craig Reynolds.
The program works by creating 'sea' with many fishes (default 500) which influence to each other by gathering into groups. 
Map have 4000x4000 units.

![boids_1](https://github.com/user-attachments/assets/1a9f9e53-1710-4a63-b290-dedbb2668867)
<br><br>

UI includes basic sliders and font created by myself without additional libraries etc.

![boids_2](https://github.com/user-attachments/assets/5c3af9da-159c-4e00-a5b1-c0fc644eab90)
<br><br>

There is an option to move and zoom in/out the screen, unfortunately every move/zoom delete the tails of fishes which was displayed.

![boids_3](https://github.com/user-attachments/assets/aa3ef52a-f598-40f8-85ea-6ab367b0245d)
<br><br>

Sliders allow you to adjust many variables. Here's a closer look at how each one works:
1. TRACK DIST - set the radius from whitch fishes start following others.
2. CLOSE DIST - set the radius from whitch fishes start to avoid others.
3. MOVE SHIFT - if fish dont follow others, it moves in scope of its direction +- MOVE SHIFT [in degrees]. For example, if fish current direction is 37 degrees and MOVE SHIFT = 20, in next iterion fish will be in the scope from 17 tp 57 degrees.
4. VIEW SHIFT – Fish have a range of vision in which they can see others. This corresponds to the fish's direction +- VIEW OFFSET. Works as in the example above. If VIEW OFFSET = 180, fish can see all fish around them; if VIEW OFFSET = 0, fish can only see fish directly in front of them.
5. NOISE FACTOR - sets the number of fishes to follow, to have full focus on follow. For example, if NOISE FACTOR = 10, if fish see 10 fishes, its direction depends on other fishes in 100%, but if fish see only 6 other fishes, its direction depend in 6/10 on other fishes and in 4/10 on random moving (MOVE SHIFT).
6. CLOSE FACTOR - affects the force with which fish that are too close [CLOSE DIST & VIEW SHIFT] want to move away from each other
7.1 FISH R , FISH G , FISH B - sets the rgb color of fish which moves randomly ( dont focus on anyone ).
7.2 FOCUS R , FOCUS G , FOCUS B - sets the rgb color of fish which is fully focused on other fishes ( number of following fishes >= NOISE FACTOR ).
7.3 every fish which follow more than 0 and less than NOISE FACTOR have blended color based on FISH rgb and FOCUS rgb.
8. SPEED - represent number of units which fishes 'jumps' on every iteration.
9. BLUR - value of transparency from 0 to 255 which is layered in every iteration. If blur = 255, fishes will dont have tails, if blur = 0, tails will not fade.
10. DELAY MS - delay betweend every iteration in milliseconds.
11. FISHES NUM - number of fishes in whole map
    
these settings allow you to create interesting effects:

![boids_4](https://github.com/user-attachments/assets/0fe18c6d-96a9-4c03-8c69-baffa37f4d06)
