:: 05Assign.csc
:: 
:: Simple variables and input/output.

:A 	int:  x, y;
	float: a, b;

   :O "Enter an integer: ";
   :I x;
   :O x, "\n";
   y := x;
   :O y, "\n";
   x := 17;
   :O x, "\n\n";
   
   :O "Enter a real number: ";
   :I a;
   :O a, "\n";
   b := a;
   :O b, "\n";
   a := 26.03;
   :O a, "\n\n";
   
:Z
