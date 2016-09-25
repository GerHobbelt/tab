
#include <string>

static const char* _help[][2] = {

    { "overview",
      "\nThere are four basic atomic types:\n"
      "\n"
      "- Int, a signed integer. (Equivalent to a 'long' in C.)\n"
      "- UInt, an unsigned integer. (Equivalent to an 'unsigned long' in C.)\n"
      "- Real, a floating-point number. (Equivalent to a 'double' in C.)\n"
      "- String, a string, stored as a byte array.\n"
      "\n"
      "There are also four structured types:\n"
      "\n"
      "- Tuple, a sequence of several values of (possibly) different types.\n"
      "  The number of values and their types cannot change at runtime.\n"
      "\n"
      "- Array, an array of values. Elements can be added and removed at\n"
      "  runtime, but the type of all of the values is the same and cannot\n"
      "  change.\n"
      "\n"
      "- Map, a hash map (associative array) from values to values. Like with\n"
      "  the array, elements can be added and removed, but the type of keys\n"
      "  and values cannot change.\n"
      "\n"
      "- Sequence, a.k.a. 'lazy list' or 'generator'. A sequence doesn't\n"
      "  store any values, but will generate a new element in the sequence\n"
      "  each time is asked to. As with arrays, all generated elements are\n"
      "  of the same type.\n"
      "\n"
      "When outputing, each element of an array, map or sequence is printed\n"
      "on its own line, even when nested inside some other structure. The\n"
      "elements of a tuple are printed separated by a tab character, '\\t'.\n"
      "\n"
      "Maps, by default, store values in an unspecified order. Use the '-s'\n"
      "command-line parameter to force a strict ordering on map keys.\n"
      "\n"
      "The default number type in 'tab' is the unsigned integer. A plain\n"
      "sequence of digits will be interpreted as a UInt.\n"
      "\n"
      "'tab' has no loops or conditional 'if' statements; the input\n"
      "expression is evaluated, and the resulting value is printed on\n"
      "standard output.\n"
      "\n"
      "Instead of loops you'd use sequences and comprehensions.\n"
      "\n"
      "The input is a file stream, usually the standard input. A file stream\n"
      "in 'tab' is represented as a sequence of strings, each string being a\n"
      "line from the file.\n"
    },

    { "syntax",
      "\nLiteral values:\n"
      " UInt:     1234 or 1234u or 0x4D2\n"
      " Int:      -1234 or 1234i or 1234s or 1234l\n"
      " Real:     +10.50 or 1. or 4.4e-10\n"
      " String:   'chars' or \"chars\"\n"
      "           supported escape sequences: \\t \\n \\r \\e \\\\\n"
      " Tuple:    a, b, c or a; b; c\n"
      " Sequence: [ expr ] or [ expr : source ]                            also [ try ... ]\n"
      " Array:    [. expr .] or [. expr : source .]                        also [. try ... .]\n"
      " Map:      { key } or { key -> val } or { key -> val : source }     also { try ... }\n"
      "       (Thrown exceptions will be ignored when there's an optional 'try'.)\n"
      "\n"
      "Function calls:\n"
      "  f(x) or f.x\n"
      "Defining variables:\n"
      "  x = expr\n"
      "Defining functions:\n"
      "  def f expr or def f (exprs) or def [ a, b expr, ... ]\n"
      "\n"
      "Operators, in order of precedence:\n"
      "  a~b  a[b]\n"
      "  :a   ?a\n"
      "  a**b\n"
      "  a*b  a/b  a%b\n"
      "  a+b  a-b\n"
      "  a&b  a|b  a^b\n"
      "  a==b a!=b a<b  a>b  a<=b  a>=b\n"
      "\n"
      "Parentheses can be used for grouping. Use ',' or ';' for separating statements.\n"
      "'a~b' is syntactic sugar for 'a[b]' is syntactic sugar for 'index(a,b)'\n"
      "':a' is syntactic sugar for 'flatten(a)'.\n"
      "'?a' is syntactic sugar for 'filter(a)'.\n"
      "\n"
      "'@' is the variable name denoting input to a function or left side of\n"
      "generator expression.\n"
      "\n"
      "Recursive calculations: << expr : start, seq >>\n"
    },

    { "examples",
      "\n"
      "Copy stdin to stdout:\n"
      "    @\n\n"
      "Count the number of lines in a file:\n"
      "    count(@)\n\n"
      "Math:\n"
      "    cos(1)**2 + sin(1)**2\n\n"
      "Output matches of a regex:\n"
      "    [ grep(@, \"[a-zA-Z]+\") ]\n\n"
      "Number the lines in a file:\n"
      "    zip(count(), @)\n\n"
      "Count the number of words in a file:\n"
      "    count(:[ grep(@, \"\\\\S+\") ])\n\n"
      "Find a list of unique words in a file:\n"
      "    { @ : :[ grep(@,\"\\\\S+\") ] }\n\n"
      "Output lines matching a regex:\n"
      "    ?[ grepif(@, \"this\"), @ ]\n\n"
      "Tally the frequency of each word in a file:\n"
      "    { @ -> sum.1 : :[ grep(@, \"\\\\S+\") ] }\n\n"
      "A histogram of word count by word length:\n"
      "    freq={ count.@ -> sum.1 : :[ grep(@, \"\\\\S+\") ] }, sort.freq\n\n"
      "Count the number of unique lines:\n"
      "     merge.[ uniques.@ ]\n\n"
      "Glue every pair of lines in a file together:\n"
      "    [ join(head(@, 2), \"\\t\") : explode.@ ]\n\n"
      "Calculate the factorial:\n"
      "    << @~0 * @~1 : 1, count.@ >>\n"
    },

    {"threads",
     "\n"
     "Use the '-t' command-line option to evaluate your expression using\n"
     "multiple threads. If you have a multi-core machine, then you will see\n"
     "a significant speedup. Parallel evaluation is done map/reduce style: N\n"
     "threads will run a CPU-intensive evaluation, while one dedicated\n"
     "thread will collect the results of all other threads, aggregate them,\n"
     "and output the final answer. Separate the 'scatter' CPU-intensive\n"
     "expression from the 'gather' aggregation expression with a special\n"
     "'-->' token. If a 'gather' expression is not specified, then a default\n"
     "\"@\" will be automatically assumed.\n"
     "\n"
     "Examples:\n"
     "\n"
     "Output all four-digit numbers, multithreaded-style:\n"
     "    :[grep(@,'[0-9]{4}')]\n\n"
     "Count the total number of four-digit numbers:\n"
     "    count.:[grep(@,'[0-9]{4}')] --> sum.@\n\n"
     "Find the most popular four-digit number:\n"
     "    { @ -> sum.1 ::[grep(@,'[0-9]{4}')] } --> (sort.flip.map.@)[-1]\n"
    },

    { "functions",
      "\nabs and array avg box bytes case cat ceil cos count cut date datetime e eq\n"
      "exp explode file filter first flatten flip floor get glue gmtime grep\n"
      "grepif has hash head hex hist if iarray index int join lines log lsh map max\n"
      "mean merge min ngrams normal now open or pairs peek pi rand real recut replace\n"
      "reverse round rsh sample second seq sin skip sort sqrt stddev stdev string\n"
      "sum take tan tabulate time tolower toupper triplets tuple uint uniques\n"
      "uniques_estimate var variance while zip\n"
    },

    {"abs",
     "\n"
     "Computes absolute value.\n"
     "\n"
     "Usage:\n"
     "\n"
     "abs Int -> Int\n"
     "\n"
     "abs Real -> Real\n"
    },
    {"and",
     "Returns 1 if all the arguments are not 0, returns 0 otherwise.\n"
     "Equivalent to 'a & b & c ...'.  See also 'or'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "and (Integer, Integer...) -> UInt\n"
    },
    {"array",
     "\n"
     "Stores a sequence or map or atomic value into an array. See also\n"
     "'sort' for a version of this function with sorting. See also: 'iarray'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "array Map[a,b] -> Arr[(a,b)]\n"
     "\n"
     "array Seq[a] -> Arr[a]\n"
     "\n"
     "array Number|String|Tuple -> Arr[Number|String|Tuple]\n"
     "    returns an array with one element.\n"
     "\n"
     "Note: when arrays are used as values in a map, they will concatenate. \n"
    },
    {"avg",
     "\n"
     "Synonym for 'mean'.\n"
    },
    {"box",
     "\n"
     "Remembers a value. Returns a 'box', which is a tuple of one\n"
     "remembered value. Stores the second argument in the box if the box is\n"
     "empty. If the box is not empty and the first argument is not zero,\n"
     "then replaces the value in the box with the second argument.\n"
     "\n"
     "Usage:\n"
     "\n"
     "box UInt, a -> (a,)\n"
    },
    {"bucket",
     "\n"
     "Return a bucket key. bucket(x, a, b, n) will split the interval [a, b]\n"
     "into n equal sub-intervals and return x rounded down to the nearest\n"
     "sub-interval lower bound. Useful for making histograms. See also:\n"
     "'hist'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "bucket Number, Number, Number, UInt -> Number\n"
     "    the first three arguments must be the same numeric type.\n"
    },
    {"bytes",
     "\n"
     "Accepts a string and returns an array of integers representing the\n"
     "bytes in the string. Warning: this function is not Unicode-aware and\n"
     "assumes the string is an ASCII bytestream.\n"
     "\n"
     "Usage:\n"
     "\n"
     "bytes String -> Arr[UInt]\n"
    },
    {"case",
     "\n"
     "A switch/case function. The first argument is compared to every\n"
     "argument at position n+1, and if they compare equal, the argument at\n"
     "position n+2 is returned. If none match equal, then the last argument\n"
     "is returned. See also: 'if'.\n"
     "\n"
     "Example: [ case(int.@; 1,'a'; 2,'b'; 'c') : count(4) ] returns a b c c.\n"
     "\n"
     "Usage:\n"
     "\n"
     "case a,a,b,...,b -> b\n"
    },
    {"cat",
     "\n"
     "Concatenates strings.\n"
     "\n"
     "Usage:\n"
     "\n"
     "cat String,... -> String. At least one string argument is required.\n"
    },
    {"ceil",
     "\n"
     "Rounds a floating-point number to the smallest integer that is greater\n"
     "than the input value.\n"
     "\n"
     "Usage:\n"
     "\n"
     "ceil Real -> Real\n"
    },
    {"cos",
     "\n"
     "The cosine function.\n"
     "\n"
     "Usage:\n"
     "\n"
     "cos Number -> Real\n"
    },
    {"count",
     "\n"
     "Counts the number of elements.\n"
     "\n"
     "Usage:\n"
     "\n"
     "count None -> Seq[UInt]\n"
     "    returns an infinite sequence that counts from 1 to infinity.\n"
     "\n"
     "count UInt -> Seq[UInt]\n"
     "    returns a sequence that counts from 1 to the supplied argument.\n"
     "\n"
     "count Number, Number, Number\n"
     "    returns a sequence of numbers from a to b with increment c. All three\n"
     "    arguments must be the same numeric type.\n"
     "\n"
     "count String -> UInt\n"
     "    returns the number of bytes in the string.\n"
     "\n"
     "count Seq[a] -> UInt\n"
     "    returns the number of elements in the sequence. (Warning: counting the\n"
     "    number of elements will consume the sequence!)\n"
     "\n"
     "count Map[a] -> UInt\n"
     "    returns the number of keys in the map.\n"
     "\n"
     "count Arr[a] -> UInt\n"
     "    returns the number of elements in the array.\n"
    },
    {"cut",
     "\n"
     "Splits a string using a delimiter. See also 'recut' for splitting with\n"
     "a regular expression.\n"
     "\n"
     "Usage:\n"
     "\n"
     "cut String, String -> Arr[String]\n"
     "    returns an array of strings, such that the first argument is split\n"
     "    using the second argument as a delimiter.\n"
     "\n"
     "cut String, String, UInt -> String\n"
     "    calling cut(a,b,n) is equivalent to cut(a,b)[n], except much faster.\n"
     "\n"
     "cut Seq[String], String -> Seq[Arr[String]]\n"
     "    equivalent to [ cut(@,delim) : seq ].\n"
    },
    {"date",
     "\n"
     "Converts a UNIX timestamp to a textual representation of a UTC date.\n"
     "\n"
     "Usage:\n"
     "\n"
     "date Int -> String\n"
     "    returns a UTC date in the \"YYYY-MM-DD\" format.\n"
    },
    {"datetime",
     "\n"
     "Converts a UNIX timestamp to a textual representation of a UTC date\n"
     "and time.\n"
     "\n"
     "Usage:\n"
     "\n"
     "datetime Int -> String\n"
     "    returns a UTC date and time in the \"YYYY-MM-DD HH:MM:SS\" format.\n"
    },
    {"e",
     "\n"
     "Returns the number e.\n"
     "\n"
     "Usage:\n"
     "\n"
     "e None -> Real\n"
    },
    {"eq",
     "\n"
     "Checks values for equality. If the first argument is equal to any of\n"
     "the other arguments, returns 1. Otherwise returns 0.\n"
     "\n"
     "Usage:\n"
     "\n"
     "eq a,a,... -> UInt\n"
    },
    {"exp",
     "\n"
     "The exponentiation function. Calling exp(a) is equivalent to e()a.\n"
     "\n"
     "Usage:\n"
     "\n"
     "exp Number -> Real\n"
    },
    {"explode",
     "\n"
     "Makes a sequence of sequences from a plain sequence: given an input\n"
     "sequence, returns that sequence for every element in it. Equivalent to\n"
     "x=@, [ glue(@, x) ].\n"
     "\n"
     "Usage:\n"
     "\n"
     "explode Seq[a] -> Seq[Seq[a]]\n"
    },
    {"file",
     "\n"
     "Opens a file and returns the lines in the file as a sequence of\n"
     "strings. (This allows a tab expression to process several files\n"
     "instead of just one.)\n"
     "\n"
     "Usage:\n"
     "\n"
     "file String -> Seq[String]\n"
    },
    {"filter",
     "\n"
     "Filters a sequence by returning an equivalent sequence but with\n"
     "certain elements removed. The input sequence must be a tuple where the\n"
     "first element is an integer; elements where this first elelemt is\n"
     "equal to 0 will be removed from the output sequence. See also:\n"
     "'while'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "filter Seq[(Integer,a...) -> Seq[(a...)]\n"
    },
    {"first",
     "\n"
     "Return the first element in a pair, map or sequence or pairs. See\n"
     "also: 'second'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "first a,b -> a\n"
     "first Map[a,b] -> Seq[a]\n"
     "first Seq[(a,b)] -> Seq[a]\n"
    },
    {"flatten",
     "\n"
     "Flattens a sequence of sequences, a sequence of arrays or a sequence\n"
     "of maps into a sequence of values.\n"
     "\n"
     "Usage:\n"
     "\n"
     "flatten Seq[ Seq[a] ] -> Seq[a]\n"
     "\n"
     "flatten Seq[ Arr[a] ] -> Seq[a]\n"
     "\n"
     "flatten Seq[ Map[a,b] ] -> Seq[(a,b)]\n"
     "\n"
     "flatten Seq[a] -> Seq[a]\n"
     "    sequences that are already flat will be returned unchanged. (Though at\n"
     "    a performance cost.)\n"
    },
    {"flip",
     "\n"
     "Given a sequence of pairs or a map, returns a sequence where the pair\n"
     "elements are swapped.\n"
     "\n"
     "Usage:\n"
     "\n"
     "flip Seq[(a,b)] -> Seq[(b,a)]\n"
     "\n"
     "flip Map[a,b] -> Seq[(b,a)]\n"
    },
    {"floor",
     "\n"
     "Rounds a floating-point number to the greatest integer that is less\n"
     "than the input value.\n"
     "\n"
     "Usage:\n"
     "\n"
     "floor Real -> Real\n"
    },
    {"get",
     "\n"
     "Accesses map or array elements (like 'index'), but returns a default\n"
     "value if the key is not found in the map or if the index is out of\n"
     "bounds. (Unlike 'index' which throws an exception.)\n"
     "\n"
     "Usage:\n"
     "\n"
     "get Map[a,b], a, b -> b\n"
     "    returns the element stored in the map with the given key, or the third\n"
     "    argument if the key is not found.\n"
     "\n"
     "get Arr[a], UInt, a -> a\n"
     "    returns the element at the given index, or the third argument if the\n"
     "    index is out of bounds.\n"
    },
    {"glue",
     "\n"
     "Adds an element to the head of a sequence. glue(1, seq(2, 3)) is\n"
     "equivalent to seq(1, 2, 3). See also: 'take', 'peek'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "glue a, Seq[a] -> Seq[a]\n"
    },
    {"gmtime",
     "\n"
     "Converts a UNIX timestamp to a UTC date and time.\n"
     "\n"
     "Usage:\n"
     "\n"
     "gmtime Int -> Int, Int, Int, Int, Int, Int\n"
     "    returns year, month, day, hour, minute, second.\n"
    },
    {"grep",
     "\n"
     "Finds regular expression matches in a string. The first argument is\n"
     "the string to match in, the second argument is the regular\n"
     "expression. Matches are returned in an array of strings. Regular\n"
     "expressions use ECMAScript syntax.\n"
     "\n"
     "Usage:\n"
     "\n"
     "grep String, String -> Arr[String]\n"
    },
    {"grepif",
     "\n"
     "Filter strings according to a regular expression.\n"
     "\n"
     "Usage:\n"
     "\n"
     "grepif String, String -> UInt\n"
     "    returns 1 if a regular expression has matches in a string, 0\n"
     "    otherwise. Equivalent to count(grep(a,b)) != 0u, except much faster.\n"
     "\n"
     "grepif Seq[String], String -> Seq[String]\n"
     "    returns a sequence of only those strings that have regular expression\n"
     "    matches. Equivalent to ?[ grepif(@,b), @ : a ].\n"
    },
    {"has",
     "\n"
     "Checks if a key exists in a map. The first argument is the map, the\n"
     "second argument is the key to check. Returns either 1 or 0.\n"
     "\n"
     "Usage:\n"
     "\n"
     "has Map[a,b], a -> UInt\n"
    },
    {"hash",
     "\n"
     "Hashes a value to an unsigned integer. The FNV hash function (32 or\n"
     "64 bit depending on CPU architecture) is used.\n"
     "\n"
     "Usage:\n"
     "\n"
     "hash a -> UInt\n"
    },
    {"head",
     "\n"
     "Accepts a sequence or array and returns an equivalent sequence that is\n"
     "truncated to be no longer than N elements. See also: 'skip', 'stripe'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "head Seq[a], UInt -> Seq[a]\n"
     "\n"
     "head Arr[a], UInt -> Seq[a]\n"
    },
    {"hex",
     "\n"
     "Marks the given unsigned integer such that it is output in hexadecimal.\n"
     "\n"
     "Usage:\n"
     "\n"
     "hex UInt -> UInt\n"
    },
    {"hist",
     "\n"
     "Accepts an array of numbers and a bucket count and returns an array of\n"
     "tuples representing a histogram of the values in the array. (The\n"
     "interval between the maximum and minimum value is split into N equal\n"
     "sub-intervals, and a number of values that falls into each\n"
     "sub-interval is tallied.) The return value is an array of pairs:\n"
     "(sub-interval lower bound, number of elements). See also: 'bucket'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "hist Arr[Number], UInt -> Arr[(Real,UInt)]\n"
    },
    {"iarray",
     "\n"
     "Exactly equivalent to 'array', except when printing the elements will\n"
     "be separated with a ';' instead of a newline.\n"
     "\n"
     "Usage:\n"
     "\n"
     "iarray Map[a,b] -> Arr[(a,b)]\n"
     "\n"
     "iarray Seq[a] -> Arr[a]\n"
     "\n"
     "iarray Number|String|Tuple -> Arr[Number|String|Tuple]\n"
     "\n"
     "iarray Arr[a] -> Arr[a]\n"
    },
    {"if",
     "\n"
     "Choose between alternatives. If the first integer argument is not 0,\n"
     "then the second argument is returned; otherwise, the third argument is\n"
     "returned. The second and third arguments must have the same type.\n"
     "\n"
     "Note: this is not a true conditional control structure, since all\n"
     "three arguments are always evaluated.\n"
     "\n"
     "Usage:\n"
     "\n"
     "if Integer, a, a -> a\n"
    },
    {"index",
     "\n"
     "Select elements from arrays, maps or tuples. Indexing a non-existent\n"
     "element will cause an error.\n"
     "\n"
     "Usage:\n"
     "\n"
     "index Arr[a], UInt -> a\n"
     "    returns element from the array, using a 0-based index.\n"
     "\n"
     "index Arr[a], Int -> a\n"
     "    negative indexes select elements from the end of the array, such that\n"
     "    -1 is the last element, -2 is second-to-last, etc.\n"
     "\n"
     "index Arr[a], Real -> a\n"
     "    returns an element such that 0.0 is the first element of the array and\n"
     "    1.0 is the last.\n"
     "\n"
     "index Map[a,b], a -> b\n"
     "    returns the element stored in the map with the given key. It is an\n"
     "    error if the key is not found; see 'get' for a version that returns a\n"
     "    default value instead.\n"
     "\n"
     "index (a,b,...), UInt\n"
     "    returns an element from a tuple.\n"
     "\n"
     "index Arr[a], Number, Number -> Arr[a]\n"
     "    returns a sub-array from an array; the start and end elements of the\n"
     "    sub-array are indexed as with the two-argument version of 'index'.\n"
     "\n"
     "index String, Integer, Integer -> String\n"
     "    returns a substring from a string, as with the array slicing\n"
     "    above. Note: string indexes refer to bytes, tab is not Unicode-aware.\n"
    },
    {"int",
     "\n"
     "Converts an unsigned integer, floating-point value or string into a\n"
     "signed integer.\n"
     "\n"
     "Usage:\n"
     "\n"
     "int UInt -> Int\n"
     "\n"
     "int Real -> Int\n"
     "\n"
     "int String -> Int\n"
     "\n"
     "int String, Integer -> Int\n"
     "    tries to convert the string to an integer; if the conversion fails,\n"
     "    returns the second argument instead.\n"
    },
    {"join",
     "\n"
     "Concatenates the elements in a string array or sequence using a\n"
     "delimiter.\n"
     "\n"
     "Usage:\n"
     "\n"
     "join Arr[String], String -> String\n"
     "\n"
     "join Seq[String], String -> String\n"
     "\n"
     "join String, Arr[String], String, String -> String\n"
     "    adds a prefix and suffix as well. Equivalent to cat(p, join(a, d), s).\n"
     "\n"
     "join String, Seq[String], String, String -> String\n"
    },
    {"lines",
     "\n"
     "Returns its arguments as a tuple, except that each element will be printed\n"
     "on its own line. See also: 'tuple'.\n"  
     "\n"
     "Usage:\n"
     "\n"
     "lines (a,b,...) -> (a,b,...)\n"
    },
    {"log",
     "\n"
     "The natural logarithm function.\n"
     "\n"
     "Usage:\n"
     "\n"
     "log Number -> Real\n"
    },
    {"lsh",
     "\n"
     "Bit shift left; like the C << operator. (See also 'rsh'.)\n"
     "\n"
     "Usage:\n"
     "\n"
     "lsh Int, Integer -> Int\n"
     "lsh UInt, Integer -> UInt\n"
    },
    {"map",
     "\n"
     "Stores a sequence of pairs or a single pair into a map.\n"
     "\n"
     "Usage:\n"
     "\n"
     "map Seq[(a,b)] -> Map[a,b]\n"
     "\n"
     "map (a,b) -> Map[a,b]\n"
     "    returns a map with one element.\n"
     "\n"
     "Note: when maps are used as values in other maps, they will merge. \n"
    },
    {"max",
     "\n"
     "Finds the maximum element in a sequence or array. See also: 'min'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "max Arr[a] -> a\n"
     "\n"
     "max Seq[a] -> a\n"
     "\n"
     "max Number -> Number\n"
     "    Note: this version of this function will mark the return value to\n"
     "    calculate the max when stored as a value into an existing key of a\n"
     "    map.\n"
    },
    {"mean",
     "\n"
     "Calculates the mean (arithmetic average) of a sequence or array of\n"
     "numbers. See also: 'var' and 'stdev'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "mean Arr[Number] -> Real\n"
     "\n"
     "mean Seq[Number] -> Real\n"
     "\n"
     "mean Number -> Real\n"
     "    Note: this version of this function will mark the returned value to\n"
     "    calculate the mean when stored as a value into an existing key of a\n"
     "    map.\n"
    },
    {"merge",
     "\n"
     "Aggregates a sequence of values. 'merge(a)' is equivalent to\n"
     "'{ 1 -> @ : a }~1', except faster.\n"
     "\n"
     "Usage:\n"
     "\n"
     "merge Seq[a] -> a\n"
    },
    {"min",
     "\n"
     "Finds the minimum element in a sequence or array. See also: 'max'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "min Arr[a] -> a\n"
     "\n"
     "min Seq[a] -> a\n"
     "\n"
     "min Number -> Number\n"
     "    Note: this version of this function will mark the return value to\n"
     "    calculate the min when stored as a value into an existing key of a\n"
     "    map.\n"
    },
    {"ngrams",
     "\n"
     "Similar to 'pairs' and 'triplets', except returns a sequence of arrays\n"
     "of length N instead of tuples.\n"
     "\n"
     "Usage:\n"
     "\n"
     "ngrams Seq[a], UInt -> Seq[Arr[a]]\n"
    },
    {"normal",
     "\n"
     "Returns random numbers from the normal (gaussian) distribution. (See\n"
     "also: 'rand', 'sample'.)\n"
     "\n"
     "Usage:\n"
     "\n"
     "normal None -> Real\n"
     "    returns a random number with mean 0 and standard deviation 1.\n"
     "\n"
     "normal Real, Real -> Real\n"
     "    same, but with mean and standard deviation of a and b.\n"
    },
    {"now",
     "\n"
     "Returns the current UNIX timestamp.\n"
     "\n"
     "Usage:\n"
     "\n"
     "now None -> Int\n"
    },
    {"open",
     "\n"
     "Same as 'file'.\n"
    },
    {"or",
     "\n"
     "Returns 0 if all the arguments are 0, returns 1 otherwise.\n"
     "Equivalent to 'a | b | c ...'.  See also 'and'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "or (Integer, Integer...) -> UInt\n"
    },
    {"pairs",
     "\n"
     "Given a sequence, return a sequence of pairs of the previous sequence\n"
     "element and the current sequence element. Example: given [ 1, 2, 3, 4 ]\n"
     "will return [ (1, 2), (2, 3), (3, 4) ]. (See also: 'triplets' and\n"
     "'ngrams'.)\n"
     "\n"
     "Usage:\n"
     "\n"
     "pairs Seq[a] -> Seq[(a,a)]\n"
    },
    {"peek",
     "\n"
     "Given a sequence, return a pair of its first element and the sequence\n"
     "itself with the first element reattached. Equivalent to 'h=take.@, h, glue(h, @)'.\n"
     "See also: 'take', 'glue'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "peek Seq[a] -> (a, Seq[a])\n"
    },
    {"pi",
     "\n"
     "Return the number pi.\n"
     "\n"
     "Usage:\n"
     "\n"
     "pi None -> Real\n"
    },
    {"rand",
     "\n"
     "Returns random numbers from the uniform distribution. (See also:\n"
     "'normal', 'sample'.)\n"
     "\n"
     "Usage:\n"
     "\n"
     "rand None -> Real\n"
     "    returns a random real number from the range [0, 1).\n"
     "\n"
     "rand Real, Real -> Real\n"
     "    same, but with the range [a, b).\n"
     "\n"
     "rand UInt, UInt -> UInt\n"
     "\n"
     "rand Int, Int -> Int\n"
     "    returns a random number from the integer range [a, b].\n"
    },
    {"real",
     "\n"
     "Converts an unsigned integer, signed integer or string into a\n"
     "floating-point value.\n"
     "\n"
     "Usage:\n"
     "\n"
     "real UInt -> Real\n"
     "\n"
     "real Int -> Real\n"
     "\n"
     "real String -> Real\n"
     "\n"
     "real String, Real -> Real\n"
     "    tries to convert the string to a floating-point value; if the\n"
     "    conversion fails, returns the second argument instead.\n"
    },
    {"recut",
     "\n"
     "Splits a string using a regular expression. See also 'cut' for\n"
     "splitting with a byte string.\n"
     "\n"
     "recut String, String -> Arr[String]\n"
     "    returns an array of strings, such that the first argument is split\n"
     "    using the second argument as a regular expression delimiter.\n"
     "\n"
     "recut String, String, UInt -> String\n"
     "    calling recut(a,b,n) is equivalent to recut(a,b)[n], except faster.\n"
     "\n"
     "recut Seq[String], String -> Seq[Arr[String]]\n"
     "    equivalent to [ recut(@,delim) : seq ].\n"
    },
    {"replace",
     "\n"
     "Search-and-replace in a string with regexes. The first argument is the\n"
     "string to search, the second argument is the regex, and the third\n"
     "argument is the replacement string. Regex and replacement string use\n"
     "ECMAScript syntax.\n"
     "\n"
     "Usage:\n"
     "\n"
     "replace String, String, String -> String\n"
    },
    {"reverse",
     "\n"
     "Reverses the elements in an array.\n"
     "\n"
     "Usage:\n"
     "\n"
     "reverse Arr[a] -> Arr[a]\n"
    },
    {"round",
     "\n"
     "Rounds a floating-point number to the nearest integer.\n"
     "\n"
     "Usage:\n"
     "\n"
     "round Real -> Real\n"
    },
    {"rsh",
     "\n"
     "Bit shift right; like the C >> operator. (See also 'lsh'.)\n"
     "\n"
     "Usage:\n"
     "\n"
     "rsh Int, Integer -> Int\n"
     "\n"
     "rsh UInt, Integer -> UInt\n"
    },
    {"sample",
     "\n"
     "Sample from a sequence of atomic values, without replacement. (See\n"
     "also: 'rand', 'normal'.)\n"
     "\n"
     "Usage:\n"
     "\n"
     "sample UInt, Seq[Int] -> Arr[Int]\n"
     "\n"
     "sample UInt, Seq[UInt] -> Arr[UInt]\n"
     "\n"
     "sample UInt, Seq[Real] -> Arr[Real]\n"
     "\n"
     "sample UInt, Seq[String] -> Arr[String]\n"
     "    the first argument is the sample size.\n"
    },
    {"second",
     "\n"
     "Return the second element in a pair, map or sequence or pairs. See\n"
     "also: 'first'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "second a,b -> b\n"
     "\n"
     "second Map[a,b] -> Seq[b]\n"
     "\n"
     "second Seq[(a,b)] -> Seq[b]\n"
    },
    {"seq",
     "\n"
     "Accepts two or more values of the same type and returns a sequence of\n"
     "those values. (A synonym for 'tabulate'.)\n"
     "If one argument is passed, then it is equivalent to [@ : arg].\n"
     "\n"
     "Usage:\n"
     "\n"
     "seq (a,...),... -> Seq[a]\n"
     "\n"
     "seq Arr[a] -> Seq[a]\n"
     "\n"
     "seq Map[a,b] -> Seq[(a,b)]\n"
     "\n"
     "seq a -> Seq[a]\n"
    },
    {"sin",
     "\n"
     "The sine function.\n"
     "\n"
     "Usage:\n"
     "\n"
     "sin Number -> Real\n"
    },
    {"skip",
     "\n"
     "Accepts a sequence or array and returns an equivalent sequence where\n"
     "the first N elements are ignored. See also: 'head', 'stripe'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "skip Seq[a], UInt -> Seq[a]\n"
     "\n"
     "skip Arr[a], UInt -> Seq[a]\n"
    },
    {"sort",
     "\n"
     "Sorts a sequence, array or map lexicographically. The result is stored\n"
     "into an array if the input is a map or a sequence. See also 'array', a\n"
     "version of this function without sorting.\n"
     "\n"
     "Usage:\n"
     "\n"
     "sort Arr[a] -> Arr[a]\n"
     "\n"
     "sort Map[a,b] -> Arr[(a,b)]\n"
     "\n"
     "sort Seq[a] -> Arr[a]\n"
     "\n"
     "sort Number|String|Tuple -> Arr[Number|String|Tuple]\n"
     "    Note: this version of this function will return an array with one\n"
     "    element, marked so that storing it as a value in an existing key of a\n"
     "    map will produce a sorted array of all such values.\n"
    },
    {"sqrt",
     "\n"
     "The square root function.\n"
     "\n"
     "Usage:\n"
     "\n"
     "sqrt Number -> Real\n"
    },
    {"stddev",
     "\n"
     "Synonym for 'stdev'.\n"
    },
    {"stdev",
     "\n"
     "Calculates the sample standard deviation, defined as the square root\n"
     "of the variance. This function is completely analogous to 'var', with\n"
     "the difference that the square root of the result is taken. See also:\n"
     "'mean'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "stdev Arr[Number] -> Real\n"
     "\n"
     "stdev Seq[Number] -> Real\n"
     "\n"
     "stdev Number -> Real\n"
     "    Note: this version of this function will mark the returned value to\n"
     "    calculate the standard deviation when stored as a value into an\n"
     "    existing key of a map.\n"
    },
    {"string",
     "\n"
     "Converts an unsigned integer, signed integer, floating-point number or\n"
     "a byte array to a string.\n"
     "\n"
     "Usage:\n"
     "\n"
     "string UInt -> String\n"
     "\n"
     "string Int -> String\n"
     "\n"
     "string Real -> String\n"
     "\n"
     "string Arr[UInt] -> String\n"
     "    Note: here it is assumed that the array will hold byte (0-255)\n"
     "    values. Passing in something else is an error. This function is not\n"
     "    Unicode-aware.\n"
    },
    {"stripe",
     "\n"
     "Accepts a sequence or array and returns an equivalent sequence except\n"
     "with only every Nth element. See also: 'head', 'skip'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "stripe Seq[a], UInt -> Seq[a]\n"
     "\n"
     "stripe Arr[a], UInt -> Seq[a]\n"
    },
    {"sum",
     "\n"
     "Computes a sum of the elements of a sequence or array.\n"
     "\n"
     "Usage:\n"
     "\n"
     "sum Arr[Number] -> Number\n"
     "\n"
     "sum Seq[Number] -> Number\n"
     "\n"
     "sum Number -> Number\n"
     "    Note: this version of this function will mark the value to be\n"
     "    aggregated as a sum when stored as a value into an existing key of a\n"
     "    map.\n"
    },
    {"take",
     "\n"
     "Returns the first element in a sequence. Equivalent to array(head(@, 1))[0].\n"
     "See also: 'peek', 'glue'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "take Seq[a] -> a\n"
     "    gives an error on empty sequence.\n"
     "\n"
     "take Seq[a], a -> a\n"
     "    returns the second argument on empty sequence.\n"
    },
    {"tan",
     "\n"
     "The tangent function.\n"
     "\n"
     "Usage:\n"
     "\n"
     "tan Number -> Real\n"
    },
    {"tabulate",
     "\n"
     "A synonym for 'seq'.\n"
    },
    {"time",
     "\n"
     "Converts a UNIX timestamp to a textual representation of a UTC time.\n"
     "\n"
     "Usage:\n"
     "\n"
     "time Int -> String\n"
     "    returns a UTC time in the \"HH:MM:SS\" format.\n"
    },
    {"tolower",
     "\n"
     "Converts to bytes of a string to lowercase. Note: only works on ASCII\n"
     "data, Unicode is not supported.\n"
     "\n"
     "Usage:\n"
     "\n"
     "tolower String -> String\n"
    },
    {"toupper",
     "\n"
     "Converts to bytes of a string to uppercase. Note: only works on ASCII\n"
     "data, Unicode is not supported.\n"
     "\n"
     "Usage:\n"
     "\n"
     "toupper String -> String\n"
    },
    {"triplets",
     "\n"
     "Similar to 'pairs', except returns triplets of before-previous,\n"
     "previous and current elements. (See also: 'pairs' and 'ngrams'.)\n"
     "\n"
     "Usage:\n"
     "\n"
     "triplets Seq[a] -> Seq[(a,a,a)]\n"
    },
    {"tuple",
     "\n"
     "Returns its arguments as a tuple. Meant for grouping when defining\n"
     "tuples within tuples. See also: 'lines'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "tuple (a,b,...) -> (a,b,...)\n"
    },
    {"uint",
     "\n"
     "Converts a signed integer, floating-point number or string to an\n"
     "unsigned integer.\n"
     "\n"
     "Usage:\n"
     "\n"
     "uint Int -> UInt\n"
     "\n"
     "uint Real -> UInt\n"
     "\n"
     "uint String -> UInt\n"
     "\n"
     "uint String, Integer -> UInt\n"
     "    tries to convert the string to an unsigned integer; if the conversion\n"
     "    fails, returns the second argument instead.\n"
    },
    {"uniques",
     "\n"
     "Returns an aggregator for counting the number of unique values. Hashes\n"
     "of all values are stored, so the result is exact as long as there are\n"
     "no hash collisions. Memory usage is proportional to the count of\n"
     "unique items. See also 'uniques_estimate'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "uniques a -> UInt\n"
    },
    {"uniques_estimate",
     "\n"
     "Returns an aggregator for estimating the number of unique values. A\n"
     "statistical estimator (HyperLogLog) is used instead of exact counts;\n"
     "memory usage is constant. Note: the estimator works better with larger\n"
     "counts of unique values. See also 'uniques'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "uniques_estimate a -> UInt\n"
    },
    {"var",
     "\n"
     "Calculates the sample variance of a sequence of numbers. (Defined as\n"
     "the mean of squares minus the square of the mean.) See also: 'mean'\n"
     "and 'stdev'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "var Arr[Number] -> Real\n"
     "\n"
     "var Seq[Number] -> Real\n"
     "\n"
     "var Number -> Real\n"
     "    Note: this version of this function will mark the returned value to\n"
     "    calculate the variance when stored as a value into an existing key of\n"
     "    a map.\n"
    },
    {"variance",
     "\n"
     "Synonym for 'var'.\n"
    },
    {"while",
     "\n"
     "Similar to 'filter', but stops the output sequence once the first\n"
     "filtered element is reached. See: 'filter'.\n"
     "\n"
     "Usage:\n"
     "\n"
     "while Seq[(Integer,a...)] -> Seq[(a...)]\n"
    },
    {"zip",
     "\n"
     "Accepts two or more sequences (or arrays) and returns a sequence that\n"
     "returns a tuple of elements from each of the input sequences. The\n"
     "output sequence ends when any of the input sequences end.\n"
     "\n"
     "Usage:\n"
     "\n"
     "zip Seq[a], Seq[b],... -> Seq[(a,b,...)]\n"
     "\n"
     "zip Arr[a], Arr[b],... -> Seq[(a,b,...)]\n"
    },

    { nullptr, nullptr }
};


const char* get_help(const std::string& key) {

    if (key.empty())
        return nullptr;

    for (unsigned int i = 0; _help[i][0] != nullptr; ++i) {

        if (key == _help[i][0])
            return _help[i][1];
    }

    return nullptr;
}

