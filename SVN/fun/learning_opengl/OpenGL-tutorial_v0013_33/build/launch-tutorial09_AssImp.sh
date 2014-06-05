#!/bin/sh
bindir=$(pwd)
cd /home/thomas/thlux/fun/learning_opengl/OpenGL-tutorial_v0013_33/tutorial09_vbo_indexing/
export LD_LIBRARY_PATH=:$LD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /home/thomas/thlux/fun/learning_opengl/OpenGL-tutorial_v0013_33/build/tutorial09_AssImp 
	else
		"/home/thomas/thlux/fun/learning_opengl/OpenGL-tutorial_v0013_33/build/tutorial09_AssImp"  
	fi
else
	"/home/thomas/thlux/fun/learning_opengl/OpenGL-tutorial_v0013_33/build/tutorial09_AssImp"  
fi
