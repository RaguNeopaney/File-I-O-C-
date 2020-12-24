#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
//*******************************
// Name : Khoa Do               *           
// Name : Ragu Neopaney         *
// Name : Yeati Mishra          *
//******************************
// Structure to read into

struct TxtDetail
{
	string Text_Title=" ";
	string Author_Full_Name=" ";
	int Word_Count=0;
	double Latter_Frequency[26] = {0};
	int Line_Count = 0;
};

// Declaration of function Seperate_Name
void Seperate_Name(string, string&, string&);			
// Declaration of function Word_Count_Of_File
void Count_Of_File(fstream &, TxtDetail&);
// Declaration of function Letter_Frequency_of_File
void Letter_Frequency_of_File(string, TxtDetail&);
// Declaration of the print function
void Print_Data(TxtDetail&,string,string);
// Declaration of the print data
void Print_Data_Alphabet(TxtDetail& printing);

int main() {
	string User_Ans = "yes";
	string File_Name, File_Data, First_Name, Last_Name, Content_Text_Holder,Letter_frequency_response ;

	// Defining objects
	TxtDetail Text_Info;
	fstream Data_File;	

	while (User_Ans == "yes" || User_Ans == "Yes")
	{
		cout << "Enter the file name: ";
		cin >> File_Name;
		// Since we asked user to input file name, we will append .txt extension at the end of the file
		File_Name = File_Name + ".txt";						
			Data_File.open(File_Name, ios::in);										// tries to opens the file the first time
			if (Data_File.fail())						
			{
				// ************************************************
				// This loop will check the file opening error.   *
				// If file fails to open it will go through the   *
				// do while loop asking user to enter valid file  *
				// name until it successfully opens the file.     * 
				//*************************************************
				do 
				{
					cout << "The file you are trying to open failed" << endl;
					cout << "Enter the file name again: ";
					cin >> File_Name;
					File_Name = File_Name + ".txt";
					Data_File.open(File_Name, ios::in); 							//tries to open the file until it successfully doesn't open
				} while (Data_File.fail());

				// TODO: COPY THIS SECTION TO ELSE PART
				getline(Data_File, Text_Info.Text_Title);
				getline(Data_File, Text_Info.Author_Full_Name);
				Data_File >> Content_Text_Holder;
				Count_Of_File(Data_File,Text_Info);
				Data_File.close();
				Seperate_Name(Text_Info.Author_Full_Name, First_Name, Last_Name);
				cout << "Would you like to like to see the latter frequency? (yes or no)" << endl;
				cin >> Letter_frequency_response;
				if (Letter_frequency_response == "Yes" || Letter_frequency_response == "yes")
				{

					Letter_Frequency_of_File(File_Name, Text_Info);
					Print_Data_Alphabet(Text_Info);
					Print_Data(Text_Info, First_Name, Last_Name);
					cout << "Do you want to process another file? (yes or no)" << endl;
					cin >> User_Ans;
	
				} 
				else
				{
					continue;
					cout << "Do you want to process another file? (yes or no)" << endl;
					cin >> User_Ans;
				}

			} 
			else
			{
				getline(Data_File, Text_Info.Text_Title);
				getline(Data_File, Text_Info.Author_Full_Name);
				Data_File >> Content_Text_Holder;
				Count_Of_File(Data_File, Text_Info);
				Data_File.close();
				Seperate_Name(Text_Info.Author_Full_Name, First_Name, Last_Name);
				cout << "Would you like to like to see the latter frequency? (yes or no)" << endl;
				cin >> Letter_frequency_response;
				if (Letter_frequency_response == "Yes" || Letter_frequency_response == "yes")
				{

					Letter_Frequency_of_File(File_Name, Text_Info);
					Print_Data_Alphabet(Text_Info);
					Print_Data(Text_Info, First_Name, Last_Name);
					cout << "Do you want to process another file? (yes or no)" << endl;
					cin >> User_Ans;

				}
				else
				{
					continue;
					cout << "Do you want to process another file? (yes or no)" << endl;
					cin >> User_Ans;
				}

			}

	}
	return 0;
}
//***************************************************************
// Definition of the function Seperate_Name.                    *
// Accepts three arguments of string. one is the string         *
// name of the Author and other two will be used as a reference *
// give the split of author full name to first and last name.   *
//***************************************************************
void Seperate_Name(string Sep_Name, string &Author_First, string &Author_Last) 
{
	int Space_Location = Sep_Name.find(" ");
	Author_First = Sep_Name.substr(0, Space_Location);
	Author_Last = Sep_Name.substr(Space_Location, Sep_Name.length());
	
}

//********************************************************
// Definition of function Word_Count_Of_File.Accepts an  *
// fstream reference as its argument.Uses loop to        *
// read each content from the file.                      *
//********************************************************
void Count_Of_File(fstream &File_Word, TxtDetail &Word_Count)
{
	int count = 0, count2=0;
	string line, line2;
	while (File_Word >> line)
	{
		++count;
	}
	Word_Count.Word_Count = count;
	File_Word.clear();
	File_Word.seekg(0L, ios::beg);
	//************************************************
	// The three string are place holder for garbage *
	// that need to be ignored when counting         *
	// lines of the content. Since we cleared and    *
	// Seek back to the starting of the file we      *
	// need to ignore text title, author Name, and   *
	// a context line therefore 4 lines below does   *
	// that before start counting the lines.         *
	//************************************************
	string ignore1, ignore2, ignore3;
	getline(File_Word, ignore1);
	getline(File_Word, ignore2);
	File_Word >> ignore3;
	while (getline(File_Word, line2)) {
		count2++;
	}
	Word_Count.Line_Count = count2;

}
void Letter_Frequency_of_File(string Name_File2, TxtDetail& Data2) {
	fstream File_Open2;	
	vector <char> Data_Storage;
	char data;
	File_Open2.open(Name_File2, ios::in);
	//**************************************************
	// Next four lines ignores the first couple        *
	// of lines of the file since they contain         *
	// author name, File title and content text on     *
	// it. it will get them from the file and put them * 
	// in the ignore variable with will never be used. *
	//**************************************************
	string ignore3, ignore4, ignore5;
	getline(File_Open2, ignore3);
	getline(File_Open2, ignore4);
	File_Open2 >> ignore5;

	while (!File_Open2.eof())
	{
		File_Open2 >> data;
		Data_Storage.push_back(data);
	}
	File_Open2.close();
	for (unsigned int i = 0; i < Data_Storage.size(); i++)
	{
		if (Data_Storage.at(i) == 'a' || Data_Storage.at(i) == 'A') {Data2.Latter_Frequency[0]++; }
		else if (Data_Storage.at(i) == 'b' || Data_Storage.at(i) == 'B') {Data2.Latter_Frequency[1]++; }
		else if (Data_Storage.at(i) == 'c' || Data_Storage.at(i) == 'C') { Data2.Latter_Frequency[2]++; }
		else if (Data_Storage.at(i) == 'd' || Data_Storage.at(i) == 'D') { Data2.Latter_Frequency[3]++; }
		else if (Data_Storage.at(i) == 'e' || Data_Storage.at(i) == 'E') { Data2.Latter_Frequency[4]++; }
		else if (Data_Storage.at(i) == 'f' || Data_Storage.at(i) == 'F') { Data2.Latter_Frequency[5]++; }
		else if (Data_Storage.at(i) == 'g' || Data_Storage.at(i) == 'G') { Data2.Latter_Frequency[6]++; }
		else if (Data_Storage.at(i) == 'h' || Data_Storage.at(i) == 'H') { Data2.Latter_Frequency[7]++; }
		else if (Data_Storage.at(i) == 'i' || Data_Storage.at(i) == 'I') { Data2.Latter_Frequency[8]++; }
		else if (Data_Storage.at(i) == 'j' || Data_Storage.at(i) == 'J') { Data2.Latter_Frequency[9]++; }
		else if (Data_Storage.at(i) == 'k' || Data_Storage.at(i) == 'K') { Data2.Latter_Frequency[10]++; }
		else if (Data_Storage.at(i) == 'l' || Data_Storage.at(i) == 'L') { Data2.Latter_Frequency[11]++; }
		else if (Data_Storage.at(i) == 'm' || Data_Storage.at(i) == 'M') { Data2.Latter_Frequency[12]++; }
		else if (Data_Storage.at(i) == 'n' || Data_Storage.at(i) == 'N') { Data2.Latter_Frequency[13]++; }
		else if (Data_Storage.at(i) == 'o' || Data_Storage.at(i) == 'O') { Data2.Latter_Frequency[14]++; }
		else if (Data_Storage.at(i) == 'p' || Data_Storage.at(i) == 'P') { Data2.Latter_Frequency[15]++; }
		else if (Data_Storage.at(i) == 'q' || Data_Storage.at(i) == 'Q') { Data2.Latter_Frequency[16]++; }
		else if (Data_Storage.at(i) == 'r' || Data_Storage.at(i) == 'R') { Data2.Latter_Frequency[17]++; }
		else if (Data_Storage.at(i) == 's' || Data_Storage.at(i) == 'S') { Data2.Latter_Frequency[18]++; }
		else if (Data_Storage.at(i) == 't' || Data_Storage.at(i) == 'T') { Data2.Latter_Frequency[19]++; }
		else if (Data_Storage.at(i) == 'u' || Data_Storage.at(i) == 'U') { Data2.Latter_Frequency[20]++; }
		else if (Data_Storage.at(i) == 'v' || Data_Storage.at(i) == 'V') { Data2.Latter_Frequency[21]++; }
		else if (Data_Storage.at(i) == 'w' || Data_Storage.at(i) == 'W') { Data2.Latter_Frequency[22]++; }
		else if (Data_Storage.at(i) == 'x' || Data_Storage.at(i) == 'X') { Data2.Latter_Frequency[23]++; }
		else if (Data_Storage.at(i) == 'y' || Data_Storage.at(i) == 'Y') { Data2.Latter_Frequency[24]++; }
		else if (Data_Storage.at(i) == 'z' || Data_Storage.at(i) == 'Z'){ Data2.Latter_Frequency[25]++; }
		else { continue;};
			
	}
	for (int i = 0; i < 25; i++)
	{
		Data2.Latter_Frequency[i] = Data2.Latter_Frequency[i] / Data_Storage.size();
	}
}
//**************************************************************************************
//Definition of function Print_Data_Alphabet. Accepts struct TxtDetail reference type. *
//Once called it will go through the array of characters and print how many times      *
//letter are repeated on the the text file.                                            *
//***************************************************************************************
void Print_Data_Alphabet(TxtDetail& printing) {
	char arr[26] = {
					'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
					'l', 'm', 'o', 'p', 'q', 'r','s','t','u','v','w','x',
					'y','z'
	};
	for (int i = 0; i < 25; i++)
	{
		if (printing.Latter_Frequency[i] == 0)
		{
			cout << arr[i] << ": " << fixed << setprecision(1) << printing.Latter_Frequency[i] << "%" << endl;
		} 
		else
		{
			cout << arr[i] << ": " <<fixed<<setprecision(4) << printing.Latter_Frequency[i]<<"%"<<endl;
		}
		

	}

}
//*********************************************************************
// Defination of fuction Print_Data. Accepts structure type txtdetail *
// and two other string type.Once called it will open a txt file name * 
// CardCatalog.txt if already open it will append the line at the     *
// end of the file.                                                   *
//*********************************************************************
void Print_Data(TxtDetail& Print,string First_Name, string Last_Name) {
	fstream Print_File;
	Print_File.open("CardCatalog.txt", ios::app);

	Print_File << "Title of the content: " << Print.Text_Title << endl;
	Print_File << "The author full name: " << Print.Author_Full_Name << endl;
	Print_File << "Author First Name: " << First_Name << endl;
	Print_File << "Author Last Name: " << Last_Name << endl;
	Print_File << "Word Count: " << Print.Word_Count << endl;
	Print_File << "Line Count: " << Print.Line_Count << endl;
	Print_File << endl;

	Print_File.close();
}


