# GNU_grep-windows
Implementing GNU-grep for windows with added features of searching through formatted text (i.e. pdf or docx)
# Grep Programs
grep searches the named input files for lines containing a match to the given pattern. By
default, grep prints the matching lines. A file named - stands for standard input. If no input
is specified, grep searches the working directory. If given a command-line option specifying
recursion; otherwise, grep searches standard input. There are four major variants of grep,
controlled by the following options.
-G
--basic-regexp
Interpret the pattern as a basic regular expression (BRE). This is the default.
-E
--extended-regexp
Interpret the pattern as an extended regular expression (ERE). (-E is specified
by POSIX.)
-F
--fixed-strings
Interpret the pattern as a list of fixed strings (instead of regular expressions),
separated by newlines, any of which is to be matched. (-F is specified by POSIX.)
-P
--perl-regexp
Interpret the pattern as a Perl-compatible regular expression (PCRE). This is
highly experimental and ‘grep -P’ may warn of unimplemented features.
In addition, two variant programs egrep and fgrep are available. egrep is the same as ‘grep -E’. fgrep is the same as ‘grep -F’. Direct invocation as either egrep or fgrep is deprecated, but is provided to allow historical applications that rely on them to run unmodified.

# Options We Have Implemented
There are several options for the use of grep which we have implemented in this project. These are the following.
-e pattern
--regexp=pattern
Use pattern as the pattern. If this option is used multiple times or is combined with the -f (--file) option, search for all patterns given. (-e is specified by POSIX.)
-f file 
--file=file
Obtain patterns from file, one per line. If this option is used multiple times or is combined with the -e (--regexp) option, search for all patterns given. The empty file contains zero patterns, and therefore matches nothing. (-f is specified by POSIX.)
-i 
-y 
--ignore-case
Ignore case distinctions, so that characters that differ only in case match each other. Although this is straightforward when letters differ in case only via lowercase-uppercase pairs, the behavior is unspecified in other situations. For example, uppercase “S” has an unusual lowercase counterpart “” (Unicode character U+017F, LATIN SMALL LETTER LONG S) in many locales, and it is unspecified whether this unusual character matches “S” or “s” even though uppercasing it yields “S”. Another example: the lowercase German letter “ß” (U+00DF, LATIN SMALL LETTER SHARP S) is normally capitalized as the two-character string “SS” but it does not match “SS”, and it might not match the uppercase letter “” (U+1E9E, LATIN CAPITAL LETTER SHARP S) even though lowercasing the latter yields the former. -y is an obsolete synonym that is provided for compatibility. (-i is specified by POSIX.)
-v  
--invert-match
Invert the sense of matching, to select non-matching lines. (-v is specified by POSIX.)
-c 
–count	Suppress normal output; instead print a count of matching lines for each input file. With the -v (--invert-match) option, count non-matching lines. (-c is specified by POSIX.)
-l 
--files-with-matches
Suppress normal output; instead print the name of each input file from which output would normally have been printed. The scanning of each file stops on the first match. (-l is specified by POSIX.)
-L 
--files-without-match
Suppress normal output; instead print the name of each input file from which no output would normally have been printed. The scanning of each file stops on the first match.
-m num
--max-count=num
Stop reading a file after num matching lines. If the input is standard input
from a regular file, and num matching lines are output, grep ensures that
the standard input is positioned just after the last matching line before exiting,
regardless of the presence of trailing context lines. This enables a calling process
to resume a search
 -V 
--version	Print the version number of grep to the standard output stream. This version number should be included in all bug reports.
--help 	Print a usage message briefly summarizing the command-line options and the bug-reporting address, then exit.


-H
--with-filename
Print the file name for each match. This is the default when there is more than
one file to search.
-h
--no-filename
Suppress the prefixing of file names on output. This is the default when there
is only one file (or only standard input) to search.
-n
--line-number
Prefix each line of output with the 1-based line number within its input file.
(-n is specified by POSIX.)
2.5 Options We Intend to Implement in Future
The rest of the programs we have discussed about in previous sections(See Section 2.1) will be implemented in our simulation project.
# Regular Expressions
A regular expression is a pattern that describes a set of strings. Regular expressions are
constructed analogously to arithmetic expressions, by using various operators to combine
smaller expressions. grep understands three different versions of regular expression syntax: “basic” (BRE), “extended” (ERE) and “perl” (PCRE). In GNU grep, there is no
difference in available functionality between the basic and extended syntaxes. In other implementations, basic regular expressions are less powerful. The following description applies
to extended regular expressions; differences for basic regular expressions are summarized
afterwards. Perl-compatible regular expressions give additional functionality, and are documented in the pcresyntax and pcrepattern manual pages, but work only if PCRE is
available in the system.
