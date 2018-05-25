::  20Loop.csc
::
::  Simple loops using break statements.

:A
	int: n, k;

	:O "Enter a positive integer upper limit for counting: ";
	:I n;
	:N;:N;
	k := 1;
	:O "Forward: ";
	:D
		:O k;
		:N;
		:? (k == n) :B; :.
		k:= k + 1;
	:U (1==0);
	:N;:N;

	k := n;
	:O "Backward: ";
	:D
		:O k;
		:N;
		:? (k == 1) :B; :.
		k := k - 1;
	:U (1==0);

	:N;:N;
:Z
