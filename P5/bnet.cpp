#include <iostream>
#include <set>
#include <map>

using namespace std;

//check input for valid values
set <char> events = {'B','E','A','J','M'};
set <char> conditions = {'t', 'f'};

map <char,char> INPUT; 
map <char,char> GIVEN;

float chain_rule (map <char,char> inputs);
float calc_prob(map <char,char> var);
float given(map <char,char> prob,map <char,char> givens );
float calc_PJ();
float calc_PA();
float calc_PM();

bool check_args (int argc, char* argv[]){
    // 1 <= argc <= 6
    if (argc< 2 || argc > 8) {
        return false;
    }
    // argv: {B, E, A, M, J} + {t,f} + given + {(<= 4)}
    bool seen_given = false;
    for (int i = 1; i< argc; i++){
        char event = argv[i][0];
        char condition = argv[i][1];
          if (string(argv[i]) == "given"){
              if (seen_given || i== 1){
                  return false;
              }
            seen_given= true;
            continue;
        }
        if( events.find(event)== events.end()){
            return false;
        }
        else if (conditions.find(condition)== conditions.end()){
            return false;
        }
        if (!seen_given){
           
            if (INPUT.find(event) != INPUT.end()){
                //checks duplicates
                return false;
            }
            else {
                INPUT.emplace(event, condition);
            }
            
        }else{ //check for givens
            
         
            if (GIVEN.find(event) != GIVEN.end()){
                //checks duplicates
                return false;
            }
           else {
                GIVEN.emplace(event, condition);
            }
            
        }

    }
    
    return true;
}



float calc_PM (){
    //P(M|A) = P(A|M) P(M)/P(A)
    //P(M)= P(M|A) P(A)/ P(A|M) 

    float PMgA= 0;

    map <char,char> A;
    A.insert(make_pair('A',INPUT['A']));
    map <char,char> M;
    M.insert(make_pair('M',INPUT['M']));

    if (A['A'] == 't'){
        PMgA = .70;
    }
    else{
        PMgA = .01;
    }

    return PMgA*calc_PA()/given(A,M);

}


float calc_PJ(){
    //P(J|A) = P(A|J) P(J)/P(A)
    //P(J)= P(J|A) P(A)/ P(A|J)

    float PJgA = 0;

    map <char,char> A;
    A.insert(make_pair('A',INPUT['A']));
    map <char,char> J;
    J.insert(make_pair('J',INPUT['J']));

     if (A['A']== 't'){
        PJgA = .90;
    }
    else{
        PJgA = .05;
    }

    return PJgA*calc_PA()/given(A,J);

}

float calc_PA(){
    //P(A|B,E)= P(B,E|A) P(A)/ P(B,E)
    //P(A)= P(A|B,E)*P(B,E)/P(B,E|A)

    float PAgBE =0;

    map <char,char> A;
    A.insert(make_pair('A',INPUT['A']));
    map <char,char> BE;
    BE.insert(make_pair('B',INPUT['B']));
    BE.insert(make_pair('E',INPUT['E']));
    if (BE['B']== 't'){
        if (BE['E']== 't'){
            PAgBE = .95;
        }
        else {
            PAgBE = .94;
        }
    } else {
        if (BE['E'] == 't'){
            PAgBE = .29;
        }
        else {
            PAgBE = .001;
        }
    }


    return PAgBE*chain_rule(BE)/given(BE,A);
}


float calc_prob(map <char,char> var){
    float prob =0;

    switch (var.begin()->first){
        case 'B':
        prob = .001;
        break;
        
        case 'E':
        prob = .002;
        break;

        case 'A':
        prob = calc_PA();
        break;

        case 'J':
        prob = calc_PJ();
        break;

        case 'M':
        calc_PM();
        break;        
    }

   if (var.begin()->second == 'f'){
       prob = 1- prob;
   }
    
    return prob;
}

float given (map <char,char> prob,map <char,char> givens ){
    // calculate P(prob|givens)
     // P(A|B) = P(B|A)P(A)/P(B)
    if (givens.size()== 0){
        return chain_rule(prob);
    }

    if (givens.size()==1 && prob.size()==1){
        return calc_prob(givens) * calc_prob(prob) / calc_prob(givens);
    }else{

     return chain_rule(givens)*chain_rule(prob)/chain_rule(givens);
    }
}


float chain_rule (map <char,char> inputs){
    // P(ABC...(n)) = P(n|ABC...(n-1)) P(ABC...(n-1))
    if (inputs.size()==1){
        return calc_prob(inputs);
    }
     if (inputs.size()==2){
        map <char,char> A; //the left side of given
        A.insert(make_pair(inputs.begin()->first, inputs.begin()->second));
        inputs.erase(inputs.begin());
        return given(A,inputs)* calc_prob(inputs);
    }else{
    map <char,char> prob; //the left side of given
    prob.insert(make_pair(inputs.begin()->first, inputs.begin()->second));
    inputs.erase(inputs.begin());
    return given(prob,inputs)*chain_rule(inputs);
    }
}


int main(int argc, char* argv[]){
    //check valid args
    if (!check_args(argc, argv)){
        cerr << "INVALID INPUT" << endl;
        return -1;
    }

  cout << given(INPUT,GIVEN) << endl;
}