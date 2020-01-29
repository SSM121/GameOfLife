#The Game of life
This is based off Conway's Game of life. A description can be found [here.](https://en.wikipedia.org/wiki/Conway's_Game_of_Life)

This repo contains 2 simple implementaions. in the unix_term folder there is a single c++ file that can be compile on a linux command line. It may work on specific bash terminal emulators. This was tested on linux mint cinnamon with the konsole terminal. The terminal is important since it uses color escape sequences. This was made to not rely on outside libraries or system calls but instead uses standard iostream items.

The second folder(olc_dep) contains the game of life using a simple graphics library from the youtuber [One Lone Coder](https://www.youtube.com/channel/UC-yuWVUplUJZvieEligKBkA) The inclusion of his info both here and in the header fullfills his license. This is cross platform and has been tested in visual studios and with the g++ command in the .cpp file. There are some dependencies that need to be there. 
