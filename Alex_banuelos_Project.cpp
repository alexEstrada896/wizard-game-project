/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
//Constants for a castle with 9 rooms (3 x 3) and the size for each room (15 x 15)
const int CASTLEROW = 3;
const int CASTLECOLOM = 3;
const int CASTLEROOMROW = 5;
const int CASTLEROOMCOLOM = 5;
//global enum for the direction user travels
enum Direction { UP, DOWN, LEFT, RIGHT, INVALID};


//structures
//structure for the characters(wizards) in the game
struct Character
{
	double health;//each characters health
	string name;//the name of each character
	char wizardType; //the element type of each character
	double defensePower, attackPower;   //the strength of each character
	char characterSymbol;//the symbol of each character on the castle
	int xRoomPos, yRoomPos;  // position of each character on the room they are on
	int xCastlePos, yCastlePos;// position of each character on the castle


};

//functions
//function to get the users character information
Character getUserInfo();
//function to start the castle and assign each position a symbol
void startCastle(char [CASTLEROW][CASTLECOLOM][CASTLEROOMROW][CASTLEROOMCOLOM],Character&,Character[],int&);
//function to show castle map
void showCastle ( char [CASTLEROW][CASTLECOLOM][CASTLEROOMROW][CASTLEROOMCOLOM], Character& );
//function to show the room map
void showRoom (char [CASTLEROW][CASTLECOLOM][CASTLEROOMROW][CASTLEROOMCOLOM], Character&,Character []);
//function to prompt the users direction
void promptDirection(char [CASTLEROW][CASTLECOLOM][CASTLEROOMROW][CASTLEROOMCOLOM], Character&,Character[],int&);
//function to convert the users direction from w , a , s  d
Direction userDirection(char);
//fuction to have user fight with the enemy
bool battle(Character&, Character&,int&);
//function to check the element type of both players and deal double damage if super effective
bool weaknessCheck (char, char );
//function to display the directions
void directions();




int main()
{
	char castleArray[CASTLEROW][CASTLECOLOM][CASTLEROOMROW][CASTLEROOMCOLOM];//4d array for each room in the castle
	int defeatedEnemies;//counts how many enemies user defeated

	Character userPlayer;//variable to store users information
	userPlayer = getUserInfo();//function to get users information
    directions();
	Character enemeyWiz[5];//structure array for the enemies
	startCastle(castleArray,userPlayer,enemeyWiz,defeatedEnemies);   //sets all the symbols in the castle



	while(true)//while user is playing 
	{
		showCastle(castleArray, userPlayer);//shows a map of the 3x3 room castle 
		showRoom(castleArray, userPlayer,enemeyWiz);//shows map of 5x5 room with user and enemies
		promptDirection(castleArray, userPlayer,enemeyWiz,defeatedEnemies);//prompts the user to move directions

		if (defeatedEnemies >= 5)//if user defeats all the enemies in the castle 
		{
			cout << "Congratulations! You defeated all the enemies and escaped the castle!"<<endl;

			char playAgain;//stores users choice to play again
			cout << "Would you like to play again? (Y/N)"<<endl;
			cin >> playAgain;

			if (playAgain == 'y' || playAgain == 'Y')//if player chooses to play again 
			{
				defeatedEnemies = 0;//reset enemies defeated
				userPlayer = getUserInfo();//get users informstion
				startCastle(castleArray,userPlayer,enemeyWiz,defeatedEnemies);//start a new castle 
			}
			else if (playAgain == 'n' || playAgain == 'N')//if user doesnt want to play again
			{
				cout << "Thank You For Playing.Goodbye"<<endl;
				return 0;
			}
			else // if user doesnt type yes or no 
			{
				cout <<"Invalid , enter y or n"<<endl;
				cin >> playAgain;
			}
		}

		promptDirection(castleArray, userPlayer, enemeyWiz, defeatedEnemies);//prompt users direction

	}
	return 0;
}

//functions
//function to get the users character information
Character getUserInfo()
{
	Character temp;// temperary variable to store the users information
//asks user to enter their character information
	cout << "Welcome!"<<endl;
	cin.get();
	cout<<"--------------"<<endl;
	cout << "Enter your characters name :"<<endl;
	cout<<">";

	getline(cin, temp.name) ;
	cout << "\nWhat element do you want your wizard to pocess? Water (W) or Fire? (F) :"<<endl;
	cout<<"--------------------------------------------------------------------------------"<<endl;
	cout<<">";
	cin >> temp.wizardType;

//validates input
	while ( !(temp.wizardType == 'w' || temp.wizardType == 'W' || temp.wizardType == 'F' || temp.wizardType == 'f'))
	{

		cout << "Error! Enter W for water or F for fire : ";
		cout<<">";
		cin >>temp.wizardType;
		cout<<"----------------------"<<endl;

	}

//displays user info based on the users chosen element

	switch (temp.wizardType)
	{
	case 'w':
		cout << "Hello Water Wizard "<<temp.name<< "! Begin your quest to defeat the evil wizard king."<<endl;
		
		break;

	case 'W':
		cout << "Hello Water Wizard "<<temp.name<< "! Begin your quest to defeat the evil wizard king."<<endl;
		break;

	case 'F':
		cout << "Hello Fire Wizard "<<temp.name<< "! Begin your quest to defeat the evil wizard king."<<endl;
		break;

	case 'f':
		cout << "Hello Fire Wizard "<<temp.name<< "! Begin your quest to defeat the evil wizard king."<< endl;
		break;



        
	}
	cin.get();
	return temp;

}

//function to set each position on the map with a symbol to indicate the users position
void startCastle (char castle [CASTLEROW][CASTLECOLOM][CASTLEROOMROW][CASTLEROOMCOLOM],Character& user,Character enemy[],int& defEnemies)
{

	defEnemies = 0;
	int seed = time(0);//random seed for the characters position
	srand(seed);


//sets the enemie character symbols on the map
	for (int a = 0 ; a < 5 ; a++)
	{
		if (a == 4)
		{
			enemy[a].characterSymbol ='W';
			enemy[a].attackPower = 2;
			enemy[a].defensePower = 2;
			enemy[a].health = 100;
		}
		else
		{
			enemy[a].characterSymbol = 'X';
			enemy[a].attackPower = 1;
			enemy[a].defensePower = 1;
			enemy[a].health = 50;
		}

	}
//sets the enemies elements
	enemy[0].wizardType = 'L';
	enemy[1].wizardType = 'E';
	enemy[2].wizardType = 'P';
	enemy[3].wizardType = 'I';
	enemy[4].wizardType = 'D';
//sets the enemies names
	enemy[0].name = "Lightning Wizard";
	enemy[1].name = "Earth Wizard";
	enemy[2].name = "Poison Wizard";
	enemy[3].name = "Ice Wizard";
	enemy[4].name = "Wizard King";


//variables to set the users information on the map
	user.characterSymbol = 'O';	//users symbol
	user.xCastlePos = (rand()%(2 - 0 + 1)) + 0;//users start position on castle map
	user.yCastlePos = (rand()%(2 - 0 + 1)) + 0;
	user.xRoomPos= (rand() % ( 4 - 0 + 1 )) + 0;//users start position on the room map
	user.yRoomPos= (rand() % ( 4 - 0 + 1 )) + 0;
	user.health = 100;
	user.attackPower = 1;
	user.defensePower = 1;

	for (int i = 0 ; i < CASTLEROW ; i ++)
	{
		for (int j = 0 ; j <CASTLECOLOM ; j++)
		{
			for (int k = 0 ; k < CASTLEROOMROW ; k ++)
			{
				for (int l = 0 ; l < CASTLEROOMCOLOM ; l ++)
				{


					castle[i][j][k][l] = '*';
				}
			}
		}
	}


	castle[user.yCastlePos][user.xCastlePos][user.yRoomPos][user.xRoomPos] = user.characterSymbol;
	//sets a random position for the 5 enemies
	for (int a = 0 ; a < 5 ; a++)
	{
		do
		{
			//puts enemies on position not already taken
			enemy[a].xCastlePos = (rand()%(2 - 0 + 1)) + 0;
			enemy[a].yCastlePos = (rand()%(2 - 0 + 1)) + 0;
			enemy[a].xRoomPos = (rand() % ( 4 - 0 + 1 )) + 0;
			enemy[a].yRoomPos = (rand() % ( 4 - 0 + 1 )) + 0;
		} while (castle[enemy[a].yCastlePos][enemy[a].xCastlePos][enemy[a].yRoomPos][enemy[a].xRoomPos] != '*');

		castle[enemy[a].yCastlePos][enemy[a].xCastlePos][enemy[a].yRoomPos][enemy[a].xRoomPos] = enemy[a].characterSymbol;
	}

}

//function to show the castle map and what room the user is in
void showCastle ( char castle[CASTLEROW][CASTLECOLOM][CASTLEROOMROW][CASTLEROOMCOLOM], Character& user)
{



	cout <<"Castle Map: "<<endl;
	for (int i = 0; i < CASTLEROW ; i++)
	{
		for (int j = 0 ; j < CASTLECOLOM ; j++)
		{
			//if user is in the room display their symbol
			if (i == user.yCastlePos && j == user.xCastlePos)
			{
				cout <<"{"<<user.characterSymbol<<"}";
			}
			else
			{
				cout <<"{ }";
			}
		}
		cout <<endl;
	}
	cout <<"-----------"<<endl;
}

//function to show which castle room the user is in
void showRoom (char castle[CASTLEROW][CASTLECOLOM][CASTLEROOMROW][CASTLEROOMCOLOM], Character& user,Character enemy[])
{
//display what room number the user is on
	cout <<"Room: "<< (user.xCastlePos + 1 )<<", "<<(user.yCastlePos + 1)<<endl;

	for (int i = 0 ; i < CASTLEROOMROW ; i++)
	{
		for (int j = 0 ; j <CASTLEROOMCOLOM ; j++)
		{
			char symbol = ' ';//variable to carry the symbol on the map
			//if the position in the room is the users, display their symbol
			if (i == user.yRoomPos && j == user.xRoomPos)
			{
				symbol = user.characterSymbol;
			}
			for (int k = 0; k < 5 ; k++)
			{
				if (enemy[k].xCastlePos == user.xCastlePos && enemy[k].yCastlePos == user.yCastlePos && enemy[k].xRoomPos == j && enemy[k].yRoomPos == i)
				{
					symbol = enemy[k].characterSymbol;
				}
			}
			//displays the symbol on each position on the map
			cout << "[" << symbol << "]";

		}
		cout<<endl;
	}
	cout<<"-----------------"<<endl;
}

//function to promt thr user to move
void promptDirection(char castle[CASTLEROW][CASTLECOLOM][CASTLEROOMROW][CASTLEROOMCOLOM], Character& user,Character enemy[],int& defEnemies)
{
	char choice;//variable to store the users choice
	cout << "Enter w, a, s, or d to move: "<<endl;
	cout<<"------------------------"<<endl;
	cin >> choice;

	Direction move = userDirection(choice);

	// Remove the current user position in the castle
	castle[user.xCastlePos][user.yCastlePos][user.xRoomPos][user.yRoomPos] = '*';

	// Move up in the room or between rooms
	if (move == UP)
	{
		if (user.yRoomPos > 0) // Move up within the room
		{
			user.yRoomPos--;
		}
		else if (user.yCastlePos > 0) // Wrap up to the previous room
		{
			user.yCastlePos--;
			user.yRoomPos = CASTLEROOMROW - 1; // Move to the bottom of the previous room
		}
		else
		{
			cout << "Error! Cannot move up further." << endl;
			return;
		}
	}
	// Move down in the room or between rooms
	else if (move == DOWN)
	{
		if (user.yRoomPos < CASTLEROOMROW - 1) // Move down within the room
		{
			user.yRoomPos++;
		}
		else if (user.yCastlePos < CASTLEROW - 1) // Wrap down to the next room
		{
			user.yCastlePos++;
			user.yRoomPos = 0; // Move to the top of the next room
		}
		else
		{
			cout << "Error! Cannot move down further." << endl;
			return;
		}
	}
	// Move left in the room or between rooms
	else if (move == LEFT)
	{
		if (user.xRoomPos > 0) // Move left within the room
		{
			user.xRoomPos--;
		}
		else if (user.xCastlePos > 0) // Wrap left to the previous room
		{
			user.xCastlePos--;
			user.xRoomPos = CASTLEROOMCOLOM - 1; // Move to the right of the previous room
		}
		else
		{
			cout << "Error! Cannot move left further." << endl;
			return;
		}
	}
	// Move right in the room or between rooms
	else if (move == RIGHT)
	{
		if (user.xRoomPos < CASTLEROOMCOLOM - 1) // Move right within the room
		{
			user.xRoomPos++;
		}
		else if (user.xCastlePos < CASTLEROW - 1) // Wrap right to the next room
		{
			user.xCastlePos++;
			user.xRoomPos = 0; // Move to the left of the next room
		}
		else
		{
			cout << "Error! Cannot move right further." << endl;
			return;
		}
	}
	// Handle invalid input
	else if (move == INVALID)
	{
		cout << "Invalid movement! Please use w, a, s, or d." << endl;
		return;
	}

//checks if user encountered enemy
	for ( int i = 0 ; i <5 ; i++)
	{
		if (user.xCastlePos == enemy[i].xCastlePos && user.yCastlePos == enemy[i].yCastlePos && user.xRoomPos == enemy[i].xRoomPos && user.yRoomPos == enemy[i].yRoomPos && enemy[i].health > 0)
		{
			//if user encounterd wizard king and has defeated the rest of the enemies
			if (enemy[i].characterSymbol == 'W' && defEnemies >= 4)
			{
				cout << "You encountered the Wizard King. Prepare for battle!" << endl;
				cin.get();
				if (! (battle(user, enemy[i], defEnemies)))    //start battle and determin if user looses
				{
					cout <<"Game Over. You were defeated by the Wizard King."<<endl;
					exit(0);
				}

			}
			//if user encounters wizard king and has not defeated the rest of the enemies
			else if (enemy[i].characterSymbol == 'W' && defEnemies < 4)
			{
				cout<<"Wizard King: You are to weak.Fight me when you defeat the others.."<<endl;
				return;
			}
			else
			{
				//if user encounters enemy they get sent in the battle function
				cout <<"You encountered the "<<enemy[i].name<<" Prepare fore battle!"<<endl;
				cout<<"----------------------"<<endl;

				if (!battle(user, enemy[i], defEnemies))
				{
					cout << "Game Over. You were defeated by the " << enemy[i].name << "." << endl;
					exit(0); // Exit the program
				}
			}


		}
	}
	// Show updated castle and room maps
	showCastle(castle, user);
	showRoom(castle, user,enemy);
}
//function to return the users direction
Direction userDirection(char choice)
{
	//returns up , down , left or right based on the users choice from w,a,s,d
	if (choice == 'w'|| choice == 'W')
	{
		return UP;
	}
	else if (choice == 'a' || choice == 'A')
	{
		return LEFT;
	}
	else if (choice == 's' || choice == 'S')
	{
		return DOWN;
	}
	else if (choice == 'd'|| choice == 'D')
	{
		return RIGHT;
	}
	else
	{
		return INVALID;
	}
}

//function battle: function to display the user and enemy wizard battling
bool battle(Character& user, Character& enemy,int& defEnemies)
{
	user.health = 100;
    


	//if user encounter a spot on the map where it already defeated an enemy
	if (enemy.health <= 0)
	{
		cout << "This enemy is already defeated!" << endl;
		return true;
		defEnemies = defEnemies + 1;
	}

	while (user.health > 0 && enemy.health > 0)//battle lasts as long as both have health
	{

		string userAnswer;//stores user answer
		int enemyChoice;//stores the enemies choice
		string enemyAnswer;//stores the enemies answer


		int seed = time(0);
		srand(seed);
		enemyChoice = (rand()%(3 - 1 + 1))+1;//generates enemies choice

		switch (enemyChoice)//chooses enemies answer based on its choice
		{
		case 1:
			enemyAnswer = "Crystal Orb";
			break;

		case 2:
			enemyAnswer = "Spell Book";
			break;

		case 3:
			enemyAnswer = "Magic Staff";
			break;

		}
		//displays enemy and users Health
		cout <<enemy.name<<" health: " <<enemy.health<<endl;
		cout <<user.name<<" health: "<<user.health<<endl;
		cout<<"----------------------------"<<endl;
		cout<<"----------------------------"<<endl;

		cout <<"Enter CO for crystal orb , SB for spell book or MS for magic staff:"<<endl;//propmts user to enter an item
		cout <<">";
		cin>> userAnswer;
		cout<<"----------------------"<<endl;
//validates input
		while (!(userAnswer == "CO" || userAnswer == "co" || userAnswer == "SB" || userAnswer == "sb" || userAnswer == "MS" || userAnswer == "ms"))
		{
			cout << "Invalid! Enter CO for crystal orb , SB for spell book or MS for magic staff:"<<endl;
			cout<<">";
			cin >> userAnswer;
			cout<<"----------------------"<<endl;
		}
//if user chose crystal orb and enemy chose spell book
		if ((userAnswer == "CO" && enemyChoice == 2 )|| (userAnswer == "co" && enemyChoice == 2 ) )
		{
			char choice;
			cout << "You chose Crystal Orb and "<<enemy.name<<" chose spell book."<<endl;
			cout <<"The Spell book cant outwit the crystal balls foresight and loses "<<endl;
			cout<<"----------------------"<<endl;
			cout<<"Make a move ( A to attack or D to increase defence):"<<endl;
			cout <<">";
			cin >>choice;
			//validates input
			while (!(choice == 'a' || choice == 'A'||choice == 'd' || choice == 'd'))
			{
				cout <<"Enter A to attack or D to increase defence"<<endl;
				cout<<">";
				cin>>choice;
				cout<<"----------------------"<<endl;
			}
			//attacks enemy if user chooses A
			if (choice == 'a' || choice == 'A')
			{
				cout <<"You Attacked!"<<endl;
				double damage = 10 * user.attackPower;//initial damage dealth

				if (weaknessCheck(enemy.wizardType, user.wizardType))//checks if attack is super effective
				{
					cout << "Damage is twice lethal!"<<endl;//changes to double damage if supereffective
					damage = damage * 2;
				}
				enemy.health = enemy.health - damage;
				cout<<"----------------------"<<endl;
			}
			//raises health if user chooses d
			if (choice == 'd' || choice == 'D')
			{
				cout <<"You increased your defence and gained health!"<<endl;
				user.health = user.health + (user.defensePower + 10);
				cout<<"----------------------"<<endl;
			}

		}
		//if user chooses spell book and enemy chose majic staff
		else if ((userAnswer == "SB" && enemyChoice == 3 )|| (userAnswer == "sb" && enemyChoice == 3 ) )
		{
			char choice;
			cout << "You chose the Spell Book and "<<enemy.name<<" chose the Magic Staff."<<endl;
			cout <<"Wisdom Triumphs over brut strength so the spell book wins! "<<endl;
			cout<<"----------------------"<<endl;
			//prompts useto attack or raise defense
			cout<<"Make a move ( A to attack or D to increase defence):"<<endl;
			cout <<">";
			cin >> choice;
			cout<<"----------------------"<<endl;
			//validates input
			while (!(choice == 'a' || choice == 'A'||choice == 'd' || choice == 'd'))
			{
				cout <<"Enter A to attack or D to increase defence"<<endl;
				cout<<">";
				cin>>choice;
				cout<<"----------------------"<<endl;
			}
			//user attacks enemy if user chooses a
			if (choice == 'a' || choice == 'A')
			{
				cout <<"You Attacked!"<<endl;
				double damage = 10 * user.attackPower;//initial damage dealt

				if (weaknessCheck(enemy.wizardType, user.wizardType)) //checks if damage dealt is super effective
				{
					cout << "Damage is twice lethal!"<<endl;//doubles damage if true
					damage = damage * 2;
				}
				enemy.health = enemy.health - (10 * user.attackPower);
				cout<<"----------------------"<<endl;
			}
			//user raises defense if they choose d
			if (choice == 'd' || choice == 'D')
			{
				cout <<"You increased your defence and gained health!"<<endl;
				user.health = user.health + (user.defensePower + 10);
				cout<<"----------------------"<<endl;
			}

		}
		//if user chose majic staff and enemy chose crystal orb
		else if ((userAnswer == "ms" && enemyChoice == 1 )|| (userAnswer == "MS" && enemyChoice == 1 ) )
		{
			char choice;
			cout << "You chose the Magic Staff and "<<enemy.name<<" chose Crystal Orb"<<endl;
			cout <<"Raw power shatters the crystal orb and the Magic Staff wins! "<<endl;
			cout<<"----------------------"<<endl;
			cout<<"Make a move ( A to attack or D to increase defence):"<<endl; // prompt user to attack or defend
			cout <<">";
			cin >> choice;
			cout<<"----------------------"<<endl;
			//validates input
			while (!(choice == 'a' || choice == 'A'||choice == 'd' || choice == 'd'))
			{
				cout <<"Enter A to attack or D to increase defence"<<endl;
				cout<<">";
				cin>>choice;
				cout<<"----------------------"<<endl;
			}
			//attacks if user chooses a
			if (choice == 'a' || choice == 'A')
			{
				cout <<"You Attacked!" <<endl;
				double damage = 10 * user.attackPower;//initial damage dealt

				if (weaknessCheck(enemy.wizardType, user.wizardType)) //checks if damage is supereffective
				{
					cout << "Damage is twice lethal!"<<endl;//if true double damage
					damage = damage * 2;
				}
				enemy.health = enemy.health - (10 * user.attackPower);
				cout<<"----------------------"<<endl;
			}
			//raises defense if user chooses d
			if (choice == 'd' || choice == 'D')
			{
				cout <<"You increased your defence and gained health!"<<endl;
				user.health = user.health + (user.defensePower + 10);
				cout<<"----------------------"<<endl;
			}

		}
		//if user chooses crystal orb and enemy chooses majic staff
		else if ((userAnswer == "co" && enemyChoice == 3 )|| (userAnswer == "CO" && enemyChoice == 3 ) )
		{
			char enemyChoice;
			cout << "You chose Crystal Orb and "<<enemy.name<<" chose Magic Staff"<<endl;
			cout <<"Raw power shatters the crystal orb and the Magic Staff wins! "<<endl;
			cout<<"----------------------"<<endl;
			cout<<"Enemy makes move..."<<endl;
			cin.get();
			cout<<"----------------------"<<endl;
			//generates choice for enemy
			enemyChoice = (rand() % (2 - 1 + 1))+1;
			//if enemy chooses attack
			if (enemyChoice == 1)
			{
				cout <<enemy.name<<" Attacked!"<<endl;
				double damage = 10 * enemy.attackPower; //base attack

				if (weaknessCheck(user.wizardType,enemy.wizardType))//checks if attack is super efective
				{
					damage = damage *2;//if true , double damage
					cout <<"Their damage is Twice lethal!"<<endl;
				}
				user.health = user.health - damage;
				cout<<"----------------------"<<endl;
			}
			//if enemy chooses defense
			if (enemyChoice == 2)
			{
				cout <<enemy.name<<" increased defence and gained health!"<<endl;
				enemy.health = enemy.health + (enemy.defensePower + 10);
				cout<<"----------------------"<<endl;
			}

		}
		//if user chooses spell book and enemy chooses crystal orb
		else if ((userAnswer == "SB" && enemyChoice == 1 )|| (userAnswer == "sb" && enemyChoice == 1 ) )
		{
			char enemyChoice;
			cout << "You chose the Spell Book and "<<enemy.name<<" chose Crystal Orb"<<endl;
			cout <<"The Spell book cant outwit the crystal orbs foresight and loses"<<endl;
			cout<<"----------------------"<<endl;
			cout<<"Enemy makes move..."<<endl;
			cin.get();
			cout<<"----------------------"<<endl;
			//generates enemys choice
			enemyChoice = (rand() % (2 - 1 + 1))+1;
			//if enemy chooses attack
			if (enemyChoice == 1)
			{
				cout <<enemy.name<<" Attacked!"<<endl;
				double damage = 10 * enemy.attackPower; //base attack

				if (weaknessCheck(user.wizardType,enemy.wizardType))//checks if attack is super efective
				{
					damage = damage *2;//if true , double damage
					cout <<"Their damage is Twice lethal!"<<endl;
				}
				user.health = user.health - damage;
				cout<<"----------------------"<<endl;
			}
			//if enemy chooses defense
			if (enemyChoice == 2)
			{
				cout <<enemy.name<<" increased defence and gained health!"<<endl;
				enemy.health = enemy.health + (enemy.defensePower + 10);
				cout<<"----------------------"<<endl;
			}

		}
		//if user chose majic staff and enemy chose spell book
		else if ((userAnswer == "ms" && enemyChoice == 2 )|| (userAnswer == "MS" && enemyChoice == 2 ) )
		{
			char enemyChoice;
			cout << "You chose the Majic Staff and "<<enemy.name<<" chose Crystal Orb"<<endl;
			cout <<"Wisdom Triumphs over brut strength so the spell book wins! "<<endl;
			cout<<"----------------------"<<endl;
			cout<<"Enemy makes move..."<<endl;
			cin.get();
			cout<<"----------------------"<<endl;
			//generates enemies choice
			enemyChoice = (rand() % (2 - 1 + 1))+1;
			//if enemy chose attack
			if (enemyChoice == 1)
			{
				cout <<enemy.name<<" Attacked!"<< endl;
				double damage = 10 * enemy.attackPower; //base attack

				if (weaknessCheck(user.wizardType,enemy.wizardType))//checks if attack is super efective
				{
					damage = damage *2;//if true , double damage
					cout <<"Their damage is Twice lethal!"<<endl;
				}
				user.health = user.health - damage;
				cout<<"----------------------"<<endl;
			}
			//if enemy chose defense
			if (enemyChoice == 2)
			{
				cout <<enemy.name<<" increased defence and gained health!"<<endl;
				enemy.health = enemy.health + (enemy.defensePower + 10);
				cout<<"----------------------"<<endl;
			}

		}
		//if both user and enemy choose the same object
		else
		{
			cout <<"Its a tie! Both fail to do damage."<<endl;
			cout<<"----------------------"<<endl;
		}
		//if user wins
		if (enemy.health <= 0)
		{
			cout << "Congratulations! , You defeated "<<enemy.name<<endl;
			cout<<"----------------------"<<endl;
			enemy.health = 0;
			enemy.characterSymbol ='0';//changes enemies symbol on the map
			defEnemies = defEnemies + 1;
			return true;//returns true 
			//adds to defeated enemie count
		
		}
		//if user looses
		else if (user.health <= 0)
		{
			cout <<"You have been defeated"<<endl;
			cout<<"----------------------"<<endl;
			
			return false;//returns false
		}



	}
	return true;
}

bool weaknessCheck (char user, char enemy)
{
	//checks if user or enemy element is super effective against one another
	if ((user == 'F' || user == 'f')&& ( enemy == 'w' || enemy == 'W'))//checks for when fire is weak to water
		return true;
	if ((user == 'W' || user == 'w')&& ( enemy == 'l' || enemy == 'L'))//checks for when water is weak to lightning
		return true ;
	if((user == 'I' || user == 'i')&& ( enemy == 'f' || enemy == 'F'))//checks for when ice is week to fire
		return true;
	if((user == 'p' || user == 'P')&& ( enemy == 'w' || enemy == 'W'))//checos for when poiso is weak to water
		return true;
	if ((user == 'F' || user == 'f')&& ( enemy == 'e' || enemy == 'E'))//checks for when fire is weak to earth
		return true;
	return false;
}
//funtion to give the directions of the game 
void directions ()
{
    cout <<"You are a wizard who is trapped in a castle..."<<endl;
    cin.get();
    cout <<"The only way out is to defeat the evil wizard king"<<endl;
    cin.get();
    cout <<"But he wont fight you right away, you need to defeat 4 other enemies hidden in the castle"<<endl;
    cin.get();
    cout <<"You will have to beat them in a wizardly rock paper sciccors "<<endl;
    cin.get();
    cout <<"Crystal Orb beats Spell book"<<endl;
    cout <<"Spell book  beats Majic staff"<<endl;
    cout <<"Magic Staff beats Crystal Orb"<<endl;
    cin.get();
    cout <<"Your element type gives you an advantage over sum of the enemies but not all"<<endl;
    cin.get();
    cout<<"Defeat the wizard king to escape the castle!!"<<endl;
    cin.get();
}