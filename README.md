# (Yet another) Chip8 Emulator

![Alt Text](https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExdjFna3poMnFyZHhvczh3M3J0OWxhb2d2bzIzemNkZmJ1ZjBxNWsweiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/TbiqNPEzT25BqP8CrN/giphy.gif)

## v1.0 (first build!)
I've been learning C++ on my own and I have a personal interest in emulation, so I decided to combine both on this project.

### The emulator can:
* Load rom via path string in main.cpp
* Fetch, decode and execute instructions

I've included some ROMs in case anyone wants to try it (you would have to build SDL2 in your system if you haven't).


### Notes:
* Audio implementation is still pending
* There's a movement bug when you start roms that require movement

### CURRENT: 

- [ ] Implement sound_timer & sdl_sound
- [ ] Fix movement bug
- [ ] General cleaning and final touches


#### done:
- [x] Find best place to put SDL
- [x] Copy ROM to internal memory
- [x] Read ROM correctly 
- [x] Get loop to read and do instructions
- [x] Goal: successfully show IBM logo
- [x] Make IBM logo show for a while, pass other tests
- [x] Refactor and clean code
- [x] Finish instructions
- [x] Implement keyboard

