Ever thought about learning a new programming language, doing your first try with a command line program, and first of all you want to have some command line options?
Maybe you have just an idea to do some difficult task in a small command line program, and of course you need options...

... but most of the time you have to reinvent the wheel?!

Why not using a small and easy library, which does exactly THAT task? Which gives you the possibility to fully concentrate on the original task to be done and developed?



This is the goal of this project.


The second goals of this project are a personal ones:
- to have fun programming similiar behaving code in different languages
- learning new programming languages through adding them to this repository


cmdlineoptions
===============

A library for some languages handling commandline options in the dashed fashion.

Currently available as:
- java
  - Currently available just as a Java class, within an eclipse project. :)
- C
  - static/shared library 
- (C++ maybe coming soon...)
- maybe other languages in the future?

It supports single dashed options like "-h", double dashed options "--help" and additional option alternatives.
It has got automatic help handling of all configured options with "-h", "--help" and "-?".

In the end you can define your own commandline parameter style, because you define the option name yourself like 'CmdOptions.create("-myoption");' or '...create("+anotheropt")', etc.

The library - or better, the libraries - are planned to be consistent over all languages, so you are able to define and check and retrieve options with similar function calls.

Current work and future plans
===============

Working on:
- ~~JUnit tests~~
- Java: better errorhandling
- ~~Java: Examples~~
- ~~C version~~
- Getting started
- Some java improvements

Future plans:
 - C++ class version
 - haskell
 - ...
