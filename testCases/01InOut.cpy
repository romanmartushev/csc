:: 01InOut.csc
::
:: Input/output testing.

:A

	int:   x0, x1;
	float:  y0, y1;

	:O "\n\n", 1, " \"start\" ", 8.5, "*";
	:N;
	:O "\n\nEnter two integers: ";
	:N;
	:I x0, x1;
	:O x1, x0;
	:O "\nEnter two real numbers: ";
	:I y0, y1;
	:O y1, " ", y0;
	:N;
:Z
