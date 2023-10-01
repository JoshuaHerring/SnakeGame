# Overview
This snake game is a project that I made in order to learn the C++ language. **To run this game** download/clone the code and Download the Raylib Library to your environment. Then simply run it in any environment that can run C++.

## Description
This software is a basic snake game. You control a snake using the wasd keys to move around a 2d plane.

There is an apple that gets randomly generated on the plane and when the head of your snake collides with it the snake eats it producing a sound and growing your snake by an additional section. A new apple then appears onto the screen and your score is incremented by 1. Your score is displayed at the top of the screen.

When the snake hits the endge of the screen he will proceed to the opposite side of the screen. If the head of the snake collides with any part of the body of the snake then it produces a sound and ends the game by displaying end game text and preventing you from eating any more apples and locking your score.


## Purpose
I wrote this snake game to learn and understand C++. This was my first project in C++ so I tried to write software that would force me to learn a wide range of C++ skills. In particular I strived to learn and understand the following C++ topics.

- Classes
- Functions
- The STL Library
- A variety of data Structers
- Variables
- Non Standard Libraries
- Expressions
- Conditionals
- Loops

## Video Demo
{Provide a link to your YouTube demonstration. It should be a 4-5 minute demo of the software running and a walkthrough of the code. Focus should be on sharing what you learned about the language syntax.}

[Software Demo Video](http://youtube.link.goes.here)

# Development Environment

I used the **C++ language** inside of the **Visual Studio Community IDE** To develop this game.

### C++ & Libraries

C++ is a very popular programming language that is often times used in operating systems, Graphical User Interfaces, embedded systems, and game development. C++ is also adept and being used on many different platforms and systems from moblie to desktop, from operating systems on Super-Computors to mars rovers.

I used vcpkg as my package manager to handle my pakages instalation and linking to my code.

Within C++ I used the STL Libraries. I used this mainly for the deque structure which holds the snake.

I also used the Raylib Library which handled a lot of the boilerplate for the graphics of the game.

# Useful Websites

- [W3schools C++](https://www.w3schools.com/cpp/cpp_intro.asp#:~:text=C%2B%2B%20is%20one%20of%20the,be%20reused%2C%20lowering%20development%20costs.)
- [vcpkg webpage](https://vcpkg.io/en/)
- [Raylib Cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html)

# Future Work

- Seperate the classes into individual files.
- Fix the bug where if you hit two buttons at the same time then you can turn immediatley backwards ending the game.
- Add different difficulties and power-ups/bad-guys into the game.
- Turn down death sound
- Add main menu screen