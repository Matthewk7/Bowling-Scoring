/* Matthew Kale, 5005997901, CS 135 - 1007, Assignment 9
 * Description: Program that scores bowling
 * Input: Input file name or bowling score
 * Output: Bowling Score
*/

/* Algorithm:
    1) Create program shell
    2) Main
        a) Loop Switch Statement with menu
        b) call functions in cases
    3) readPlayerRolls
        a) Read in from file and save to array
        b) Return true call generateScoresText
        c) Return false and exit
    4) getPlayerRolls
        a) Loop to read in Frame
        b) Loop to read in rolls
            *) Roll 1 - test for strike
            *) Roll 2 - test for spare
    5) generateScoresText
        a) Read in array
        b) Test all possible score outcomes
        c) Ouput Frame and Roll number
        d) Add score
        e) Loop until complete
        f) Write out as string
        g) ask to save in file
*/

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

bool readPlayerRolls (int[], int&, string filename);
void getPlayerRolls (int[], int&);
void generateScoreText(int[], int, string&);

int main(){

    char selection; 
    for (int i =0; i < 10000; i++){
    cout << "********************************" << endl;
    cout << "Welcome to Bedrock Bowling Alley" << endl;
    cout << "********************************" << endl;
    cout << "Menu Options" << endl;
    cout << "R/r Read roll data from file" << endl;
    cout << "M/m Manually enter data" << endl;
    cout << "Q/q Quit" << endl;
    cout << "Selection: ";

    cin >> selection;
    switch (selection){
        case 'R':
        case 'r':
        {
            int rollnum = 0;
            int rolls[21];
            string filename;
            string output;
            if (readPlayerRolls(rolls, rollnum, filename) == false){
                        
                break;
            }
            else{
                generateScoreText(rolls, rollnum, output); 
                break;
            } 
            break;
            
        }
        
        case 'M':
        case 'm':
        {
            int rollnum = 0;
            int rolls[21];
            string output;
            getPlayerRolls(rolls, rollnum);
            generateScoreText(rolls, rollnum, output); 

            break;
        }

        case 'Q':
        case 'q':
        {
            return 0;
        }
    }
    }
}

bool readPlayerRolls(int rolls[], int& rollnum, string filename)
{
    ifstream infile;
    cout << "Enter filename to read: ";
    cin >> filename;
    infile.open(filename);
    if(!infile.is_open() ){
        cout << "File read error \"" << filename << "\"" << endl;
        return false;
    }
    if(infile.is_open() ){   
        for (rollnum = 0; rollnum <= 21; rollnum++){
            infile >> rolls[rollnum];
            if (infile.eof() == true){
                break;
            }
        }
        cout << "Successfully read file \"" << filename << "\"" << " Roll Count: " << rollnum << endl;

    }
    return true;
}

void getPlayerRolls(int rolls[], int& rollnum){
    int i = 0;
    for (int frameNum = 1; frameNum <= 10; frameNum++){
        while (i <= 21){
            cout << "Frame # " << frameNum << endl;
            cout << "Roll #1 ";
            cin >> rolls[i];
            if (rolls[i] == -1){
                return;
            }            
            if (rolls[i] == 10){ 
                break;
            }
            i++;
            cout << "Roll #2 ";
            cin >> rolls[i];
            if (rolls[i] == -1){
                return;
            }
            i++;
            break;
        }
        rollnum = i;
        cout << endl;
    }
}

void generateScoreText(int rolls[], int rollnum, string& output)
{
    int i = 0;
    int score = 0;
    //Frame Number
    for (int frameNum = 1; frameNum <= 10; frameNum++){
        if (i == rollnum){
            break;
        }
        cout << "Frame #" << frameNum << endl;    
        //Roll Number
        while (i <= rollnum){
            cout << "-Roll #1 ";
            if (rolls[i] == 10 && rolls[i+1] == 10 && rolls[i+2] == 10 && frameNum == 10){
                score += (rolls[i]+rolls[i+1]+rolls[i+2]);
                cout << "-Score " << score << endl << endl;
                i++;
                break;
            }
            if (rolls[i] == 10 && i+2 == rollnum && frameNum != 10){
                cout << "Strike" << endl;
                score += (rolls[i]+rolls[i+1]);
                cout << "-Score " << score << endl << endl;
                i++;
                break;
            }    
            // Strike 2 10th frame incomplete
            if (frameNum == 10 && rolls[i] == 10 && rolls[i+1] == 10){
                cout << rolls[i] << endl;
                score += (rolls[i] + rolls[i+1]);
                cout << "-Score " << score << endl << endl;                
                cout << "-Game in Progress-" << endl;
                break;
            }
            // Strike 1 10th frame incomplete
            if (frameNum == 10 && rolls[i] == 10 && i+1 == rollnum){
                cout << rolls[i] << endl;
                score += (rolls[i]);
                cout << "-Score " << score << endl << endl;                
                cout << "-Game in Progress-" << endl;
                break;
            }
            //First Roll Strike previous frame spare
            if ((rolls[i-1] + rolls[i-2] == 10) && rolls[i] == 10){
                // First Roll Strike incomplete 2 later
                if (i+2== rollnum){
                    cout << "Strike" << endl;
                    score += (rolls[i]+rolls[i+1]);
                    cout << "-Score " << score << endl << endl;
                    i++;
                    break;
                    break;    
                }

                // Add up Strike with future               
                cout << "Strike" << endl;
                score += (rolls[i]+rolls[i+1]+rolls[i+2]);
                cout << "-Score " << score << endl << endl;
                i++;
                break;
                break;    
            }    
            // Normal Strike
            if (rolls[i] == 10){
                // Prevents 2nd roll next roll is last
                if (i+1== rollnum){
                    break;
                }     
                // Calculates Score           
                cout << "Strike" << endl;
                score += (rolls[i]+rolls[i+1]+rolls[i+2]);
                cout << "-Score " << score << endl << endl;
                i++;
                break;
                break;
            }
            // First Roll No Strike
            else {cout << rolls[i] << endl;}
            score += rolls[i];
            i++; 
            if (i == rollnum){
                cout << "-Score " << score << endl << endl;
                //Partial Bonus Normal
                if (i == rollnum){
                    cout << "-Game in Progress-" << endl;
                    break;
                }                
                break;
            }
            // Input file first roll is -1 
            if (rolls[i] == -1){
                cout << "-Game in Progress-" << endl;
                break;
            }
            // Roll #2
            // Check if game is in progress
            if(i-1 == rollnum){
                cout << "-Game in Progress-" << endl;
                break;
            }
            cout << "-Roll #2 ";
            // Spare
            if (rolls[i] + rolls[i-1] == 10){
                cout << "Spare" << endl;
                //Partial Bonus Spare

                if (frameNum == 10 && rollnum == i+1){
                    score += (rolls[i]);   
                    cout << "-Score " << score << endl << endl;
                    cout << "-Game in Progress-" << endl;
                    break;
                }
                // Adds to score
                score += (rolls[i]+rolls[i+1]);
                cout << "-Score " << score << endl << endl;
                i+=1;
                break;
                break;
            }
            // 2nd roll no spare
            else {
                cout << rolls[i] << endl;  
                score += rolls[i];
                cout << "-Score " << score << endl << endl;
                i+=1;
            }
            // Input file 2nd roll is -1
            if (rolls[i] == -1){
                cout << "-Game in Progress-" << endl;
                break;
            }

        break;           
        }
        
    }

    char choice;
    cout << "Save game to file (y/n)? ";
    cin >> choice;
    if (choice == 'y'){
        ofstream ofile;   
        string ofilename;     
        cout << "filename: ";
        cin >> ofilename;

        ofile.open(ofilename);
        if(ofile.is_open() ){   
        cout << "STILL NEED TO WRITE TO FILE" << endl;
        // ofile << str;
        ofile.close();
        return;
    }
    if (choice == 'n'){
        cout << endl << endl;
        return;    
    }
    }
}
