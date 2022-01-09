#ifndef _BOOK_HPP_
#define _BOOK_HPP_
#include <algorithm>   
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "page.hpp"
using namespace std;

/**
 * @brief used to check whether the file(pages) are exhausted
 * Did not list in book classs because this is file problem instead of an attribute of book
 */
bool fileExhausted(const char * pageName, int num){ //check whether run out of files
    try{
        Page currentPage;
        currentPage.readPage(pageName);
    }
    catch(openException & e){
        if (num == 1){ // first file can not be open, it may be broken, or the book is not start from page1!
            errorMessage(e.what());
        }
        else {    //run out of files
            return true;
        }
    }
    return false;
}

/**
 * @brief This book class is used to store the pages file information of a directory
 * step2 step3 step4 are based on implementing this class
 * It stores information of containing pages, reachable pages and ending page information.
 */
class Book{
private:
    set<int> containPage;
    set<int> referPage;
    set<int> reachablePage;
    map<int, int> reachablePageWithDepth;     //record page with its depth
    char * bookName;
    bool winPage;
    bool losePage;
    bool winBook;
public:
    Book(): containPage(), referPage(), reachablePage(), winPage(false), losePage(false), winBook(false){}
    ~Book() {}
    string getPageName(int num, string fileName){
    fileName += "//page";
    stringstream ss;
    ss<<num; 
    string number = ss.str();
    fileName +=  number;
    fileName += ".txt";
    return fileName;
    }

    /**
     * @brief This function check whether the book is correct: has lose and win pages,
     *  all refered pages are valid
     * 
     * @param directoryName is the input path of directory
     */
    void checkBook(char * directoryName){
        int num = 1;
        bookName = directoryName;
        string preName(bookName);
        string fileName = getPageName(num, preName);
        const char * newName = fileName.c_str();
        while (!fileExhausted(newName, num)){
            Page currentPage;
            currentPage.readPage(newName);
            if (currentPage.isLose()){
                losePage = true;
            }
            else if (currentPage.isWin()){
                winPage = true;
            }
            else{
                vector<string> currentReference = currentPage.getReference();
                vector<string>::iterator it = currentReference.begin();
                while(it != currentReference.end()){
                    int refer = atoi((*it).c_str());
                    referPage.insert(refer);
                    ++it;
                }
            }
            containPage.insert(num);
            num ++;
            fileName = getPageName(num, preName);
            newName = fileName.c_str();
        }
        if (!(winPage && losePage)) throw noEndingException();
        if (!checkRefer()) throw unmatchedException();
    }

    //This function check whether all refered page are in the containing pages of the book
    bool checkRefer(){
        containPage.erase(1); //because refer page does not have 1. Before comparision, we need to remove it
        if (referPage.size() != containPage.size()) return false;
        set<int>::iterator it1 = referPage.begin(); 
        set<int>::iterator it2 = containPage.begin();
        while(it1 != referPage.end()){
            if ((*it1)!=(*it2)) return false;
            ++it1;
            ++it2;
        }
        return true;
    }

    /**
     * @brief This function read the given book according to user input 
     * User can choose which next page to read, and it will end when book
     * has reached the win or lose page.
     */
    void readBook(){
        size_t num = 1;
        string preName(bookName);
        string fileName = getPageName(num, preName);
        const char * fileNameConst = fileName.c_str();
        Page firstPage;
        firstPage.readPage(fileNameConst);
        firstPage.printText();
        firstPage.printChoice();
        bool beginner = true;
        if ((firstPage.isWin() || firstPage.isLose())) return; //if first page is valid end page, end reading
        vector<string> refer = firstPage.getReference();

        while (true){ //when user does not meet ending page
            string nextNum;
            cin >> nextNum;
            num = atoi(nextNum.c_str()); //index of num, should be positive integer
            while (!checkNum(nextNum) || num > refer.size()){
                cout << "That is not a valid choice, please try again" << endl;
                cin >> nextNum;
                num = atoi(nextNum.c_str());
            }
            int pageNum = atoi(refer[num - 1].c_str()); //get real page number
            if (beginner){                              //for initial case
                beginner = false;
                fileName = getPageName(pageNum, preName);
                fileNameConst = fileName.c_str();
                Page secondPage;
                secondPage.readPage(fileNameConst);
                secondPage.printText();
                secondPage.printChoice();
                refer = secondPage.getReference();
                if (secondPage.isLose() || secondPage.isWin()) return;
            }
            else {
                fileName = getPageName(pageNum, preName);
                fileNameConst = fileName.c_str();
                Page currentPage;
                currentPage.readPage(fileNameConst);
                currentPage.printText();
                currentPage.printChoice();
                refer = currentPage.getReference();
                if (currentPage.isLose() || currentPage.isWin()) return;
            }
        }
    }

    /**
     * @brief This function check whether the pages are reachable
     * if page is reachable, it will also record with the min depth of this page
     * else it will call printDiff for those unreachable pages.
     */
    void checkReachable(){
        bool ChangeFlag = true;                 //check for whether there are any new changes in this round
        reachablePage.insert(1);
        containPage.insert(1);                  //remove it in check so add it back this time;
        reachablePageWithDepth.insert(make_pair(1, 0));   // first page must have 0 depth
        int depth = 1;                              //keep track of the depth of set;---the depth of the min page depth
        while(ChangeFlag){                        //when there exist changes
            ChangeFlag = false;
            set<int> currentReachablePage = reachablePage; //used to record reachablePage in this round of search
            set<int>::iterator itReachSet = currentReachablePage.begin();
            while (itReachSet != currentReachablePage.end()){
                Page thisPage;                  
                string preName(bookName);
                string fileName = getPageName((*itReachSet), preName);
                const char * fileNameConst = fileName.c_str();
                thisPage.readPage(fileNameConst);
                if ((thisPage.isWin() || thisPage.isLose())){ //encounter end page, ignore it
                    ++itReachSet;
                    continue;
                }
                vector<string> refer = thisPage.getReference();
                vector<string>::iterator itPageRefer = refer.begin();
                while(itPageRefer != refer.end()){
                    int reachable = atoi((*itPageRefer).c_str());
                    set<int> copyReachableBefore = reachablePage;
                    pair<set<int>::iterator,bool> pr;       
                    pr = reachablePage.insert(reachable); //insert return a pair, its second means whether insert is successful
                    if (pr.second){                      //if insert has happened
                        ChangeFlag = true;   
                        set<int>::iterator currentIt = reachablePage.begin();
                        set<int>::iterator beforeIt = copyReachableBefore.begin();
                        while (currentIt !=  reachablePage.end()){
                            beforeIt = copyReachableBefore.find(*currentIt);
                            if (beforeIt == copyReachableBefore.end()){ //didn't find current page in before copy
                                reachablePageWithDepth.insert(make_pair(*currentIt, depth)); //added with itReachSet depth
                            }
                            ++currentIt;
                        }
                    }
                    ++itPageRefer;
                }
                ++itReachSet;
            }    
            ++depth;
        }
    }

    //print reachable page with depth
    void printReachable(){
        map<int, int>::iterator myIt = reachablePageWithDepth.begin();
        while (myIt != reachablePageWithDepth.end()){
            cout << "Page " << myIt->first << ":" << myIt->second << endl;
            ++myIt;
        }
        if (reachablePage.size() != containPage.size()){
            printDiff();
        }
    }

    //print unreachable page, by find differrent of containPage and reachablePage
    void printDiff(){
        set<int> diff;
        set<int>::iterator it2 = reachablePage.begin();
        diff = containPage;
        while(it2 != reachablePage.end()){ // find diff set from containPage and reachablePage
            diff.erase(*it2);
            ++it2;
        }
        set<int>::iterator it3 = diff.begin();
        while (it3 != diff.end()){
            cout << "Page " << (*it3) << " is not reachable" << endl;
            ++it3;
        }
    }

    //find all path of win ways
    void findPath(){ //use a vector<bool> has exact same size with reachablePage, vector.indexOf()
                        //every element with same position represent same posision has been visited
        int startPage = 1;
        vector<pair<int, int> > allPath; //record all win path, pair<pageNumber, optionNumber>
        findPathHelper(startPage, allPath);
        if (!winBook) cout << "This story is unwinnable!" << endl;
    }

    /**
     * @brief Helper function to achieve finding paths
     * @param thisPageNum is number of current page
     * @param allPath store the path current used, it will be updated when a whole path is finded or failed 
     */
    void findPathHelper(int thisPageNum, vector<pair<int, int> > allPath){
        Page thisPage;
        string preName(bookName);
        string fileName = getPageName(thisPageNum, preName);
        const char * fileNameConst = fileName.c_str();
        thisPage.readPage(fileNameConst);
        bool visited = false;
        for (vector<pair<int, int> >::iterator itv = allPath.begin(); itv != allPath.end(); ++itv){
            if (itv->first == thisPageNum) visited = true; //check whether has already visited this page
        }

        if (thisPage.isLose()) return; //do nothing, find next
        else if (thisPage.isWin()){                  //if find win page, print path
            winBook = true;
            vector<pair<int, int> >::iterator printIt = allPath.begin();
            while (printIt != allPath.end()){
                cout << printIt->first << "(" << printIt->second << "),";
                ++printIt;
            }
            cout << thisPageNum << "(win)" << endl;
            return;
        }
        else if (visited) return; 
        else{
            vector<string> refer = thisPage.getReference();
            vector<string>::iterator itPageRefer = refer.begin();
            allPath.push_back(make_pair(thisPageNum, 1)); //default setting
            int option = 1;
            while (itPageRefer != refer.end()){
                int nextPage = atoi((*itPageRefer).c_str());
                for (vector<pair<int, int> >::iterator itv = allPath.begin(); itv != allPath.end(); ++itv){
                    if (itv->first == thisPageNum) itv->second = option;
                }
                findPathHelper(nextPage, allPath); //recursively find next page in path
                ++ itPageRefer;
                ++ option;
            }
        }
    }
};

#endif