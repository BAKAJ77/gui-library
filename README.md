# GUI Library

## About
This is a C++ graphical user interface library that I have developed for my final year university coursework project. This library was implemented in C++ 17 and has only been tested in a Windows OS environment, therefore cross-platform compatability is not ensured.

## Building the project
You will only require CMake in order to build this project. </br>
1. Firstly, you will need a local copy of the repository on your computer. Easiest way to do it is cloning straight from GitHub.
2. Go to the root directory of the project and create a new folder, you can call it whatever you want though I usually just name it `Build`.
3. Go into the new folder you've created and execute `Command Prompt` in this directory.
4. Once open, simply run this command `cmake ../`. This should generate the project files necessary for you to build the library yourself.
5. This is an optional step, however you tell CMake to build the library and generate its binaries for you by simply running this command `cmake --build .` after the one in step 3.
6. The compiled binaries for the library, its tests, and the examples should be located in the `bin` folder.

## License
This project is released under the terms of the MIT license. See [LICENSE](LICENSE) for more information or see https://opensource.org/licenses/MIT.
