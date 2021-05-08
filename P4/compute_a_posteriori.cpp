#include <iostream>
#include <map>
#include <string>

using namespace std;

map <char, int> evidence = {
    //initialized so *.find works
    {'C',0},
    {'L',0}
};













bool check_arg(int argc, char* argv[]){
    // argc should be 1 or 0
    if (argc > 1) {
        return false;
    }
    // argv should only have C or L
    for (int i = 0; argv[i] != '\0'; i++){
        char candy = *argv[i];

        if ( evidence.find(candy)== evidence.end()){
            return false;
        }
        else {
            evidence[candy] ++;
        }
    }
    return true;
}



int main(int argc, char* argv[]){

    if (!check_arg(argc, argv)){
        cerr << "INVALID INPUT" << endl;
        return -1;
    }
        
    int numc = evidence['C'];
    int numl = evidence ['L'];
    int evidence_size = numc + numl;
    float clikely = numc/evidence_size;
    float llikely = 1-clikely;

    /*
    h1 (prior: 10%): This type of bag contains 100% cherry candies.
    h2 (prior: 20%): This type of bag contains 75% cherry candies and 25% lime candies.
    h3 (prior: 40%): This type of bag contains 50% cherry candies and 50% lime candies.
    h4 (prior: 20%): This type of bag contains 25% cherry candies and 75% lime candies.
    h5 (prior: 10%): This type of bag contains 100% lime candies. 
    */

    return 0;
}