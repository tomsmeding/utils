utils
=====

A really simple set of tools for quick one-line scripting in your favourite shell.

Explanation by example is easiest here.

	$ q.seq echo hi \; echo bye
	hi
	bye

	$ q.seq echo mornin
	mornin

	$ q.repeat 3 echo hi there
	hi there
	hi there
	hi there

	$ q.repeat 2 echo hi \; echo bye
	hi
	bye
	hi
	bye

	$ q.repeat 2 q.seq echo hi \; echo bye  #q.repeat <n> q.seq === q.repeat <n>
	hi
	bye
	hi
	bye

	$ q.repeat 3 q.repeat 2 echo hi \; echo bye  #repeat 3: {repeat 2: {echo hi}, echo bye}
	hi
	hi
	bye
	hi
	hi
	bye
	hi
	hi
	bye
