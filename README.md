# C++ Game Development with SFML

To compile the program, run the following command from the root directory. For ease, the include and lib libraries for SFML are included within the src directory, and all relevant .dlls are included within the bin directory alongside the target executable. In theory (untested), this should mean that the cloned repository itself should allow for compilation without issue but this is also windows.

```bash
g++ src/*.cpp -Isrc -o bin/sfmlGame.exe -Isrc\include -Lsrc\lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
```

To run the program:

```bash
start bin/sfmlGame
```

Note, there is also the Makefile which, in theory, should provide the object and executable files within the root directory, however, my computer has issues attempting to run cmake which I cannot be bothered fixing at the moment so I take no responsibility if it doesn't work.

For more information: <https://www.sfml-dev.org/tutorials/2.6/>