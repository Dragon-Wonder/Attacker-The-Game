# Change Log

All notable changes to this project will be documented here.
This project adheres to [Semantic Versioning](http://semver.org/)

## [0.9.8-Alpha.6] - 2021-09-02
### Added
* More monsters

### Updated
* Reduced monster skill points per level from 18 -> 15
* Changed Mana modifying state to be based on DEF, DEX, and LUK

## Fixed
* Modifier calculator being off and not recalculating

## [0.9.8-Alpha.5] - 2019-04-10
### Updated
* Readme.md with some additional controls

### Added
* SDL display to the winning/losing message
* Element types to monsters
* Element types to spells
* Modifier to damage based on elements (Suggestion: #14, partially implemented)

### Fixed
* src/ui/image_error.xpm variable name including file path

## [0.9.8-Alpha.4] - 2019-04-09
### Changed
* Updated the Images/readme.md file to have to correct image referenced and correct source paths.
* More work on the level up
* Locked door tile now replaced with unlocked door when walked through (aka unlocked)
* Made src/ui/image_error.xpm simplifier and smaller

## [0.9.8-Alpha.3] - 2019-04-05
### Added
* Visual Studio Project file

### Fixed
* Some files paths being wrong from when I moved stuff into folders


## [0.9.8-Alpha.2] - 2019-04-05
### Added
* More work on the level up support with SDL (still WIP)

### Changed
* Screen won't refresh constantly when displaying an unchanged screen.
* Changed "cons" stat to "con" to be better in line with the other names
* Improved Doxygen stuff
* Splash screen now appears in Non-private releases
* Moved away from CodeBlocks because things are broken
* Moved src files to folders to better organize code better

### Fixed
* Splash not being correct ratio

## [0.9.8-Alpha.1] - 2019-04-04
### Added
* Level up support with SDL (WIP)

### Removed
* Excess whitespace

### Fixed
* More spelling mistakes

## [0.9.7-Alpha] - 2019-03-30
### Removed
* Some code left in when debugging

### Fixed
* Spelling mistakes

## [0.9.6-Alpha] - 2016-07-29
### Added
* Doxygen stuff for new functions added in last update
* Some equations that will likely remain unused for a while
* Mana regen
* Messages to SDL screen about when to look at terminal to do stuff.

### Updated
* Finished battle scene (Note, I still haven't fully tested the balance)

### Fixed
* Bug with player initialize taking newline for input before it


## [0.9.5-Alpha] - 2016-07-28
### Fixed
* Merge mess up from the last update (I keep forgetting that since I have my code in two places I have to copy the git between them as well)

### Updated
* Modified equations for Health, Mana and gold

### Added
* Doxygen equations for health, mana and gold
* Monsters
* Started Battle Scene (unfinished)
* Damage calculating equation

## [0.9.4-Alpha] - 2016-07-25
### Fixed
* Doxygen file
* SDL Screen crashing on Load / New / Save

### Added
* Level up function for player
* Monsters


## [0.9.3-Alpha] - 2016-07-19
### Added
* Saving / loading
* More Doxygen info
* Health Calculations
* Healing

### Updated
* Changed how config prompts are handled
* Changed default map size
* Improved Doxygen file


## [0.9.2-Alpha] - 2016-07-14
### Fixed
* Walking will no longer replace all tiles with dirt floor
* Walking up/down being flipped around

### Added
* Better Todo list
* Some Calculations (Health, dodge check, element multi) currently all just a carry over from the old program. Will likely be changed later.

### Updated
* Shrunk tile pic size from 24 to 16


## [0.9.1-Alpha] - 2016-07-13
### Added
* Basic menu system (WIP)

### Fixed
* Error with entering player stats
* Map not loading correctly

### Added
* Doxygen file (still needs some tweaking)

### Updated
* Changed max screen size + map size
* Changed default font


## [0.9.0-Alpha] - 2016-07-12
### Updated
* Rewrote the program from the ground up
* Program now uses SDL graphics
* Change log to be more in line with my other programs
* Versioning to be more in line with my other programs

### Notes
* Reset the versioning, deprecated all earlier versions
* I wanted to make a new game from scratch but kept coming back to this one, so I just decided to redo this one from the ground up.
* This is the first of the rewrites. At the moment it can make a dungeon and allows you to walk around. It is very skeleton like and has a lot of features tagged as "add later"


## Pre-rewrite change log
```
## [1.5.4-C] - 2015-09-25
### Added
* Global Version
* Warning about using code blocks for compiling

### Fixed
* Some Code Block settings

### Updated
* Cleaned Save.cpp

## [1.5.3-C] - 2015-09-24
### Added
* Proper Header Files
* Global Debug Value

### Updated
* Cleaned up code

### Fixed
* Autoversion (keeps getting messed up)
* Spelling mistakes

### Notes
* I keep saying I'm not going to update this anymore but I was looking at it and I just couldn't deal with how bad it was and had to fix it a bit.


## [1.5.2-C] - 2015-09-22
### Fixed
* Version info being wrong
* Compile issue

## [1.5.0-C] - 2015-09-22
### Added
* Verison.h
* Code Blocks Support
* Icon
* Boilerplate info
* Compile.bat

### Removed
* Change log at the start of every file

### Updated
* Folders of the program to be cleaner
* Compiler from Cygwin to MinGW / Code blocks

### New
* Change log (everything before this one is considered "lost")
```