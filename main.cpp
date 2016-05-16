/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on January 10, 2014, 6:49 PM
 * Testing something like a hashcash algorithm
 * Sample output
 *      The initial random number = 867605078
 *      The base message = What a difference a day makes!
 *      The total time take = 5 (secs)
 *      The number of zeroes = 5
 *      The hex output = 00000273f4e5e9e2c510995a0b1116cdaf6d4f5f
 *              0 zeroes occured 915586 times
 *              1 zeroes occured 57248 times
 *              2 zeroes occured 3557 times
 *              3 zeroes occured 212 times
 *              4 zeroes occured 22 times
 *              5 zeroes occured 1 times
 */

//System Libraries
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <ctime>
#include <sstream>
using namespace std;

//Sha1 algorithm copied from somewhere
#include "GeneralHashFunctions.h"
//using namespace sha1;

//Function Prototypes
int count0(char [],int);
void prntRes(int [],int);

//Execution Begins here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    //Choose a random number and declare the hex for sha1
    int randNum=rand();
    const int HXSIZE=41;
    char hex[HXSIZE];;
    cout<<"The initial random number = "<<randNum<<endl;
	string strHash;
	//Create a message
    string msg="What a difference a day makes!";
    cout<<"The base message = "<<msg<<endl;
    //Setup the number of loops and loop variables
	int endLoop = 6, freq[HXSIZE] = {}, cntZero=0, cntDigits=0;
    //Record the start time
    int strTime=time(0);
    //Loop until you have reached the number of zeroes desired
    do{
        //Create a concatenation of the two by first converting the random
        //number to a string
        ostringstream convert;   // stream used for the conversion
		ostringstream convert2;
		randNum += 50;
		convert << randNum++;     // insert the textual representation of 'Number' in the characters in the stream
        string strRnd = convert.str();
        string newMsg=msg+strRnd;
        //cout<<newMsg<<endl;
        //Convert to a character message
        char cMsg[100];
        strcpy_s(cMsg, newMsg.c_str());
        int size=sizeof(cMsg)-1;
        //utilize the sha1 function
        unsigned char code[20];
//        calc(cMsg, size, code);
//        toHexString(code, hex);
//        cntZero=count0(hex,endLoop+1);
		convert2 << FNVHash(newMsg);
		strHash = convert2.str();
		cntDigits = strHash.length();
		cntZero = 10 - cntDigits;	// 10 is the maxlen of unsigned 32 bit int
//		cout << strHash << "  " << cntDigits << endl;
		freq[cntZero]++;
    }while(cntZero<endLoop);
    //Take the time it took
    int endTime=time(0);
    //Output the result
    cout<<"The total time take = "<<endTime-strTime<<" (secs)"<<endl;
    cout<<"The number of zeroes = "<<cntZero<<endl;
//    cout<<"The hex output = "<<hex<<endl;
	cout << "The last hash was " << strHash << endl;
    prntRes(freq,cntZero);
    //Exit stage right

	system("Pause");

    return 0;
}

void prntRes(int freq[],int n){
    //Output the frequency for each occurence
    for(int i=0;i<=n;i++){
        cout<<i<<" zeroes occured "<<freq[i]<<" times"<<endl;
    }
}

int count0(char str[],int n){
    int cnt=-1;
    do{
        cnt++;
    }while(str[cnt]=='0');
    return cnt;
}

/* OUTPUT
The initial random number = 10235
The base message = What a difference a day makes!
The total time take = 184 (secs)
The number of zeroes = 7
The last hash was 753
0 zeroes occured 4163901 times
1 zeroes occured 1137167 times
2 zeroes occured 113831 times
3 zeroes occured 11481 times
4 zeroes occured 1160 times
5 zeroes occured 122 times
6 zeroes occured 7 times
7 zeroes occured 1 times
Press any key to continue . . .
*/