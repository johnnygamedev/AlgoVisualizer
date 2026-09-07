# Algorithm Visualizer (C++ / Raylib)
A quick sorting visualizer I built using C++ and Raylib. I wanted to see how sorting algorithms actually work step-by-step (havent done them in awhile so wanted to get back on the wagon for algorithms with the simple ones), so I rewrote the standard loops to update the screen frame-by-frame instead of finishing instantly.

# Key Features
Step-by-Step Sorting: Selection, Bubble, and Insertion sort broken down into step functions so you can watch them sort elements in real time.

Interactive Buttons: Simple UI buttons with mouse collision and hover states to switch algorithms or reset the array on the fly.

Color Tracking: Blue highlights active comparisons, White shows unsorted bars, and Purple marks the array when fully sorted.

Randomized Arrays: Uses C++ random tools (std::mt19937_64) to spawn a new set of values when you reset.

30 FPS Cap: Lowered the framerate to 30 FPS so the sorting steps run slow enough to actually follow.

# Tech Used
Language: C++

Graphics / UI: Raylib

Tools: std::vector, std::set, std::mt19937_64

# Controls
Selection / Bubble / Insertion Buttons: Switches the active sorting algorithm and regenerates the array.

Reset Button: Spawns a brand new unsorted array.

