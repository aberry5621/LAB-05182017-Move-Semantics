//
//  main.cpp
//  LAB 05182017 Move Semantics
//
//  Created by ax on 5/20/17.
//  Copyright © 2017 COMP235. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;
class Glob
{
public:
    Glob() { *dataPtr = 111; }
    Glob(const Glob& lvalueP)
    {
        cout << "Regular constructor is called!\n";
        *dataPtr = 111;
        //...
    }
    Glob(Glob&& rvalueP)
    {
        cout << "Move constructor is called!\n";
        dataPtr = rvalueP.dataPtr; //Steal address
        rvalueP.dataPtr = nullptr; //remove ownership
        //...
    }
    //Coded to produce a rvalue
    Glob operator+ (const Glob& p_glob)
    {
        Glob temp;
        *(temp.dataPtr) = *dataPtr + *(p_glob.dataPtr);
        return temp;
    }
    // lvalue
    Glob operator= (const Glob& p_lhs)
    {
        cout << "regular lvalue reference parameter used!\n";
        Glob temp;
        *(temp.dataPtr) = *(p_lhs.dataPtr);
        return temp;
    }
    // rvalue
    Glob operator= (Glob&& rvalueP)
    {
        cout << "rvalue reference paramter used!\n";
        Glob temp;
        *(temp.dataPtr) = *(rvalueP.dataPtr);
        return temp;
    }
    //0. Run this code and observe the outputs from the driver given below
    //I. Overload the assignment operator, using a regular lvalue reference parameter
    //II. Overload the assignment operator, using rvalue reference paramter
    //III. Then in the driver, demonstrate assignments in the similar way
private:
    int *dataPtr = new int;
};
int main()
{
    cout << "MOVE SEMANTICS" << endl;
    
    // basic rvalue references

    cout << "&&rvalueRef is assigned the result of an expression... 2 + 3" << endl;
    int &&rvalueRef = 2 + 3;
    cout << "&rvalueRef is : ";
    cout << &rvalueRef << endl;
    
    
    // doubleRef is assigned the result of an expression
    cout << "&&doubleRef is assigned the result of an expression... sqrt(36.0)" << endl;
    double &&doubleRef = sqrt(36.0);
    cout << "&doubleRef is : ";
    cout << &doubleRef << endl;
    
    // Globbie LAB exercises
    Glob globbie1;
    Glob globbie2;
    Glob globbie3(globbie1); //Regular constructor
    cout << endl;
    Glob globbie4(globbie1 + globbie2); //Move constructor
    Glob globbie5;
    cout << endl;
    cout << "LVALUE EXAMPLE: " << endl;
    cout << endl;
    globbie5 = globbie1; // lvalue
    cout << endl;
    Glob globbie6;
    cout << "RVALUE EXAMPLE: " << endl;
    cout << endl;
    globbie6 = globbie1 + globbie2; // rvalue
    cout << endl;
    cout << "Construct Globbie 7 with RVALUE argument: " << endl;
    Glob globbie7(globbie1 + globbie2 + globbie3);
    globbie1 = globbie7;
    globbie2 = globbie1;
    globbie3 = globbie4;
    return 0;
}
