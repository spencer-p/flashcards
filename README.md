flashcards
==========

A simple C program to quiz the user with .txt files. The .txt files must be in this format:

Title

word:definition\n

word:definition\n
: is the delimeter for definitions. \n is the delimeter for new words or phrases.

The source allows for 128 different definitions, but that's easily modifiable.

To use, just make fc && ./fc

From there, type getcards and give it a path, then type study, multiplechoice, or fillintheblank to test yourself in a variety of ways. The string "quit" can be used almost anywhere to stop the current activity.
