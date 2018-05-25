:/  StringInit.csc
/:
:/  Tests string initialization and assignment.
/:

:A
	scribble[10]: name;
	scribble[10]: place;
	scribble[10]: name2;
	scribble[10]: name3;
	scribble[10]: sport;

	name := "Steven";
	place := "Bemidji";
	name2 := name;

	:O name;
	:N;
	:O place;
	:N;
	:O name2;
	:N;
	name3 := "baseball";
	:O name3;
	:N;
	sport := name3;
	:O name, " from ", place, " loves ", sport;
	:N;
:Z
