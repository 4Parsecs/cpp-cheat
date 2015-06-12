/*
ANSI C cheat.

This file is being split up into smaller parts to c/
*/

#include "common.h"

/* +1 for the null char */
#define PRIxPTR_WIDTH ((int)(sizeof(void*)*2))

/*
One way to define constant is with preprocessor directives.

However using a const may be a better idea because:

- constants have scope
- produce meaningful error messages
*/

#define PI 3.14

/*
Example where this would cause problems:

    int PI = 3.14;

`PI` expands to `3.14`

Compiler reads:

    int 3.14 = 3.14;

but it will be hard to figure error message.

Compare this with the very simple message generated if PI were a constant
*/

/* Use parenthesis or order of operation might destroy you: */
#define PI_PLUS_ONE (3.14 + 1)

/* common recipe to control compilation: */
#define DEBUG
#ifdef DEBUG
int debugVar;
#endif

/* # # line */

/* From now on, counts from given line to report errors: */

/* # line 1 */

/* # global scope */

    /* This is a global variable: can be accessed and modified everywhere */
    int global = 1;

    /* OK! */
    int global2 = 1+1;

    int ret1() {
        int i;
        /* before main! */
        return 1;
    }

    int uninitializedGlobal;

    /* ERROR: only var declarations with const initialization allowed */

        /* Non-const. */
        /*int global2 = global+1;*/

        /* Funcion call. */
        /*puts("asdf");*/
        /*int global3 = ret1();*/

        /* Branching statement. */
        /*if(1){}*/

    /* ERROR */
    /* Cannot create scopes here like that */
    /* They'd be useless anyways. */

        /*{}*/

    int same_name_as_variable() { return 0; }

/* Typecast */

    typedef struct void_ptr_cb_payload { int i; } void_ptr_cb_payload;

    int void_ptr_cb(int i, void* payload) {
        void_ptr_cb_payload* pay = payload;
        return i + pay->i;
    }

    typedef struct void_ptr_cb_payload2 { int i; int j; } void_ptr_cb_payload2;

    int void_ptr_cb2(int i, void* payload) {
        void_ptr_cb_payload2* pay = payload;
        return i + pay->i + pay->j;
    }

    int void_ptr_caller(int i, int (*cb)(int i, void* payload), void* payload) {
        return i + cb(2, payload);
    }

/* Pointer array */

    int* get_arr(int i) {
        /*int is[] = {i};*/
        /*return is;*/
            /* WARN */
            /* return adress of local var */
            /* data is destroyed on return! */

        int* ip = (int*) malloc(sizeof(int) * 1);
        return ip;
    }

    /* cheatsheet on pointers and arrays */
    void print_array(int **mat, int m, int n) {
        int i, j;
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                printf("%d ", mat[i][j]);
            }
            printf("\n");
        }
    }

/* Functions */

    void func_array(int a[]){
        assert(a[0] == 1);
    }

    int goto_func(int i) {
        /*goto goto_func_after;*/
        in_func_label:
        return 1;
    }

    int setjmp_func(int jmp, jmp_buf env_buf) {
        if (jmp)
            longjmp(env_buf, 1);
        else
            return 1;
    }

    int post_inc_global() {
        global++;
        return global - 1;
    }

    struct func_struct { int i; };
    void func_struct_1(struct func_struct s) {
        assert(s.i == 1);
    }

    int int_func_int(int i) {
        return i;
    }

    int* int_ptr_func_int_ptr(int *ip) {
        (*ip)++;
        return ip;
    }

    const int* const_int_ptr_func_int_ptr(int *ip) {
        (*ip)++;
        return ip;
    }

#if __STDC_VERSION__ >= 199901L
    void const_array_size_argument(int is[const]) {
        is[0] = 1;
        int j;
        /* Compilation ERROR: assignment of read-only parameter is: */
            /*is = &j;*/
    }
#endif


/* # Algorithms */

    /* Simple fun algorithms. */

    /* Random. */

        /* Returna a random float in a range. */
        float rand_range(float a, float b) {
            return ((b - a) * ((float)rand() / RAND_MAX)) + a;
        }

    /* a pow b naive. */
    int pow2(int a, int b) {
        int res = 1;
        int i;
        for(i=0; i<b; i++)
            res *= a;
        return res;
    }

    /* TODO does not work. */
    float pow2f(float a, float b) {
        float res = 1.f;
        float i;
        for(i = 0; i < b; i++)
            res *= a;
        return res;
    }

/*
# main

    # Call main from the program

        Seems legal:
        http://stackoverflow.com/questions/13948562/recursion-using-main-function#comment19237980_13948579

        Illegal in C++ however.

    # main signature

        - http://stackoverflow.com/questions/204476/what-should-main-return-in-c-and-c
        - http://stackoverflow.com/questions/4207134/what-is-the-proper-declaration-of-main

        Valid signatures: either:

            int main()

    or:

            int main(int argc, char *argv[])

        Or equivalent ones to the above:

        TODO name of equivalend:

            int main(int argc, char **argv)

        Default return type `int` (C89 only):

            main()

        Explicit `void` prototype:

            int main(void)
*/
int main(int argc, char **argv) {

    /*
    Comments.
    */
    {
        /* Standard multi line comment. */
        /*
        assert(false);
        */

        /* A comment may contain `/ *`, but GCC warns with `-Wcomment`. */

#if __STDC_VERSION__ >= 199901L
        /* Double slash comment like in C++ were only introduced in C99. */
        /*assert(false);*/
#endif
    }

    /*
    # Basic types

        Types like `int`, `char`, `float` and `_Complex`.

    # Derived types

        Types which are not based, bur defined by users,
        e.g., arrays, structs and unions.
    */


    /* # variables */
    {
        {
            int i;
            i = 5;
        }

        {
            int i = 5;
            int j = 7;
        }

        /* 31 bit + 1 sign bit integer */
        {
            int i = 5, j = 7;
        }

        /* # Uninitilized variables. */
        {
#ifdef UNDEFINED_BEHAVIOUR
            /*
            Undefined behaviour for local variables:
            http://stackoverflow.com/questions/11962457/why-is-using-an-uninitialized-variable-undefined-behavior-in-c

            WARN -Wuninitialized
            */
            {
                int uninitializedLocal;
                printf("uninitializedLocal = %d\n", uninitializedLocal);
            }
#endif

            /* Fixed to 0 for global or static function variables. */
            {
                assert(uninitializedGlobal == 0);
            }
        }
    }

    /*
    # Literals

        *Literals* are values that can be expressed through a single
        language dedicated feature:

        - int:    `1`
        - long:   `1L`
        - float:  `1.0f`
        - double: `1.0`and their
        - char:   `'a'`
        - string: `"abc"`

        Some base types do not have specific literals: e.g. `short`.

        C99 introduces compound literals, which allow creation of literals for

        - arrays
        - structs
        - unions
    */
    {
#if __STDC_VERSION__ >= 199901L
        /*
        # compound literals

            Before C99 there were no literals for arrays, structs or unions,
            while literals existed for ints, chars and even strings (which are arrays of chars...)

            Compound literals are exactly that: literals for types that are made up of many smaller
            pieces, thus compounded.

            Great source: <www.drdobbs.com/the-new-c-compound-literals/184401404>
        */
        {
            /* Compound literals for arrays */
            {
                int *is;

                is = (int[2]){ 0, 1 };
                assert(is[0] == 0);
                assert(is[1] == 1);

                /* Reassign is to a new array. */
                /* Old memory becomes innacessible. */
                is = (int[2]){ 2, 3 };
                assert(is[0] == 2);
                assert(is[1] == 3);

                /* The effect is the same as `int is[] = { 1 }`, */
                /* that is: fill with zeroes. */
                is = (int[2]){ 1 };
                assert(is[0] == 1);
                assert(is[1] == 0);

                /* Major application: pass initialized arrays and structs to functions. */
                {
                    func_array((int[]){ 1 });
                    func_struct_1((struct func_struct){ .i = 1 });
                }
            }

            /*
            Compound literals yield lvalues.

            It is possible to take the address of compound literals.

            Unlike string literals, array literals can be modified.

            This means that the compound literal is an unnamed stack variable,
            and takes stack space.
            */
            {
                int *ip;
                ip = &(int){1};
                ip[0]++;
                assert(*ip == 2);
            }

            /* Int useless examples */
            {
                int i;

                i = (int){1};
                assert(i == 1);

                i = (int){1} + (int){1};
                assert(i == 2);

                /* Any expression is fine */
                {
                    i = 0;
                    i = (int){i + 1};
                    assert(i == 1);
                }
            }

            /*
            Scope of compound literals.

            Just like for normal variable declaration,
            compound literal memory can only be accessed in the scope in which it is declared.

            http://stackoverflow.com/questions/14955194/lifetime-of-referenced-compound-array-literals
            */
            {
                int *p;
                {
                    p = (int[]){1, 2};
                    assert(p[0] == 1);
                }
                /* BAD *p is undefined. */
                /*assert(p[0] == 1);*/
            }
        }
#endif
    }

    /*
    # types
    */
    {
        /*
        # Integer types

        # Integer literals

            Types that represent integer numbers are called integer types.

            This classification is explicitly used on the C specification,
            some operations or rule of the c language are only valid for integer types,
            while others work also for floating point types.

            `char` is also an integer type
        */
        {
            /* # char */
            {
                /* char has fixed size 1 byte: */
                assert(sizeof(char) == 1);

                /*
                6.4.4.4 Character constants
                */
                {
                    /* char literals are specified by single quotes */
                    char c = 'a';

                    /*
                    Actually, char literals are integers which happen to fit into char.

                    This has been changed in C++.

                    http://stackoverflow.com/questions/433895/why-are-c-character-literals-ints-instead-of-chars
                    */
                    assert(sizeof('a') == sizeof(int));

                    /*
                    Char literals can be cast to integers by replacing them with
                    their corresponding ASCII integer value for example, 'a' == 97
                    TODO check. Guaranteed?

                    > The value of an integer character constant containing more than one character (e.g.,
                    'ab'), or containing a character or escape sequence that does not map to a single-byte
                    execution character, is implementation-defined.
                    */
                    assert('a' == 97);

                    /*
                    WARN: multi-character character literals are obscure valid code, but the
                    byte ordering is undefined, so they are rarelly useful, and should be avoided. 

                    gcc raises 4.8 warnings on -pedantic.
                    */
                    /* assert('ab' == 'ab'); */

                    /* Possible via escape sequences are like in strings. */
                    assert('\'' == 0x27);
                    assert('\n' == 0x0a);
                }
            }

            /*
            # short

                Short has no specific literals, the only way is to typecast.
            */
            {
                { short si = 1; }
                { short si = (short int)1; }
                { int i = 1; }
                /* Lower case possible but bad, since l looks more like 1 than `L`.*/
                { long li = (long)1l; }
                { long li = (long)1L; }
            }

#if __STDC_VERSION__ >= 199901L
            /* # long long int */
            {
                { long long lli = 8ll; }
                { long long lli = 8LL; }
            }
#endif

            /* ERROR: mixed cases not allowed */

                /*{ long long lli = 8Ll; }*/

            /* Short, long and long long are the same as the int versions: */

                assert(sizeof(short) == sizeof(short int));
                assert(sizeof(long) == sizeof(long int));
                assert(sizeof(long long) == sizeof(long long int));

            /*
            # unsigned

                C has unsigned versions of all built-in data types.

                These basically have more or less double the maximum size
                of the signed version, and are always positive.

                You should always use unsigned sizes for quantities which must be positive such as:

                - array indexes
                - memory sizes (size_t)

                As this will give clues to the compiler
                and humans about the positive quality of your number
            */
            {
                /* Literals. */
                {
                    { unsigned char uc = (unsigned char)1; }
                    { unsigned short usi = (unsigned short int)1u; }
                    { unsigned int ui = 1u; }
                    { unsigned int ui = 1U; }
                    { unsigned long uli = 1lu; }
                    { unsigned long uli = 1LU; }
                    { unsigned long long ulli = 1llu; }
                    { unsigned long long ulli = 1LLU; }

                    /* The following are not recommended unless you are into code obfsucation: */
                    { unsigned long uli = 1Lu; }
                    { unsigned long uli = 1lU; }
                    { unsigned long long ulli = 1LLu; }
                    { unsigned long long ulli = 1llU; }

                    /* ERROR: */
                    /*{ unsigned long long ulli = 1Llu; }*/
                }

                /*
                # unsigned char

                # signed char

                # char vs unsigned char

                    For all integer types, `signed X` is the same as `X`.

                    `char` is the exception: there are *three* char types in C!

                    - `char`: unspecified if signed or not
                    - `signed char`
                    - `unsigned char`

                    http://stackoverflow.com/questions/2054939/is-char-signed-or-unsigned-by-default
                */

            }

            /* # Bases for integer literals */
            {
                /* # Hexadecimal */
                {
                    assert(16 == 0x10   );
                    assert(16 == 0x10   );
                    assert(16 == 0x10l  );
                    assert(16 == 0x10ll );
                    assert(16 == 0x10u  );
                    assert(16 == 0x10ul );
                    assert(16 == 0x10ull);

                    /* Case does not matter. */
                    assert(0xaB == 0xAb );
                }

                /* Octal. */
                {
                    assert(16 == 020);
                }

                /*
                # Binary literals

                    No ANSI way, but exist as a GNU extension.
                    <http://stackoverflow.com/questions/18244726/why-doesnt-c-have-binary-literals>
                */
            }

            /*
            # Integer representation

                C does not fix the binary representation for signed integers,
                it only states which properties represenations must have.

                As an example, the C standard explicitly mentions that the following
                representations (but there may be more) are compatible with the standard:

                - 2’s complement
                - 1’s complement
                - signed magnitude

                Unsigned representation however seems to be fixed at the canonical binary.
                This is what allows bitmasks to work.

                <http://stackoverflow.com/questions/12125650/what-do-the-c-and-c-standards-say-about-bit-level-integer-representation-and-m>
            */
        }

        /* # Floating point types and literals */
        {
            /*
            # float

                Usually implemented as IEEE 754 32-bit float.
            */
            {
                float f1 = 1.23e-34f;
                assert(1. == 1.0f);
                assert(1.f == 1.0f);
                assert(1e0f == 1.0f);
                /* ERROR: there must be a dot without `e`. */
                /*float f = 1f;*/
            }

            /*
            # double

                Usually implemented as IEEE 754 32-bit float.
            */
            { double d = 1.23; }

            /*
            # long double

                Usually implemented as an 80-bit float, which is an extension allowed by IEEE.

                In, IEEE requires the exponent to have as many bits as the next larger defined size,
                which is 128-bit wth 15 bit exponent.

                This leaves 64-bits for the seignificand.

                sizeof usually says 128 because it is memory aligned.
            */
            {
                { long double ld = 1.23l; }
                { long double ld = 1.23L; }
            }

#if __STDC_VERSION__ >= 199901L
            /*
            # float hex literal

                E.g.:

                    0xA.8p10

                Equals:

                    1010.1000 * 2^3 = 10.5 x 2^10

                The exponent is given *in decimal*.
            */
            {
                assert(0xA.0p0  ==   10.0);
                assert(0xA.8p0  ==   10.5);
                assert(0x1.8p1  ==    3.0);
                assert(0x1.0p10 == 1024.0);
            }

            /* There is no octal float literal: */
            {
                /*float f = 01.2p3;*/
            }
#endif
        }

#if __STDC_VERSION__ >= 199901L
        /*
        # Boolean type

        # _Bool

            Aliased as `bool` in `stdbool.h`.
        */
        {
            _Bool b = 0;
        }
#endif

#if __STDC_VERSION__ >= 199901L
#ifndef __STDC_NO_COMPLEX__
        /*
        # Complex types

        # _Complex

            Possibly added to C99 to help replace FORTRAN once and for all.

        # Complex literals.

            Not part of the language: defined in the stdlib. For this reason,
            we have to cheat on complex literal together with the complex.h header.

        # STDC_NO_COMPLEX

            If defined the implementation may not have complex.h.

            Therefore, it is possible to be compliant without it.
        */
        {
            { float _Complex c; }
            { double _Complex c; }
            { long double _Complex c; }

            /*
            WARN: You must say `double _Complex` or `float _Complex`:
            just `_Complex is not standard.
            */
            {
                /* _Complex c */
            }

            /*
            # Complex integer types

                Complex integer types are not specified in C.

                GCC adds them as an extension.
            */
            {
                /*int complex zi = 1 + 1*I;*/
            }
        }
#endif
#endif

        /*
        # void type

            Mysterious type with many unrelated use cases:

            - indicate that a function returns nothing: `void f();`
            - indicate that a function takes no arguments: `int f(void);`
            - pointers that can be typecast to any type for polymorphism
        */
        {
            /* ERROR: variable or field declared void */

                /*void v;*/

            /* ERROR: invalid application of sizeof to void type */

                /*printf("sizeof (void) = %d\n", sizeof(void));*/
        }
    }

    /*
    # Constant expressions

    # Compile time constants

        Defined in C99 6.6.

        The fact that an expression is a compile time constant
        or not has effects such as:

        -   when declaring an array, if the size is a constant expression
            then the array is a regular aray, if not it is a VLA statring on C99,
            or a compilation error before.

        -   only constant expressions can be used in `_Static_assert`

        C++ does not allow const pointer typecasts, so `const` variables generate constant expressions.
        There is an even more explicit language feature in C++11 via the `constexpr` keyword.
    */
    {
    }

#if __STDC_VERSION__ >= 201112L
    /*
    # Static_assert

    # _Static_assert

        Makes compile time assertions.

        Can only take constant expressions (C99 6.6).

        Issues warnings or prevents compilation if failed.

        C++ has the analogous `static_assert`.
    */
    {
        /* ERROR: static assertion failed: "Error message". */
        /*_Static_assert(0, "Error message.");*/

        _Static_assert(1, "e");
        _Static_assert(1 + 1, "e");

        const int i = 1;
        /* ERROR: expression in static assertion is not constant. */
        /*_Static_assert(i, "e");*/
    }
#endif

    /*
    # Conversions

    # typecast

        C99 6.3 "conversions"

        Transformation of one datatype to another.

        Can be done either implicitly or explicitly via a typecast operator.

        Some convertions may are allowed by the standard implicitly,
        but generate compiler warnings when done implicitly because in practice
        they should almost never be used.

        Some convertions are not allowed by the standard
        and should always generate compilation errors.

        Typecasts only transform the data:
        it seems that it is not possible to change the type of a variable itself:
        http://stackoverflow.com/questions/2822795/how-i-change-a-variable-of-a-type-to-another-one-in-c
    */
    {
        /*
        # Implicit typecasts done on operations

            The standard specifies which operations generate which typecasts.
        */
        {
            /* On assignment, the value is cast to the type of the variable assigned to. */
            {
                int i;
                /* A typecast to int is done because `i` is `int`. */
                i = 0.1;
                /* SAME: */
                i = (int)0.1;
                assert(i == 0);
            }

            /*
            If an operation involves an integer type and a floating type,
            TODO the integer type is cast to the floating type.
            */
            {
                assert(1/2 == 0);
                assert(1/2.0 == 0.5);

                /* Typecasts happen on the same order that the operations are evaluated. */
                assert(2.0*(1/2) == 0.0);
                assert((2.0*1)/2 == 1.0);
            }

            /*
            If an operation involves a smaller integer type and a larger integer type
            TODO the smaller type is first cast to the larger type
            */
            {
                assert((char)CHAR_MAX + 1 == ((int)(char)CHAR_MAX + 1));
            }
        }

        /*
        # unsigned to signed

        # signed to unsigned

            6.3.1.3
        */
        {
            /* OK: can be represented. */
            {
                assert(((unsigned char)127) == ((char)127));
            }

            /* OK: to unsigned that cannot be represented wraps around. */
            {
                assert(((unsigned char)-1) == UCHAR_MAX);
            }

#ifdef IMPLEMENTATION_SIGNAL
            /*
            To signed is implementation defined, or implementation-defined signal.

            GCC 4.8 x86 does 2's complement.
            */
            {
                printf("(char)UCHAR_MAX = %d\n", (char)UCHAR_MAX);
            }
#endif
        }

        /*
        # float to int

        # int to float

        # typecasts between integer and floating point types

            C99 6.3.1.4 Real floating and integer
        */
        {
            /* float to int rounds towards 0. */
            {
                assert((int)0.5 == 0);
                assert((int)-0.5 == 0);
            }

            /*
            int to float can cause loss of precision if the int does not fit 
            in the fp mantissa.

            Implementations define if they will round to the nearerst
            larger or smaller float.
            */

#ifdef UNDEFINED_BEHAVIOUR
            /*
            If the float does not fit in an int, undefined behavior.
            */
            {
                /* Integral part too large. */
                printf("(int)1e1023L = %d\n", (int)1e1023L);

                /*
                Negative integer part cannot be represented by unsigned types:
                http://stackoverflow.com/questions/10541200/is-the-behaviour-of-casting-a-double-to-unsigned-int-defined-in-the-c-standard

                Setting it to 0 is a common behavior.
                */
                printf("(unsigned int)-1.1 = %u\n", (unsigned int)-1.1);

                /*
                Infinities and NAN
                http://stackoverflow.com/questions/3986795/casting-float-inf-to-integer
                */
                printf("(int)NAN = %u\n", (int)NAN);
            }
#endif
        }

        /* Array to pointer of same type: */
        {
            int is[] = {0, 1, 2};
            int *is2 = is;
            assert(is2[0] == 0);
        }

        /*
        # Implicit operator typecasts

        # Usual arithmetic conversions

            C99 6.3.1.8 "Usual arithmetic conversions"

            Operators are like functions, but they have one extra piece of magic:

            - the types of their inptus are not specified
            - they can be "overloaded"

            So unlike functions, we need magic rules for how to convert incompatible types.
        */
        {
        }

        /*
        # void typecast

            It is however possible to cast any type to void.

            But that cannot have any effect since you cannot set the result to a variable.

            It can however be used to avoid unused variable warnings.
        */
        {
            /*
            # Unused function arguments

                - avoid compiler warnings
                - document intent to developpers

                <http://stackoverflow.com/questions/4647665/why-cast-an-unused-function-parameter-value-to-void>

                Why would a function not use a parameter in real life:

                -   callbacks with fixed signature for which you don't need some parameters

                -   macros that can be turned on or off. In particular, remember that `assert()` is a macro
                    and can be toggled with `NDEBUG`.
            */
            {
                int i = 0;
                (void)i;
                i = 1;
            }

            /*
            # Unused return value

                - avoid compiler warnings
            */
        }

        /*  */
        {
        }

        /* # Impossible typecats */
        {

            /* Certain typecasts always generates compilation errors. */

            /* Implicit pointer to int is impossible: */

                /*
                {
                    int* ip;
                    int i;
                    i = ip;
                }
                */

            /* Pointer to float is impossible even with explicit typecast: */

                /*
                {
                    int* ip;
                    float f;
                    f = (float)ip;
                }
                */

            /* Pointers of different types, */
            /* even if types for which data can be converted like floats and doubles: */

                /*
                {
                    float* fp;
                    double* dp;
                    dp = fp;
                }
                */

            /* Array to array of different size: */

                /*
                {
                    int is1[1];
                    int is2[2];
                    is2 = (int[])is1;
                }
                */
        }
    }

    /*
    # Overflow

        Overflow has two meanings:

        -   mathemtaical definition: making an operation in which the result
            is larger than the maximum value or smaller than the minimum value.

            This is the more common meaning of the term *overflow* outside of this context.

            In this section this will be called *mathematical overflow*.

            There is no automatic overflow check on operations
            except at initialization and assignment by constants
            at compile time.

            Operations that can overflow mathematically but never overflow include:

            - unsigned integer sum or multiplication

        -   flag definition: raising the overflow FLAG on a x86 processor or analogous.

            This is the meaning of overflow in the ANSI C definition.

            Therefore, in this section this will be called simply *overflow*.

            Overflow always implies undefined behaviour. This could include a program crash!

            Operations that may overflow include:

            - signed integer sum or multiplication

            Since this kind of overflow modifies an observable processor state,
            it is possible for compilers to detect this situation.

        Flag overflow always implies mathematical overflow, but not the converse.

        For instance, unsigned integer overflow never raises the overflow flag of an x86
        processor: it just wraps around.

        Therefore, unsigned integer multiplication never overflows.

        # GCC overflow specifics

            gcc 4.8 is smart enough to warn in many cases with `-Woverflow`:
            which is part of `-Wall`. We have turned it off so it wont annoy us on our tests.

            `-ftrapv` causes gcc to detect an overflow and raise a `SIGABRT`,
            this making their behaviour defined.
    */
    {
        /* Integer overflow */
        {
            /* Deterministic for unsigned integer types. */
            {
                unsigned char i;
                i = UCHAR_MAX + (char)1;
                assert(i == 0);
            }

#ifdef UNDEFINED_BEHAVIOUR
            /*
            Undefined behaviour because signed.

            http://stackoverflow.com/questions/3948479/integer-overflow-and-undefined-behavior
            */
            {
                char i;
                i = CHAR_MAX + 1;
                printf("CHAR_MAX + 1 = %x\n", i);
            }
#endif

            /* Unsigned multiplication does modulo: */
            {
                unsigned char uc = 255;
                uc *= 2;
                assert(uc == 254);
            }

#ifdef UNDEFINED_BEHAVIOUR
            /* Undefined behaviour because signed. */
            {
                char c = CHAR_MAX;
                c *= 2;
                printf("CHAR_MAX * 2 = %x\n", c);
            }
#endif

            /*
            # Detect overflows

                Sum: http://stackoverflow.com/questions/199333/best-way-to-detect-integer-overflow-in-c-c

                Multiplication: http://stackoverflow.com/questions/1815367/multiplication-of-large-numbers-how-to-catch-overflow
            */
        }

        /*
        Initialize with literal that does not fit into type

        TODO what happens?
        */
        {
            if (0) {
                unsigned char uc = UCHAR_MAX + 1;

                /*char c = 1e1000;*/
            }

            /* Floating point */
            {
                assert(1.00000000000000000000000000000000000000000000001 == 1.0);
            }
        }
    }

    /*
    # Type qualifiers

        Can be added to types to modify their semantics.
    */
    {
        /* Repeating qualifiers is OK and has no effect. C99 9.7.3.4 */
        {
            const const const const int i = 0;

            /* In practice, this is more likely to happen when the qualifier is hidden on a typedef. */
            {
                typedef const int ci;
                const ci i;
            }
        }

        /*
        # const qualifier
        */
        {
            int i = 0;
            const int ic = 0;
            /* Same. */
            /*int const ic = 0*/
            const int ic2 = i;

            /*
            BAD.

            Legal and compiles without warning, but is bad since ic3 cannot get a value
            unless you typecast its pointer with a warning.

            consts should normally get a value at initialization time.
            */
            const int ic3;

            /* ERROR: assignment of read only variable ic. TODO Illegal or undefined?. */
            {
                const int ic = 0;
                /*ic = 1;*/
            }

            /*
            # Modify const through pointer cast

                Casting a const to a non-const through a pointer is legal.

                Modifying he const with the pointer is undefined behavior (C99 6.7.3.5).

                For this reason, const it does not generate compile time constant expressions (C99 6.6):
                the undefined behavior could be to change the value of the const.

                In particular, existing implementaions may or may not put `const` in read only memory,
                so that the undefined behavior may be a page fault.

                `gcc` for example puts global constants on the `.rodata` section of the elf output.

                In practice however it might work for local function variables,
                which are just on the stack or registers.

                Many compilers raise warnings or prevent compilation of such constructs. 

                In C++, discarding const is illegal, and const generates compile time constants.
            */
            {
                const int ic = 0;

#ifdef UNDEFINED_BEHAVIOUR
                /*
                WARN: initialization discards const qualifier from pointer type.

                Likely to work since local variable.
                */
                /*
                int *ip = &ic;
                *ip = 1;
                assert(ic == 1);
                */
#endif
            }

            /*
            # const pointers

                There are 3 types of const pointers:

                - `const X *` or `X const *`    : cannot change the data of the thing pointer points to
                - `X * const`                   : cannot change which thing the pointer points to
                - `const X * const` or `X const * const` : both of the above
            */
            {
                /* const int * */
                /* int const * */
                {
                    int i = 0;
                    int j = 0;

                    const int *cip = &i;
                    int const *icp = &i;

                    /* Can change which opbject it points to. */

                        cip = &j;
                        icp = &j;

                    /* ERROR: const * prevents from changing the data of the object pointed to */

                        /**cip = 2;*/
                        /**icp = 2;*/
                }

                /* int * const */
                {
                    int i = 0;
                    int j = 0;
                    int *const ipc = &i;

                    *ipc = 1;
                    assert(i == 1);

                    /* ERROR: cannot change what is being pointed to */

                        /*ipc = &j;*/

                    /*
                    # Single line declaration of multiple const pointers

                        Just like `*` must be repeated once per variable, `*const` must also be repeated.
                    */
                    {
                        int i = 0;
                        int *const ipc2, *const ipc3, *ipcBad;
                        /*               ^^^^^^ */
                        /*               must repeat the `iconst` for each variable declared! */

                        i = 0;
                        ipcBad = &i;
                        *ipcBad = 1;
                    }

                    {
                        const int ic = 0;

                        /* WARN */
                        /* Initialization discards const. */
                        /* It would be possible to change the value of the const. */

                            /*int *const ipc = &ic;*/

                        /* BAD: we changed the value! */

                            /**ipc = 1;*/
                    }
                }

                const int* const cipc = &ic;

                const int cis2[2] = { 1, 2 };
                /* ERROR */
                /*cis2[0] = 1;*/

                /*
                # const pointers to pointers

                    There are 7 possibilities at level 2 already!

                    To not mix up:

                    - const always applies to the pointer at its left.
                    - if there is no such pointer, it applies to the data
                */
                {
                    int const ** icpp;
                    int * const * ipcp;
                    int ** const ippc;

                    int const * const * icpcp;
                    int const ** const icppc;
                    int * const * const ipcpc;

                    int const * const * const icpcpc;
                }

                    /*
                    # add const is not possible

                        `const int * = int *` is possible, but it is not possible to do `const int ** = int **`.

                        This is a bit counter-intuitive at first since:

                        -   we feel like we are adding a `const` qualifier increases restrictoins.

                            However, when it may lead to const modification, it is not acceptable.

                        -   the phenomenon only appears at level 2 pointers to pointers, not with simple pointers

                        Similar considerations apply to the `volatile` qualifier.

                        http://stackoverflow.com/questions/1468148/initialization-between-types-const-int-const-and-int-is-not-allowed-why
                    */
                    {
                        /* If `const int ** = int **` were possible then we could change constants. */
                        {
                            int* p = 0;

                            /* (1) THIS cannot be done: `const int ** = int **` */
                            /*int const** pp = &p;    */

                            /*int const c = 123;*/

                            /* OK, &c is int const*, and *p is int const* lvalue. p points to c now! */
                            /**pp = &c;*/

                            /* OK: p is not const. We changed c! */
                            /**p = 666;*/
                        }

                        /* The problem only arises in multidimensional cases. */
                        /* Here it is impossible to change a const. */
                        {
                            int i = 0;
                            int const * p = &i;
                        }
                    }
            }

            /*
            # const struct
            */
            {
                /*
                The entire struct is const.

                Members of a const struct cannot be modified.
                */
                {
                    struct s { int i; };
                    const struct s s = { 1 };
                    /* ERROR */
                    /*s.i = 2;*/
                }

                /* Single members can be declared const. */
                {
                    struct s {
                        int i;
                        const int j;
                    };
                    struct s s = { 0, 1 };
                    s.i = 2;
                    /* ERROR */
                    /*s.j = 2;*/
                }

                /* Entire structs cannot be declared const. */
                {
                    /* WARN: useless type qualifier */
                    /*const struct s { int i; };*/
                }
            }

            /*
            # Return const from func

                - <http://stackoverflow.com/questions/8716330/purpose-of-returning-by-const-value>
                - <http://stackoverflow.com/questions/8406898/benefits-of-using-const-with-scalar-type-e-g-const-double-or-const-int?lq=1>
            */
            {
                /*
                USELESS

                There seem to be no noticeable effect of returning const for non pointer scalars.
                */
                {
                    /*int_func();*/
                    /*const_int_func();*/
                }

                /*
                For pointer types this has a noticeable effect
                */
                {
                    /* OK */
                    {
                        int i = 0;
                        (*int_ptr_func_int_ptr(&i)) = 2;
                        assert(i == 2);
                    }

                    /* ERROR */
                    {
                        int i = 0;
                        /*(*const_int_ptr_func_int_ptr(&i)) = 2;*/
                        /*assert(i == 2);*/
                    }
                }

                /*
                For structs this also has a noticeable effect.

                In C++ however there can be noticeable effect
                because the returned object may have a non-const function that changes it
                so that the following is possible:

                    objFunc().nonConst();

                but the following would not be:

                    constObjFunc().nonConst();
                */
                {
                    /*struct_func*/
                    /*const_struct_func*/
                }
            }

#if __STDC_VERSION__ >= 199901L
            /*
            # const in array size function argument

                Same effect as declaring `int *const`, but without cast to pointer.
            */
            {
                int is2[2];
                is2[0] = 0;
                const_array_size_argument(is2);
                assert(is2[0] == 1);
            }
#endif
        }
    }

    /*
    # automatic

        Is the name for the default way to declare var
        that is not volatile neither register.

        Sadly, in C++11 is is something completely different: type inference.
    */
    {
        /* SAME: */
        int i;
        auto int i2;

        /* ERROR: */
        /*auto i3;*/
    }

    /*
    # volatile qualifier

        Compiler will not store this value in cpu registers or cache as speed optimization
        instead of in RAM.

        Applications:

        -   allow access to memory mapped devices

        -   allow uses of variables between setjmp and longjmp

        -   allow uses of sig_atomic_t variables in signal handlers.

        -   multithreading, where variable may to change value at any time on another thread.

            For example on global scope:

                int other_task_finished;

            And on some function which must wait for another thread to finish a task:

                other_task_finished = 0;
                while(other_task_finished == 0){
                    yield();
                }

            If the value were stored in register, other threads in other processes may never see an update.

            Concurrent operations on volatile variables are not guaranteed to be atomic.

            Unfortunatelly, this cannot be demonstrated as of ANSI C99 since there is no multithread support.
    */
    {
        volatile int vi;
    }

    /*
    # register

        hint to compiler that ri be stored in register
        instead of in RAM

        not necessarily honored

        almost always done without a hint if possible
    */
    {
        {
            register int ri;
        }

        /* ERROR: cpu registers don't have addresses! */
        {
            register int ri;
            /*int* ip = &ri;*/
        }

        /*
        BAD: impossible to store compound types in registers
        compiler will certainly not honor `register` hint
        */
        {
            struct S { int i; };
            register struct S s;
        }
    }

#if __STDC_VERSION__ >= 201112L
#if defined(__GNUC__) && __GNUC__ >= 4 && __GNUC_MINOR__ >= 9
    /*
    # Generic

        Compile time variable type inference!
    */
    {
#define typename(x) _Generic((x), \
        int:     "int", \
        float:   "float", \
        default: "other")

        int i;
        float f;
        void* v;
        assert(strcmp(typename(i), "int")   == 0);
        assert(strcmp(typename(f), "float") == 0);
        assert(strcmp(typename(i), "other") == 0);
    }
#endif
#endif

    /*
    # union

        Like struct, but all fields share the same data space.

        If there are several data sizes, the struct has the size of the largest.

        TODO applications: <http://stackoverflow.com/questions/4788965/c-c-when-would-anyone-use-a-union-is-it-basically-a-remnant-from-the-c-only>
    */
    {
        {
            union U {
                int i;
                int j;
            } u;
            u.i = 0;
            u.j = 1;
            assert(u.i == 1);
        }
    }

    /*
    # Order of evaulation of arguments

        The order of evaluation for expressions that are arguments
        of functions or operators is unspecified behaviour.

        For example, it is unspecified behaviour in
        `f1() * f2()` if `f1` or `f2` is evaluated first,
        which may matter if they have side-effects.

        The same goes for `g(f1(), f2())`.

        Also note that there is a further separation between evaluation (getting the value to pass forward),
        and side effects which this evaulation may have (increasing `i` on an `i++`).
        See sequence point` for that.

    # Sequence point

        <http://stackoverflow.com/questions/10782863/what-is-the-correct-answer-for-cout-c-c>
        <http://stackoverflow.com/questions/3575350/sequence-points-in-c>
        <http://stackoverflow.com/questions/4176328/undefined-behavior-and-sequence-points>

        Some language features force side effects of an expression evaluation
        to happen before continuing while others don't.

        A typical example of a side effect is the increment of `i` on `i++`,
        being the main effect the returning of the value of `i` before the increment.

        Sequence points are the operations which enforce order of evaulation.

        A full list is given here: <http://en.wikipedia.org/wiki/Sequence_point>

        Since operators such as `*` or `+` are not on the sequence point list,
        it is undetermined behaviour in `f1() * f2()` if `f1` or `f2` is evaluated first.
        The same goes for `-`, `/` and the evaulation of arguments of a function.

        Other operators however do create sequence points, for example the comma operator.

        In simple cases, gcc 4.7 is smart enough to notice undefiened behaviour and emmits a warning.
        This warning has been ignored for test purposes by a test only `-Wno-sequence-point` flag.
    */
    {
        /*
        Undefined behaviour.

        `=`does not create sequence points, to it is not possible to know if the side effect of `++`
        will happen before or after the assigment.

        Therefore, it is possible that this gives either:

            post_increment_return = 0;
            i = post_increment_return;
            i++;

        or

            post_increment_return = 0;
            i++;
            i = post_increment_return;
        */
        {
            int i = 0;
            i = i++;
            printf("i = i++ = %d\n", i);
            assert(i == 0 || i == 1);
        }

        /*
        Defined behaviour because the return statement
        guarantees that all side effects have happened.

        Contrast with `i = i++`, which has no return statement.
        */
        {
            global = 0;
            global = post_inc_global();
            assert(global == 0);
        }

        /*
        `+` does not specify a sequence point between its two sides.

        Therefore, the side effect of either `++` (incrementing i) may or may not happen before the other `++` is evaluated.

        This allows for the following outputs:

            0 + 0           (neither side effect happened before the other)
            1 + 0 or 0 + 1  (one side effect happened before the other)
        */
        {
            int i = 0;
            int j = i++ + i++;
            printf("i++ + i++ = %d\n", j);
            assert(j == 0 || j == 1);
        }

        /*
        Undefined behaviour.

        The return statements are full expressions,
        so they guarantee that either one or the other function call happens first.

        However, it is not possible to know which side of `-` is evaulated first.

        Ouptput depends on evaulation order, giving either:

            0 - 1 = -1

        if the first `post_inc_global()` is evaluated first or

            1 - 0 = 1

        if the second `post_inc_global()` is evaluated first.
        */
        {
            global = 0;
            int j = post_inc_global() - post_inc_global();
            printf("post_inc_global() - post_inc_global() = %d\n", j);
            assert(j == -1 || j == 1);
        }

        /*
        Defined behaviour because of the commutativity of addition and because the return statements guarantees
        that all side effects are done with.

        Constrast with `++global + ++global`, which is undefined because there are no return statements.

        This may give either:

            0 + 1 = 1

        or

            1 + 0 = 1

        so both are the same by coincidence.
        */
        {
            global = 0;
            assert(post_inc_global() + post_inc_global() == 1);
        }

        /*
        Comma operator introduces a sequence point.
        */
        {
            int i = 0;
            assert((i++, i++) == 1);
        }

        /* declarators in declarator sequence instroduce sequence points */
        {
            int i = 0, j = i;
            assert(j == 0);
        }

        /*
        Boolean operators `||` and `&&` introduce a sequence point.
        */
        {
            /*
            The following happens:

            - the first i++ returns 0
            - since this is false, the second side is evaulated
            - since `||` adds a sequence point, the increment side effect must happen
            - i now equals one, and `||` evals true
            */
            {
                int i = 0;
                assert(i++ || i);
            }

            /* same as for `||` */
            {
                int i = 1;
                assert(! (i-- && i));
            }
        }
    }

    /* # Operators */
    {
        /*
        # Arithmetic operators

            Always be on the lookout for overflows. Rockets have fallen because of them.
        */
        {
            /*
            # Sum

            # +
            */
            {
                /* Basic example. */
                assert((1 + 2) == 3);

                /* TODO what happens on overflow? */
            }

            assert((2 * 3) == 6);

            /*
            # Division

                Division is the most complex of the basic operations.

                Integer division and floating point division are different
                operations, which translate to different CPU instructions!

                Remember that if an operation involves a floating point and an integer,
                C first casts the integer type to a floating point type, then does
                the floating point operation.

                Division by `0` leads to different problems, which are also different
                on the floating point and integer cases.

            # INT_MIN / -1

                `INT_MIN / -1` is undefined in 2's complement,
                and 2's complement is explicitly said to be compliant to the C
                integer representation standard.
            */
            {
                assert((4 / 2) == 2);

                /* integer division */
                assert((1 / 2) == 0);

                /* floating poitn division */
                assert((1.0 / 2.0) == 0.5);

                /*
                floating poitn division. `1` is cast to `double` point,
                according to the usual arithmetic conversions.
                */
                assert((1 / 2.0) == 0.5);

                /* Same as above. */
                assert((1 / (double)2) == 0.5);
            }

            /* # Unary minus */
            {
                /*
                Unary minus can overflow for the smallest negative number!

                TODO example.
                */
            }

            /*
            # Modulus

            # %
            */
            {
                assert((3 % 3) == 0);
                assert((4 % 3) == 1);
                assert((5 % 3) == 2);
                assert((6 % 3) == 0);
            }

            /* # Comparison operators */
            {
                assert((1 == 1) == 1);
                assert((0 == 1) == 0);

                assert((0 >  1) == 0);
                assert((0 >  0) == 0);
                assert((0 > -1) == 1);
                assert((0 <  1) == 1);
                assert((0 <  0) == 0);
                assert((0 < -1) == 0);

                assert((0 >=  1) == 0);
                assert((0 >=  0) == 1);
                assert((0 >= -1) == 1);
                assert((0 <=  1) == 1);
                assert((0 <=  0) == 1);
                assert((0 <= -1) == 0);
            }
        }

        /*
        # Boolean operators

            The boolean operators treat all integers as:

            - 0: false
            - != 0: true

            The output of the boolean operators is always either 0 or 1.
        */
        {
            /*
            # !

            # Negation
            */
            {
                assert((!0) == 1);
                assert((!1) == 0);
                assert((!2) == 0);
                assert((!-1) == 0);

                /*
                `x == 0` is equivalent to `!x`.

                But its likely more readable to use `== 0` when doing comparisons,
                and to leave `!x` just for boolean operations.
                */
            }

            /*
            # ||

            # or
            */
            assert((0 || 0) == 0);
            assert((0 || 1) == 1);
            assert((1 || 0) == 1);
            assert((1 || 1) == 1);

            /*
            # &&

            # and
            */
            assert((0 && 0) == 0);
            assert((0 && 1) == 0);
            assert((1 && 0) == 0);
            assert((1 && 1) == 1);

            /*
            # Short circuit evaluation

                For operators `||`, `&&` and `?`, the second side is only evaluated if needed.

                On this example:

                - 1 is evaulated to true
                - || does not need to go any further, so i++ is not evaluated

                Those operators also define sequence points.
            */
            {
                int i = 0;
                1 || i++;
                assert(i == 0);
                1 && i++;
                assert(i == 1);
            }
        }

        /* # Bitwise operators */
        {
            /*
            # ~

            # NOT bitwise
            */
            assert((~(char)0x00) == (char)0xFF);
            assert((~(char)0xFF) == (char)0x00);

            /*
            # &

            AND bitwise
            */
            {
                assert(((char)0x00 & (char)0x00) == (char)0x00);
                assert(((char)0xFF & (char)0x00) == (char)0x00);
                assert(((char)0xFF & (char)0xFF) == (char)0xFF);

                /*
                # Even

                # Odd

                # Find if number is even or odd

                    http://stackoverflow.com/questions/160930/how-do-i-check-if-an-integer-is-even-or-odd

                    This is another "application" of `&`.

                    But seems to be as fast as `%`, and is definitely less readable.
                */
                {
                    assert((3 & 1) == 1);
                    assert((4 & 1) == 0);
                }
            }

            /*
            # ||

            # OR bitwise
            */
            assert(((char)0x00 | (char)0x00) == (char)0x00);
            assert(((char)0xFF | (char)0x00) == (char)0xFF);
            assert(((char)0xFF | (char)0xFF) == (char)0xFF);

            /*
            # ^

            # XOR bitwise
            */
            assert(((char)0x00 ^ (char)0x00) == (char)0x00);
            assert(((char)0xFF ^ (char)0x00) == (char)0xFF);
            assert(((char)0xFF ^ (char)0xFF) == (char)0x00);

            /*
            # bitmask

                The major aplication of bitwise operators it making masks to:

                - set: MASK &
                - reset
                - toggle
                - retrieve

                bits from unsigned integer fields.

                These exist to allow to use one bit to store one bit,
                because the minimal addressable unit on computers is 8 bits.

                While such operators exist in almost all languages,
                they are much more common in low level languages like C
                where optimization is more present.

                Only work because C fixes the binary representation of unsigned integers.
            */

            /*
            # <<

            # >>

            # Shift operators

                Low level bit shifting.

                For the right input, the result would
                depend on which integer representation is being used,
                which is not fixed by the C standard.
            */
            {
                assert((1u << 0u) == 1u);
                assert((1u << 1u) == 2u);
                assert((1u << 2u) == 4u);
                assert((1u << 3u) == 8u);

                assert((8u >> 0) == 8u);
                assert((8u >> 1) == 4u);
                assert((8u >> 2) == 2u);
                assert((8u >> 3) == 1u);
                assert((8u >> 4) == 0u);
                assert((5u >> 1) == 2u);

                /* Negative operands */
                {
                    /* TODO undefined or implementation defined? */
                    printf("-1 << 1u = %d\n", -1 << 1u);
#ifdef UNDEFINED_BEHAVIOUR
                    /* http://stackoverflow.com/questions/4945703/left-shifting-with-a-negative-shift-count */
                    /*printf("2u << -1 = %d\n", 2u << -1);*/
#endif
                }

                /*
                # Binary operator on floating point numbers

                    Fun, but not possible.

                    http://stackoverflow.com/questions/1723575/how-to-perform-a-bitwise-operation-on-floating-point-numbers
                */
                {
                    /*1.2 << 1;*/
                }
            }
        }

        /*
        # assign
        */
        {
            {
                int i = 0;
                i = 1;
                assert(i == 1);
            }

            /*
            = returns rvals
            */
            {
                int i;
                assert((i = 1) == 1);

                /*
                This is why this works (and probably why it is made behave like this.
                */
                {
                    int i, j, k;
                    i = j = k = 1;
                    /*i = (j = (k = 1));*/
                    assert(i == j && j == k && k == 1);
                }
            }

            /*
            # self assign initialization

                Good old undefined behaviour through innocent statements.

                <http://stackoverflow.com/questions/11186261/why-is-int-i-i-legal>
            */
            {
                int self_assign_init = self_assign_init;
                printf("self_assign_init = %d\n", self_assign_init);
            }

            /*
            # lvalue

                Something that can be on the left side of an assign, such as a variable.

                Every lvalue is a rvalue.

            # rvalue

                Something that can only be used on the right side of an assign,
                but not on the left side.
            */
            {
                /*
                In C, assign does not return lvalues.

                In C++ it does.
                */
                {
                    int i = 0, j = 1, k = 2;
                    /*(i = j) = k;*/
                }

                /*
                Function returns are rvalues.

                In C++, this has an exception: functions that return references return lvalues
                */
                {
                    /*int_func_int(1) = 1;*/
                    /*struct_func().i = 1;*/
                }

                /*
                A dereferenced pointer becomes an lvalue.
                */
                {
                    int i = 0;
                    (*int_ptr_func_int_ptr(&i)) = 2;
                    assert(i == 2);
                }
            }
        }

        /*
        # Increment

            # Pre-increment vs post-increment

                <http://stackoverflow.com/questions/24886/is-there-a-performance-difference-between-i-and-i-in-c>

                Which is faster?

                - in c, equal
                - in c++, ++i potentially if i is a complex object

            # Why the increment operator exits

                Why it exists if equivalent to x=x+1?

                Because there is an x86 instruction for that

                Why?

                - because it takes less program memory `inc eax`, instead of `sum eax,1`
                - and is a *very* common instruction

                What about +=, -=, etc. ?

                Same thing: `ax = ax + bx` == `sum ax,bx`
        */
        {
            int i;

            i = 0;
            assert(i++ == 0);
            assert(i == 1);

            i = 0;
            assert(++i == 1);
            assert(i == 1);

            i = 1;
            assert(i-- == 1);
            assert(i == 0);

            i = 1;
            assert(--i == 0);
            assert(i == 0);

            /*
            Also works for floating point,
            although the usage is much less common.
            */
            double f = 0.5;
            assert(f++ == 0.5);
            assert(f == 1.5);
        }

        /*
        Composite operators

            Do an operation and an assign at the same time.

            Exist for many operators.

            Why do they exist? Assemby support probably,
            as many assembly operations overwrite one of the operands.
        */
        {
            int i;

            i = 0;
            assert((i += 1) == 1);
            assert(i == 1);

            i = 1;
            assert((i -= 1) == 0);
            assert(i == 0);

            i = 1;
            assert((i *= 2) == 2);
            assert(i == 2);

            i = 2;
            assert((i /= 2) == 1);
            assert(i == 1);

            i = 3;
            assert((i %= 2) == 1);
            assert(i == 1);

            i = 0xFF;
            assert((i &= (char)0x00) == (char)0x00);
            assert((char)i == (char)0x00);

            /* same others bitwise, except ~= */
        }

        /*
        # ternary operator #question mark #?

            Called ternary operator since it is the only operator that
            takes 3 inputs.

            It seems that the only use for the ternary operator is writing less,
            so it is completely redundant with and if else:
            http://stackoverflow.com/questions/758849/the-ternary-conditional-operator-in-c
        */
        {
            assert((1 < 2 ? 3 : 4) == 3);
            assert((1 > 2 ? 3 : 4) == 4);

            /* The ternary operator can also yield lvalues. */
            {
                int x = 0, y = 1, *xp = &x, *yp = &y;
                *(1 ? xp : yp) = 10;
                assert(x == 10);
            }

            /* The possible to initialize consts with the ternary operator. */
            {
                const int i = 0 ? 1 : 2;
                char *s = 0 ? "a" : "b";
            }
        }

        /*
        # comma operator

            Obscure and almost useless C operator.
        */
        {
            /*
            Commas here are part of the declarator sequence,
            just like in functions calls/defs. They are not
            comma operators!
            */

                int i=0, a=1, b=2, c=3;

            /*
            ignores values on left
            takes only last value on right

            BAD: operations on left has no effect
            */

                assert((i = 0, 1       ) == 1);
                assert((i = 0, i = 1, 2) == 2);

            /*
            assign has precedence over comma
            BAD: operation on right has no effect
            */
            {
                i = 2;
                (i = 0), 1;
                i = 0, 1;
                assert(i == 0);
            }

            /* ERROR */
            /* declaration int j does not return a value */
            /*int j=0, 1;*/

            /* operation on left comes first */
            {
                i=2;
                assert((i=0, i) == 0);
                i=2;
                assert((i=0, i++, i) == 1);
            }

            /* must be parenthesis protected when passesd as function argument */
            /* to differentiate from argument separtor comma */
            {
                int i = 0;
                assert(int_func_int((i++, i)) == 1);
            }
        }
    }

    /*
    # pointer

        Pointers contain addresses of variables instead of the value.

        Using the dereference operator `*`, you can get the value from the address.
    */
    {
        int i;
        int *pi, *pi2;
        /* BAD */
        /* you are modifying some random piece of memory!!!! */
        /* must declare like that: multiple stars */
        /**pi = 7;*/
        pi = &i;
        *pi = 1;
        assert(i == 1);
        assert(*pi == 1);
        i = 2;
        assert(i == 2);
        assert(*pi == 2);

        printf("(void*)pi = %p\n", (void*)pi);
        printf("(void*)(pi+1) = %p\n",(void*)(pi+1));

        /* OK: implicit conversion * -> int: */

            pi2 = pi + 1;
            printf("(void*)(pi2-pi) = %p\n", (void*)(pi2-pi));
            assert(pi2 - pi == 1);

        /* ERROR: incompatible pointer type */

            /*float* fp = &i;*/

        /* OK: works with explicit cast: */

            float* fp = (float*)&i;

        /*
        # single line multiple pointer declaration

            You must put an asterisk for each pointer, or they are not taken to be pointers!

            This is not very intuitive since the asterisk is part of the type, not of the variable.
        */
        {
            /* correct */
            {
                int i, *ip ;
                ip = &i;
            }

            /* ERROR: ip2 is not a pointer, but an int! */
            {
                /*int i;*/
                /*int* ip, ip2;*/
                /*ip = &i;*/
                /*ip2 = &i;*/
            }
        }

        /*
        # NULL pointer

            Good source: <http://c-faq.com/null/macro.html>

            Basic usage: indicate error as return value from function
        */
        {
            /*
            Why it works: it never points to any possible valid memory location.
            (`&` operator never gives anything equal to it).
            this is so guaranteed that gcc emmits a warning in the following code
            */
            {
                int i = 0;
                /* WARN GCC 4.7 warning: &i will never be null. Smart. */
                /*assert(&i != NULL);*/
            }

            /* how it prints like: */

                printf("NULL = %p\n", NULL);

            /* `if(NULL)` and `if(!NULL)` in error checking code always work as expected */

                assert(!NULL);

            /*
            # NULL macro vs 0

                Relationship to 0: typecasting `(int)0` to any pointer type as
                `(int*)0`, `(char*)0` always gives NULL.

                This is a valid way of representing the NULL pointer,
                but it is better style to always use the `NULL` macro

                The exact definition of `NULL` is implementation dependant.
                A very common implementation is as `(void*)0`.

                C++11 also introduces the related `nullptr`.
            */
            {
                assert(NULL == (int*)0);
                assert(NULL == (char*)0);
                printf("sizeof(NULL) = %zu\n", sizeof(NULL));
            }

            /* ERROR: comparison of distinct pointer types requires a cast: */
            {
                /*assert((int*)0 == (char*)0);*/
            }

            /*
            Never dereference the NULL pointer since it is guaranteed to point to nothing.

            TODO to ANSI C, undefined behaviour? or guaranteed error?

            May lead to a Segmentation fault.
            */
            {
                /*volatile int i = *(int*)NULL;*/
            }
        }

        /*
        # void pointer

            Cannot be dereferenced without typecast.

            Can be typecast implicily to/from any *data* type.
            Not allowed implicitly in C++.

            For function pointers:

            - C leaves it undefined
            - POSIX 7 allows
            - C++ forbids it, C++11 allows it conditionally
        */
        {
            void* vp;
            int* ip;
            int i = 0;
            typedef struct S { int i; int j; } S;
            S s = {0, 1};

            /*
            There is no corresponding data type.

            Since there is no data, there is no data size.

            This means that `sizeof(void)` is not possible, nor are pointer arithmetic operations.
            */
            {
                /* it is however possible to get the size of a `void*` */

                    printf("sizeof (void*) = %zu\n", sizeof(void*));

                /* ERROR: invalid application of sizeof to void type */

                    /*vp = vp + 1;*/
            }

            /* int* to void*: */

                vp = (void*)&i;

            /* void* to int*: */

                ip = (int*)vp;

            /* void* to int. GCC 4.8: cast from pointer to int of different size: */
            /* `-Wpointer-to-int-cast */

                /*i = (int)vp;*/

            /*
            Typecast to the bad type.

            Compiles and runs!
            */
            {
                /* ERROR: aggretage value used where integer was expected */
                /* i = (int)s; */

                /* HAHA: you can't stop me now compiler! */
                vp = (void*)&s;
                ip = (int*)vp;
                i = *ip;
                /* Proabably defined because it is the first field. */
                /* Reordering is not possible, but what about padding before first field TODO? */
                /*assert(i == 0);*/
            }

            /*
            # Applications of void*

                If possible, avoid them, since they allow you to bypass type safety.

                Valid use cases:

                -   In libc, it is the return type of `malloc`, since it cannot know what type of pointer to return.
                    You should use implicit casts with it only:
                    <http://stackoverflow.com/questions/605845/do-i-cast-the-result-of-malloc>

                -   Extra parameters to callback functions.

                    The callback caller cannot know beforehand how many extra parameters. Solution:

                    - add a `void *` argument to caller and callback. `payload` is a common argument name.
                    - pass a struct pointer to the caller with the extra parameters
                    - pass the `void *` argument to the callback on the caller body
                    - in the callback body typecast the void* to the struct and use it

                    Of course, you can typecast to a different type than passed,
                    and if you do so welcome to the magic land of undefined behavior.
            */
            {
                void_ptr_cb_payload payload = {4};
                void_ptr_cb_payload2 payload2 = {4, 8};
                assert(void_ptr_caller(1, void_ptr_cb , &payload ) ==  7);
                assert(void_ptr_caller(1, void_ptr_cb2, &payload2) == 15);
            }
        }
    }

    /*
    # array

        C arrays are simply lots of values put side by side on memory.

        Because they are side by side, it is simple to get the nth value
        quickly (random access), unless like, say, a linked list, in which
        you have to go follow lots of links before you reach the searched value.
    */
    {
        {
            int is[3];
            is[0] = 0;
            is[1] = 1;
            is[2] = 2;
            assert(is[0] == 0);
            assert(is[1] == 1);
            assert(is[2] == 2);
        }

        {
            int is[] = { 0, 1, 2 };
            assert(is[0] == 0);
            assert(is[1] == 1);
            /* Allocates exact size. */
            assert(is[2] == 2);
            /* ERROR */
            /*is = {3,4,5};*/
        }

        {
            int is[4] = { 1, 2 };
            assert(is[0] == 1);
            assert(is[1] == 2);
            assert(is[2] == 0);
            assert(is[3] == 0);
        }

        {
            int is[4]  = { 1, 2 };
            int is2[4] = { 1, 2 };
            /* ERROR incompatible pointer types */
            /*is = is2;*/
        }

        /*WARN array too small*/
        {
            /*int is[2] = { 1, 3, 2 };*/
        }

        /* ERROR no negative sized array! */
        {
            /*int is[-1];*/
        }

        /*
        ERROR no 0 size array

        Possible as a gcc extension.
        */
        {
            /*int is[0];*/
        }

#if __STDC_VERSION__ >= 199901L
        /*
        # Designated initializer for arrays

            Allows to initialize array elements in any order.

            There is also a struct version.
        */
        {
            {
                int is[] = {
                    [1] = 1,
                    [0] = 0,
                };
                assert(is[0] == 0);
                assert(is[1] == 1);
            }

            /* Missing elements are zeroed. */
            {
                int is[2] = {
                    [1] = 1,
                };
                assert(is[0] == 0);
                assert(is[1] == 1);
            }

            /*
            Multiple assignments for a single int.

            Only last takes effect.

            WARN -Woverride-init
            */
            {
                int is[1] = {
                    [0] = 0,
                    [0] = 1,
                };
                assert(is[0] == 1);
            }

            /* arrays of structs can refer multiple times to the same struct */
            {
                struct S { int i; int j; };

                struct S ss[] = {
                    [0].i = 0,
                    [0].j = 1,
                    [1].i = 2,
                    [1].j = 3,
                };

                assert(ss[0].i == 0);
                assert(ss[0].j == 1);
                assert(ss[1].i == 2);
                assert(ss[1].j == 3);
            }

            /*
            Mix designated and non designated initialization.

            Non deignated pick off where the last designated left.

            Non specified ones are zero.
            */
            {
                {
                    int is[4] = {
                        -1,             /* [0] */
                                        /* [1] was not specified, so it is 0. */
                        [2] = 1,
                        2,              /* [3], because it comes after [2] */
                    };
                    assert(is[0] == -1);
                    assert(is[1] == 0);
                    assert(is[2] == 1);
                    assert(is[3] == 2);
                }

                /* possible to overwrite values */
                {
                    int is[2] = {
                        0,          /* [0] first assign */
                        1,          /* [1] first assign */
                        [0] = 2,    /* [0] second assign, overwrites first */
                        3,          /* [1] because comes after [0], second assign, overwrites first */
                    };
                    assert(is[0] == 2);
                    assert(is[1] == 3);
                }
            }
        }
#endif

        /*
        # 1[is]

            Obscure and confusing access syntax that you should
            never use except to surprise your friends.

            All that the standard says is that: a[b] = *(a + b).
            If a is the int and b the pointer or the contrary
            does not matter: all that matters is that one is an int and the other a pointer.

            This seems to have been left like this since it is easier to compile.

            <http://stackoverflow.com/questions/381542/in-c-arrays-why-is-this-true-a5-5a>
        */
        {
            int is[] = { 1, 3, 2 };
            assert(is[1] == 1[is]);
        }

        /*
        # Get array length on compile time
        */
        {
            int is[] = {0, 1, 2};
            assert(sizeof(is)/sizeof(is[0]) == 3);
        }

        /*
        # Set array length from a variable

            Before C99, array length had to be a compile time constant expression (C99 6.6):
            therefore you could not use variables for it, even `const` variables
            (which can be modified via typecasts).

            The two workarounds were:

            - enum
            - macros

            Sometimes you can also get away with `sizeof`, but this is limited.

            C99 introduces VLA which allows that, but may introduce a performace overhead.
            If the size is not a compile time constant expression, then the array
            automatically becomes a VLA.

            Bottomline: use enums. Macros have no scope, VLA has overhead.
        */
        {
            {
#if __STDC_VERSION__ < 199901L
                /* ERROR: cannot be initialized */
                /*
                int n = 2;
                int isVla[n] = { 1, 2 };
                */
#endif
            }

            {
                /* ERROR: cannot be initialized */
                /*
                const int n = 2;
                int isVla[n] = { 1, 2 };
                */
            }

            /* Enum. Seems to be the best general solution. */
            {
                {
                    enum N { N = 3 };
                    int is[N];
                    assert(sizeof(is)/sizeof(is[0]) == 3);
                }

                /* Expressions involving enums are also fine. */
                {
                    enum N { N = 3 };
                    int is[N + 1];
                    assert(sizeof(is)/sizeof(is[0]) == 4);
                }
            }

            /*
            sizeof works well when you want to copy the size of an existing array
            that had it size determined by the initialization.
            */
            {
                int is[] = {0, 1, 2};
                int is2[sizeof(is)/sizeof(is[0])];
                assert(sizeof(is2)/sizeof(is2[0]) == 3);
            }

            /*
            # Macro

                Shares the disadvantage of every macro of having no scope.

                Use enum instead.
            */
            {
#define DEFINESIZE 3
                int is[DEFINESIZE];
                is[2] = 1;
            }
        }

        /* Array type madness. */
        {
            /* Pointers and arrays are different types. */
            {
                assert(sizeof(int*) != sizeof(int[3]));
                assert(sizeof(int[3]) == 3 * sizeof(int));
                /*
                # int []

                    Is this a type? is it different from int*?
                */
            }

            /* Some operators like `+` implicly convert arrays to pointers to the same type. */
            {
                int is[2];
                assert(sizeof(is + 1) == sizeof(int*));
            }

            /*
            ERROR: declaration of `vs` as an array of voids.
            You cannot have an array of void: how many bytes should the compiler allocate?
            */
            {
                /*void vs[2];*/
            }

            /* ERROR: ou can't declare multidimentional arrays like that. */
            {
                /*int[2] iss[2];*/
            }
        }

        /* Locations in memory of an array. */
        {
            int is[3];
            puts("locations of array:");
            printf("(void*)is = %p\n",(void*)is);
            printf("(void*)&is[0] = %p\n",(void*)&is[0]);
            printf("(void*)&is[1] = %p\n",(void*)&is[1]);
            printf("(void*)&is[2] = %p\n",(void*)&is[2]);
        }

        /* Loop array. The only way is with the good and old for loop. */
        {
            int is[] = { 0, 1, 2 };
            int i;
            for (i=0; i < sizeof(is)/sizeof(is[0]); i++) {
                printf("%d ",is[i]);
            }
        }

        /*
        # Bounds breaking

            No bound check is done to avoid overhead.

            Time to break down the program by making this access memory
            locations it should not try to access! =)

            Other less fun languages check those things and allow programs to avoid breakdown:
            C does not. You try to cheat your OS, and the OS kills you.

            The C standard specifies that such actions lead to unspecified behaviour.

            It may lead to Segmentation faults or not.

            Note however that this does not always happen, as a program may
            just access another location inside its legal memory address space
            but in a completelly unpredicatable manner, and the os has no way to it did this

            This leads to very hard to debug errors, but is inevitable if you want
            to avoid the overhead of checking arrays bounds on every dereference
        */
        {

            int is[2] = { 0, 1 };
            volatile int j;
            size_t i;

            /*
            GCC 4.7 is smart enough to warn agains this one.
            */
            {
                /*j = is[2];*/
            }

            /*
            GCC 4.7 is not smart enough to warn agains this one!

            May lead to segmentation faults, but this is unlikely.

            Unspecified behaviour.
            */
            if (0) {
                srand(time(NULL));
                i = rand() % 2;
                printf("overflow = %d\n", is[2 + i]);
            }

            /* This will almost certainly lead to a segmentation fault. */
            if (0) {
                for (size_t i = 0; i < SIZE_MAX; i++) {
                    is[i] = 0;
                    /*j = is[i];*/
                }
                assert(is[0] == 0);
            }
        }

        /*
        # Multidimentional arrays

            Before using them, always consider using single dimentional arrays,
            which are much simpler to handle with some multiplication and modulos.

            It is easier to explicily calculate indexes than to deal with the C
            type system.

            Cases where this would be a better design choice: TODO
        */
        {
            int *m1[2];
            int m11[] = { 1, 2, 3    };
            int m12[] = { 4, 5, 6, 7 };
            m1[0] = m11;
            m1[1] = m12;

            /* ERROR: cannot know    how much memory to allocate! */

                /*int m31[][3];*/

            /* Error: = {...} works only at declaration */

                /*int m111[2][3];*/
                /*m111[0] = &(int*[3]){1,2,3};*/

            /* Allocate the exact ammount: 2 pointeres to int[3]. */
            int m2[][3] = {
                { 1, 2, 3 },
                { 4, 5, 6 }
            };

            /* Allocate 3x3, fills only 2x3. The rest is 0 or m3[0] gets a NULL pointer? */
            int m3[3][3] = {
                { 1, 2, 3 },
                { 4, 5, 6 }
            };

            /*
            ERROR: last must be there.

            This is an array of m[3] arrays!!
            the data on an array is sequentially written to RAM 
            and all of its elements have a fixed size (so they can be indexed!) 

            If you don't know the `sizeof(m[3])`, (and you don't know the sizeof(m[]!)) 
            you can't put all those m[3] sequentially on the RAM. 

            The compiler could look at each element of the initialization 
            and ensure they all have the *same size*, and then take that size, 
            but this would take a long time, so it just forces the user to input this 
            */
            {
                /*int m3[][] = {*/
                    /*{ 1, 2, 3    },*/
                    /*{ 4, 5, 6, 7 }*/
                /*}*/
            }

            /*
            Pass multidimentional arrays to functions.

            Never do that: pass an array, give m and n and do some operations instead.
            */
            {
                puts("\npass multidim to func:");
                enum { mc = 2 };
                /* Two int pointers. */
                int* mat[mc];
                int mat1[][3] = {
                    { 1, 2, 3 },
                    { 4, 5, 6 }
                };
                int i;
                for (i = 0; i < mc; i++) {
                    /* First points to the int at address 0 of the matrix mat1. */
                    mat[i] = mat1[i];
                }
                print_array(mat, 2, 3);
            }

            /* Multidimentional > 2 */
            {
                int m4[][2][3] = {
                    {{1, 2, 3}, {4 , 5,  6 }},
                    {{7, 8, 9}, {10, 11, 12}}
                };
                /* Allocates exact amount for first: 2x2x2. */

                int m41[3][2][3] = {
                    {{ 1, 2, 3}, {4 , 5,  6 }},
                    {{ 7, 8, 9}, {10, 11, 12}}
                };
                /* Allocates one extra for first dimension */

                /* ERROR: only first can be empty: */
                /*
                 int m4[][][2] = {
                    {{1,2},{3,4}},
                    {{5,6},{7,8}}
                };
                */

                enum {MC = 2, NC = 4};
                int m5[MC][NC];

                /*
                int m7[mc][nc] = {
                    {1,2,3},
                    {4,5,6}
                };
                */
            }

            /* Matrix pattern. */
            {
                int i, j;
                for (i = 0; i < 2; i++) {
                    printf("\n");
                    for(j = 0; j < 3; j++) {
                        printf("%d ", m1[i][j]);
                    }
                }
                printf("\n\n");
            }
        }

        /*
        # string

            By convention, *C strings* are simply char arrays
            terminated by the null character.

            This convention is used throughout libc string functions,
            such as `printf`, `strcmp` and others
            so that you don't have to pass an additional size parameter to them
            (those functions stop operating when they see the first null char).

            Nothing prevents you from making a "string" that contains a null char,
            except that you will break a very well stabilished convention,
            and libc functions will not work properly with it...

            If you absolutelly need a "string" with a null char, just use regular
            array functions to manipulate it, and pass string lengths around.
        */
        {
            /* Basic example. */
            {
                char cs[] = "abc";

                /* SAME: */
                /*char cs[] = { 'a', 'b', 'c', '\0' }*/

                assert(cs[0] == 'a' );
                assert(cs[1] == 'b' );
                assert(cs[2] == 'c' );
                assert(cs[3] == '\0');

                cs[0] = 'A';
                assert(strcmp(cs, "Abc") == 0);

                /* ERROR: you cannot assign a string to memory like this, */
                /* except at initialization */

                    /*cs = "Abc";*/

                /* You probably want `strcpy`. */
            }

            /*
            # Iterate string
            */
            {
                /* Pointer version. */
                {
                    char s[] = "abc";
                    char s2[] = "ABC";
                    char *cPtr;
                    for (cPtr = s; *cPtr != '\0'; cPtr++){
                        *cPtr = toupper(*cPtr);
                    }
                    assert(strcmp(s, s2) == 0);
                }
            }


            /* String initialization */
            {
                /*
                char * vs char[] initialization

                http://stackoverflow.com/questions/1704407/what-is-the-difference-between-char-s-and-char-s-in-c

                With *, it cannot be modified later. Implementations may store it in readonly memory.

                In Linux, this is either `.rodata` or directly on the `.text` segment.
                */
                {
                    {
                        char *s = "abc";
                        assert(s[0] == 'a');
                        /* Unefined behaviour. On Linux, segfault. */
                        /*cs[0] = '0';*/
                    }

                    {
                        char s[] = "abc";
                        assert(s[0] == 'a');
                        /* OK */
                        s[0] = '0';
                    }

                    /* TODO why can't we do the same thing with integers? E.g.: */
                    {
                        /*int * is = {1, 3, 2};*/
                    }
                }

                /*
                Parenthesis. Legal but ugly. GCC 4.8 gives an error with `-pedantic`.
                */
                {
                    /*char s[] = ("abc");*/
                }
            }

            /*
            # String literals

                http://en.cppreference.com/w/c/language/string_literal
            */
            {
                /* Escape chars in string conts */
                {

                    /* Octal bytes */
                    assert(!strcmp("\141", "a"));

                    /* Hexadecimal bytes. */
                    {
                        assert(!strcmp("\x61", "a"));

                        /*
                        WARNING: Hex escape out of range.

                        Happens because f can be part of a hex literal,
                        and C tries to put it together.

                        TODO what happens exactly according to ANSI C?
                        Undefined behaviour?
                        */
                        /*{ "\xfff"; }*/

                        /*
                        The solution is to either concatenate strings, or use another escape:
                        */
                        assert(strcmp("\xff""f", "\xff\x66") == 0);

                        /* Chinese UTF-8. */
                        puts(">>>\xe4\xb8\xad<<< zhong1, chinese for \"middle\" in utf8");
                    }

                    /*
                    \0 is the NUL char, but you can't insert is directly on the literal,
                    or else the string is interpreted to end there since C strigs are NUL terminated.
                    */
                    printf(">>>%c<<< NUL char\n", '\0');

                    /* Double quotes. */
                    assert(strcmp("\"", "\x22") == 0);

                    /* Single quote. Likely exists for symmetry with character literals. */
                    assert(strcmp("\'", "\x27") == 0);

                    /* Backslash. */
                    assert(strcmp("\\", "\x5c") == 0);

                    /*
                    WARNING: Unknown escape sequence. TODO what ANSI C says can happen?
                    */
                    /*assert(strcmp("\c", "\x0b") == 0);*/

                    /* Alert. Your terminal may interpret this as a sound beep or not. */
                    assert(strcmp("\a", "\x07") == 0);

                    /* Backspace. */
                    assert(strcmp("\b", "\x08") == 0);

                    /* Feed */
                    assert(strcmp("\f", "\x0c") == 0);

                    /* New line */
                    assert(strcmp("\n", "\x0a") == 0);

                    /* Carriage return */
                    assert(strcmp("\r", "\x0d") == 0);

                    /* Tab */
                    assert(strcmp("\t", "\x09") == 0);

                    /* Vertical tab */
                    assert(strcmp("\v", "\x0b") == 0);

                    /* Famous extensions: \e GNU for ESC */
                }

                /* String literals may be concatenated */
                /* no spaces are implied. */
                {
                    char cs[] = "ab" "cd";
                    assert(strcmp(cs, "abcd") == 0);

                    /* This cannot be done with variables, */
                    /* but can be useful if you have a string that is defined in a macro: */
                    {
#define STRING_AB "ab"
                        char cs[] = STRING_AB "cd";
                        assert(strcmp(cs, "abcd") == 0);
                    }

                    /* Another application is to break a long string literal over severl lines */
                    /* no newline is implied: */
                    {
                        char cs[] = "ab"
                                    "cd";
                        assert(strcmp(cs, "abcd") == 0);
                    }

                    /* It is not possible to break a string literal on multiple lines. */
                    /*
                    {
                        char cs[] = "ab
                                    cd";
                        assert(strcmp(cs, "abcd") == 0);
                    }
                    */
                }
            }
        }
    }

    /* # Branching statements */
    {
        /* # if */
        {
            /* Only 0 counts as false. */
            if (0) {
                assert(0);
            }

            if (1){
                assert(1);
            }

            if (-1) {
            } else {
                assert(0);
            }

            if (-1) {
            } else if (0) {
                assert(0);
            } else {
                assert(0);
            }

            /* Can ommit braces for single statements. */
            {
                {
                    if (0) assert(0);
                    if (0)
                        assert(0);
                    if (0) { assert(0); }
                }

                {
                    if (0)
                        assert(0);
                    else
                        assert(1);
                }

                /* Possible but very ugly to use only one pair of braces. */
                {
                    if (0) {
                        assert(0);
                    } else
                        assert(1);

                    if (0)
                        assert(0);
                    else {
                        assert(1);
                    }
                }
            }

            /* Scope */
            {
                int i = 0;
                if (1) {
                    int i = 1;
                    assert(i == 1);
                }
            }
        }

        /*
        # switch

            Why does this exists (could be done with if):

            - readability
            - not repeating the deciding variable / expression many times
            - TODO is there no compilation preformance gain via special assembly instructions?).

        # case

            See switch.
        */
        {
            int i, j;
            for(i = -1; i < 6; i++) {
                switch (i) {
                    case 0:

                        assert(i == 0);

                        /* OK new inner scope */
                        int j;

                        /* ERROR redeclaration */
                        /*int i = 1;*/

                    break;

                    case 1:

                        assert(i == 1);

                        /* ERROR single inner scope. */
                        /*int j;*/

                    break;

                    /* Same action for multiple cases. */
                    case 2:
                    case 3:

                        assert(i == 2 || i == 3);

                    break;

                    /* Google C++ style recommends the following style. */
                    case 4: {
                        assert(i == 4);
                        break;
                    }
                    case 5: {
                        assert(i == 5);
                        break;
                    }

                    default:
                        assert(i != 0 && i != 1);
                    break;
                }
            }

            /*
            -   case statements are just like GOTO labels

            -   break is like a jump

            -   each case does not need a corresponding break

            -   and switch statements can contain any other construct like `if` or `while`
                even outside of a case break pair.

            The major application of this is to impress your friends
            with your mastery of C obscurantism.

            However there is a classic optimization trick that relies on that:
            <http://en.wikipedia.org/wiki/Duff%27s_device>

            # Duff's device
            */
            {
                int i = 0;
                switch (2) {
                    while (i < 2) {
                    label_switch_in_while:
                    case 0:
                        i++;
                    }
                    case 1:
                        i++;
                        break;
                    case 2:
                        goto label_switch_in_while;
                }
                printf("%d\n", i);
                assert(i == 3);
            }
        }

        /*
        # for vs while

            In theory, whatever you can to with for you can do with while.

            However x86 has a loop instruction that increments and
            contional jumps in a single step.

            Therefore, using a simple for is a better hinto to your
            compiler to use this more efficient looping instruction.

            Moral: if you when know how many loops you will do, use `for`,
            otherwise use `while`.

            Using for also serves as self documentation telling readers that you know
            beforehand how many times the loop will execute.
        */

        /* # for loop */
        {
            /* Basic example. */
            {
                int i;
                int is[] = { 0, 1, 2 };
                for (i = 0; i < 3; ++i) {
                    assert(i == is[i]);

                    /* OK new scope. */
                    int i = -1;
                    /* From now on, the loop's `i` is invisble. */
                    assert(i == -1);
                }
                assert(i == 3);
            }

            /*
            Like for `if`, if there is only a single statement,
            braces can be omitted.
            */
            {
                int i;
                int is[] = { 0, 1, 2 };
                for (i = 0; i < 3; ++i)
                    assert(i == is[i]);
                    /* ERROR redeclaration note different if bracketes used. */
                    /*int i;*/
            }

            /*
            Multiple loop variables: one of the few "uses" of the comma operator.

            Arguably though, `while` loops are more readable in that case,
            like in any other case that is not a straight single integer variable increase.

            TODO check. Is this really the comma operator?
            */
            {
                int i;
                float f;
                for (i = 0, f = 0.0f; i * f < 7; i++, f += 0.5) {}
                assert(i == 4);
            }

#if __STDC_VERSION__ >= 199901L
            {
                /* Putting `int i = 0` inside the `for` is only possible in C99. */
                {
                    int is[] = {0, 1, 2};
                    for (int i = 0; i < 3; ++i) {
                        assert(i == is[i]);
                        /* ERROR: redeclaration. */
                        /*int i;*/
                    }
                    /* ERROR undeclared. */
                    /*assert(i == 3);*/
                }

                /*
                This allows for a second way of initializing multiple variables
                in a single for, besides the existing comma operator.

                This syntax does not however allow to initialize
                two variables of different types.
                */
                {
                    int is[] = {0, 1, 2};
                    for (int i = 0, j = 0; j < 30; ++i, j += 10) {
                        assert(i == is[i]);

                        /* ERROR: redeclaration. */
                        /*int i;*/
                    }
                }
            }
#endif

            /* Nested loops. */
            {
                /* Basic example. */
                {
                    int n = 0;
                    int is[] = {0, 0, 1, 1};
                    int js[] = {0, 1, 0, 1};
                    for (int i = 0; i < 2; i++) {
                        for (int j = 0; j < 2; j++) {
                            assert(i == is[n]);
                            assert(j == js[n]);
                            n++;
                        }
                    }
                }

                /*
                # Break out of nested loops

                    http://stackoverflow.com/questions/1257744/can-i-use-break-to-exit-multiple-nested-for-loops

                    One of the few widely accepted uses of goto.

                    Languages like Java have labeled loops to avoid the goto.

                */
                {
                    /* TODO example: find number in a two dimensional array. */
                }
            }

            /* Different loop step. */
            {
                int n = 5;
                int step = 2;
                int is[] = {0, 1, 2, 3, 4};
                int js[] = {0, 2, 4};
                int js2[] = {1, 3};
                int j = 0;
                for (int i = 0; i < n; i += step) {
                    assert(js[j] == is[i]);
                    if (i < n - step + 1)
                        assert(js2[j] == is[i + 1]);
                    j++;
                }
            }

            /* # Backward loops. */
            {
                int n = 3;
                int is[] = { 0, 1, 2 };
                int js[] = { 2, 1, 0 };
                int j = 0;
                for (int i = n - 1; i >= 0; --i) {
                    assert(is[i] == js[j]);
                    j++;
                }

                /*
                # Backward loops with unsined loop variables

                    Here things get messy: <http://stackoverflow.com/questions/665745/whats-the-best-way-to-do-a-reverse-for-loop-with-an-unsigned-index>

                    It becomes clear why the google c++ style recommends not to use unsigned,
                    but how can that be avoided for example for `size_t`?
                */
                {
                    /* Infinite loop, since `i >= 0` always holds! */
                    /*
                    {
                        int n = 3;
                        int is[] = { 0, 1, 2 };
                        int js[] = { 2, 1, 0 };
                        int j = 0;
                        for (unsigned int i = n - 1; i >= 0; --i) {
                            assert(is[i] == js[j]);
                            j++;
                        }
                    }
                    */

                    /*
                    Two variables solution.

                    Downside: one more variable, one extra operation per loop. 

                    Upside: very clear.
                    */
                    {
                        unsigned int n = 3;
                        int is[] = { 0, 1, 2 };
                        for (unsigned int i_fake = n; i_fake > 0; --i_fake) {
                            unsigned int i = i_fake - 1;
                            assert(is[i] == i);
                        }
                    }

                    /*
                    Module madness solution.

                    Downside: mind twisting.

                    Upside: efficient: no extra var or operation.
                    */
                    {
                        unsigned int n = 3;
                        int is[] = { 0, 1, 2 };
                        for (unsigned int i = n - 1; i < n; --i) {
                            assert(i == is[i]);
                        }
                    }

                    /*
                    Post increment solution.

                    Mnemonic: the goes to operator `-->`

                    Downside: only works for step of 1.

                    Upside: efficient: no extra var or operation.
                    */
                    {
                        unsigned int n = 3;
                        int is[] = { 0, 1, 2 };
                        for (unsigned int i = n - 1; i-- > 0;) {
                            assert(i == is[i]);
                        }
                    }
                }
            }
        }

        /* # while */
        {
            {
                int i = 0;
                int is[] = { 0, 1, 2 };
                while (i < 3) {
                    assert(i == is[i]);
                    i++;
                }
                assert(i == 3);
            }

            /* # do-while */
            {
                int i = 0;
                int i2;
                int is[] = { 0, 1, 2 };
                do {
                    i2 = 2*i*i + 3*i + (i % 2);
                    assert(i == is[i]);
                    i++;
                } while (i2 < 7);
                /* Don't forget the ';'. */

                /*
                Application Loop must execute at least once to know if it will continue.

                Without do-while, you would have to either:

                -   `int i2 = 2*i*i + 3*i + (i % 2);`

                    So you have to type this huge expression twice!

                -   write a function that does:

                        2*i*i + 3*i + (i % 2);

                    This function is almost useless (used only twice)
                    adding needless boilerplate to your code.

                both of which are not very attractive alternatives.
                */
            }
        }

        /*
        # goto

            One of the most basic loops: tranlates to an unconditional `jmp` in x86.
        */
        {
            /*
            However, avoid using this as it may generate unreadable code.

            Opinions vary, but possible acceptable uses are:

            -   break out of nested loops, widely supported

            -   any forward jump, e.g. for error handling.
                Those are equivalent to return, which is well accepted.

            Very few people support gotos that go backwards.

            `return` is essentially a forward jump inside a function.
            */

            /* Basic example. */
            {
                goto basic_example;
                    assert(0);
                basic_example:
                    assert(1);
            }

            /*
            goto cannot cross functions: that would lead to crazy
            things like uninitialized parameters, and no return.

            Use `setjmp` for that.
            */
            {
                int i;
                goto_func_after:
                    i = 1;
                /*goto in_func_label;*/
            }

            /* Labels cannot be at the end of compound statments */
            {
                { /*label_end_compound:*/ }
                { label_end_compound: 1; }
            }

            /* Labels and loops */
            {
                int i;
                for ( /*label_in_for:*/ i = 0; i < 2; i++)
                label_after_if:
                {
                    label_after_if2: 1;
                }
            }

            /* Labels and switch. */
            {
                int a = 1;
                switch (a) {
                    case 0:
                    label_case_0:
                        assert(a == 1);
                    break;
                    case 1:
                        goto label_case_0;
                    break;
                }
            }
        }

        /*
        # setjmp.h

            Jumps without scope restrictions of goto labels.

            # setjmp

                Saves register states, including instruction and pointer registers.

                Return value:

                - 0 if did not return from longjmp
                - != 0 if just returned from a lonjmp

                Application: error handling a la exception. Return val encodes the exception type.

            # longjmp

                Restores register states.

            # longjmp and signals

                If you longjmp from a signal handler you can recatch the signal afterwards.
        */
        {
            jmp_buf env_buffer;
            int val;

            val = setjmp(env_buffer);
            printf("setjmp = %i\n", val);
            if (val != 0) {
                /* Returned from longjmp. */
                /* Val encodes the error code. */
            } else {

                /* This is evaulated normally. */
                assert(setjmp_func(0, env_buffer) == 1);

                /* This assert is never evaluated. */
                assert(setjmp_func(1, env_buffer) * 0 == 1);
            }
        }
    }

    /* # command line args */
    {
        printf("argv[0] = %s\n", argv[0]);
        int i = 0;
        if (argc > i) {
            i++;
            printf("argv[%d] = %s\n", i, argv[0]);
        }
        if (argc > i) {
            i++;
            printf("argv[%d] = %s\n", i, argv[0]);
        }
    }

    /*
    # environment variables

        # getenv

            Returns NULL if not found.

        TODO: setenv in POSIX but not in ANSI C?
    */
    {
        printf("getenv\n");
        printf("  HOME = %s\n", getenv("HOME"));
        printf("  NOT_DEFINED = %s\n", getenv("USERPROFILE"));
        assert(getenv("NOT_DEFINED") == NULL);
    }

    /*
    # trigraphs

        Absolutelly obscure feature for very old systems which do not support certain
        characters or because of keyboards which don't support them easily

        It is so obscure that gcc even emmits a warning if you use those!!

        Is the first substitution made to source, even before the preprocessor.

        They are commented out here so that compilers like
        gcc won't annoy us with warnings.
    */
    {
        /*assert('??=' == '#');*/
        /*assert('??(' == '[');*/
        /* TODO literal backslash? */
        /*assert('??/' == '\');*/
        /*assert('??)' == ']');*/
        /*assert('??'' == '^');*/
        /*assert('??<' == '{');*/
        /*assert('??!' == '|');*/
        /*assert('??>' == '}');*/
        /*assert('??-' == '~');*/

        /*
        TODO how to escape a trigraph on a string literal, say: `??=` ?
        is it necessary to use `\x`?
        */
        /*printf("??")*/
    }

    /*
    # Standard library.

    # stdlib

        This section is about the stdlib, not the language itself.

        It is not possible to implement many parts of the stdlib portably
        just in terms of the language, as the only way to do that is with extensions (Linux / POSIX / assembly).

        E.g.:

        - IO: printf and family
        - malloc
    */
    {
        /*
        # errno.h

            Used for error handling.

            Defines `errno`, which can be set by user or library functions to indicate the error type.

            It is commonly used in operations such as file IO.

            Also define a few possible values which libc may set `errno` to:

            - EDOM. Domain error. Generated for example on `sqrt(-1.0)` of `math.h`.
            - EILSEQ
            - ERANGE

            *Many* more such errors are defined for example by POSIX.

            Each error has an error message string associated to it.
            To get that error message, consider using `strerror`.
            To print an error message to stderr, consider using `perror`.
        */
        {
            errno = 0;      /* no error */
            errno = EDOM;   /* EDOM error */
        }

        /*
        # unicode

            Use wchar.

        # wchar.h
        */
        {
#include <wchar.h>
            char cs[] = "汉语";
            printf("%s\n", cs);

            /* BAD: only changes first byte you get trash all over: */
            /*cs[0] = 'a';*/
            /*printf("%s\n",cs);*/

            /* WARN */
            /*cs[0] = '英';*/

            /* You *need* setlocale to print correctly: */
            setlocale(LC_CTYPE, "");

            wchar_t  wcs[] = L"汉语";

            printf("%ls\n", wcs);

            wcs[0] = L'英';
            printf("%ls\n", wcs);

            wcs[0] = L'a';
            printf("%ls\n", wcs);

            /* ERROR: non wide init */
            /*wchar_t  wideString2[] = "asdf";*/
        }

        /*
        # fenv.h

            contains flags that indicate the status of floating point related registers

            TODO get some interesting and basic samples working
        */

#if __STDC_VERSION__ >= 199901L
#ifndef __STDC_NO_COMPLEX__
        /*
        # complex.h

            Defines:

            - convenient typedefs like `_Complex` and `I`
            - common operations over complex types: creal, cimag, cabs, etc.

            The complex types themselves are a feature of the language and shall not be described here.

            There is no direct printf way to print complex numbers:
            <http://stackoverflow.com/questions/4099433/c-complex-number-and-printf>

            All functions provided by this header are prefixed by `c`.

            <http://en.wikipedia.org/wiki/Tgmath.h#Complex_numbers>

            # complex vs _Complex

                `complex` is a typedef to `_Complex` contained in this header.

                The actual type keyword is `_Complex`: the language could not add
                a `complex` keyword because it could conflict with older programs.

                Adding `_Complex` however is fine because it is a reserved identifier.

                Prefer using `complex`: in the future it may become an actual keyword.
                It is easier to read and write.

            # I vs _Complex_I

                TODO

            # _Imaginary

                Defined in non normative section of C11.

                TODO vs complex?
        */
        {
#include <complex.h>
            const double err = 10e-6;

            /* Typedef to literal. There is not explicit literal in the language. */
            assert(I == _Complex_I);

            const double complex zd =  1.0 + 2.0*I;
            const double complex zd2 = 1.0 + 1.0*I;

            assert(sizeof(float complex ) <= sizeof(double complex));
            assert(sizeof(double complex) <= sizeof(long double complex));

            /* Real and imaginary parts. */
            assert(creal(zd) == 1.0);
            assert(cimag(zd) == 2.0);

            /* Subtraction. */
            assert(creal(zd - zd2) == 0.0);
            assert(cimag(zd - zd2) == 1.0);

            /* Multiplication. */
            assert(creal(zd * zd) == -3.0);
            assert(cimag(zd * zd) ==  4.0);

            /* Division. */
            assert(creal(zd / zd) == 1.0);
            assert(cimag(zd / zd) == 0.0);

            /* Conjugation. */
            assert(creal(conj(zd)) ==  1.0);
            assert(cimag(conj(zd)) == -2.0);

            /* absolute value == norm == module */
            assert(abs(cabs(3.0 + 4.0 * I) - 5.0) < err);

            /*
            # csqrt

                Unlike sqrt, can return imaginary outputs and take imaginary inputs.
            */
            {
                assert(cabs(csqrt(-1.0) - I) < err);
            }

            /*
            # cproj

                TODO
            */

            /*
            # csin

                TODO
            */
            /*assert(cabs(csin(I) - ) < err);*/
        }
#endif
#endif

#if __STDC_VERSION__ >= 201112L
            /*
            # noreturn.h

                Defines `noreturn`, a macro to `_Noreturn`.
            */
#endif

        /*
        # iso646.h

            Obscure header with macros that avoid using characters such as `|` or '~'
            which may be hard to type on certain international keyboards.

            - and:      &&
            - and_eq:   &=
            - bitand:   &&
            - bitor:    &
            - compl:    |
            - not:      !
            - not_eq:   !=
            - or:       ||
            - or_eq:    |=
            - xor:      ^
            - xor_eq:   ^=
        */
        {
#include <iso646.h>
            assert(1 and 1);
        }

#if __STDC_VERSION__ >= 199901L
        /*
        # tgmath.h

            TODO

            http://libreprogramming.org/books/c/tgmath/
            http://carolina.mff.cuni.cz/~trmac/blog/2005/the-ugliest-c-feature-tgmathh/
        */
        {
/* #include <tgmath.h> */
        }
    }
#endif

    /*
    # Design patterns

        A good way to learn is to look at existing libraries:

        - https://github.com/libgit2/libgit2
    */
    {
        /*
        # Objects

            Prefix every function that acts on an object with the name of the object.

            The first non return parameter of the function
            should be a pointer to the struct, AKA self in many languages.

            E.g., libgit 2 repository methods are all of the type:

                git_repository_X(git_repository* repo, ...);
        */

        /*
        # Private struct fields

            Use opaque structs and expose public fields through getter and setter methods.
        */

        /*
        # Namespaces like in C++

            Prefix everything public in your entire libray with a single identifier.

            E.g., in libgit2, every public identifier starts with `git_`.

            Of course, with this it is not possible to omit the namespace like in C++,
            but many C++ coding styles don't allow that either because it becomes confusing what is what.
        */

        /*
        # Inheritance

            The closest substitution to inheritance is struct inclusion / composition:

                typedef struct derived {
                    struct base* base;
                }

            The difference is that you cannot automatically give base methods to the inheriting class.

            But even in C++, object composition is considered a more flexible approach than
            inheritance and is used in some cases.
        */
    }

    /*
    # main return

        Valid returns are:

        - `EXIT_SUCCESS` or `0` to indicate success
        - `EXIT_FAILURE`        to indicate failure

        C99: return is optional. If omited a `return 0` is added to the program.

        But just always return to be C89 compatible.
    */
    {
        printf("ALL ASSERTS PASSED\n");
        return EXIT_SUCCESS;
        return EXIT_FAILURE;
    }
}