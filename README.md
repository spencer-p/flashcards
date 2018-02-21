flashcards
==========

A simple C program to quiz the user with .txt files. The .txt files must be in this format:

>Title

>word:definition\n

>word:definition\n

: is the delimeter for definitions. \n is the delimeter for new words or phrases.

The source allows for 128 different definitions, but that's easily modifiable.

To use in your local folder, just run

    $ make fc && ./fc

If you want to be cool and have it everywhere, run

    $ make install

This command will use sudo and compile the program into your /usr/local/bin/ directory under the name flashcards. Once it's there, you can run my program anywhere by simply typing flashcards.

Commands run from inside the program:
* getcards - This loads a set of data from an inputted path. test.txt is an example included.
* study - prints out the cards one at a time. n for next, f for flip, q for quit
* multiplechoice - Is what it sounds like.
* fitb - Fill In The Blank. It is what it sounds like.
* quit - quits. durr.
* help - prints out a list of commands
* frontback - toggle being prompted with the front or back of a card
* mascfem - a disaster of a mode that should be ignored

## Postmortem from 2018

This is the first program I wrote for fun in C when I was a freshman in high
school. When I started writing this, I didn't even know that structs existed.
This project came a long way really fast as I learned to manage structs,
memory, string tokenization, and on. Somehow I even wrote this documentation
soon after (despite a lack of comments in the code itself).

There's a lot of questionable stuff in here (installing to `/bin` is
interesting) and some odd coding style, but overall I'm very impressed with how
much this program pulls off considering how little I knew when I started.

I later [reacreated this project with
ncurses](https://github.com/spencer-p/study).
