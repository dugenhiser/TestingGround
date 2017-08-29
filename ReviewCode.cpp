/***********************************************************************
 * This program will parse the given ged file and will give a file
 * that contains an alphabetical list which contains first and last names,
 * and birthdays if the person has them. Then it will display the family tree
 * if the first person of the ged file.
 ***********************************************************************/
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<cstdlib>

using namespace std;
/*
  This is the tree class and a list class combined as one, it allows us
  to set everything that is needed and able to create the btree
*/
class FamTreeList
{
public:
   FamTreeList();
   string getFname();
   string getLname();
   string getBirthday();
   string getId();
   int getYear();
   FamTreeList* getNext();
   FamTreeList* getMother();
   FamTreeList* getFather();
   
   void setID(string myId);
   void setBirthday(string myBirthday);
   void setLname(string last);
   void setFname(string first);
   void setNext(FamTreeList* FamTreeList);
   void setYear(int myYear);
   void setMother(FamTreeList* node);
   void setFather(FamTreeList* node);
   // void level();
   
   
private:
   string firstName, lastName, birthday, id;
   FamTreeList* mother, *father;
   FamTreeList* next;
   int year;
};

/*
  This will allow us to sort alphabeticaly and do a level order traversal
*/

class Sorted
{
public:
   Sorted();
   void openfile();
   void readInfo();
   void level(FamTreeList *node);
   void insert(FamTreeList *node);
   bool compare(FamTreeList *node1, FamTreeList *node2);
   FamTreeList* search(string item);
   FamTreeList *getRoot();
   FamTreeList *getLevelRoot();


private:
   FamTreeList* root, *levelRoot;
   FamTreeList* temp, *prev;
   ofstream sorted;
   ifstream fin;
   string info;
   bool bigger;


};

/*
  Main creates a sorted class called sort that will then open a file
  then call a funtion to read info that will read it into a file that
  will be sorted then it will display level order traversal.
*/

int main(int argv, char *argc [])
{
   Sorted sort;
   sort.openfile();
   sort.readInfo();
   FamTreeList* root = sort.getRoot();
   FamTreeList* it = root;
   ofstream fout;


   sort.level(sort.getLevelRoot());

   fout.open("sorted.dat");


   while (it != NULL)
   {
     
	  fout << it->getFname() << " ";
	  
      if (!it->getLname().empty())
         fout << it->getLname();
      if (!it->getLname().empty() && !it->getBirthday().empty())
      {
         fout << ", b." << it->getBirthday();
      }
      else
         fout << " " << it->getBirthday();
      fout << endl;

      it = it->getNext();

   }

   fout.close();
   return 0;
}

/*******************************************************
 *
 *
 ******************************************************/
FamTreeList::FamTreeList()
{

}

/*******************************************************
 * set next
 ******************************************************/
void FamTreeList::setNext(FamTreeList* FamTreeList)
{
   next = FamTreeList;
}

/*******************************************************
 *return next
 ******************************************************/
FamTreeList* FamTreeList::getNext()
{
   return next;
}

/*******************************************************
 *return mother
 ******************************************************/
FamTreeList* FamTreeList::getMother()
{
   return mother;
}

/*******************************************************
 * return father
 ******************************************************/
FamTreeList* FamTreeList::getFather()
{
   return father;
}

/*******************************************************
 * return firstName
 ******************************************************/
string FamTreeList::getFname()
{
   return firstName;
}

/*******************************************************
 *return lastname
 ******************************************************/
string FamTreeList::getLname()
{
   return lastName;
}

/*******************************************************
 *return birthday
 *
 ******************************************************/
string FamTreeList::getBirthday()
{
   return birthday;
}

/*******************************************************
 * returns id
 ******************************************************/
string FamTreeList::getId()
{

   return id;
}

/*******************************************************
 *sets id
 ******************************************************/
void FamTreeList::setID(string myId)
{
   id = myId;
}

/*******************************************************
 *set birthday
 ******************************************************/
void FamTreeList::setBirthday(string myBirthday)
{
   birthday = myBirthday;
}

/*******************************************************
 *set last name
 ******************************************************/
void FamTreeList::setLname(string last)
{
   lastName = last;
}

/*******************************************************
 *set first name
 ******************************************************/
void FamTreeList::setFname(string first)
{
   firstName = first;
}

/*******************************************************
 *set year
 ******************************************************/
void FamTreeList::setYear(int myYear)
{
   year = myYear;
}

/*******************************************************
 * return year
 ******************************************************/
int FamTreeList::getYear()
{
   return year;
}

/*******************************************************
 * opens the file
 ******************************************************/
void Sorted::openfile()
{
   fin.open("cameron.ged");
}

/*******************************************************
 * sets root to NULL
 ******************************************************/
Sorted::Sorted()
{
   root = NULL;
}

/*******************************************************
 *parses the file into serperate parts for the sorted
 * and level order
 ******************************************************/
void Sorted::readInfo()
{
   while (fin >> info)
   {      
      if (info == "0")
      {
         fin >> info;
         
         // For getting the individual information
         if (info[0] == '@' && info[1] == 'I')
         {
            FamTreeList *person = new FamTreeList;
            person->setID(info);
            
            while (info != "GIVN" && info != "SURN")
               fin >> info;
            //Finds first name
            if (info == "GIVN")
            {
               getline(fin, info);
               if (info[0] == ' ')
                  info.erase(0, 1);
               person->setFname(info);    
            }
            
            while (info != "SURN" && info != "BIRT" && info != "3")
               fin >> info;
            
            
            if (info != "3")
            {
			   //finds last name
               if (info == "SURN")
               {
                  getline(fin, info);
				  if (info[0] == ' ')
				  {
					  info.erase(0, 1);
				  }
                  person->setLname(info);
               }
               
               while (info != "BIRT" && info != "3")
                  fin >> info;
               //Finds birthday               
               if (info == "BIRT")
               {
                  fin >> info >> info;
                  if (info == "DATE")
                  {
                     getline(fin, info);
                     person->setBirthday(info);
                     
                     int i = 4;
                     string temp;
                     while (i != 0)
                     {
                        temp.push_back(info[info.length() - i]);
                        i--;
                     }
                     int year = atoi(temp.c_str()); 
                     person->setYear(year);                     
                  }
                  
                                  
               }
            }
			insert(person);
         }
         
         // for putting into the family tree      
         if (info[0] == '@' && info[1] == 'F')
         {
            
            string poo = info;
            FamTreeList * mother = new FamTreeList;
            FamTreeList *father = new FamTreeList;
            while (info != "HUSB" && info != "WIFE"  && info != "CHIL")
            {
               fin >> info;
            }
           
            if (info == "HUSB")
            {
               fin >> info;
               father = search(info);
            
               
               
            }
            
            while (info != "WIFE"  && info != "CHIL")
            {
               fin >> info;
            }
            
            if (info == "WIFE")
            {
               fin >> info;
               
               mother = search(info);
             
               
            }
            
            while (info != "CHIL")
            {
               fin >> info;
            }
            
            if (info == "CHIL")
            {
               fin >> info;
               if (levelRoot == NULL)
               {
                  levelRoot = search(info);
                  levelRoot->setFather(father);
                  levelRoot->setMother(mother);
                 
               }
               else
               {
                  temp = search(info);
                  temp->setFather(father);
                  temp->setMother(mother);
                 
               }
            }
         }
      }
   }
}

/*******************************************************
 * Returns root
 ******************************************************/
FamTreeList* Sorted::getRoot()
{
   return root;
}

/*******************************************************
 * Returns level root
 ******************************************************/
FamTreeList* Sorted::getLevelRoot()
{
   return levelRoot;
}

/*******************************************************
 * Will insert node into a list in alpabetical order.
 ******************************************************/
void Sorted::insert(FamTreeList * node)
{

   if (root == 0)
   {
      node->setNext(root);
      root = node;
   }

   else
   {
      temp = root->getNext();
      prev = root;

      if (compare(node, root))
      {
         node->setNext(root);
         root = node;
      }

      else
      {
         while (temp != 0)
         {

            if (compare(temp, node))
            {

               prev = temp;
               temp = temp->getNext();
            }

            else
               break;

         }

         node->setNext(temp);
         prev->setNext(node);

      }
   }

}

//compares left to right to see which is smaller;
bool Sorted::compare(FamTreeList *node1, FamTreeList *node2)
{
   //This is to make sure it is in right order.
   //Mainly for the van Ostern name
   string fName1 = node1->getFname();
   string fName2 = node2->getFname();
   string lName1 = node1->getLname();
   string lName2 = node2->getLname();

   int i = 0;
   while (lName1[i])
   {
      lName1[i] = toupper(lName1[i]);
      i++;
   }

   i = 0;

   while (lName2[i])
   {
      lName2[i] = toupper(lName2[i]);
      i++;
   }




   if (lName1.empty() || lName2.empty())
   {
      if (lName1.empty())
      {
         if (lName2.empty())
         {
            if (fName1 < fName2)
               return true;
            else
               return false;
         }
         return true;
      }



      else
         return false;
   }

   else
   {
      if (lName1 == lName2)
      {
         if (fName1 == fName2)
         {
            if (node1->getYear() < node2->getYear())
            {
               return true;
            }

            else
               return false;
         }

         else if (fName1 < fName2)
         {
            return true;
         }

         else
            return false;
      }

      else if (lName1 < lName2)
      {
         return true;
      }

      else
         return false;
   }

}

/*******************************************************
 * returns the correct node for the searched item
 ******************************************************/
FamTreeList* Sorted::search(string item)
{

   temp = root;

   while (temp->getId() != item)
   {
      temp = temp->getNext();
   }



   return temp;
}

/*******************************************************
 * sets father
 ******************************************************/
void FamTreeList::setFather(FamTreeList* node)
{
   father = node;
}
/*******************************************************
 * sets mother
 ******************************************************/
void FamTreeList::setMother(FamTreeList* node)
{
   mother = node;
}

/*******************************************************
 * Level order traversal
 ******************************************************/
void Sorted::level(FamTreeList *node)
{
   const int MAX = 100;
   FamTreeList *queue[MAX];
   FamTreeList *temp;
   int front = 0;
   int back = 0;
   int lastBack = 1;
   int i = 0;
   bool first = 0;
   
   string grandparentLevel[7] = { "Parents:", "GrandParents:", "Great GrandParents:"
                                  , "2nd Great GrandParents:", "3rd Great GrandParents:"
                                  , "4th Great GrandParents:", "5th Great GrandParents:" };
   
   queue[back++] = node;

   
   while (front != back)
   {
     
      temp = queue[front];
      front = (front + 1) % MAX;
	
	 
      if (temp != NULL)
      {
		  
		
			  cout << "       ";
			  if (!temp->getFname().empty())
				  cout << temp->getFname() << " ";
			  if (!temp->getLname().empty())
				  cout << temp->getLname();
			  if (!temp->getBirthday().empty())
				  cout << ", b. " << temp->getBirthday() << " ";
			  cout << endl;
		  
         queue[back] = temp->getFather();
         back = (back + 1) % MAX;
         queue[back] = temp->getMother();
         back = (back + 1) % MAX;
         
         if (front == lastBack)
         {
            cout << grandparentLevel[i] << endl;
            grandparentLevel[i++];
            lastBack = back;
         }
         
      }
   }
}


