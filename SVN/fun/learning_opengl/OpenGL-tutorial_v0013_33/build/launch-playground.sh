#!/bin/sh
bindir=$(pwd)
cd /home/thomas/thlux/fun/learning_opengl/OpenGL-tutorial_v0013_33/playground/
export LD_LIBRARY_PATH=:$LD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /home/thomas/thlux/fun/learning_opengl/OpenGL-tutorial_v0013_33/build/playground 
	else
		"/home/thomas/thlux/fun/learning_opengl/OpenGL-tutorial_v0013_33/build/playground"  
	fi
else
	"/home/thomas/thlux/fun/learning_opengl/OpenGL-tutorial_v0013_33/build/playground"  
fi
