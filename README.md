-----
SETUP
-----
Download VS Code From here: https://code.visualstudio.com/
Make sure you have the following extensions in VS code installed.
>C/C++,
>Include Autocomplete (optional),
>Shader languages support for VS Code (optional)

If on 'WINDOWS' platform download and install MinGW.
https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download
Then download all necessary packages for MinGW listed below.
>mingw-developer-toolkit,
>mingw32-base,
>msys-base,
>mingw32-gcc-g++

Add 'C:/MinGW/bin' to your 'path' in 'system environment variables'
You can access 'system environment variables' by going to properties of 'This PC'/'My Computer'
and clicking 'advanced system settings'
NOTE: you will have to restart cmd or vs code if it is running.

Copy folders inside '.SDK' folder and paste it into 'C:/MinGW'
This will allow mingw to compile the code using the nessassary libraries required for the project.

Open the folder containing 'main.c' with vs code and go to debug tab on the left.
Make sure from the drop down your platform is selected and click debug.
-----------
INFORMATION
-----------
This game engine was created by Zeeshan Abid.
It uses the following libraries:
>Glew, Glu, OpenGL, SDL2, SDL2 Image, SDL2 TTF, Open AL, Bullet Physics Library