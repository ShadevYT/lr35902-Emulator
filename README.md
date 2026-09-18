# lr35902-Emulator
A C++ emulator/core for the Sharp LR35902 processor (Game Boy) in the early stages of development.

Created by **shadev64**.

Current Status (v0.1)
Register and RAM/ROM memory structure (64KB).
Loading `.gb` files into memory.
Reading initial opcodes via console.
Instruction decoding (In progress).

How to download and compile---
1:Download the repo in zip.
2:Go to your lr35902 folder and open the cmd with administrator permissions.
----This part requires a c++ compiler and CMake.
3:Insert this codes in your cmd and your folder of the emulator in order:
mkdir build |
cd build |
cmake .. |
cmake --build . |
