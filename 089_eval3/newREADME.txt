Choose Your Own Adventure
===========================================================================

In this evaluative assignment, you will be writing a program that presents
a "choose your own adventure" story (CYOA). For those of you not familiar
with this type of story, a "choose your own adventure" book presents a
story, but you do not read every page in order. Instead, pages end with a
choice of where to go. E.g. a page might end with 

 1. If you want to try to sneak past the sleeping dragon, turn to page 47.  
 2. If you want to leave the dragon's cave and go home, turn to page 59.
 3. If you want to draw your sword and attack the dragon, turn to page 32. 

The reader then selects one of these options, turns to the indicated page,
and continues the story. 

For our purposes, the "pages" of the adventure will be provided in a single
directory and numbered, starting with page1.txt. See the included example
directories. Note that we define the story as the set of consecutive page
numbers for which files exist. What we mean by this is that you can look
for page1.txt, page2.txt, page3.txt, etc., in order. As soon as one file
does not exist, you can conclude that you have seen all the pages in the
story (without having to look for other file names). Put another way there
are no "gaps" in the numbers of pages. 

Input format:

The format of an input file is as follows:

 1. The first part of the file is a "navigation" section. It has exactly
    one of the following parts.
    
    1a. The single word "WIN" on a line by itself
    1b. The single word "LOSE" on a line by itself
    1c. One or more lines which describe the choices available at the end
        of this page. Each of these lines is a page number followed by a
	colon, followed by text describing the choice. The page number must
	be a positive integer (strictly greater than 0). Any text is allowed
	after the colon, up to (and including) the newline which ends it.
	An example of three such lines would be: 

47:Try to sneak past the sleeping dragon
59:Leave the dragon's cave and go home
32:Draw your sword and attack the dragon

        Note that these are the same options as above, but slightly
	reformatted as the user of this program will not need to explicitly
	know the page numbers. Furthermore, note that there is no limit to
	the number of choices that can be presented to a user in our
	stories. We *could* give you a story with 10,000 choices on a page,
	100,000 choices on a page, or even 2,000,000 choices on a page.
        All text before the first colon must be a valid number.  We only
	plan to test with base 10 numbers.  If you want to accept octal and/or
	hexadecmial, it is up to you, but not required: we will not test with
	any number other than base 10.

 2. A single line that starts with a # sign, which separates the navigation
    section from the text of hte page. It is legal (but not required) to
    write any text after the #. Your program should ignore anything on this
    line after the #. 

 3. The remainder of the file is the text of the page. You should read this
    text and when the user is on the corresponding page, display it exactly
    as it was in the input file. Note that any text is legal in this
    portion of the file (there is now way any of this input can be
    invalid).

Note that we provide two example stories (one written by Drew,
and one written by Genevieve!) in the story1 and story2 directories.
There are also a variety of other test cases available in

/usr/local/ece551/cyoa/

some of which are valid and some of which are not.  These other test
cases do not really tell meaningful stories (though story1 and story2
are also there for convenience).

Step 1
===========================================================================

For the first part of this assignment, you should make the following:

  - A C++ class Page, which represents a single page in the adventure
    story. This class should make good use of C++'s STL to store the
    information.

  - A program cyoa-step1 that takes the name of one single page as an
    input. This program should read the specified page, check for any
    errors, and if no errors are found, print the page out in the format
    described below. If any errors are found, your program should print an
    error message and exit failure. 

    Note that for this step, you are only reading one page in isolation, so
    you cannot check if the page numbers in the choices are actually valid
    for the story (beyond checking that they are positive numbers).
     
Output format:

Your program (both this program, and the ones in later steps) should print
a page with choices for what to do (i.e., not a WIN or LOSE page) as
follows: 

 1. First, print the text of the page, exactly as it appeared in the input
    file. 
 2. Next, print a blank line.
 3. Then print

What would you like to do?

 4. Then print another blank line.
 5. Then print each possible choice, one per line. For each line, print a
    space, the number of the choice, a period, and another space (e.g.
    " 1. "). After that, print the text of the choice. Possible choices
    should be listed in same order as in the file, which may not be the
    same ordering as by page numbers.
    
For example, if the text of the page were

You see a dragon sleeping in the cave

and the choices were those in the example above, you would print

====start of sample output=====
You see a dragon sleeping in the cave

What would you like to do?

 1. Try to sneak past the sleeping dragon
 2. Leave the dragon's cave and go home
 3. Draw your sword and attack the dragon
====end of sample output=====

If the page has WIN or LOSE instead of choices, you should

 1. First, print the text of the page, exactly as it appeared in the input
    file. 
 2. Next, print a blank line.
 3. Then print either
 
Congratulations! You have won. Hooray!

    or

Sorry, you have lost. Better luck next time!

    You should print the former if the page is a WIN page, and the later if
    the page is a LOSE page. 

    For this phase, make sure your Makefile produces cyoa-step1. As you
    progress through the later phases, you MUST leave cyoa-step1 building
    and working correclty (i.e., we will explicitly test this program).

Hint: You should write cyoa-step1.cpp with *as little* code in it as
possible. It should mostly make use of classes and functions that you have
written in other files, so you can reuse them for later steps.

Be sure your code compiles, test it well, and submit it before proceeding
to the next step. 

Step 2
===========================================================================

For this step, you are going to make cyoa-step2, which should let a person
"read" the story. In particular:

 1. The cyoa-step2 program should take one single command line argument: a
    directory name. This directory should contain the files for each page.
    
 2. The program should read each page, starting at page1.txt. It is an
    error if there is no file named page1.txt in the specified directory.
    
 3. Your program should continue reading pages until a particular page does
    not exist. Note that it is NOT an error for some pageN.txt (N > 1) to
    not exist. It simply indicates that you have read all the pages in the
    story.  It is not an error if there are other pages which were not part
    of the story.  For example, if a directory contains page1.txt page2.txt
    page3.txt page5.txt, then the story consists of pages 1, 2, and 3.  The
    existence of a file named page5.txt is not a problem and your program should
    not do anything with page5.txt.   It is, however, an error if one of the
    pages that is part of the story has an invalid format. 
    
 4. After reading all pages, your program should verify the following
    conditions are met for the story as a whole:
    4a. Every page that is referenced by a choice is valid (e.g., if page
        12 might send you to page 19, there needs to be a page 19 in the
	story). 
    4b. Every page (except page 1) is referenced by at least one *other*
        page's choices. (e.g., if there is a page 12, then some other page
	must have a choice to go to page 12).
	 - Note this does NOT guarantee that each page is reachable from page
	   1.  You could have a group of pages which are not at all reachable
	   but reference each other.
    4c. At least one page must be a WIN page and at least one page must be
        a LOSE page.
	
 5. After checking for any problems with the story, you should begin the
    story on page 1: 
    5a. Display the current page.
    5b. If the current page is WIN or LOSE, exit successfully.
    5c. Otherwise, read a number from the user for their choice. If the
        input is not a number, or it is not valid for the choices on the
	page, prompt the user with the message
	"That is not a valid choice, please try again"
	and read another number. Repeat until they give a valid
	choice.
    5d. Go to the page corresponding to the choice the user selected, and
        repeat the process until you exit in 5b (a WIN or a LOSE page). 

Make sure your Makefile produces cyoa-step2 (and that cyoa-step1 still
builds and runs correctly). Test your program well, and submit before
moving on to the next step. 

As before, we recommend that you write very little code in main, instead
making use of functions and classes you wrote elsewhere.

Step 3
===========================================================================

For this step, you will be writing a program that determines the
"story depth" of each page. The "story depth" of a page P is the
minimum number of other pages that a user has to see while reading
through the story before reaching page P. The story depth of page 1 is
always 0 (as it is the first page). Any page in page 1's choices
(except page 1 if it were to loop back to itself) has story depth
1. If you look at the data provide in story1, the story depths are:

Page 1:0
Page 2:1
Page 3:1
Page 4:1
Page 5:2
Page 6:2
Page 7:2
Page 8:2
Page 9:2
Page 10:3
Page 11:2
Page 12:2
Page 13:3
Page 14:3

Here is what your cyoa-step3 program will do:

 1. As with Step 2, the program will take a directory as a command
    line argument. It should read the input and check for errors as in
    Step 2 (good thing you wrote that code in a re-usable way, right?) 

 2. Determine the "story depth" of each page in the story as described
    above. Note that some pages may not be reachable from the start,
    in which case they have no defined story depth. For each page (in
    numerical order starting from page 1), if the page is reachable
    from the start, your program should print its story depth with the
    following format: 

Page 4:1

    that is, Page (number):(number) where the first number is the page
    number and the second number is the story depth. If the page is
    not reachable from the start and has no story depth, your program
    should print that information in the following format:

Page 27 is not reachable

Note that the output of cyoa-step3 for story1 should be as shown
above. 

Hint 1: Think about the story as a graph (make sure you have read and
        understood AoP Chapter 25), and think about what graph algorithm
        makes the most sense here. Especially think about how and when
        you want to mark a node "visited."
Hint 2: In the next step you may want a similar, but slightly
        different graph algorithm. How can you best avoid duplication
        of code here (AoP even gives you some hints on this...)?

Make sure your Makefile produces cyoa-step3 (and that cyoa-step1 and
cyoa-step2 still build and run correctly). Test your program well, and
submit before moving on to the next step.

Step 4
===========================================================================

For this step, you are going to write cyoa-step4 which will help you
find all cycle-free ways to "win" a given choose your own adventure
story. Note that this does NOT mean you are to assume the story has no
cycles. It only means that you should print each way to win that does
not repeat the same page. For example, if the story had a path to win
like 

       +--------+
       |        |
       V        |
 1->2->3->4->5->6->7(win)
    ^     |  |     ^
    |     |  |     |
    +-----+  +->8->9

You would only report the paths that use pages 1,2,3,4,5,6,7 and
1,2,3,4,5,8,9,7 as those are the two ways to win without repeating a
page (there are infinite ways to win if you allow repetition of
pages).  
    
 1. As with Steps 2 and 3, the program will take a directory as a
    command line argument. It should read the input and check for
    errors as in Step 2 (you are really glad you wrote reusable code
    now, right?)  

 2. The program should then determine all possible cycle-free winning
    paths. The paths should be reported one per line, with a format of
    page number(choicenumber),pagenumber(choice number)...pagenumber(win)  
    For example, your program might print:

1(1),2(3),3(1),4(2),5(3),6(1),7(win)
1(1),2(3),3(1),4(2),5(3),8(1),9(2),7(win)

The first lines says you start on page 1 and select choice 1. Then
page 2 where you select choice 3. Next is page 3 where you select
choice 1. This continues until page 7, where you win. 

Note that you may print the lines in any order. I.e., if the above
answer is correct, then so is this answer (where the lines are the
same, but their order has been swapped): 

1(1),2(3),3(1),4(2),5(3),8(1),9(2),7(win)
1(1),2(3),3(1),4(2),5(3),6(1),7(win)

If there are no ways to win (the win page is unreachable from the
start page), your program should instead print 

This story is unwinnable!

The program should still exit successfully if it prints the above
message, which is not an error (but instead a legitimate result of the
program).  

Hint: Step 3 hinted that you want a similar but slightly different
      graph algorithm here. Think especially about how and when you
      want to mark nodes as "visited" in this problem, if you want to
      find ALL cycle-free winning paths. That is, you only want to
      avoid re-visiting a node on the same path.

Make sure your Makefile produces cyoa-step4 (and that cyoa-step1,
cyoa-step2, and cyoa-step3 still build and run correctly). Test your
program well, and submit.

Code Quality
===========================================================================

Your code will also be graded for its quality. Your grader will assess the
quality of the abstraction, naming, formatting, OOP, and documentation
of your code. For this assignment, this means to think about:
  - Abstraction: function length and design, .hpp/.cpp file separation
  - Naming: class, variable, function names
  - Formatting: standard (you can do this automatically by saving in
    Emacs; otherwise, you should run clang-format on your source code
    file)
  - OOP: you have at least two classes, and their relationships,
    fields, and methods make sense, using access specifiers and const
    appropriately 
  - Documentation: comment describing each of the functions you write,
    as well as a comment if you write anything complex or unusual. 

Testing
===========================================================================

We will provide a "pregrader" you can use to run your own test cases
to make sure your code's output agrees with the output of our
implementation. Before the deadline, when you do 'grade', the
pregrader will look for a file testcases.txt with the following
format: 

#error
cyoa-step1 invalid.txt
cyoa-step2 broken1

#success
cyoa-step1 story1/page1.txt
cyoa-step2 story1 < test1/input2.txt
cyoa-step3 story1
cyoa-step4 story1

That is, a section with the #error header containing error test cases,
which should give an appropriate error message and exit with a failure
status. You are free to make your own test files.

The next section has a #success header and is followed by test cases
that should have a success status. For these the pregrader will check
that your results match ours. Note, you must provide input files for
what the user would type to "read" a story. For example, you might
have a directory test1 with test inputs for story1, where there might
be a file input2.txt with this contents: 

2
1

You can easily generate test files like this by doing

tee test1/input2.txt | ./cyoa-step2 story1

then "reading" the story. Note that you will need to press control-D
when you are done to indicate end of input to "tee". Your typed inputs
will be saved to test1/input2.txt, so that you could then read the
story like 

./cyoa-step2 story1 < test1/input2.txt

You may write as many test cases as you like, but you are limited to
20 seconds of compute time by the pregrader.

Reminders
===========================================================================

Before the hard deadline, your code will be graded by the pregrader
that runs your test cases. After the hard deadline, your code will be
graded ONCE. You may run "grade" as many times as you like, but the
last commit after which you run grade before the deadline will be your
submission. Grading quality takes some time, so expect your real grade
to take about a week to come back.

When testing, you should think of error cases, corner cases, and
design your own test inputs. Your code should valgrind without errors
on all cases and without memory leaks on all success cases.

This is an INDIVIDUAL assignment. You are only allowed to communicate
regarding this assignment with an instructor or TA.