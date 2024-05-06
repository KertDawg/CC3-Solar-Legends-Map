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
1. Open the `Solar Legends Base Map.FCW` as the base map to draw on.
1. Run the program by typing `SOLARSYSTEM` in the CC3+ window.

##  Using it
This will generate a map for a given day in the Solar Legends game.  The dialog box shows the following options:

**Closest Planet Number**
: This is the index of the innermost planet to draw.  1 is for Mercury, 2 is for Venus, etc.
**Farthest Planet Number**
: This is the index of the outermost planet to draw.
**Day Number**
: This is the day of the campaign.  Start on Day 1.  If the players are on a rocket ship for 10 days, then the next map will be day 11.
**Orbital Radius**
: This is a measure of how big the map is.  A value of 1,000 will show the inner planets and the asteroid belt.  A value of 500 will show the belt out to Saturn.  The higher the number, the closer the view will be to the sun.
**Planet Scale**
: This is how big the symbols that represent the planets are.  The larger the number, the larger the planets will appear.
**Draw Asteroids**
: Should we draw the asteroid belt?
**Draw Labels**
: Should we draw the text labels under each planet?
**Draw Scale**
: Should we draw the map scale showing distance in days of fuel?

When you have selecetd your option, hit `OK` and the map will be drawn.  It is suggested that you turn on `Sheet Effects` to see things correctly.  **DON'T SAVE OVER THE BASE MAP!!!**  Remember to `Save As...` to save this as a different file.

