#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

void ExportFile(vector<string> id, vector<string> name, vector<int> scores){
    cout<<"Enter Name of newFile (without .csv extention) : ";
    string newFileName;
    cin>>newFileName;
    newFileName +=".csv";
    ofstream exportFile(newFileName);
    exportFile<<"ID,Name,Score\n";
    for(int i=0;i<id.size();i++){
        exportFile << id[i]<< ",";
        exportFile << name[i]<<",";
        exportFile << scores[i]<<"\n";
    }
    cout<<"Records have been exported to "<< newFileName <<endl;     
    
    }

bool findRecord(vector<string> id,vector<string> names, vector<int> scores, string searchID){
    cout<<"\n\n\n";
    for(int i=0; i<id.size(); i++){
        if(id[i]==searchID){
            cout<<"\n#ID    Name    Grade\n"<<id[i]<<" "<<names[i]<<" "<<scores[i]<<"\n\n\n";
            return true;
        }
    }
    cout<<"Record not found!"<<endl;
    return false;
}

void eraseRecord(vector<string> &id,vector<string> &names, vector<int> &scores, string searchID){
    for(int i=0; i<id.size(); i++){
        if(id[i]==searchID){
            id.erase(id.begin()+i);
            names.erase(names.begin()+i);
            scores.erase(scores.begin()+i);
        }
    }
}

bool copyID(vector<string> id, string newID){
    for(int i=0; i<id.size(); i++){
        if(id[i]==newID){
            return true;
        }
    }
    return false;
}
void showRecords(vector<string> id,vector<string> names, vector<int> scores){
    cout<<"\n\n\n#ID     Name     Score\n";
    for(int i=0; i<names.size(); i++){
        cout<<id[i]<<"  "<<names[i]<<"  "<<scores[i]<<endl;
    }
    cout<<"\n\n\n";
}

int main(){
    vector<string> names;
    vector<string> ID;
    vector<int> scores;
    ifstream file("students.csv");
    string line;
    //------------
    // Get Data From Input File and store in respective arrays
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name;
        int score;
        getline(ss, id, ',');
        getline(ss, name, ',');
        ss >> score;
        ID.push_back(id);
        names.push_back(name);
        scores.push_back(score);
    }
    //------------

    int input;
    string newID, newName, searchID;
    int newScore;
    ShowMenu:
    cout<<"Welcome to Student Record Manager!\n1. View All Records\n2. Search Records\n3. Add Record\n4. Update Record\n5. Delete Record\n6. Export Records\n7. Exit\nEnter your choice: ";
    cin>>input;//get input for which action to perform
    switch(input){

        /////////////
        //Show student records
        case 1:
            showRecords(ID,names, scores);
            break;
        /////////////



        ///////////////
        //Search record for a specific student
        case 2:
            cout<<"Enter Student ID: ";
            cin>>searchID;
            findRecord(ID,names,scores,searchID);
            break;
        ////////////



        ///////////////////////////////
        // Add a new record
        case 3:
            cout<<"Enter Student ID: ";
            cin>>newID;
            if(copyID(ID,newID)){///Check if ID already exists
                cout<<"ID already exists!"<<endl;
                break;
            }
            else{
                ID.push_back(newID);
            }
            cout<<"Enter Student Name: ";
            cin.ignore();
            getline(cin, newName);////get full Name
            //for examaple "john Doe" 
            cout<<"Enter Student Score: ";
            do{cin>>newScore;
                if(newScore<0 || newScore>100){
                    cout<<"Invalid Score! Please enter a score between 0 and 100: ";
                }
            }while(newScore<0 || newScore>100);
            names.push_back(newName);
            scores.push_back(newScore);
            cout<<"\n\nRecord added successfully!\n\n\n";
            break;
        ////////////////////////////
        //////
        


        ////////////////
        ////Update an existing record
        case 4:
            cout<<"Enter Student ID: ";
            cin>>searchID;
            if(findRecord(ID,names,scores,searchID)){
                cout<<"Enter new Student Name: ";
                cin.ignore();
                getline(cin, newName);//get full name
                cout<<"Enter new Student Score: ";
                do{cin>>newScore;///chech for invalid score input
                    if(newScore<0 || newScore>100){
                        cout<<"Invalid Score! Please enter a score between 0 and 100: ";
                    }
                }while(newScore<0 || newScore>100);
                for(int i=0; i<ID.size(); i++){
                    if(ID[i]==searchID){
                        names[i]=newName;
                        scores[i]=newScore;
                    }
                }
            }
            cout<<"\n\nRecord updated successfully!\n\n\n";
            break;
        //////////////////////////////



        /////////////////////////////////
        ///Delete a student record
        case 5:
            cout<<"Enter Student ID: ";
            cin>>searchID;
            if(findRecord(ID,names,scores,searchID)){
                eraseRecord(ID,names,scores,searchID);
            }
            break;
        ///////////



        /////////////////////////////
        ///export the records after all the actions are performed
        case 6:
            ExportFile(ID,names,scores);
            break;
        //////////////



        ///////////////
        case 7:
            return 0;
        default:
            break;
        ///////////////

    }
    goto ShowMenu;/////Show menu again
    return 0;
}