#include "page.hpp"
#include "errorHandeler.h"

int main(int argc, char ** argv){
    try{
    if (argc == 2){
        Page mypage;
        mypage.readPage(argv[1]);
        mypage.printText();
        mypage.printChoice();
    }
    else throw argumentException();
    }
    catch(exception & e){
        errorMessage(e.what());
    }
    return EXIT_SUCCESS;
}