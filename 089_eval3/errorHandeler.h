#ifndef _ERROR_H_
#define _ERROR_H_

#include <exception>
#include <stdexcept>
#include <iostream>
using namespace std;

/**
 * @brief This library holds all exception dealing functions
 * Those functions are called when there exist throw condition
 * in page.hpp and book.hpp
 */

void errorMessage(const char * msg) {
  std::cerr << msg << std::endl;
  exit(EXIT_FAILURE);
}

//when the referred page do not match any existing page in book
struct unmatchedException: public exception{
    const char* what () const throw(){
     return "given reference page does not match all existing pages in books!";   
    }
};

//when the book doesn't have win/lose page
struct noEndingException: public exception{
    const char* what () const throw(){
     return "Lack of lose or win page for the book!";   
    }
};

//when there is no colon in choice text
struct noColonException: public exception{
    const char* what () const throw(){
     return "There is no : for the choice!";   
    }
};

//when the given page is not positive 
struct nonPositiveIndexException: public exception{
    const char* what () const throw(){
     return "The choice page is not positive integer!";   
    }
};

//when the page does not have any info(neither win, lose, or any optioins)
struct nonPageInfoException: public exception{
    const char* what () const throw(){
     return "The page does not have any win, lose, or optioins!";   
    }
};

//when the endPage occur and it also has some options
struct endPageHasOptionException: public exception{
    const char* what () const throw(){
     return "The end page should not have any options!";   
    }
};

//when the endPage has both win and lose flag
struct endPageWinAndLoseException: public exception{
    const char* what () const throw(){
     return "The end page should not have win and lose at the same time!";   
    }
};

//when there is no divide partition symbol(#) in the page
struct noPartitionException : public exception{
    const char* what () const throw(){
     return "There is no # to divide the page!";   
    }
};

//when cannot open the file;
struct openException : public exception{
    const char* what () const throw(){
     return "Cannot open the file!";   
    }
};

//when the arguments is invalid
struct argumentException : public exception{
    const char* what () const throw(){
     return "Invalid arguments!";   
    }
};


#endif