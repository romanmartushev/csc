:A

int : x := 5;
int : y := 10;
int : z;

:I z, y;
:? (z > y)
	:O 5, "Hi";
:.
:? (y > z)
	:O 5, "BYE";
:.

:Z