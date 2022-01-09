#ifndef _PAGE_HPP_
#define _PAGE_HPP_
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "errorHandeler.h"

using namespace std;
#define ZERO 48 //ascii of 0
#define NINE 57 //ascii of 9


/**
 * @brief This function check whether input is number
 * @return true if it is number
 */
bool checkNum(string pageNum){ //ascii from 48-57, 1 to 9; also first number can not be 0
    if (pageNum[0] == ZERO) return false;
    size_t j = 0;
    for(size_t i = 0; i < pageNum.length(); i ++){
        if(pageNum[i]<= NINE && pageNum[i]>= ZERO){ // if it is digit from 0 to 9
            j++;
            }
    }
    if (j == pageNum.length()) {//all places of word is digit
        return true;
    }
    return false;
}

/**
 * @brief This class is used to store all information of a single page
 * including text content, referred pages, end information
 *  And print the content of this page
 */
class Page{
private:
    string text;
    vector<string> choice; 
    bool winPage;
    bool losePage;
    vector<string> reference;
public:
    Page(): text(), choice(), winPage(false), losePage(false), reference(){}
    ~Page() {}

    /**
     * @brief This function reads all text, reference, ending information and store it
     * 
     * @param pageName is the name of the reading page
     */
    void readPage(const char * pageName){
            ifstream afile;
            afile.open(pageName);
            if (afile.fail()) throw openException();
            bool choicePart = true;
            while (!afile.eof()){
                string currentLine;
                getline(afile, currentLine);
                if (currentLine[0] == '#') {
                    choicePart = false;
                    continue;
                }
                if (choicePart){                        //choice Parse
                    size_t split = currentLine.find(":");
                    string PageNum = currentLine.substr(0, split);
                    if (split != string::npos){
                        if (checkNum(PageNum)){         // if the page number is positive integer
                            reference.push_back(PageNum); //record the referenced pages
                            currentLine = currentLine.substr(split + 1);
                            choice.push_back(currentLine);
                        } 
                        else{
                        throw nonPositiveIndexException();
                        } 
                    }
                    else if(currentLine == "WIN"){
                        winPage = true;
                        continue;
                    }
                    else if (currentLine == "LOSE"){
                        losePage = true;
                        continue;
                    }
                    else {
                        throw noColonException();
                    }
                }
                else {                                  //Text parse
                    text += currentLine;
                    text += "\n";
                }
            }
            if (choicePart) throw noPartitionException();
            afile.close();
            text = text.substr(0, text.length() - 1);
            if (reference.size() != 0 && (winPage||losePage)) throw endPageHasOptionException();
            if (winPage == true && losePage == true) throw  endPageWinAndLoseException();
            if (reference.size() == 0 && winPage == false && losePage == false) throw nonPageInfoException();
    }
    
    //print the choices that user can choose
    void printChoice(){
        if (winPage){
            cout << "Congratulations! You have won. Hooray!" << endl;
            return;
        }
        else if (losePage){
            cout << "Sorry, you have lost. Better luck next time!" << endl;
            return;
        }
        cout << "What would you like to do?" << endl;
        cout << endl;
        vector<string>::iterator it = choice.begin();
        int index = 1;
        while (it != choice.end()){
            cout << " " << index << ". " << (*it) <<endl;
            ++it;
            ++index;
        }
    }

    //print text content of page
    void printText(){
        cout << text << endl; 
    }
    
    //check whether it is win page
    bool isWin(){
        return winPage;
    }

    //check whether it is lose page
    bool isLose(){
        return losePage;
    }

    //get the references/choice pages of the page
    vector<string> getReference(){
        return reference;
    }
};

#endif