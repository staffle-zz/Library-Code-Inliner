# Library-Code-Inliner
This is a tool that automatically fetch all the required code in a cpp file with all of its dependencies given you have a little bit maintained library of codes. See readme.md file for details about library.

There are 2 main features of the tool.
1. #require a b c ... (adds content and all the dependencies of a.h , b.h , c.h , ....) , you can write these lines arbitary number of times, anywhere in code.
 (Examples)
```c++
#require MOD mi
#require INF N kmp
#require lcm
```
2. #author x y x ... (add that line as a comment on the top of the code. Just a cute little feature :p).You can write these lines arbitary number of times, anywhere in code.
```c++
#author I dont care what you write here, it is just an example
#author This problem seems hard, then it doesn't, but it really is. 
#author awesome video :) (https://www.youtube.com/watch?v=M64HUIJFTZM) 
```

How to use.
1. copy the content of repository into a folder. (aka "Working_folder") (Suggestion : make a new one, dont change your current working folder.)
2. run ./install.sh (This is Optional , it basically compiles the source code of tool once again and make a new executable file. It is needed after any change in tool source code.
3. Make a new build system and copy the content of Gen_and_run.sublime-build. (Or you can use compile.sh from terminal run if not using sublime.)
4. write code in main.template . (see example file) (select View -> syntax -> c++)
5. ctrl + b (for generate and Run , make sure build system is the one you made in #3) (or run ./comile.sh in terminal)
6. in case of  no error , submit.cpp will run automatically on io/in as input and io/out as output. 
6. submit.cpp has your final code ready for submission.



No need to write "#include" or "using namespace std" anywhere , neighther in libraries not in main.template code.

A typical library code will look something like this :
 (Example for lcm.h) 
 
```c++
#require ll gcd
ll lcm(ll a , ll b){
  return a/gcd(a,b)*b;
}
```
In one piece of library code you can directly refer to another library code. without worrying about dependecies. (like i referred to gcd.h in lcm without writing the gcd function itself.)
