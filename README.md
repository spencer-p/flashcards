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

From there, type getcards and give it a path, then type study, multiplechoice, or fillintheblank to test yourself in a variety of ways. The string "quit" can be used almost anywhere to stop the current activity.
