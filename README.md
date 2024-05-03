# CC3-Solar-Legends-Map
A Campaign Cartographer XP add-on to generate a solar system map for Solar Legends

## Solar Legends
Solar Legends is a tabletop roleplaying game.  You can find it [here](https://solarlegends.kertdawg.net/).  It uses a solar system map that changes over time.  The planets orbit the sun.  This map represents that movement.

## Campaign Cartographer
Campaign Cartographer 3 Plus (CC3 or CC3+) is a cartography program.  There is an add-on available called "Cosmographer."  CC3-Solar-Legends-Map requires CC3+ and Cosmographer to run.  This add-on is an XP type add-on.

## Building
This guide assumes Visual Studio 2022 Community.  VS 2019 should also work with some tweaks to the setup.  Visual C++ is required.

1. Download `xp template 2022.vsix` and configure it per [these instructions](https://cc.monsen.cc/blog/XP%20Template.html).
1. Open `CC3PlanetXP.sln` in Visual Studio.
1. Build and run the CC3PlanetXP project.  It should launch a CC3+ window.
1. Run the program by typing `SOLARSYSTEM` in the CC3+ window.
