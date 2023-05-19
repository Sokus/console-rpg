# ConsoleRPG
This projects main purpose is to create a game, entirely under console terminal without any graphic libraries - it was the first project I have ever worked on. Apart from system headers and standard library this project has no dependencies.

https://github.com/Sokus/console-rpg/assets/26815390/de0f842e-efbf-4dc1-a4cb-390b03f39786

This project is dependent on two Windows API functions, first one for getting the standard output handle:
```c
HANDLE WINAPI GetStdHandle(
    _In_ DWORD nStdHandle
);
```  
And the second one that lets us change the color used in the terminal:
```c
BOOL WINAPI SetConsoleTextAttribute(
    _In_ HANDLE hConsoleOutput,
    _In_ WORD   wAttributes
);
```  
It has only 16 colors to choose from, but by creatively using some ASCII characters (for example ▓▓▒▒░░) we could easily increase the number of perceived colors available to 784. All textures are stored as a series of numbers (color indices) in .txt files.
