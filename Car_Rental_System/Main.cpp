#include<iostream>
#include<vector>
#include<string>
#include <iostream>
#include <stdio.h>
#include <fstream> 
#include <sstream> 
#include <stdlib.h>
#include <cstdio>
using namespace std;


/****************************************************HELPER FUNCTION*********************************************************/

bool is_number(const string &s) {
    // Check if the string is empty
    if (s.empty()) {
        return false;
    }
    // Check each character in the string
    for (char c : s) {
        if (!isdigit(c)) {
            return false; // If any character is not a digit, return false
        }
    }
    return true; // If all characters are digits, return true
}


string take_date(){
    string s3;
    cout<<"Enter the year(a 4-digit number):\n";
    cin>>s3;
    if(!is_number(s3) || !(stoi(s3)>0 && stoi(s3)<=9999)){
        cout<<"This year is not valid.\n";
        return take_date();
    }

    string s2;
    cout<<"Enter a month(between 1 to 12):\n";
    cin>>s2;
    if(!is_number(s2) || !(stoi(s2)>0 && stoi(s2)<13)){
        cout<<"This month is not valid.\n";
        return take_date();
    }
    string s1;
    cout<<"Enter the day(between 1 to 31):\n";
    cin>>s1;
    if( !is_number(s1) ){
        cout<<"This day is not valid.\n";
        return take_date();
    }
    else {
        if((stoi(s2)==2 && !(stoi(s1)>0 && stoi(s1)<30)) || (!((stoi(s3) % 100 != 0) && (stoi(s3) % 4 == 0)) && stoi(s1)==29)){
            cout<<"This day is not valid.\n";
            return take_date();
        }
        else if((stoi(s2)==4 || stoi(s2)==6 || stoi(s2)==9 || stoi(s2)==11) && !(stoi(s1)>0 && stoi(s1)<31)){
            cout<<"This day is not valid.\n";
            return take_date();
        }
        else if((stoi(s2)==1 || stoi(s2)==3 || stoi(s2)==5 || stoi(s2)==7 || stoi(s2)==8 || stoi(s2)==10 || stoi(s2)==12) && !(stoi(s1)>0 && stoi(s1)<32)){
            cout<<"This day is not valid.\n";
            return take_date();
        }
    }
    string date=(s3)+"-"+(s2)+"-"+(s1);
    return date;        
}



int get_number_of_records(const string& filename) {
    ifstream file(filename);
    string line;
    int count = 0;

    while (getline(file, line)) {
        count++;
    }

    file.close();
    return count;
}


void update_record(const string& filename, const string& record_id, const string& new_data) {
    fstream file(filename, ios::in | ios::out);
    string line;

    if (!file){
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    file.seekg(0, ios::beg);

    ofstream temp("temp.csv");

    while (getline(file, line)){
        stringstream ss(line);
        vector<string> data;
        string item;
        while (getline(ss, item, ',')) {
            data.push_back(item);
        }

        if (!data.empty() && data[0] == record_id) {
            temp << new_data << endl;
        } else {
            for (size_t i = 0; i < data.size(); ++i){
                temp << data[i];
                if (i != data.size() - 1) {
                    temp << ",";
                }
            }
            temp << endl;
        }
    }

    file.close();
    temp.close();

    // Remove the original file
    remove(filename.c_str());

    // Rename the temporary file to the original filename
    rename("temp.csv", filename.c_str());
}



int daysBetweenDates(string date1, string date2)
{
	stringstream ss(date1 + "-" + date2);
	int year, month, day;
	char hyphen;

	// Parse the first date into seconds
	ss >> year >> hyphen >> month >> hyphen >> day;
	struct tm starttm = { 0, 0, 0, day,
						month - 1, year - 1900 };
	time_t start = mktime(&starttm);

	// Parse the second date into seconds
	ss >> hyphen >> year >> hyphen
		>> month >> hyphen >> day;
	struct tm endtm = { 0, 0, 0, day,
						month - 1, year - 1900 };
	time_t end = mktime(&endtm);

	// Find out the difference and divide it
	// by 86400 to get the number of days
	return (end - start) / 86400;
}

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


/****************************************************************USER CLASS*****************************************************************/

class user{
    public:
        int Id;
        string Name={};
        string password={};
        string mobile={};
        int Fine_Due;
        int record;
        void Available_cars();
        void Rented_Cars(int role);
        void Pay_dues(int role);
        void Return_Car(int role);
        void book_car(int role);
        void Profile(int role);
        void Update_Profile(int role);
};


void user::Update_Profile(int role){
    string filename;
    if(role==1) filename="Customer.csv";
    else filename="Employee.csv";

    cout<<"What do you want to update?\n1.Name\t\t2.Password\t\t3.Mobile No\n";
    string b;
    cin>>b;
    string new_data;
    if(b=="1"){
        cout<<"Enter you new Name:\n";
        string name;
        cin>>name;
        new_data=to_string(Id)+","+name+","+password+","+to_string(Fine_Due)+","+to_string(record)+","+mobile+",Existing";
        string old="Each_Cus_DBs/"+this->Name+".csv";
        string newname="Each_Cus_DBs/"+name+".csv";
        rename(old.c_str(),newname.c_str());
    }
    else if(b=="2"){
        cout<<"Enter you new password(minimum 4 letters):\n";
        string pass;
        cin>>pass;
        if(pass.size()<4){
            cout<<"Your password is less than 4 letters.\n";
            return Update_Profile(1);
        }
        new_data=to_string(Id)+","+Name+","+pass+","+to_string(Fine_Due)+","+to_string(record)+","+mobile+",Existing";
    }
    else if(b=="3"){
        cout<<"Enter you new mobile number(of 10 digits):\n";
        string pass;
        cin>>pass;
        if(is_number(pass)==0 || pass.size()!=10){
            cout<<"Invalid mobile number.\n";
            return Update_Profile(1);
        }
        new_data=to_string(Id)+","+Name+","+password+","+to_string(Fine_Due)+","+to_string(record)+","+pass+",Existing";
    }
    else {
        cout<<"Not a valid option.\n";
        return Update_Profile(1);
    }
    update_record(filename,to_string(Id),new_data);
    cout<<"Your profile is updated :))\n";
    cout<<"-----------------------------------------------------------------\n";
}

void user::Available_cars(){
    cout<<"------------------------AVAILABLE CARS-------------------------\n\n";
    ifstream file("cars.csv"); // Open the CSV file
    if (!file.is_open()) {
    cerr << "Error: Unable to open file." << endl;
    return ;
    }
    string line;
    while (getline(file, line)) {
        vector<string> parts = split(line, ','); 
        if(parts[5]=="In_Use")
        {
            cout<<"Id: "<<parts[0]<<"\nModel Name: "<<parts[1]<<"\nCondition: "<<parts[2]<<"\nRental Price per day: "<<parts[4];
            if(parts[3]=="NA") cout<<"\nAvailability: Yes";
            else cout<<"\nAvailability: No";
            cout << "\n\n\t\t\t*********\t\t\t\n";
        }
    }
    file.close();
    cout<<"-----------------------------------------------------------------\n";
}


void user::Pay_dues(int role){
    cout<<"------------------------PAY DUES-------------------------\n\n";
    if(Fine_Due==0){
        cout<<"You don't have dues :)\n";
        return;
    }
    cout<<"Your current dues are Rs."<<Fine_Due<<"\n";
    cout<<"Enter the amount you want to clear:\n";
    string sum;
    cin>>sum;
    if(is_number(sum)==0 || stoi(sum)<0) {
        cout<<"Not a valid number.\n";
        return Pay_dues(role);
    }
    if(stoi(sum)!=0) cout<<"Thank you for paying.\n";
    if(stoi(sum)>=Fine_Due) cout<<"You have no dues left.\n";
    else cout<<"You still have Rs."<<Fine_Due-stoi(sum)<<" as our fine dues.\n";
    Fine_Due=Fine_Due-stoi(sum);
    string data=to_string(this->Id)+","+this->Name+","+this->password+","+to_string(Fine_Due)+","+to_string(record)+","+mobile+",Existing";
    string filename;
    if(role==1) filename="Customer.csv";
    else filename="Employee.csv";
    update_record(filename,to_string(Id),data);
    cout<<"----------------------------------------------------------------\n";
}


void user::Rented_Cars(int role){
    cout<<"------------------------RENTED CARS-------------------------\n\n";
    string filename;
    if(role==1) filename="Each_Cus_DBs/"+this->Name+".csv";
    else filename="Each_Emp_DBs/"+this->Name+".csv";
    ifstream file(filename); 
    if (!file.is_open()) {
    cerr << "You have not rented any cars yet." << endl;
    return ;
    }

    string line;
    while (getline(file, line)) {
    vector<string> parts = split(line, ','); 
    cout<<"Id: "<<parts[0]<<"\nModel Name: "<<parts[1]<<"\nCondition: "<<parts[2]<<"\nStart Date: "<<parts[3]<<"\nEnd Date: "<<parts[4]<<"\nRental Price per day: "<<parts[5]<<"\nStatus: "<<parts[6];
    cout << "\n\n\t\t\t*********\t\t\t\n";
    cout << endl;
    }
    file.close();
    cout<<"------------------------------------------------------------------\n";
}



void user::Return_Car(int role){
    cout<<"------------------------RETURN CAR-------------------------\n\n";
    cout<<"Enter the car Id:\n";
    string id;
    cin>>id;
    if(is_number(id)==0) {
        cout<<"The Id should consist of only numbers.\n";
        return Return_Car(role);
    }
    int ret_id=stoi(id);
    cout<<"Enter the following details of today's date\n";
    string s1;
    s1=take_date();

    cout<<"What is the condition of car currently?"<<endl;
    cout<<"1.Good\t\t\t2.Damaged"<<endl;
    string s;
    cin>>s;
    if(s!="1" && s!="2") {
        cout<<"Not a valid option.\n";
        return Return_Car(role);
    }
    string filename;
    if(role==1) filename="Each_Cus_DBs/"+this->Name+".csv";
    else filename="Each_Emp_DBs/"+this->Name+".csv";
    ifstream file(filename);
    if (!file.is_open()) {
    cerr << "Error: You have not rented any car yet." << endl;
    return;
    }
    int flag=0;
    string line;
    while (getline(file, line)) {
        vector<string> parts = split(line, ','); 
        if (stoi(parts[0]) ==  ret_id && parts[6].compare("Rented")==0){
            if(daysBetweenDates(parts[3],s1)<0){
                cout<<"You entered a date of a day before you rented the car.\n";
                return Return_Car(role);
            }
            if(daysBetweenDates(parts[4],s1)>0 ){
                int fine = daysBetweenDates(parts[4],s1)*(stoi(parts[5])*1.5) ;
                cout<<"You are returning the car after the due date and this leads to a fine of Rs."<<fine<<".\n";
                record -= 1;
                Fine_Due +=fine;
            }
            int con;
            if(parts[2].compare("Good")==0) con=1;
            else con=2;
            if(stoi(s)-con!=0){
                if(stoi(s)==2){
                    cout<<"As you have caused damage to the car. You will be fined Rs.5000.\n";
                    Fine_Due+=5000;
                    record -=2;
                    parts[2]="Damaged";
                }
                else {
                    cout<<"Thank you for improving the car's condition:)))\n";
                    record +=2;
                    parts[2]="Good";
                }
            }
            string new_data = parts[0]+","+parts[1]+","+parts[2]+","+parts[3]+","+parts[4]+","+parts[5]+",Returned";
            file.close();
            string filename;
            if(role==1) filename="Each_Cus_DBs/"+this->Name+".csv";
            else filename="Each_Emp_DBs/"+this->Name+".csv";
            flag=1;
            cout<<"You successfully returned the car."<<endl;
            update_record(filename,parts[0],new_data);
            string fname="cars.csv";
            string car=parts[0]+","+parts[1]+","+parts[2]+",NA,"+parts[5]+",In_Use";
            update_record(fname,parts[0],car);
            string f1name;
            if(role==1)  f1name="Customer.csv";
            else f1name="Employee.csv";
            string data=to_string(this->Id)+","+this->Name+","+this->password+","+to_string(Fine_Due)+","+to_string(record)+","+mobile+",Existing";
            update_record(f1name,to_string(this->Id),data);
            break;
        }
        if(flag==0) cout<<"You have not rented any car with this id.\n";
    }
    cout<<"-----------------------------------------------------------------------\n";
}

void user::Profile(int role){
    cout<<"\n\n----------------------------------YOUR PROFILE-----------------------------------\n";
    string filename;
    if(role==1) filename="Customer.csv";
    else filename = "Employee.csv";
    ifstream file(filename);
    if (!file.is_open()) {
    cerr << "This profile doesn't exist." << endl;
    return ;
    }

    string line;
    while (getline(file, line)) {
        vector<string> parts = split(line, ','); 
        if(parts[0]==to_string(this->Id)){
            cout<<"Id: "<<Id<<endl;
            cout<<"Name: "<<Name<<endl;
            cout<<"password: "<<password<<endl;
            cout<<"Mobile No: "<<mobile<<endl;
            cout<<"Fine Due: "<<Fine_Due<<endl;
            cout<<"Your record: "<<record<<endl;
        }
    }
    file.close();
    cout<<"\n------------------------------------------------------------------------\n";
}

void user::book_car(int role)
{
    cout<<"\n\n------------------------RENT A CAR-------------------------\n\n";
    cout<<"Do you want to see the list of available cars?\n1.Yes\t\t\t2.No\t\t\t3.Exit\n";
    string a;
    cin>>a;
    if(a=="1") Available_cars();
    else if(a=="3"){
        return;
    }
    else if(a!="2") {
        cout<<"Not a valid option.\n";
        return book_car(role);
    }
    cout<<"Enter the car id you want to rent\n";
    string s;
    cin>>s;
    if(!is_number(s)){
        cout<<"The Id should be consist of numbers only.\n";
        return book_car(role);
    }
    cout<<"Enter the following details of today's date i.e., the start date\n";
    string s1;
    s1=take_date();
    cout<<"Enter the following details of end date\n";
    string s2;
    s2=take_date();
    if(daysBetweenDates(s1,s2)<0){
        cout<<"Your dates are not correct!\n";
        return book_car(role);
    }
    else if(daysBetweenDates(s1,s2)>15){
        cout<<"Sorry, we don't allow renting cars for more than 15 days :(((\n";
        return ;
    }

    ifstream file("cars.csv");
    if (!file.is_open()) {
    cerr << "Error: Unable to open file." << endl;
    return;
    }

    string line;
    int flag=0;
    string change ;
    string new_data;
    string id,price,cond;
    while (getline(file, line)) {
        vector<string> parts = split(line, ','); 
        
        if(parts[0].compare(s)==0){
            if (parts[3].compare("NA") == 0 && parts[5]!="Deleted") {
                id=parts[0];
                price=parts[4];
                cond=parts[2];
                cout << "\nCar is Available." << endl;
                cout<<"It has a per day rental price of Rs."<<parts[4]<<"."<<endl;
                vector<string> sdate=split(s1,'-');
                vector<string> edate=split(s2,'-');
                cout<<"The total cost for these days will be Rs."<<stoi(parts[4])*(daysBetweenDates(s1,s2)+1)<<".\n";
                if(role==2) cout<<"Being a part of our company,you get a discount of 15%. The discounted price for you will be Rs."<<0.85*(float)(stoi(parts[4])*(daysBetweenDates(s1,s2)+1))<<endl;
                cout<<"The car is in "<<parts[2]<<" state."<<endl;
                cout<<"\nChoose one of the two options\n";
                cout<<"1.You want to rent the car and are ready to pay the amount now.\n";
                cout<<"2.You don't want to rent the car.\n";
                int cfm;
                cin>>cfm;
                if(cfm!=1 && cfm!=2) {
                    cout<<"Not a valid option.\n";
                    return book_car(role);
                }
                if(cfm==1){
                    if(record>0){
                    flag=1;
                    new_data = parts[0]+","+parts[1]+","+parts[2]+","+s2+","+parts[4]+",In_Use"+","+this->Name;
                    change=parts[0];
                    fstream file;
                    string fname;
                    if(role==1) fname="Each_Cus_DBs/"+this->Name+".csv";
                    else fname="Each_Emp_DBs/"+this->Name+".csv";
                    file.open(fname, ios::out | ios::app);
                    file <<parts[0]<<","<< parts[1] << ","<<parts[2] <<","<<s1<<","<<s2<<","<<stoi(parts[4])<<","<<"Rented"<<"\n";
                    file.close();
                    }
                    else{
                        flag=2;
                        cout<<"Sorry....you don't have a good record enough to rent a car :(((\n";
                    }
                }
                else{
                    flag=2;
                    cout<<"\n-----------------Thank you!!------------------";
                }
                break;
            }
        }  
    }
    file.close();
    if(flag==0) cout<<"This car is not available :(\n";
    else if(flag==1) {
        string filename="cars.csv";
        cout<<"You successfully rented the car :)\nBelow is the invoice."<<endl;
        cout<<"\n\n----------------------ABW's CAR RENTAL SYSTEM-------------------------\n\n";
        cout<<"You rented the following car.\n";
        cout<<"Car Model   \t\t\t"<<s<<"\n";
        cout<<"Car Id       \t\t\t"<<id<<"\n";
        cout<<"Rental Price\t\t\tRs."<<price<<"\n";
        cout<<"Start Date  \t\t\t"<<s1<<"\n";
        cout<<"End Date    \t\t\t"<<s2<<"\n";
        cout<<"Total Price  \t\t\tRs."<<(daysBetweenDates(s1,s2)+1)*stoi(price)<<"\n\n";
        cout<<"Please remember this car id. It will be required while returning the car.\n";
        update_record(filename,change,new_data);
    }
    cout<<"------------------------------------------------------------------------\n";
}


/******************************************************************CUSTOMER CLASS********************************************************************/


class customer:public user{
    public:
    void Display_Menu()
    {
        if(this->Fine_Due>50000) {
            cout<<"Sorry...your fine due exceeds the upper bound we had set. So, you need to pay the dues to avail our facilities.\n";
            cout<<"Choose one of the following options:\n1.Pay dues\t\t\t2.Exit\n";
            string a;
            cin>>a;
            if(a=="1") Pay_dues(1);
            else if(a=="2") return ;
            else {
                cout<<"Not a valid option.\n";
                return Display_Menu();
            }
        }
        else{
        cout<<"Please choose one of the below option number."<<endl;
        cout<<"1.Show the list of available cars."<<endl;
        cout<<"2.Show the list of rented cars."<<endl;
        cout<<"3.Rent a Car."<<endl;
        cout<<"4.Return a rented car."<<endl;
        cout<<"5.Pay dues."<<endl;
        cout<<"6.Show Profile."<<endl;
        cout<<"7.Update Profile."<<endl;
        cout<<"8.Logout."<<endl;
        string s;
        cin>>s;
        if(!is_number(s)){
            cout<<"It should be a number.\n";
            return Display_Menu();
        }
        int a = stoi(s);
        switch(a){
            case 1:
                Available_cars();
                break;
            case 2:
                Rented_Cars(1);
                break;
            case 3:
                book_car(1);
                break;
            case 4:
                Return_Car(1);
                break;
            case 5:
                Pay_dues(1);
                break;
            case 6:
                Profile(1);
                break;
            case 7:
                Update_Profile(1);
                break;
            case 8:
                cout<<"You are successfully logged out.\n";
                return;
            default:
                cout<<"Not a valid option.\n";
        }
        cout<<"Do you want to exit from the application?\n1.Yes\t\t\t2.No\n";
        string a1;
        cin>>a1;
        if(a1=="1"){
            cout<<"Thank you for using our services !!\n";
            return ;
        }
        else if(a1=="2"){
            system("cls");
            Display_Menu();
        }
        else {
            cout<<"Not a valid option.\n";
            Display_Menu();
        }
        }
    }

};



/**************************************************************EMPLOYEE CLASS*****************************************************************/


class employ:public user{
    public:
        void Display_Menu()
        {
            cout<<"Please choose one of the below option number."<<endl;
            cout<<"1.Show the list of available cars."<<endl;
            cout<<"2.Show the list of rented cars."<<endl;
            cout<<"3.Rent a Car."<<endl;
            cout<<"4.Return a rented car."<<endl;
            cout<<"5.Pay dues."<<endl;
            cout<<"6.Show Profile."<<endl;
            cout<<"7.Update my profile."<<endl;
            cout<<"8.Logout."<<endl;
            string s;
            cin>>s;
            if(!is_number(s)){
                cout<<"It should be a number.\n";
                return Display_Menu();
            }
            int a = stoi(s);
            switch(a){
                case 1:
                    Available_cars();
                    break;
                case 2:
                    Rented_Cars(2);
                    break;
                case 3:
                    book_car(2);
                    break;
                case 4:
                    Return_Car(2);
                    break;
                case 5:
                    Pay_dues(2);
                    break;
                case 6:
                    Profile(2);
                    break;
                case 7:
                    Update_Profile(2);
                    break;
                case 8:
                    cout<<"You are successfully logged out.\n";
                    return;
                default:
                    cout<<"Not a valid option.\n";
            }
            cout<<"Do you want to exit from the application?\n1.Yes\t\t\t2.No\n";
            string a1;
            cin>>a1;
            if(a1=="1"){
                cout<<"Thank you for using our services !!\n";
                return ;
            }
            else if(a1=="2"){
                system("cls");
                Display_Menu();
            }
            else {
                cout<<"Not a valid option.\n";
                Display_Menu();
            }
        }


        
};


/******************************************************************MANAGER CLASS*****************************************************************/


class manager{
public:
    int Id;
    string Name;
    string password;
    string mobile;
    void Add(){
        cout<<"\n\n---------------------------------------ADD------------------------------\n";
        cout<<"What do you want to add?\n1.Car\t\t2.Customer\t\t3.Employee\n";
        string a;
        cin>>a;
        string filename;
        if(a=="1"){
            filename="cars.csv";
            fstream file;
            string model,condition,price;
            cout<<"Enter the model name of the car:\n";
            cin>>model;
            cout<<"Enter the current condition of the car:\n1.Good\t\t\t\t2.Damaged\n";
            string a1;
            cin>>a1;
            if(a1=="1") condition="Good";
            else if(a1=="2") condition="Damaged";
            else {cout<<"Not a valid option\n";return Add();}
            cout<<"Enter the per day rental price of the car:\n";
            cin>>price;
            if(is_number(price)==0 || stoi(price)<=0){
                cout<<"Not a valid number.\n";
                return Add();
            }
            file.open(filename,ios::out | ios::app);
            int Id=get_number_of_records(filename);
            file<<Id<<","<< model << ","<<condition <<","<<"NA"<<","<<price<<",In_Use"<<"\n";
            file.close();
            cout<<"This car is added to the system!!"<<endl;
        }
        else if(a=="2" ||a=="3"){
            if(a=="2") filename="Customer.csv";
            else filename="Employee.csv";
            fstream file;
            string name,password,mobile;
            cout<<"Enter the name of the person:\n";
            cin>>name;
            cout<<"Enter a password for him(min 4 letters and should consist of a single word):\n";
            cin>>password;
            if(password.size()<4){
                cout<<"Length is less than 4."<<endl;
                return Add();
            }
            cout<<"Enter his mobile number: \n";
            cin>>mobile; 
            if(!is_number(mobile) || mobile.size()!=10){
                cout<<"Not a valid number\n";
                return Add();
            }
            file.open(filename,ios::out | ios::app);
            int Id=get_number_of_records(filename);
            file<<Id<<","<<name << ","<<password<<","<<"0"<<",10,"<<mobile<<",Existing\n";
            file.close();
            cout<<"This person is added to the system!!"<<endl;
        }
        else cout<<"Not a valid option.\n";
        cout<<"-----------------------------------------------------------------\n";
    }

    void Delete(){
        cout<<"\n\n---------------------------------------DELETE------------------------------\n";
        cout<<"What do you want to delete?\n1.Car\t\t2.Customer\t\t3.Employee\n";
        string a;
        cin>>a;
        string filename;
        int flag=0;
        if(a=="1"){
            filename="cars.csv";
            cout<<"Enter the car Id which you want to delete:\n";
            string id;
            cin>>id;
            if(is_number(id)==0){
                cout<<"The id should consist of only numbers.\n";
                return Update();
            }
            ifstream file(filename); 
            if (!file.is_open()) {
            cerr << "Error: Something is wrong. Please try again." << endl;
            return Delete();
            }
            string line;
            vector<string> parts;
            while (getline(file, line)) {
                parts = split(line, ','); 
                if(parts[0]==id && parts[3]=="NA" && parts[5]=="In_Use"){
                    flag=1;
                    break;
                }
            }
            file.close();
            if(flag==0) {
                cout<<"Either you entered an invalid id number or this car is rented by someone.\n";
                return Delete();
            }
            string data= parts[0]+","+parts[1]+","+parts[2]+","+parts[3]+","+parts[4]+",Deleted";
            update_record(filename,id,data);
            cout<<"This car is deleted!!!\n";
        }
        else if(a=="2" ||a=="3"){
            if(a=="2") filename="Customer.csv";
            else filename="Employee.csv";
            cout<<"Enter the person Id whom you want to delete:\n";
            string id;
            cin>>id;
            if(is_number(id)==0){
                cout<<"The id should consist of all numbers.\n";
                return Delete();
            }
            ifstream file(filename); // Open the CSV file
            if (!file.is_open()) {
                cerr << "Error: Something is wrong. Please try again." << endl;
                return Delete();
            }
            string line;
            vector<string> parts;
            while (getline(file, line)) {
                parts = split(line, ','); 
                if(parts[0]==id && parts[6]=="Existing"){
                    cout<<"You are trying to delete "<<parts[1]<<". He has fine dues of Rs."<<parts[3]<<"\n";
                    cout<<"Are you sure you want to delete him?\n1.Yes\t\t\t2.No\n";
                    string b;
                    cin>>b;
                    if(b=="1") {
                        flag=1;
                    }
                    else if(b=="2") cout<<"------------------------Thank you!----------------------\n";
                    else cout<<"Not a valid option.\n";
                    break;
                }
            }
            file.close();
            if(flag==1){
                string data= parts[0]+","+parts[1]+","+parts[2]+","+parts[3]+","+parts[4]+","+parts[5]+",Deleted";
                update_record(filename,id,data);
                cout<<"This person is deleted!!!\n";
            }
        }
        else {cout<<"Not a valid option.\n";return Delete();}
        if(flag==0 && stoi(a)<=3 && stoi(a)>=1){
            cout<<"Invalid Id\n";
        }
        cout<<"--------------------------------------------------------------------------\n";
    }


    void Update(){
        cout<<"\n\n---------------------------------------UPDATE------------------------------\n";
        cout<<"What do you want to update?\n1.Car\t\t2.Customer\t\t3.Employee\n";
        string a;
        cin>>a;
        string filename;
        int flag=0;
        if(a=="1"){
            cout<<"Enter the id of the car you want to update:\n";
            string s;
            cin>>s;
            if(is_number(s)==0){
                cout<<"The id should consist of only numbers.\n";
                return Update();
            }
            filename="cars.csv";
            ifstream file(filename); // Open the CSV file
            if (!file.is_open()) {
            cerr << "Error: Something is wrong. Please try again." << endl;
            return Update();
            }
            string line;
            vector<string> parts;
            while (getline(file, line)) {
                parts = split(line, ','); 
                if(parts[0]==s && parts[5]=="In_Use" && parts[3]=="NA"){
                    cout<<"You are updating a car of model "<<parts[1]<<"."<<endl;
                    flag=1;
                    break;
                }
                else if(parts[0]==s && parts[5]=="In_Use" ){
                    cout<<"This car is currently rented. You can only update attributes of cars that are not rented.\n";
                    return Update();
                }
            }
            file.close();
            if(flag==0) {cout<<"You entered an invalid car id.\n";return Update();}
            cout<<"Which attribute of the car do you want to update?\n1.Model\t\t2.Condition\t\t3.Rental price per day\n";
            string b;
            cin>>b;
            int change=0;
            if(b=="1") {
                cout<<"Enter the new model name for this car.\n";
                string s1;
                cin>>s1;
                change=1;
                parts[1]=s1;
            }
            else if(b=="2"){
                cout<<"Enter the new condition of this car.\n1.Good\t\t\t2.Damaged\n";
                string s1;
                cin>>s1;
                if(s1=="1") {parts[2]="Good";change=1;}
                else if(s1=="2") {parts[2]="Damaged";change=1;}
                else {cout<<"Not a valid option.\n";return Update();}
            }
            else if(b=="3"){
                cout<<"Enter the new rental price per day for this car.\n";
                string s1;
                cin>>s1;
                change=1;
                parts[4]=s1;
            }
            else {cout<<"Not a valid option.\n";return Update();}
            if(change==1){
                flag=2;
                string new_data=s+","+parts[1]+","+parts[2]+","+parts[3]+","+parts[4]+","+parts[5];
                update_record(filename,s,new_data);
            }
        }
        else if(a=="2" || a=="3"){
            if(a=="2") filename="Customer.csv";
            else filename="Employee.csv";
            cout<<"Enter the id of the person whose data you want to update:\n";
            string s;
            cin>>s;
            if(is_number(s)==0){
                cout<<"The id should consist of only numbers.\n";
                return Update();
            }
            ifstream file(filename); // Open the CSV file
            if (!file.is_open()) {
            cerr << "Error: Unable to open file." << endl;
            return ;
            }
            string line;
            vector<string> parts;
            while (getline(file, line)) {
                parts = split(line, ',');
                if(parts[0]==s && parts[6]=="Existing"){
                    cout<<"You are updating the data of "<<parts[1]<<"."<<endl;
                    flag=1;
                    break;
                }
            }
            file.close();
            if(flag==0) {cout<<"You entered an invalid id number.\n";return Update();}
            cout<<"Which attribute of "<<parts[1]<<" do you want to update?\n1.Fine_Due\t2.Record\n";
            string b;
            cin>>b;
            int change=0;
            if(b=="1") {
                cout<<"Enter the new fine dues for this person.\n";
                string s1;
                cin>>s1;
                if(is_number(s1)==0 || stoi(s1)<0){
                    cout<<"The fine due should consist of only positive numbers.\n";
                    return Update();
                }
                else if(stoi(s1)>50000){
                    cout<<"The fine dues cannot exceed Rs.50000.\n";
                    return Update();
                }
                change=1;
                parts[3]=s1;
            }
            else if(b=="2"){
                cout<<"Enter the new record number for this person.\n";
                string s1;
                cin>>s1;
                if(is_number(s)==0){
                    cout<<"The record should consist of only numbers.\n";
                    return Update();
                }
                else if(stoi(s1)<0){
                    cout<<"Record can't be negative.\n";
                    return Update();
                }
                else if(stoi(s1)<10){
                    cout<<"You cannot set the record greater than 20.\n";
                    return Update();
                }
                change=1;
                parts[4]=s1;
            }
            else {cout<<"Not a valid option.\n";return Update();}
            if(change==1){
                flag=2;
                string new_data=s+","+parts[1]+","+parts[2]+","+parts[3]+","+parts[4]+","+parts[5]+",Existing";
                update_record(filename,s,new_data);
            }
        }
        else {cout<<"Not a valid option.\n";return Update();}
        if(flag==2) cout<<"You have successfully updated the data.\n";
        cout<<"-----------------------------------------------------------\n";
    }



    void Available_Cars(){
        cout<<"\n\n------------------------AVAILABLE CARS-------------------------\n\n";
        ifstream file("cars.csv"); // Open the CSV file
        if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return ;
        }

        string line;
        while (getline(file, line)){
            vector<string> parts = split(line, ','); 
            if(parts[5]=="In_Use")
            {
                cout<<"Id: "<<parts[0]<<"\nModel: "<<parts[1]<<"\nPresent Condition: "<<parts[2]<<"\nRental price for a day: "<<parts[4];
                if(parts[3]!="NA"){
                    cout<<"\nAvailability: No\nRented By: "<<parts[6]<<endl;
                }
                else cout<<"\nAvailability: Yes.\n";
                cout<<"\t\t\t***********\t\t\t\n";
            }
        }
        file.close();
        cout<<"\n\n-----------------------------------------------------------------\n";

    }


    void Current_Data(int role){
        string filename;
        string name;
        if(role==1) {filename="Customer.csv";name="CUSTOMERS";}
        else {filename="Employee.csv";name="EMPLOYEES";}
        cout<<"\n\n------------------------CURRENT "<<name<<"-------------------------\n\n";

        ifstream file(filename); // Open the CSV file
        if (!file.is_open()) {
        cerr << "Error: No data available." << endl;
        return ;
        }
        if(get_number_of_records(filename)==0) {
            cout<<"You don't have any customer currently.\n";
            return;
        }
        string line;
        while (getline(file, line)){
            vector<string> parts = split(line, ','); 
            if(parts[6]=="Existing")
            {
                cout<<"Id: "<<parts[0]<<"  |  Name: "<<parts[1]<<"  |  password: "<<parts[2]<<"  |  Fine Due: "<<parts[3]<<"  |  Record: "<<parts[4]<<" | Mobile No: "<<parts[5]<<endl;
            }
        }
        file.close();
        cout<<"\n\n---------------------------------------------------------------------\n";
    }


    void Update_Profile(){
        cout<<"\n\n----------------------------------YOUR PROFILE-----------------------------------\n";
        string filename="Manager.csv";
        ifstream file(filename);
        if (!file.is_open()) {
        cerr << "This profile doesn't exist." << endl;
        return ;
        }

        string line;
        while (getline(file, line)) {
            vector<string> parts = split(line, ','); 
            if(parts[0]==to_string(this->Id)){
                cout<<"Id: "<<Id<<endl;
                cout<<"Name: "<<Name<<endl;
                cout<<"password: "<<password<<endl;
                cout<<"Mobile No: "<<mobile<<endl;
            }
        }
        file.close();

        cout<<"\n\nDo you want to update your profile?\n1.Yes\t\t\t2.No\n";
        string a;
        cin>>a;
        if(a=="1"){
            cout<<"What do you want to update?\n1.Name\t\t2.Password\t\t3.Mobile No.\n";
            string b;
            cin>>b;
            string new_data;
            if(b=="1"){
                cout<<"Enter you new Name.\n";
                string name;
                cin>>name;
                new_data=to_string(Id)+","+name+","+password+","+mobile;
            }
            else if(b=="2"){
                cout<<"Enter you new password(minimum 4 letters).\n";
                string pass;
                cin>>pass;
                if(pass.size()<4){
                    cout<<"Your password is less than 4 letters.\n";
                    return Update_Profile();
                }
                new_data=to_string(Id)+","+Name+","+pass+","+mobile;
            }
            else if(b=="3"){
                cout<<"Enter you new mobile number(of 10 digits).\n";
                string pass;
                cin>>pass;
                if(is_number(pass)==0 || pass.size()!=10){
                    cout<<"Invalid mobile number.\n";
                    return Update_Profile();
                }
                new_data=to_string(Id)+","+Name+","+password+","+pass;
            }
            else {
                cout<<"Not a valid option.\n";
                return Update_Profile();
            }
            update_record(filename,to_string(Id),new_data);
            cout<<"Your profile is updated :))\n";
        }
        else if(a!="2"){
            cout<<"Invalid option.\n";
            return Update_Profile();
        }
        cout<<"\n------------------------------------------------------------------------\n";
    }


    void Display_Menu(){
        cout<<"\n\nPlease choose one of the below option number."<<endl;
        cout<<"1.Show the list of available cars."<<endl;
        cout<<"2.Add a car/customer/employee."<<endl;
        cout<<"3.Delete a car/customer/employee."<<endl;
        cout<<"4.Update a car/customer/employee."<<endl;
        cout<<"5.Show the list of all customers.\n";
        cout<<"6.Show the list of all employees.\n";
        cout<<"7.Show/Update my profile.\n";
        cout<<"8.Logout."<<endl;
        string s;
        cin>>s;
        if(!is_number(s)){
            cout<<"Not a valid option.\n";
            Display_Menu();
        }
        int a=stoi(s);
        switch(a){
            case 1:
                Available_Cars();
                break;
            case 2:
                Add();
                break;
            case 3:
                Delete();
                break;
            case 4:
                Update();
                break;
            case 5:
                Current_Data(1);
                break;
            case 6:
                Current_Data(2);
                break;
            case 7:
                Update_Profile();
                break;
            case 8:
                cout<<"Thank you for using our services !!\n";
                cout<<"You are successfully logged out.\n";
                return;
            default:
                cout<<"Not a valid option.\n";
                Display_Menu();
        }
        cout<<"Do you want to exit from the application?\n1.Yes\t\t\t2.No\n";
        string s1;
        cin>>s1;
        if(!is_number(s1)){
            cout<<"Not a valid option.\n";
            return Display_Menu();
        }
        int a1= stoi(s1);
        if(a1==1){
            cout<<"Thank you for using our services !!\n";
            return ;
        }
        else if(a1==2){
            system("cls");
            Display_Menu();
        }
        else {
            cout<<"Not a valid option.\n";
            Display_Menu();
        } 
    }    
};


/***************************************************************LOGIN FUNCTION*****************************************************************/


void Login()
{
    int count=0;
    cout<<"\n\n------------------------LOGIN-------------------------\n\n";
    string new_name,new_password;
    string s;
    cout<<"Choose your role among the following:\n1.Customer\t\t2.Employee\t\t3.Manager\t\t4.Exit\n";
    cin>>s;
    if( !is_number(s) || stoi(s)>4){
        cout<<"Not a valid option.\n";
        return Login();
    }
    else if(stoi(s)==4){
        return;
    }

    int  a = stoi(s);
    cout<<"Enter your name:(First Name)"<<endl;
    cin>>new_name;

    cout<<"Enter your password:(single word)"<<endl;

    cin>>new_password;


    string filename ;
    if(a==1) 
    {
        filename="Customer.csv";
        customer New_Customer;
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            vector<string> parts = split(line, ','); 
            if (parts[1] ==new_name  && parts[2] == new_password && parts[6]=="Existing") {
                count=1;
                New_Customer.Name=parts[1];
                New_Customer.Id = stoi(parts[0]);
                New_Customer.password= parts[2];
                New_Customer.mobile=parts[5];
                New_Customer.Fine_Due=stoi(parts[3]);
                New_Customer.record=stoi(parts[4]);
                break;
            }
        }
        file.close();
        if(count==1) {
            system("cls");
            cout<<"------------------------------MENU----------------------------------\n\n";
            cout<<"Welcome "<<New_Customer.Name<<"......."<<endl;
            New_Customer.Display_Menu();
        }
    }
    else if(a==2) {
        filename="Employee.csv";
        employ New_Employee;
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            vector<string> parts = split(line, ','); 
            if (parts[1] ==new_name  && parts[2] == new_password && parts[6]=="Existing") {
                
                count=1;
                New_Employee.Name=parts[1];
                New_Employee.Id = stoi(parts[0]);
                New_Employee.password= parts[2];
                New_Employee.mobile=parts[5];
                New_Employee.Fine_Due=stoi(parts[3]);
                New_Employee.record=stoi(parts[4]);
                break;
            }
        }
        file.close();
        if(count==1) {
            system("cls");
            cout<<"------------------------------MENU----------------------------------\n\n";
            cout<<"Welcome "<<New_Employee.Name<<"......."<<endl;
            New_Employee.Display_Menu();
        }
    }
    else if(a==3) {
        filename="Manager.csv";
        manager New_manager;
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            vector<string> parts = split(line, ','); 
            if (parts[1] ==new_name  && parts[2] == new_password) {
                
                count=1;
                New_manager.Name=parts[1];
                New_manager.Id = stoi(parts[0]);
                New_manager.password= parts[2];
                New_manager.mobile=parts[3];
                break;
            }
        }
        file.close();
        if(count==1) {
            system("cls");
            cout<<"------------------------------MENU----------------------------------\n\n";
            cout<<"Welcome Sir......."<<endl;
            New_manager.Display_Menu();
        }
    }
    else if(a==4){
        return;
    }
    
    if(count==0 && a<=3 && a>=1) {cout<<"You entered wrong data!!"<<endl;return Login();}
    
}

/******************************************************** REGISTER FUNCTION ************************************************************************/


void Register()
{
    string Name,password;
    cout<<"\n\n------------------------REGISTER-------------------------\n\n";
    cout<<"Enter your name(First Name):"<<endl;
    cin>>Name;
    cout<<"Enter a password(of minimum 4 letters and should consists of single word):"<<endl;
    cin>>password;
    if(password.size()<4){
        cout<<"Length is less than 4."<<endl;
        return Register();
    }
    string mobile;
    cout<<"Enter your 10-digit mobile number:"<<endl;
    cin>>mobile;
    if(!is_number(mobile) || mobile.size()!=10){
        cout<<"Not a valid number\n";
        return Register();
    }
    else{
        string filename ;
        filename="Customer.csv";
        ifstream file(filename);
        int Id=get_number_of_records(filename);
        if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
        }
        int flag=0;
        string line;
        while(getline(file, line)){
            vector<string> parts = split(line, ',');
            if (parts[1]==Name) {
                flag=1;
                cout<<"This user name already exists. Try using a different one.\n";
                cout<<"3\n";
                break;
            }
        }
        file.close();
        if(flag==1) {
            return Register();
        }
        fstream ofile;
        ofile.open(filename,ios::out | ios::app);
        if(flag==0) {
            ofile<<Id<<","<< Name << ","<<password <<","<<"0"<<","<<"10,"<<mobile<<",Existing\n";
            cout<<"You are successfully registered!"<<endl;
        }
        ofile.close();
    }

}


/********************************************************MAIN FUNCTION****************************************************************/


int main()
{   
    cout<<"--------------------------------------------------------------------------------------------\n\n";
    cout<<"\t\t******** WELCOME TO ABW's CAR RENTAL SYSTEM ********\t\t\t\t\t\n\n";
    cout<<"--------------------------------------------------------------------------------------------\n";
    cout<<"Choose one of the two options."<<endl;
    cout<<"1.Login \t 2.Register(Only if you are a new customer) \t 3.Exit"<<endl;
    string a;
    cin>>a;
    if(a=="1"){
        Login();
        return main();
    }
    else if(a=="2"){
        Register();
        return main();
    }
    else if(a=="3") return 0;

    else {
        cout<<"Invalid option.\n";
        return main();
    }
    return 0;
}

