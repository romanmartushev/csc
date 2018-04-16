:/ 02InOut.csc
  Input/output testing.
/: 

:A

	scribble[1]:  c0, c1;
	
	:O "\nEnter at least one character: ";
	:I c0;
	:O c0;
	:O "\nEnter at least one character: ";
	:I c1;
	:O c1, " ", c0;
	:N
:Z
