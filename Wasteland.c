#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define pf printf
#define sf scanf
#define MAX 20

typedef struct stats
{
  char name[MAX];
  int health;
  int handWpn;
  int rangedWpn;
  int ammo;
  int barter;
}Stats;

typedef struct node
{
	int data;
	struct node *next;
}node;


////////////////////////////
//Function Prototypes///////
///////////////////////////
void Load(Stats *p_ptr);
void Welcome();
void StatsSetup(Stats *p_ptr);
void StatsSetupSaved(Stats *p_ptr);
void Intro(char *name);
void HealthDamage(int p_health);
void Death();
void Win();
void SaveGame(Stats player);
void LoadGame(Stats *p_ptr);
void Guide(Stats player);
void Travel(Stats *p_ptr_two);
node *buildList(node *head, int num);
int GetNth(node *head, int index);
void GearCheck(Stats player);
void Purchase(Stats *p_ptr_two);
int Random_Num();
void SafeZone(Stats *p_ptr_two);
void AbandStruct(Stats *p_ptr_two);
void HosTown(Stats *p_ptr_two);
void HosHuman(Stats *p_ptr_two);
void Radiation(Stats *p_ptr_two);
void WildAnimal(Stats *p_ptr_two);


////////////////////////////
//********* MAIN *********//
///////////////////////////
int main()
{
  Stats player;
  srand((unsigned)time(NULL));

  Load(&player);
  Guide(player);

  system("PAUSE");
  return 0;
}


////////////////////////////
//Game Setup///////////////
///////////////////////////
void Load(Stats *p_ptr)
{
  char choice = NULL;
  FILE *fp;

  fp = fopen("", "r");
  if(fp == NULL)
    {
      pf("*** No saved game data on file ***\n\n");
      Welcome();
      StatsSetup(p_ptr);
    }
  else
    {
      pf("*** Saved game data on file ***\n");
	  pf("*** Would you like to continue? ***\n");
	  pf("1---Yes\n");
	  pf("2---No\n");
	  do
	  {
		 choice = fgetc(stdin);
	  }while((choice != '1') && (choice != '2'));

	  switch(choice)
	  {
	  case '1':
		  {
			  Welcome();
			  LoadGame(p_ptr);
			  fclose(fp);
			  break;
		  }
	  case '2':
		  {
			  Welcome();
			  StatsSetupSaved(p_ptr);
			  fclose(fp);
			  break;
		  }
	   }
    }
}

void Welcome()
{
  pf("#####################################\n");
  pf("##########  THE WASTELAND  ##########\n");
  pf("#####################################\n");
  pf("#####  Survival based mini-sim  #####\n");
  pf("#####################################\n\n");
}

void StatsSetup(Stats *p_ptr)
{
  char ch;
  char *tempStr;
  int i = 0;
  int buffSize = MAX;

  tempStr = (char *)malloc(sizeof(char) * buffSize);
  if(tempStr == NULL)
  {
    pf("Error with tempStr mem allocation\n");
	exit(1);
  }

  do
  {
	pf("Character's name: ");
	ch = getchar();
  }while(ch == '\n');
  tempStr[i] = ch;
  i++;

  while(ch != '\n')
    {
      ch = getchar();
      tempStr[i] = ch;
      i++;
      if(i >= buffSize)
		{
			tempStr = (char *)realloc(tempStr, buffSize * 2);
			if(tempStr == NULL)
				pf("Error with tempStr mem reallocation\n");
			buffSize = buffSize * 2;
		}
    }
  tempStr[i] = '\n'; //added to find end of line

  for(i=0; i < MAX; i++) 
    {
      p_ptr->name[i] = tempStr[i];
      if(p_ptr->name[i] == '\n')
	  {
		p_ptr->name[i] = 0;
		break;
	  }
    }

  if(p_ptr->name[MAX-1] != '\n')
  {
	 p_ptr->name[MAX-1] = 0;
  }
  free(tempStr);

  /*//DEBUG CODE//
  pf("String stored: \n");
  for(i=0; i<strlen(p_ptr->name) + 1; i++)
  {
	  if(p_ptr->name[i] == '\0')
		pf("%d: ***\n", i);
	  else
		pf("%d: %c\n", i, p_ptr->name[i]);
  }
  pf("String length: %d\n", strlen(p_ptr->name));
  pf("Size of string: %d\n", sizeof(p_ptr->name));
  //DEBUG CODE//*/

  pf("\n\n");
  p_ptr->health = 100;
  p_ptr->handWpn = 1;
  p_ptr->rangedWpn = 1;
  p_ptr->ammo = 0;
  p_ptr->barter = 150;

  Intro(p_ptr->name);
}

void StatsSetupSaved(Stats *p_ptr)
{
  char ch;
  char *tempStr;
  int i = 0;
  int buffSize = MAX;

  tempStr = (char *)malloc(sizeof(char) * buffSize);
  if(tempStr == NULL)
  {
    pf("Error with tempStr mem allocation\n");
	exit(1);
  }

  while ((ch = getchar()) != '\n' && ch != EOF);
  do
  {
	pf("Character's name: ");
	ch = getchar();
  }while(ch == '\n');
  tempStr[i] = ch;
  i++;

  while(ch != '\n')
    {
      ch = getchar();
      tempStr[i] = ch;
      i++;
      if(i >= buffSize)
		{
			tempStr = (char *)realloc(tempStr, buffSize * 2);
			if(tempStr == NULL)
				pf("Error with tempStr mem reallocation\n");
			buffSize = buffSize * 2;
		}
    }
  tempStr[i] = '\n'; //added to find end of line

  for(i=0; i < MAX; i++) 
    {
      p_ptr->name[i] = tempStr[i];
      if(p_ptr->name[i] == '\n')
	  {
		p_ptr->name[i] = 0;
		break;
	  }
    }

  if(p_ptr->name[MAX-1] != '\n')
  {
	 p_ptr->name[MAX-1] = 0;
  }
  free(tempStr);

  /*//DEBUG CODE//
  pf("String stored: \n");
  for(i=0; i<strlen(p_ptr->name) + 1; i++)
  {
	  if(p_ptr->name[i] == '\0')
		pf("%d: ***\n", i);
	  else
		pf("%d: %c\n", i, p_ptr->name[i]);
  }
  pf("String length: %d\n", strlen(p_ptr->name));
  pf("Size of string: %d\n", sizeof(p_ptr->name));
  //DEBUG CODE//*/

  pf("\n\n");
  p_ptr->health = 100;
  p_ptr->handWpn = 1;
  p_ptr->rangedWpn = 1;
  p_ptr->ammo = 0;
  p_ptr->barter = 150;

  Intro(p_ptr->name);
}

void Intro(char *name)
{
  pf("%s", name);
  pf("\nWelcome to the wasteland.\n");
  pf("Use extreme caution!\n");
  pf("Be wary of hostile factions scattered throughout ruined towns.\n");
  pf("Avoid interaction with wild animals and radioactive regions.\n");
  pf("Items/weapons can be gathered from abandoned structures.\n");
  pf("Or bought with bartered goods in 'safe' towns.\n");
  pf("To survive, find the small town rumored to be unaffected by devistation.\n\n");
}


////////////////////////
//Player Functions/////
////////////////////////
void HealthDamage(int p_health)
{
  if(p_health <= 0)
    {
      Death();
    }
  else if(p_health > 0 && p_health <= 25)
    {
      pf("*** You are seriously injured! ***\n");
      pf("*** Health: %d ***\n", p_health);
      pf("\n");
    }
  else
    {
      pf("*** You are injured. ***\n");
      pf("*** Health: %d ***\n", p_health);
      pf("\n");
    }
}

void Death()
{
  pf("\nIn the wasteland, few survive... many die.\n");
  pf("You are...\n\n");
  pf("******         *********         ****        ******      \n");
  pf("*******        *********        ******       *******     \n");
  pf("**    **       **              **    **      **    **    \n");
  pf("**     **      **             **      **     **     **   \n");
  pf("**      **     *********     **        **    **      **  \n");
  pf("**      **     *********     ************    **      **  \n");
  pf("**      **     **            ************    **      **  \n");
  pf("**     **      **            **        **    **     **   \n");
  pf("********       *********     **        **    ********    \n");
  pf("*******        *********     **        **    *******     \n");
  pf("\n");
}

void Win()
{
  pf("\n\n");
  pf(" ****       **    ****         ****    ********       \n");
  pf(" ** **      **    ****       **   **   ********       \n");
  pf(" **  **     **    ****     **          **             \n");
  pf(" **   **    **    ****    **           ********       \n");
  pf(" **    **   **    ****    **           ********       \n");
  pf(" **     **  **    ****    **           **             \n");
  pf(" **      ** **    ****     **          **             \n");
  pf(" **       ****    ****       **   **   ********       \n");
  pf(" **        ***    ****         ****    ********       \n");
  pf("\n\n");
}


////////////////////////
//Action Functions/////
///////////////////////
void SaveGame(Stats player)
{
  FILE *fp;

  pf("*** Saving game ***\n");
  fp = fopen("c:/Users/John/Documents/Visual Studio 2012/Projects/GameDevelopment/SaveGame.txt", "w");
  if(fp == NULL)
  {
     pf("Error with writing save game\n");
	 exit(1);
  }
  fprintf(fp, "%s\n", player.name);
  fprintf(fp, "%d\n", player.health);
  fprintf(fp, "%d\n", player.handWpn);
  fprintf(fp, "%d\n", player.rangedWpn);
  fprintf(fp, "%d\n", player.ammo);
  fprintf(fp, "%d\n", player.barter);
  fclose(fp); 
}

void LoadGame(Stats *p_ptr)
{
  FILE *fp;
  char str[MAX];
  char strArray[6][MAX];
  int i = 0;
  int index = 0;
  int ch;

  fp = fopen("c:/Users/John/Documents/Visual Studio 2012/Projects/GameDevelopment/SaveGame.txt", "r");
  if(fp == NULL)
  {
    pf("Error with loading save game\n");
  }
  else
  {
	  while(index < 6)
	  {
		for(i=0; (i<sizeof(str)) && ((ch=fgetc(fp)) != feof(fp)) && (ch != '\n'); i++)
		{
			str[i] = ch;
		}
		str[i] = '\0';
		strcpy(strArray[index], str);
		index++;
	  }

	fclose(fp);
	strcpy(p_ptr->name, strArray[0]);

	p_ptr->health = atoi(strArray[1]);
	p_ptr->handWpn = atoi(strArray[2]);
	p_ptr->rangedWpn = atoi(strArray[3]);
	p_ptr->ammo = atoi(strArray[4]);
	p_ptr->barter = atoi(strArray[5]);

	/*//DEBUG CODE//
	pf("String stored in name: \n");
	for(i=0; i<strlen(p_ptr->name)+1; i++)
	{
	  if(p_ptr->name[i] == '\0')
	  {
		pf("%d: ***\n", i);
	  }
	  else
	  {
		pf("%d: %c\n", i, p_ptr->name[i]);
	  }
	}
	pf("String length: %d\n\n", strlen(p_ptr->name));
	pf("Int stored in health: %d\n", p_ptr->health);
	pf("Int stored in handWpn: %d\n", p_ptr->handWpn);
	pf("Int stored in rangedWpn: %d\n", p_ptr->rangedWpn);
	pf("Int stored in ammo: %d\n", p_ptr->ammo);
	pf("Int stored in barter: %d\n", p_ptr->barter);
	//DEBUG CODE//*/
  }
}

void Guide(Stats player)
{
  Stats *p_ptr_two = &player;
  int input = 0;

  pf("\nGuide:\n");
  pf("1---Travel\n");
  pf("2---Check your vitals and gear\n");
  pf("3---Quit Game\n");

  sf("%d", &input);
  while (input < 1 && input > 3) {
	  sf("%d", &input);
  }

switch(input)
{
case 1:
	{
	Travel(p_ptr_two);
	break;
	}
case 2:
	{
	GearCheck(player);
	break;
	}
case 3:
	{
	SaveGame(player);		
	break;
	}
}
}

void Travel(Stats *p_ptr_two)
{
	static node *p = NULL;
	static int i = 0;
	static int two_Before_Previous_Random = 0;
	static int before_Previous_Random = 0;
	static int previous_Random = 0;
	static int callCount = 0;
	int random = 0;

	do
	{
		random = Random_Num();
	}while(random > 6 || (random == previous_Random) || (random == (before_Previous_Random = GetNth(p, i-2))) || (random == (two_Before_Previous_Random = GetNth(p, i-3))) );

	switch(random)
	{
	case 1:
		{
			//DEBUG CODE//
			//pf("\nCase 1\n");
			//pf("Previous random number was %d\n", previous_Random);
			//pf("Random number 2 nodes before was %d\n", before_Previous_Random);
			//DEBUG CODE//

			callCount ++;
			i++;
			previous_Random = 1;
			p = buildList(p, random);
			SafeZone(p_ptr_two);
			break;
		}
	case 2:
		{
			//DEBUG CODE//
			//pf("\nCase 2\n");
			//pf("Previous random number was %d\n", previous_Random);
			//pf("Random number 2 nodes before was %d\n", before_Previous_Random);
			//DEBUG CODE//

			callCount ++;
			i++;
			previous_Random = 2;
			p = buildList(p, random);
			WildAnimal(p_ptr_two);
			break;
		}
	case 3:
		{
			//DEBUG CODE//
			//pf("\nCase 3\n");
			//pf("Previous random number was %d\n", previous_Random);
			//pf("Random number 2 nodes before was %d\n", before_Previous_Random);
			//DEBUG CODE//

			if(callCount > 3)
			{
				callCount = 0;
				i++;
				previous_Random = 3;
				p = buildList(p, random);
				HosTown(p_ptr_two);
				break;
			}
			else
			{
				callCount ++;
				i++;
				previous_Random = 3;
				p = buildList(p, random);
				Travel(p_ptr_two);
				break;
			}
		}
	case 4:
		{
			//DEBUG CODE//
			//pf("\nCase 4\n");
			//pf("Previous random number was %d\n", previous_Random);
			//pf("Random number 2 nodes before was %d\n", before_Previous_Random);
			//DEBUG CODE//

			callCount ++;
			i++;
			previous_Random = 4;
			p = buildList(p, random);
			AbandStruct(p_ptr_two);
			break;
		}
	case 5:
		{
			//DEBUG CODE//
			//pf("\nCase 5\n");
			//pf("Previous random number was %d\n", previous_Random);
			//pf("Random number 2 nodes before was %d\n", before_Previous_Random);
			//DEBUG CODE//

			callCount ++;
			i++;
			previous_Random = 5;
			p = buildList(p, random);
			Radiation(p_ptr_two);
			break;
		}
	case 6:
		{
			//DEBUG CODE//
			//pf("\nCase 6\n");
			//pf("Previous random number was %d\n", previous_Random);
			//pf("Random number 2 nodes before was %d\n", before_Previous_Random);
			//DEBUG CODE//

			if(callCount > 3)
			{
				callCount = 0;
				i++;
				previous_Random = 6;
				p = buildList(p, random);
				HosHuman(p_ptr_two);
				break;
			}
			else
			{
				callCount ++;
				i++;
				previous_Random = 6;
				p = buildList(p, random);
				Travel(p_ptr_two);
				break;
			}
		}
	}
}

node *buildList(node *head, int num)
{
	node *tmp;
	tmp = (node *)malloc(sizeof(node));
	if(tmp == NULL)
	{
		printf("Error with node *tmp mem alloc\n");
		exit(1);
	}

	tmp->data = num;

	if(head == NULL)
	{
		tmp->next = head;
		head = tmp;
		return tmp;
	}
	else
	{
		node *tail = head;
		while(tail->next != NULL)
		{
			tail = tail->next;
		}
		tmp->next = tail->next;
		tail->next = tmp;
		return head;
	}
	free(tmp);
}

int GetNth(node *head, int index)
{
	node *current = head;
	int count = 0;

	if(index < 0)
	{
		return count;
	}
	else
	{
		while(current != NULL)
		{
			if(count == index)
			{
				return current->data;
			}
			count ++;
			current = current->next;
		}
	}
}

void GearCheck(Stats player)
{
  pf("\n--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- \n");
  pf("A check of your vitals and gear...\n");
  if(player.health < 0)
    {
      pf("Health:              0\n");
    }
  else if(player.health > 100)
    {
	  pf("Health:              100\n");
    }
  else
	{
      pf("Health:              %d\n", player.health);
	}
		   
  pf("Hand weapon:         ");
  switch(player.handWpn)
    {
    case 1:
      {
		pf("Tactical knife\n");
		break;
      }
    case 2:
      {
		pf("Steel axe\n");
		break;
      }
    case 3:
      {
		pf("Rare katana\n");
		break;
      }
    }
  pf("Ranged weapon:       ");
  switch(player.rangedWpn)
    {
    case 1:
      {
		pf("Empty\n");
		break;
      }
    case 2:
      {
		pf("12-gauge pump shotgun\n");
		break;
      }
    case 3:
      {
		pf("Semi-auto pistol\n");
		break;
      }
    case 4:
      {
		pf("Carbine rifle\n");
		break;
      }
    }
  pf("Ammo:                ");
  if(player.ammo == 0) 
  {
    pf("Empty\n");
  }
  else
  {
    pf("%d\n", player.ammo);
  }
  pf("Bartered goods:      ");
  if(player.barter == 0)
  {
    pf("Empty\n");
  }
  else
  {
    pf("%d\n", player.barter);
  }
  pf("--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- \n");

  Guide(player);
}

void Purchase(Stats *p_ptr_two)
{
	int choice = 0;
	int purchaseItem = 0;

	pf("--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- \n");
	pf("\This community has items for trade. Would you like to participate? \n");
	pf("--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- \n");
	pf("1---Yes, purchase items\n");
	pf("2---No, decline offer\n");
	do
	{
		sf("%d", &choice);
	}while((choice != 1) && (choice != 2));

	if(choice == 1)
	{
		
		pf("\nBarter: %d  Health: %d\n", p_ptr_two->barter, p_ptr_two->health);
		pf("**************************************\n");
		pf("*                                    *\n");
		pf("* Items for trade:                   *\n");
		pf("* 1---Health(+20)        -10  barter *\n");
		pf("* 2---Health(+45)        -25  barter *\n");
		pf("* 3---Ammo(+10)          -10  barter *\n");
		pf("* 4---Ammo(+20)          -30  barter *\n");
		pf("* 5---Steel Axe          -40  barter *\n");
		pf("* 6---Pistol(+Ammo)      -70  barter *\n");
		pf("* 7---Shotgun(+Ammo)     -80  barter *\n");
		pf("* 8---Rifle(+Ammo)       -110 barter *\n");
		pf("* 9---EXIT                           *\n");
		pf("*                                    *\n");
		pf("**************************************\n");
		do
		{
			sf("%d", &purchaseItem);
		}while((purchaseItem != 1)&&(purchaseItem != 2)&&(purchaseItem != 3)&&(purchaseItem != 4)&&(purchaseItem != 5)&&(purchaseItem != 6)&&(purchaseItem != 7)&&(purchaseItem != 8)&&(purchaseItem != 9));

		switch(purchaseItem)
		{
		case 1:
			{
				if(p_ptr_two->barter < 10)
				{
					pf("\n---> Not enough goods to barter!\n");
					break;
				}
				else
				{
					pf("\n---> Health increased by 20\n");
					p_ptr_two->health += 20;
					p_ptr_two->barter -= 10;
					break;
				}
			}
		case 2:
			{
				if(p_ptr_two->barter < 25)
				{
					pf("\n---> Not enough goods to barter!\n");
					break;
				}
				else
				{
					pf("\n---> Health increased by 45\n");
					p_ptr_two->health += 45;
					p_ptr_two->barter -= 25;
					break;
				}
			}
		case 3:
			{
				if(p_ptr_two->barter < 10)
				{
					pf("\n---> Not enough goods to barter!\n");
					break;
				}
				else
				{
					pf("\n---> Ammo increased by 10\n");
					p_ptr_two->ammo += 10;
					p_ptr_two->barter -= 10;
					break;
				}
			}
		case 4:
			{
				if(p_ptr_two->barter < 30)
				{
					pf("\n---> Not enough goods to barter!\n");
					break;
				}
				else
				{
					pf("\n---> Ammo increased by 20\n");
					p_ptr_two->ammo += 20;
					p_ptr_two->barter -= 30;
					break;
				}
			}
		case 5:
			{
				if(p_ptr_two->barter < 40)
				{
					pf("\n---> Not enough goods to barter!\n");
					break;
				}
				else
				{
					pf("\n---> Steel Axe is now equipped\n");
					p_ptr_two->handWpn = 2;
					p_ptr_two->barter -= 40;
				break;
				}
			}
		case 6:
			{
				if(p_ptr_two->barter < 70)
				{
					pf("\n---> Not enough goods to barter!\n");
					break;
				}
				else
				{
					pf("\n---> 9mm semi-auto Smith & Wesson is now equipped\n");
					pf("---> 5 rounds of ammunition loaded\n");
					p_ptr_two->rangedWpn = 3;
					p_ptr_two->ammo += 10;
					p_ptr_two->barter -= 70;
				break;
				}
			}
		case 7:
			{
				if(p_ptr_two->barter < 80)
				{
					pf("\n---> Not enough goods to barter!\n");
					break;
				}
				else
				{
					pf("\n---> 12-gauge pump shotgun made by Benelli is now equipped\n");
					pf("---> 5 rounds of ammunition loaded\n");
					p_ptr_two->rangedWpn = 2;
					p_ptr_two->ammo += 5;
					p_ptr_two->barter -= 80;
				break;
				}
			}
		case 8:
			{
				if(p_ptr_two->barter < 110)
				{
					pf("\n---> Not enough goods to barter!\n");
					break;
				}
				else
				{
					pf("\n---> AR-15 carbine rifle chambered in .223 is now equipped\n");
					pf("---> 10 rounds of ammunition loaded\n");
					p_ptr_two->rangedWpn = 4;
					p_ptr_two->ammo += 10;
					p_ptr_two->barter -= 110;
				break;
				}
			}
		case 9:
			{
				pf("\n---> No items purchased.\n");
				break;
			}
		}
	}
	else
	{
		pf("\n---> No items purchased.\n");
	}
}


////////////////////////
//Random Number Gen////
///////////////////////
int Random_Num()
{
  int random = 0;

  random = rand()%10 +1;
  return random;
}


//////////////////////
//Good Scenarios/////
/////////////////////
void SafeZone(Stats *p_ptr_two)
{
	static int count = 0;
	int random = 0;

	do
	{
		random = Random_Num();
	}while(random > 3);

	switch(random)
	{
	case 1:
		{
			pf("\nYou have entered a small town.\n");
			pf("And have been permitted a temporary stay with shelter.\n\n");
			Purchase(p_ptr_two);
			count++;
			Guide(*p_ptr_two);
			break;
		}
	case 2:
		{
			pf("\nCongrats, you have found a thriving town!\n");
			pf("All non-violent persons are allowed to stay for no more than one week.\n\n");
			Purchase(p_ptr_two);
			count++;
			Guide(*p_ptr_two);
			break;
		}
	case 3:
		{
			if(count > 4)
			{
				pf("\nThere is hope for humanity yet...\n");
				pf("%s has found the town unaffected by devastation!\n", p_ptr_two->name);
				pf("Congratulations! You have finished the game!\n");
				Win();
				break;
			}
			else
			{
				pf("Another small town, destroyed and empty. This will be a good spot to rest.\n");
				p_ptr_two->health += 5;
				Guide(*p_ptr_two);
				break;
			}
		}
	}
}

void AbandStruct(Stats *p_ptr_two)
{
	static int count = 0;
	int weapon = 0;
	int benefit = 0;
	int random = 0;
	int choice = 0;
	
	random = Random_Num();
	while(random > 3)
	{
		random = Random_Num();
	}

	benefit = Random_Num();
	while(benefit > 5)
	{
		benefit = Random_Num();
	}

	weapon = Random_Num();
	while(weapon > 2)
	{
		weapon = Random_Num();
	}

	switch(random)
	{
	case 1:
		{
			pf("\nThere appears to be an abandoned shopping center ahead.\n");
			pf("The possibility of usable items/weapons is high!\n");
			switch(benefit)
			{
			case 1:
				{
					pf("Health supplies found.\n");
					p_ptr_two->health += 10;
					count ++;
					break;
				}
			case 2:
				{
					pf("Some ammunition gathered.\n");
					p_ptr_two->ammo += 5;
					count ++;
					break;
				}
			case 3:
				{
					pf("Found useful items to barter with.\n");
					p_ptr_two->barter += 15;
					count ++;
					break;
				}
			case 4:
				{
					pf("Unfortunately, this time...there are no resources here.\n");
					count ++;
					break;
				}
			case 5:
				{
					if(weapon == 1)
					{
						pf("\nYou found a Steel Axe!\n");
						pf("Would you like to equip this weapon?\n");
						pf("1---Yes\n");
						pf("2---No\n");
						do
						{
							sf("%d", &choice);
						}while((choice != 1) && (choice != 2));
						if(choice == 1)
						{
							p_ptr_two->handWpn = 2;
						}
						else
						{
							pf("You did not equip the Steel Axe.\n");
						}
						count ++;
					}
					if(weapon == 2)
					{
						pf("\nYou found a 9mm semi-auto Smith & Wesson!\n");
						pf("Would you like to equip this weapon?\n");
						pf("1---Yes\n");
						pf("2---No\n");
						do
						{
							sf("%d", &choice);
						}while((choice != 1) && (choice != 2));
						if(choice == 1)
						{
							p_ptr_two->rangedWpn = 3;
						}
						else
						{
							pf("You did not equip the 9mm semi-auto Smith & Wesson.\n");
						}
						count ++;
					}
					break;
				}
			}

			break;
		}
	case 2:
		{
			pf("\nThere appears to be an abandoned neighborhood ahead.\n");
			pf("The possibility of usable items/weapons is moderate!\n");
			switch(benefit)
			{
			case 1:
				{
					pf("Health supplies found.\n");
					p_ptr_two->health += 25;
					count ++;
					break;
				}
			case 2:
				{
					pf("Unfortunately, this time...there are no resources here.\n");
					count ++;
					break;
				}
			case 3:
				{
					pf("Found useful items to barter with.\n");
					p_ptr_two->barter += 10;
					count ++;
					break;
				}
			case 4:
				{
					pf("Unfortunately, this time...there are no resources here.\n");
					count ++;
					break;
				}
			case 5:
				{
					if(weapon == 1)
					{
						pf("\nYou found a 12-gauge pump shotgun made by Benelli!\n");
						pf("Would you like to equip this weapon?\n");
						pf("1---Yes\n");
						pf("2---No\n");
						do
						{
							sf("%d", &choice);
						}while((choice != 1) && (choice != 2));
						if(choice == 1)
						{
							p_ptr_two->rangedWpn = 2;
						}
						else
						{
							pf("You did not equip the 12-gauge pump shotgun made by Benelli.\n");
						}
						count ++;
					}
					if(weapon == 2)
					{
						pf("Unfortunately, this time...there are no resources here.\n");
						count ++;
					}
					break;
				}
			}
			break;
		}
	case 3:
		{
			pf("\nThere appears to be an abandoned vehicle ahead.\n");
			pf("The possibility of usable items/weapons is low!\n");
			switch(benefit)
			{
			case 1:
				{
					pf("Unfortunately, this time...there are no resources here.\n");
					count ++;
					break;
				}
			case 2:
				{
					pf("Unfortunately, this time...there are no resources here.\n");
					count ++;
					break;
				}
			case 3:
				{
					pf("Found useful items to barter with.\n");
					p_ptr_two->barter += 20;
					count ++;
					break;
				}
			case 4:
				{
					pf("Unfortunately, this time...there are no resources here.\n");
					count ++;
					break;
				}
			case 5:
				{
					if(count > 4)
					{
						pf("\nYou found a rare Japanese Katana blade, awesome!\n");
						pf("Would you like to equip this weapon?\n");
						pf("1---Yes\n");
						pf("2---No\n");
						do
						{
							sf("%d", &choice);
						}while((choice != 1) && (choice != 2));
						if(choice == 1)
						{
							p_ptr_two->handWpn = 3;
						}
						else
						{
							pf("You did not equip the rare Japanese Katana blade.\n");
						}
						count = 0;
					}
					else
					{
						pf("Nice, a contatiner of ammunition.\n");
						p_ptr_two->ammo += 15;
						count++;
					}
					break;
				}
			}
			break;
		}
	}

	Guide(*p_ptr_two);
}


/////////////////////
//Bad Scenarios/////
////////////////////
void HosTown(Stats *p_ptr_two)
{
	int damage = 30;
	if (p_ptr_two->handWpn > 1)
		damage = 25;
	else if (p_ptr_two->handWpn > 2)
		damage = 20;
	else if (p_ptr_two->rangedWpn > 1)
		damage = 20;
	else if (p_ptr_two->rangedWpn > 2)
		damage = 15;
	else if (p_ptr_two->rangedWpn > 3)
		damage = 10;


	pf("\nThis town appears to be hostile!\n");
	p_ptr_two->health -= damage;
	HealthDamage(p_ptr_two->health);
	if (p_ptr_two->health > 0)
		Guide(*p_ptr_two);
}

void HosHuman(Stats *p_ptr_two)
{
	int damage = 25;
	if (p_ptr_two->handWpn > 1)
		damage = 20;
	else if (p_ptr_two->handWpn > 2)
		damage = 15;
	else if (p_ptr_two->rangedWpn > 1)
		damage = 15;
	else if (p_ptr_two->rangedWpn > 2)
		damage = 10;
	else if (p_ptr_two->rangedWpn > 3)
		damage = 5;

	pf("\nHide! A horde of hostile humans approaches.\n");
	p_ptr_two->health -= damage;
	HealthDamage(p_ptr_two->health);
	if (p_ptr_two->health > 0)
		Guide(*p_ptr_two);
}

void Radiation(Stats *p_ptr_two)
{
	int damage = 5;
	pf("\nGeiger counter reads excessive levels of radiation.\n");
	p_ptr_two->health -= damage;
	HealthDamage(p_ptr_two->health);
	if (p_ptr_two->health > 0)
		Guide(*p_ptr_two);
}

void WildAnimal(Stats *p_ptr_two)
{
	int damage = 15;
	if (p_ptr_two->handWpn > 1)
		damage = 15;
	else if (p_ptr_two->handWpn > 2)
		damage = 10;
	else if (p_ptr_two->rangedWpn > 1)
		damage = 10;
	else if (p_ptr_two->rangedWpn > 2)
		damage = 5;
	else if (p_ptr_two->rangedWpn > 3)
		damage = 1;

	pf("\nKill them all! A pack of wild animals threatens your survival.\n");
	p_ptr_two->health -= damage;
	HealthDamage(p_ptr_two->health);
	if (p_ptr_two->health > 0)
		Guide(*p_ptr_two);
}


