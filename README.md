# ConsoleRPG
 This projects main purpose is to create a game, entirely under console terminal without any graphic libraries. The only ones used are mostly libraries like Windows.h, string, vector, math.h, etc.
All the textures are saved in .txt files, where every pixel is represented by ID (every available color is indexed, I would say there are about seven houndred of them).
The most important thing in the project is how Windows.h library lets us modify attributes of the console:

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, <liczba>);

Code shown above lets us change the color of letters and the background to predefined combination. The console has 16 available colors, which theoretically gives us 256 combinations, but we have to remember that some of the combinations wouldnt be of much use - for example blue letters on blue background etc. 
Additionally, I used 3 ASCII characters, that let us trick human eye into seeing more colors. Using them should give us 4 times as much colors (3 ASCII characters + space as blank pixel), but if we take situations that look identical into consideration we will be left with exactly 735 colors.
Here are some links that show how the game currently looks like, what ASCII characters are used and how they look up close:
https://drive.google.com/file/d/10v6TLQDO5ertlBdH-ZcFyCvQTPcQKq-5/view
https://drive.google.com/file/d/1IytSQRTtdcAuf3kRXl20wlp9scNOa-DL/view
https://drive.google.com/file/d/1z8tyksdds9qTBh8k3AaWG07WM9RDwmGI/view

