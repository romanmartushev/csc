:: declarations.mnc
::
:: Declarations testing with simple input/output.

:A
	int: m, n, k;
	float: a, b, c;

	:O "Enter 3 integers: ";
	:I m, n , k;
	:O m, n, k;
	:O "\n\n";
	:O "Enter 3 real numbers: ";
	:I a, b, c;
	:O a, b, c;
	:O "\n\n";
	:O 99, 2345, 10;
	:O 3.2, 1.0e+3, 222.55;
	:O "a", "b", "c";
	:N
:Z
