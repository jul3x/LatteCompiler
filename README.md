# LatteCompiler
Simple compiler from Latte (statically typed language) to x86 GAS assembly.  
Second task of Compilers Construction course at MIMUW.

# Language
Latte is a statically typed language with syntax and semantics very similar to Java.  
Non-context grammar of this language is described in src/Latte.cf file (BNF format).  
For now - this version of latc_x86 does not support any extension of Latte language.

# Features

* computation of trivial arithmetical expressions in compilation time  
* computation of trivial boolean expressions in compilation time  
* postprocessing: removal of redundant code (`push/pop` and `pop/push` sequences)  
* postprocessing: removal of not reachable code (after `ret`)  

# Used tools
* BNFC 2.8 for compiler front-end generating.

# Dependencies  
Dependencies of parser and lexer:  
* bison  
* flex  

C++:  
* gcc 9  
* ld 2.31  
* make  

# Compilation
Type ```make``` in main directory of repository to create executable - `latc_x86`.

# Usage
* ```./latc_x86 foo/bar/in.lat # to compile in.lat file in foo/bar directory```  

generates file `in.s` and executable `in` in foo/bar directory.  

* ```./run_tests.sh```  

runs every test in tests directory and checks if compiled code produces desired output.

# Repository structure
* LatteCompiler
    * src - contains source code of project  
    * lib - contains runtime.o and runtime.s - files with definitions of library functions of Latte language written in GAS x86. Library functions are using functions from libc - they are provided in other files in this directory.  
    * tests - contains *.lat, *.input and *.output files for tests
        * bad - semantic or syntax errors that compiler should recognise
        * good - good code with appropriate desired output
        * extensions - for now semantically bad code (this version of compiler does not support extensions)

