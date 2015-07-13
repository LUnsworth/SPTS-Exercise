//Compiler set used: TDM-GCC 4.9.2 64-bit release (default set that comes with Bloodshed Dev-C++. g++.exe used judging by the compile log.
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void getuniquelines(vector<string> input);
void getmean(vector<string> input);
void getmode(vector<string> input);
void getmedian(vector<string> input);
void getrange(vector<string> input);
void getpopularity(vector<string> input);
void printtop(vector<char> letters, vector<int> frequency, int limit);
void printbottom(vector<char> letters, vector<int> frequency, int limit);

int main() {
	cout << "Welcome to Luke Unsworth's c++ exercise submission.\n";
	cout << "Enter strings of your choice, enter a characterless string to continue.\n";
	
	//input capture string.
	string strinp;
	//Vector to hold strings. Seems appropriate??
	vector<string> lines;
	
	int x, a;
	//Used to keep the loop going if you enter a blank line as the very first thing.
	int inputvalidation = 0;
	
	//String capture loop.
	while(1){
		getline(cin, strinp);
		if(strinp == "")
		{
			if(inputvalidation==0)
			{
				cout << "Please don't quit before you've done anything, try entering a string!\n";
			}
			else
			{
				break;
			}
		}
		else
		{
			//Push string to end of vector.
			lines.push_back(strinp);
			inputvalidation = 1;
		}
	};
		
	//The screen printouts will be done in the functions.
	getuniquelines(lines);
	getmean(lines);
	getmode(lines);
	getmedian(lines);
	getrange(lines);
	getpopularity(lines);
	return 0;
}

void getuniquelines(vector<string> input){
	int uniquelines = 0;
	int a, b;
	int flag = 0;
	string comp1, comp2;
	
	for(a=0;a<(input.size()-1);a++){
		comp1 = input[a];
		flag = 0;
		for(b=(a+1);b<input.size();b++){
			comp2 = input[b];
			if(comp1.compare(comp2)==0){
				//If the string matches another in the list, set a flag.
				flag = 1;
				//As soon as a match is found exit the nested loop, in the name of efficiency.
				break;
			}
		}
		if(flag == 0)
		{
			uniquelines++;
		}
	}
	//As the loop terminates at the penultimate entry, the last entry will ALWAYS be classed as unique.
	uniquelines++;
	if(uniquelines == 1)
	{
		cout << "There is 1 unique line." << endl;
	}
	else
	{
		cout << "There are " << uniquelines << " unique lines." << endl;
	}
	
}

void getmean(vector<string> input){
	float mean;
	int x = 0;
	for(x=0;x<input.size();x++){
		mean += float(input[x].size());
	}
	mean = mean / float(input.size());
	cout << "The mean string length is: " << mean << endl;
}

void getmode(vector<string> input){
	vector<int> mode;
	int modenumber = 0, tempmode = 0, tempmodenumber = 0;
	int lengths[input.size()];
	int temp, sorted;
	int x, y;
	
	mode.push_back(0);
	
	//Get the lengths of all the strings input.
	for(x=0;x<input.size();x++){
		lengths[x] = input[x].size();
	}
	//Sort lengths into order, makes it easier that way.
	sorted = 0;
	while(sorted!=1){
		//Assume initially sorted.
		sorted = 1;
		for(x=0;x<(input.size()-1);x++){
			if(lengths[x] > lengths[x+1]){
				temp = lengths[x];
				lengths[x] = lengths[x+1];
				lengths[x+1] = temp;
				sorted = 0;
			}
		}
	};

	//Loop through the sorted list. Incrementing a counter if the next element matches.
	for(x=0;x<(input.size()-1);x++){
		if(lengths[x] == lengths[x+1])
		{
			tempmode = lengths[x];
			tempmodenumber++;
		}
		else
		{
			if(tempmodenumber > modenumber)
			{
				//Clear any preceding modal values.
				mode.clear();
				//Populate first element with new mode values.
				mode.push_back(tempmode);
				modenumber = tempmodenumber;
			}
			else if(tempmodenumber == modenumber)
			{
				//If the unique string length is just as common as the current most common, push it into a vector!
				mode.push_back(tempmode);
				modenumber = tempmodenumber;
			}
			//Reset counters for next sequence.
			tempmode = 0;
			tempmodenumber = 0;
		}
	}
	//Not very elegant, but add the mode checks again just in case the last two elements match.
	if(tempmodenumber > modenumber)
		{
			//Clear any preceding modal values.
			mode.clear();
			//Populate first element with new mode values.
			mode.push_back(tempmode);
			modenumber = tempmodenumber;
		}
		else if(tempmodenumber == modenumber)
		{
			//If the unique string length is just as common as the current most common, push it into a vector!
			mode.push_back(tempmode);
			modenumber = tempmodenumber;
		}

	//Hardcode 2, because I'm struggling to implement it more elegantly in the loop...
	if((input.size() == 2) && (tempmode != 0))
	{
		mode[0] = tempmode;
		modenumber = tempmodenumber;
	}
	//Increment the number by 1 as it will have matched n-1 times.
	modenumber++;
	if(mode[0] == 0)
	{
		cout << "There is no modal value." << endl;
	}
	else if(mode.size()>1)
	{
		cout << "Multimodal! The following string lengths appeared " << modenumber << " times: ";
		for(x=0;x<mode.size();x++){
			cout << mode[x];
			if(x<(mode.size()-1))
			{
				cout << ", ";
			}
			else
			{
				cout << ".";
			}
		}
		cout << endl;
	}
	else
	{
		cout << "The modal string length is: " << mode[0] << " which appeared "<< modenumber << " times." << endl;
	}
}

void getmedian(vector<string> input){
	float median;
	int lengths[input.size()];
	int x, sorted, medianint, temp;
	
	//Get the lengths of all the strings input.
	for(x=0;x<input.size();x++){
		lengths[x] = input[x].size();
	}
	
	//Sort the lengths into ascending order.
	sorted = 0;
	while(sorted!=1){
		//Assume initially sorted.
		sorted = 1;
		for(x=0;x<(input.size()-1);x++){
			if(lengths[x] > lengths[x+1]){
				temp = lengths[x];
				lengths[x] = lengths[x+1];
				lengths[x+1] = temp;
				sorted = 0;
			}
		}
	};
	
		//DEBUG
//	for(x=0;x<input.size();x++){
//		cout << lengths[x] << endl;
//	}
	
	//If there are an odd number of elements in the list get the number in the middle.
	if(input.size() % 2 != 0)
	{
		medianint = (input.size() + 1) / 2;
		//Reduce position by 1 to offset position 0 being the first element.
		median = float(lengths[medianint-1]);
	}
	else
	{
		//Otherwise do the mean of the two in the middle.
		medianint = input.size() / 2;
		median = float(lengths[(medianint - 1)]) + float(lengths[medianint]);
		median = median / 2;
	}
	
	cout << "The median string length is: " << median << endl;
}

void getrange(vector<string> input){

	int range;
	int lengths[input.size()];
	int x, temp;
	int sorted = 0;
	
	for(x=0;x<input.size();x++){
		lengths[x] = input[x].size();
		//For debugging
		//cout << lengths[x] << endl;
	}
	
	//sorting loop!
	while(sorted!=1){
		//Assume initially sorted.
		sorted = 1;
		for(x=0;x<(input.size()-1);x++){
			if(lengths[x] > lengths[x+1]){
				temp = lengths[x];
				lengths[x] = lengths[x+1];
				lengths[x+1] = temp;
				sorted = 0;
			}
		}
	};
	
	//Making sure the last element is grabbed, not garbage from RAM.
	range = lengths[(input.size()-1)] - lengths[0];
	
	cout << "The range of string lengths is: " << range << endl;
}

void getpopularity(vector<string> input){
	//Initialise a vector for each unique character.
	vector<char> letters;
	//Initialise corresponding vector to hold frequency of each character.
	vector<int> frequency;
	int a, b, c, d;
	//Sorting variables.
	int sorted = 0;
	int temp = 0;
	char tempch;
	bool match;
	
	//1st character will always be unique in the list.
	letters.push_back(input[0][0]);
	frequency.push_back(1);

	//Loop across all strings, getting the frequency of each character.
	//Loop across each input string.
	for(a=0;a<input.size();a++){
		//Loop across each character of the string.
		for(b=0;b<input[a].size();b++){
			//Reset match flag for each character check.
			match = false;
			//Loop across the unique character list.
			for(c=0;c<letters.size();c++){
				//cout << "Character in vector is " << input[a][b] << ", character in char vector is " << letters[c] << endl;
				if(input[a][b] == letters[c])
					{
						match = true;
						break;
					}
			}
			//Once out of the third loop, perform the necessary incrememnt or push.
			if((a==0) && (b==0))
			{
				//Do nothing for the very first character checked.
			}
			else
			{
				if(match == true)
					{
						//If the character matches an existing character, increment it's counter.
						frequency[c]++;
					}
					else
					{
						//If it's a new character to the list, push it onto the vector and assign initial counter.
						letters.push_back(input[a][b]);
						frequency.push_back(1);
					}
			}
		}
	}
	
	//Sort the two vectors into descending order of popularity.
	while(sorted!=1){
		//Assume initially sorted.
		sorted = 1;
		for(a=0;a<(frequency.size()-1);a++){
			if(frequency[a] < frequency[a+1]){
				tempch = letters[a];
				temp = frequency[a];
				letters[a] = letters[a+1];
				frequency[a] = frequency[a+1];
				letters[a+1] = tempch;
				frequency[a+1] = temp;
				sorted = 0;
			}
		}
	};
	
	//For now output first and last 5 entries in the array. Might work on golf style scoring...
	if(letters.size()<=5){
		cout << "There's not quite enough for a top 5, so here they all are in descending order:" << endl;
		printtop(letters, frequency, letters.size());
	}
	else if(letters.size()<10)
	{
		//Arbitrate a middle point for aesthetic symmetry.
		b = letters.size()/2;
		cout << "Almost enough for a top and bottom 5... here are the top " << b << ":" <<  endl;
		printtop(letters, frequency, b);
		cout << "And now for the bottom " << letters.size() - b << ":" << endl;
		printbottom(letters, frequency, letters.size() - b);
	}
	else
	{
		cout << "The 5 most used characters are:" << endl;
		printtop(letters, frequency, 5);
		cout << "The 5 least used characters are:" << endl;
		printbottom(letters, frequency, 5);
	}
}

void printtop(vector<char> letters, vector<int> frequency, int limit){
	int a;
	for(a=0;a<limit;a++){
		if(frequency[a]==1)
		{
			cout << letters[a] << ", which was used once." << endl;
		}
		else
		{
		cout << letters[a] << ", which was used " << frequency[a] << " times." << endl;
		}
	}
}

void printbottom(vector<char> letters, vector<int> frequency, int limit){
	int a;
	for(a=letters.size() - 1;a>=letters.size() - limit;a--){	
		if(frequency[a]==1)
		{
			cout << letters[a] << ", which was used once." << endl;
		}
		else
		{
		cout << letters[a] << ", which was used " << frequency[a] << " times." << endl;
		}
	}
}

