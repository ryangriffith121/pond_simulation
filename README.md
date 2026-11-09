# Pond Simulation

A small C++ simulation of koi swimming around a pond, drawn with [SFML 3](https://www.sfml-dev.org/). Every fish is generated procedurally: its body bends as it swims, its tail sways, its fins flap, and it picks its own lazy path around the pond.

## Features

- **Wandering fish.** Each koi picks a destination, turns towards it at a limited turn rate, slows down in tight turns, and picks a new one when it arrives (or after 10-20 seconds).
- **Flexible bodies.** A chain of 20 points follows the head, so the body curves naturally when the fish turns. A wave runs from head to tail for the swimming motion.
- **Drawn entirely in code.** Body, forked tail, pectoral and pelvic fins, eyes and spots are built from SFML shapes. There are no image files.
- **Every koi is different.** Each fish gets slightly random proportions (body, tail, fins and eyes each vary by up to 12%), 3 to 5 spots in a random color, and its own speed and turning ability.
- **Stays in the pond.** The whole body, not just the head, is kept inside the pond edges.

## Requirements

- Windows with Visual Studio and the **Desktop development with C++** workload
- [SFML 3.1.0](https://www.sfml-dev.org/download/) (Visual C++, 64-bit build matching your compiler)
- C++17 or newer

## Building and running

SFML is not stored in this repository (`External/` and `*.dll` are in `.gitignore`), so you need to add it yourself:

1. **Clone the repo.**
2. **Download SFML 3.1.0** and unpack it so the folder `pond_sim/External/SFML-3.1.0/` contains `include/` and `lib/`.
3. **Copy the SFML DLLs** from SFML's `bin/` folder into `pond_sim/pond_sim/` (next to `main.cpp`). Debug builds use the `-d` DLLs (for example `sfml-graphics-d-3.dll`) and Release builds use the others (`sfml-graphics-3.dll`).
4. **Open `pond_sim/pond_sim.slnx`** in Visual Studio, choose **x64** and **Debug** or **Release**, and press **F5**.

The project is set to the `v145` platform toolset. If your Visual Studio does not have it, retarget the project under *Project → Properties → Platform Toolset*.

## Using it

There are no controls: a window opens and the fish swim. Close the window to quit.

To change what is in the pond, edit `main.cpp`:

```cpp
const int WINDOW_WIDTH = 500;    // the window and the pond are the same size
const int WINDOW_HEIGHT = 500;

//                x position  y position  name    size  color {red, green, blue}
pond1.addFish(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3, "Paco", 150, { 230, 230, 245 });
```

- **size** is the fish's length from nose to tail tip, in pixels.
- **color** is the body color. The spots get a random color that is re-rolled if it is too close to the body color.

## How it works

**Movement** (`Fish::update`)
1. The fish picks a destination roughly ahead of it (within about 30 degrees, 2 to 5 body lengths away). If a wall is in the way, it aims for a point 60-100% of the way to the wall instead of giving up on that direction.
2. It turns towards the destination, limited by its turn rate, and eases off its speed the sharper the turn is.
3. Each point of the body follows the one in front of it at a fixed spacing.
4. A sine wave, bigger towards the tail, is added to the body points to make the swimming wiggle.
5. If any part of the body would leave the pond, the fish is nudged back in.

**Drawing** (`Fish::draw`), back to front: tail fin, fins, body (a triangle strip along the body points, with a round nose), spots, then eyes.

## Project layout

```
pond_simulation/
├── README.md
└── pond_sim/
    ├── pond_sim.slnx            Visual Studio solution
    ├── External/SFML-3.1.0/     SFML (not in git, see above)
    └── pond_sim/
        ├── main.cpp             window, main loop, which fish are in the pond
        ├── pond.h / pond.cpp    Pond: holds the fish, updates and draws them
        ├── fish.h / fish.cpp    Fish: movement and drawing
        └── pond_sim.vcxproj
```

## Tuning

These constants are at the top of the private section in `fish.h`:

| Constant | Default | What it does |
|---|---|---|
| `minWanderTime` / `maxWanderTime` | 10 / 20 | Seconds before a fish gives up on a destination and picks another |
| `wallMargin` | 0.6 | How close to a wall a fish aims, in body lengths. Smaller means they use more of the pond |
| `wiggleAmount` | 0.04 | How far the tail swings side to side, as a fraction of body length |
| `partVariation` | 0.12 | How much each body part can randomly differ (0.12 is up to 12% bigger or smaller) |
| `noSpotChance` | 0.0 | Chance a koi has no spots. 0 means every koi has spots, 0.25 means one in four is plain |
| `eyeSize` | 5 | Eye radius in pixels, the same for every fish size |
| `pupilSize` | 0.5 | Pupil radius as a fraction of the eye |
| `bigFinSize` / `smallFinSize` | 0.16 / 0.10 | Pectoral and pelvic fin length as a fraction of body length |

Swimming speed (0.3 to 0.7 body lengths per second) and turn rate (1.4 to 2.0 radians per second) are chosen per fish in the `Fish` constructor in `fish.cpp`.

## Known limitations

- The fish ignore each other, so they can swim through one another.
- The Visual Studio project files are Windows-only. The C++ code only depends on SFML, which also supports Linux and macOS, but there is no build file for them yet.
