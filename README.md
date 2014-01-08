cmdlineoptions
===============

A library for some languages handling commandline options in the dashed fashion.

Currently available as:
- java
  - Currently available just as a Java class, within an eclipse project. :)
- C
  - ... not ... quite ... ready ... 
- (C++ maybe coming soon...)
- maybe other languages in the future?

It supports single dashed options like "-h", double dashed options "--help" and additional option alternatives.
It has got automatic help handling of all configured options with "-h", "--help" and "-?".

In the end you can define your own commandline parameter style, because you define the option name yourself like 'CmdOptions.create("-myoption");' or '...create("+anotheropt")', etc.

The library - or better, the libraries - are planned to be consistent over all languages, so you are able to define and check and retrieve options with similar function calls.

Current work and future plans
===============

Working on:
- JUnit tests
- Java: refactoring [done]
- Java: better errorhandling
- Java: Examples
- C version
- Getting started

Future plans:
 - C++ version
 - ... 
