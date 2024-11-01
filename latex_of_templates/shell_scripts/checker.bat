@echo off

cd %1

del .\main.exe

g++ -o main.exe main.cpp -DLOCAL -std=c++17 -ftrapv

for %%i in (*.in) do (
    main.exe < %%i > %%~ni.out
    echo case %%~ni:
    echo My:
    type %%~ni.out
    echo Answer:
    type %%~ni.ans
)

cd ../shell