# Algorithm Visualizer (C++ / Raylib)
A quick sorting visualizer I built using C++ and Raylib. I wanted to see how sorting algorithms actually work step-by-step(havent done them in awhile so wanted to get back on the wagon for algorithms with the simple ones), so I rewrote the standard loops to update the screen frame-by-frame instead of finishing instantly.

# Key Features
Step-by-Step Sorting: Bubble, Selection, and Insertion sort loops into step functions so you can watch them move array items in real time.

Color Tracking: Uses Blue to show elements being actively compared or moved, White for unsorted values, and turns Purple when the array is fully sorted.

Randomized Arrays: Uses standard C++ random tools (std::mt19937_64) to spawn a new set of randomized values every time you launch.

30 FPS Target: Capped the framerate at 30 FPS so the algorithms run slow enough to clearly follow.

# Tech Used
Language: C++

# Graphics: Raylib

