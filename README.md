# wedding_shuffle
Finds all combinations of wedding guests seated at a circular table, all guests can either sit at the same chair, move one seat to the left, or one seat to the right.
Guests are labeled with individual characters in a string. 
shuffle_barriers method introduces a barrier at a specified index which cannot be crossed, output of the program is all possible combinations of the shuffle with the barrier in place. 
Example: shuffle_barriers("abcd",{2}) returns 
ab|cd 
ab|dc 
ba|cd 
ba|dc 
db|ca 
