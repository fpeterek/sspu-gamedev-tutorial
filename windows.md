# How to run SFML projects on Windows

Disclaimer: I do not use Windows, I refuse to use Windows, I have no idea 
how to use Windows. This likely isn't the only, nor the most optimal way
to do this. I, however, do not care. If you believe you can do it better,
I will be happy if you submit a merge request.

## Dependencies

### G++

Follow the following instructions to install MinGW:

1) https://code.visualstudio.com/docs/cpp/config-mingw
2) https://www.msys2.org/

It is necessary to follow the instructions found on the second page 
precisely. It is only necessary to follow step 3-4 from the first tutorial.
The first two steps are not necessary, they do, however, make working
with VSCode a bit easier (ie. by ensuring VSCode is installed - it is
difficult to work with a program not found on the device you're currently
using). However, feel free to use any text editor or IDE you like.
I'm only using VS Code for demonstration purposes.

### SFML

Download the SFML library from here: 

https://www.sfml-dev.org/download/sfml/2.5.1/

Extract the archive and copy the extracted folder to the folder where
the SFML project you wish to run is located.

Alternatively, you can perform a system-wide installation of SFML. I do not,
however, know how to do that. Should you wish to pollute your system, you
should do so at your own risk.

## Compilation

Since we're using MinGW, we can use standard GCC flags, as the majority
of us are used to.

```
g++ src/main.cpp -O3 -I .\SFML-2.5.1\include\ -L .\SFML-2.5.1\lib\ -o main -lsfml-window -lsfml-graphics -lsfml-system
```

## Running the program

Unless you have performed a system-wide installation, we must specify
the path to the SFML .dlls. To do so, we can run the following command.

```
$env:Path += ";SFML-2.5.1\bin"
```

This will update the Path variable for the current terminal window.
This change, however, will not be kept and you will need to rerun
the command should you open a new terminal window.

This command must be run from the folder where the `SFML-2.5.1` folder
is located. Otherwise, you must, naturally, modify the command to contain
a correct path.

After we have updated the Path variable, we can run the program using
the following command.

```
./main.exe
```
