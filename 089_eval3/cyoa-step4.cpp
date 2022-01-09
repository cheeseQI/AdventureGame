#include "page.hpp"
#include "errorHandeler.h"
#include "book.hpp"

int main(int argc, char ** argv){
    try{
        if (argc == 2){
            Book mybook;
            mybook.checkBook(argv[1]);
            mybook.checkReachable();
            mybook.findPath();
        }
        else throw argumentException();
    }
    catch(exception & e){
            errorMessage(e.what());
    }
        return EXIT_SUCCESS;
}