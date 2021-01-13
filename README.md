VNES_Engine
=====
A visual Novel Engine for the NES coded in C.
The end goal is to make it generic enough so that the code can be reused as a base on other games, or even different platform (PC or other consoles).

[Open this project in 8bitworkshop](http://8bitworkshop.com/redir.html?platform=nes&githubURL=https%3A%2F%2Fgithub.com%2FNightenDushi%2FVNES_Engine&file=VN_Engine.c).

**Feature**
- TypeWritter effect
- Choice
- Jump to specific line
- Change character expression

**ToDo in the future**
- Labels (so you don't have to specify the specific line to jump to) (!)
- Flags and conditional jump
- More flexible way to add characters to the game

__
Files:

**VNES_Engine.c**
Main file : initialize data and manage the game loop

**script_fr.h, script_en.h**
Contain the visual novel content (texte, choices...) in french and english. The english script is still a work in progress.

**beach_shertigan.s**
Music file not yet included in the game (sadly)

