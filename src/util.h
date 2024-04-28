// String compare returns 0 (false) if the two strings are
// equal, which is kind of the opposite of what I want. It 
// does this because it's not a binary result, it also tells
// you which is greater than the other, which may be useful
// in a number of cases, but not really for a "string is equal"
// situation, which you would expect to be TRUE if you asked
// that question.
#define STREQ(a,b) strcmp(a,b) == 0