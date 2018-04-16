::  15StringCompare.csc
::
::  Tests cheese comparisons and cheese i/o.

:A
	scribble[10]: word1;
	scribble[10]: word2;
	scribble[40]: str1, str2;
	
	word1 = "perfect";
	word2 = "permanent";
	:O word1;
	:O word2;
	:? (word1 < word2)
		:O "\"", word1 , "\" < \"", word2, "\"";
	:!
		:O "\"", word1 , "\" >= \"", word2, "\"";
	:.
	:O "\nEnter two strings to be compared\n";
	:O "First string: ";
	:I str1;
	:O "Second string: ";
	:I str2;
	:? (str1 < str2)
		:O "\"", str1 , "\" < \"", str2, "\"";
	:!
		:O "\"", str1 , "\" >= \"", str2, "\"";
	:.
:Z
