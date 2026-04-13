# Simple implementation of the classic Timberman game

This is a simple implementation of the classic Timberman game, originally made from the version in the book
Beginning C++ Game Programming (third edition) by John Horton, published by Packt. It was done to brush up
on C++ which (judging by the code in this project) was not a day too early.

## Who's it for
Might work as inspiration and study for individuals who want to get started with game programming using the 
SFML - Simple and Fast Multimedia Library.

## What it is
This is a very basic implementation of the game. Some improvements have been made to the original listing in
the book, such as: Modified event handling, example of class based sprites (the clouds) and putting branches and 
text message handling in helper classes. I might go back to it eventually to refactor the code even more but for now 
it remains in this state to perhaps encourage someone else to get started improving it. Why not make classes for
branches and (more) bees? Refactor repetitive code into more functions?

## What it does
The object of the game is to chop as much wood from the tree as possible before the timer runs out while avoiding
being hit by branches.

The player can start, pause/unpause the game with space bar and start a new game with enter key.

## What it does NOT do
No resources in the form of graphics or sounds are included in this as I didn't have the time to check wether the ones
I used was permitted to share. Check the code to see what filenames they have and add your own. :)
