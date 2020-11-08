#include <iostream>
#include <fstream>

using namespace std;

class Helper
{
public:
	static char* GetStringFromBuffer(char* str)
	{
		char * copy = new char[strlen(str) + 1];
		strcpy(copy, str);
		return copy;
	}
};

class Date
{
	int Day;
	int Month;
	int Year;

public:
	Date()
	{
		Day = 25;
		Month = 07;
		Year = 2019;
	}
	Date(int day, int mnth, int year)
	{
		Day = day;
		Month = mnth;
		Year = year;
	}
	static Date CurrentDate;
	void SetDateDate(int day, int mnth, int year)
	{
		Day = day;
		Month = mnth;
		Year = year;
	}
	void PrintDate()
	{
		cout << "\t" << Day << "/" << Month << "/" << Year << endl;
	}
	bool compareDate(const Date & date)										//Check Posts For Latest Date
	{
		if (Day == date.Day || Day == date.Day - 1)
			if (Month == date.Month)
				if (Year == date.Year)
				{
					return true;
				}
		return false;
	}
};

Date Date::CurrentDate(25, 07, 2019);

class SocialNetworkApp;
class Object;
class Users;
class Pages;
class Posts;
class Activity;
class Comments;

class Activity
{
	int Type;
	char * Value;
public:
	~Activity()
	{
		if (Value != nullptr)
		{
			delete[]Value;
			Value = nullptr;
		}
	}
	Activity()
	{
		Type = 0;
		Value = nullptr;
	}
	int getType()
	{
		return Type;
	}
	void setActivity(int type, char * value)
	{
		Type = type;
		Value = Helper::GetStringFromBuffer(value);
	}
	void printActivity()
	{
		if (Type == 1)
		{
			cout << " feeling " << Value;
		}
		if (Type == 2)
		{
			cout << " thinking about " << Value;
		}
		if (Type == 3)
		{
			cout << " making " << Value;
		}
		if (Type == 4)
		{
			cout << " celebrating " << Value;
		}
	}

};

class Object
{
	char * ID;
public:
	Object()
	{
		ID = nullptr;
	}
	Object(char * id)
	{
		ID = Helper::GetStringFromBuffer(id);
	}

	void SetId(char * id)
	{
		ID = Helper::GetStringFromBuffer(id);
	}
	char * GetId()
	{
		return ID;
	}
	void PrintId()
	{
		cout << ID;
	}

	~Object()
	{
		if (ID != nullptr)
		{
			delete[]ID;
			ID = nullptr;
		}
	}

	virtual void PrintName() = 0;
	virtual void Display() = 0;
};

class Comments : public Object
{
	char * Text;
	Object * CommentBy;
	Posts * Post;
public:

	Comments()
	{
		Text = nullptr;
		CommentBy = nullptr;
		Post = nullptr;
	}
	Comments(char * Id, char * coment, Object * acount, Posts * post) :Object(Id)
	{
		Text = Helper::GetStringFromBuffer(coment);
		CommentBy = acount;
		Post = post;
	}
	~Comments()
	{
		if (Text != nullptr)
		{
			delete[]Text;
			Text = nullptr;
		}
	}
	Posts* getPost()
	{
		return Post;
	}
	void PrintName() {}

	void Display()
	{
		cout << "\t";
		CommentBy->PrintName();
		cout << " wrote: " << Text << "\n\n";
	}
};

class Posts :public Object
{
	char * Description;
	int totalLikes;
	int totalComments;
	Date _Date;
	Comments ** _Comment;
	Object * Share;
	Object ** Likes;
	Activity _Actvity;
public:
	Posts()
	{
		Description = nullptr;
		totalLikes = 0;
		totalComments = 0;
		_Comment = nullptr;
		Share = nullptr;
		Likes = nullptr;
	}
	static int Totalposts;
	Posts(char * Id, char * description, int day, int month, int year, int types, char * value, Object* share, Object** likeBy, int noOflike) :Object(Id)
	{
		Description = Helper::GetStringFromBuffer(description);
		_Date.SetDateDate(day, month, year);
		_Actvity.setActivity(types, value);
		Share = share;
		Likes = likeBy;
		totalLikes = noOflike;
	}
	Date getDate()
	{
		return _Date;
	}
	void setComments(Comments** coments, int noOfComnts)
	{
		_Comment = coments;
		totalComments = noOfComnts;
	}
	void addComments(Comments * coments)
	{
		Comments ** temp = new Comments*[totalComments + 1];
		for (int i = 0; i < totalComments; i++)
			temp[i] = _Comment[i];
		temp[totalComments] = coments;
		_Comment = temp;
		totalComments++;
	}
	int getTotalComments()
	{
		return totalComments;
	}
	void PrintName() {}
	Object * getSharedBy()
	{
		return Share;
	}
	void SetValues(char * Id, Date date, Posts * post, Object* share)
	{
		SetId(Id);
		_Date = date;
		Description = Helper::GetStringFromBuffer(post->Description);
		Share = share;
	}
	void PrintTimeline()
	{
		Object::PrintId();
		_Date.PrintDate();
		_Actvity.printActivity();
		cout << Description;
		Share->Display();
		ViewLikers();
	}
	void ViewLikers()
	{
		for (int i = 0; i < totalLikes; i++)
		{
			Likes[i]->Display();
		}
	}
	bool Search(char * keyWord)
	{
		int count = 0;	bool found = false;
		for (int i = 0; Description[i] != '\0'; i++)
		{
			for (int j = 0; keyWord[j] != '\0' && Description[i + j] != '\0'; j++)				//Compare Every Alphabet Of Word
			{
				if (keyWord[j] == Description[i + j])
				{
					found = true;
					count++;
				}
				else
				{
					found = false;
					count = 0;
				}
			}
			if (count == strlen(keyWord) && found == true)
			{
				return found;
			}
		}
	}
	void showSearchResults()
	{
		cout << "\n---" << GetId() << "\t";
		Share->PrintName();
		cout << " - " << Description << " \n ";
	}
	void LikePost(Users * liker);
	void Display()
	{
		cout << "\n";
		Share->PrintName();
		cout << " is";
		_Actvity.printActivity();
		cout << "\n\"" << Description << "\"\n";
		_Date.PrintDate();
		int i = 0;
		while (i < totalComments)
		{
			cout << "\t";
			_Comment[i]->Display();
			i++;
		}
	}
	void viewPage()
	{
		int i = 0;
		cout << "\n---   \"" << Description << "\"\n";
		while (i < totalComments)
		{
			_Comment[i]->Display();
			i++;
		}
	}
	~Posts()
	{
		if (Description != nullptr)
		{
			delete[]Description;
			Description = nullptr;
		}
		for (int i = 0; i < totalComments; i++)
		{
			delete[]_Comment[i];
		}

		for (int i = 0; i < totalLikes; i++)
		{
			delete[]Likes[i];
		}
	}
};
int Posts::Totalposts = 0;

class Pages : public Object
{
	char * Title;
	Posts ** TimelinePosts;
	int totalPosts;
	
public:
	Pages()
	{
		Title = nullptr;
		totalPosts = 0;
		TimelinePosts = new Posts*[11];
		for (int i = 0; i < 11; i++)
		{
			TimelinePosts[i] = nullptr;
		}
	}
	static int Totalpages;
	Posts * getPosts(int index)
	{
		return TimelinePosts[index];
	}

	~Pages()
	{
		if (Title != nullptr)
		{
			delete[]Title;
			Title = nullptr;
		}
		for (int i = 0; i < totalPosts; i++)
		{
			delete[]TimelinePosts[i];
			TimelinePosts[i] = nullptr;
		}
		delete[]TimelinePosts;
		TimelinePosts = nullptr;
	}

	void ReadPageFromFile(ifstream & fin)
	{
		char * buffer = new char[60];
		fin >> buffer;
		Object::SetId(buffer);
		Title = new char[50];
		fin.getline(Title, 50);
		delete[]buffer;
		buffer = nullptr;
	}

	char * getTitle()
	{
		return Title;
	}

	int getTotalPosts()
	{
		return totalPosts;
	}

	void PrintName()
	{
		cout << Title;
	}

	void Display()
	{
		cout << "\n" << GetId() << Title;
	}

	void setPosts(int noOfPost, Posts** post)
	{
		totalPosts = noOfPost;
		TimelinePosts = post;
	}

	void PrintTimeline()
	{
		for (int i = 0; i <totalPosts; i++)
		{
			TimelinePosts[i]->Display();
		}
	}
	void sharedPost(int id)
	{
		TimelinePosts[id]->Display();
	}

	Posts* getPost(int index)
	{
		if (index < totalPosts)
		{
			return TimelinePosts[index];
		}
		else
			return 0;
	}
	bool Search(char * keyWord)
	{
		for (int i = 0; Title[i] != '\0'; i++)
		{
			bool found = true;
			int j = 0;
			while (Title[i + j] != '\0' && keyWord[j] != '\0')
			{
				if (Title[i + j] != keyWord[j])
				{
					found = false;
					break;
				}
				j++;
			}
			if (found == true)
				return found;
		}
		return 0;
	}
	void showSearchResults()
	{
		cout << "\nPages:\n";
		cout << "\n---" << GetId() << "\t" << Title << "\n";
	}

};
int Pages::Totalpages = 0;
class Users : public Object
{
	static int totalUsers;
	char * Fname;
	char * Lname;
	char ** LikedPages;
	int totalLikedPages;
	int totalFriends;
	char ** FriendList;
	Users ** _Friendlist;
	Pages ** _LikedPages;
	Posts ** TimelinePosts;
	int totalPosts;

public:

	Users()
	{
		Fname = nullptr;
		Lname = nullptr;
		totalLikedPages = 0;
		totalFriends = 0;
		totalPosts = 0;
		FriendList = new char*[10];
		for (int i = 0; i < 10; i++)
		{
			FriendList[i] = nullptr;
		}
		LikedPages = new char*[10];
		for (int i = 0; i < 10; i++)
		{
			LikedPages[i] = nullptr;
		}
		_Friendlist = new Users*[10];
		for (int i = 0; i < 10; i++)
		{
			_Friendlist[i] = nullptr;
		}
		_LikedPages = new Pages*[12];
		for (int i = 0; i < 12; i++)
		{
			_LikedPages[i] = nullptr;
		}
		TimelinePosts = new Posts*[11];
		for (int i = 0; i < 11; i++)
		{
			TimelinePosts[i] = nullptr;
		}
	}

	static Users * CurrentUser;

	Users(char * Id, char * fname, char * lname, char ** likedPages, int totalPages, int totalfriends, char ** friendlist) :Object(Id)
	{
		Fname = Helper::GetStringFromBuffer(fname);
		Lname = Helper::GetStringFromBuffer(lname);
		LikedPages = likedPages;
		totalLikedPages = totalPages;
		totalFriends = totalfriends;
		FriendList = friendlist;
		if (totalFriends != 0)
		{
			_Friendlist = new Users *[totalFriends];
		}
		for (int i = 0; i < totalFriends; i++)
		{
			_Friendlist[i] = new Users();
		}
		if (totalLikedPages != 0)
		{
			_LikedPages = new Pages*[totalLikedPages];
		}
		for (int i = 0; i < totalLikedPages; i++)
		{
			_LikedPages[i] = new Pages();
		}
		totalUsers++;
		TimelinePosts = new Posts*[11];
		for (int i = 0; i < 11; i++)
		{
			TimelinePosts[i] = nullptr;
		}
	}

	~Users()
	{
		if (Fname != nullptr)
		{
			delete[]Fname;
			Fname = nullptr;
		}

		if (Lname != nullptr)
		{
			delete[]Lname;
			Lname = nullptr;
		}
		for (int i = 0; i < totalLikedPages; i++)
		{
			if (LikedPages[i] != nullptr)
			{
				delete[] LikedPages[i];
			}
		}
		delete[] LikedPages;
		LikedPages = nullptr;
		for (int i = 0; i < totalFriends; i++)
		{
			if (FriendList[i] != nullptr)
			{
				delete[] FriendList[i];
			}
		}
		delete[] FriendList;
		FriendList = nullptr;
		for (int i = 0; i < totalPosts; i++)
		{
			delete[]TimelinePosts[i];
			TimelinePosts[i] = nullptr;
		}
	}
	void ReadUsersFromFile(ifstream & fin)
	{
		char * buffer = new char[60];
		fin >> buffer;
		fin >> buffer;
		Fname = Helper::GetStringFromBuffer(buffer);
		fin >> buffer;
		Lname = Helper::GetStringFromBuffer(buffer);

		delete[]buffer;
		buffer = nullptr;
		totalUsers++;
	}
	static int getTotalUsers()
	{
		return totalUsers;
	}

	char * getUserFname()
	{
		return Fname;
	}

	char * getUserLname()
	{
		return Lname;
	}

	char ** getFriendList()
	{
		return FriendList;
	}
	char *getFriendList(int index)
	{
		return FriendList[index];
	}

	char * getLikedPages(int index)
	{
		return LikedPages[index];
	}
	char ** getLikedPages()
	{
		return LikedPages;
	}

	int getTotalLikedPages()
	{
		return totalLikedPages;
	}

	int getTotalFriends()
	{
		return totalFriends;
	}

	Posts * getPosts(int index)
	{
		return TimelinePosts[index];
	}

	void Display()
	{
		cout << "\n" << GetId() << "\t" << Fname << " " << Lname;
	}

	void setPosts(int noOfPosts, Posts ** post)
	{
		totalPosts = noOfPosts;
		TimelinePosts = post;
	}

	void setPages(Pages*page, int index)
	{
		_LikedPages[index] = page;
	}

	void setFriends(Users*friends, int index)
	{
		_Friendlist[index] = friends;
	}

	void PrintName()
	{
		cout << Fname << " " << Lname;
	}

	void addPost(Posts* post)
	{
		int i = 0;
		Posts**tempPost = new Posts*[totalPosts + 1];
		while (i < totalPosts)
		{
			tempPost[i] = TimelinePosts[i];
			i++;
		}
		tempPost[totalPosts] = post;
		if (TimelinePosts != nullptr)
			delete[]TimelinePosts;
		TimelinePosts = tempPost;
		totalPosts++;
	}

	Users* getFriend(int index)
	{
		return _Friendlist[index];
	}

	void printHomepage(Date date)
	{
		cout << "\n----------------------------------------------------------------\n";
		PrintName();
		cout << " - Homepage\n\n";
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < _Friendlist[i]->totalPosts; j++)
			{
				if (_Friendlist[i]->getPosts(j)->getDate().compareDate(date))					//Compare Date Check Posts for Latest Date
				{
					_Friendlist[i]->TimelinePosts[j]->Display();
				}
			}
		}
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < _LikedPages[i]->getTotalPosts(); j++)
			{
				if (_LikedPages[i]->getPost(j)->getDate().compareDate(date))
				{
					_LikedPages[i]->sharedPost(j);
				}
			}
		}
	}

	void printTimeline()
	{
		cout << "\n----------------------------------------------------------------\n";
		PrintName();
		cout << " - Timeline\n\n";
		for (int i = 0; i < totalPosts; i++)
			TimelinePosts[i]->Display();
	}

	bool Search(char * keyWord)
	{
		bool found = false;

		if (strcmp(keyWord, Fname) == 0 || strcmp(keyWord, Lname) == 0)
			found = true;
		else
			found = false;
		if (found == true)
			return found;

		return 0;
	}

	void ShowSearchResult()
	{
		cout << "\n---" << GetId() << "\t\t" << Fname << " " << Lname << endl;
	}
};
int Users::totalUsers = 0;
Users * Users::CurrentUser = nullptr;

void Posts::LikePost(Users * liker)
{
	int i = 0;
	Object ** buffer = new Object*[totalLikes + 1];
	while (i < totalLikes)
	{
		buffer[i] = Likes[i];
		i++;
	}
	buffer[totalLikes] = liker;
	if (Likes != nullptr)
		delete[]Likes;
	Likes = buffer;
	totalLikes++;
}

class SocialNetworkApp
{
	Pages ** Pagelist;
	Users ** Userlist;
	Posts ** Postlist;
	Comments ** Comment;
	int totalLikedPages;
	int totalFriends;
	int totalPosts;
	int totalComments;
	int totalPages;
	int totalUsers;

public:
	SocialNetworkApp()
	{
		Pagelist = nullptr;
		Userlist = nullptr;
		totalUsers = 0;
		totalPages = 0;
		totalLikedPages = 0;
		totalFriends = 0;
	}
	~SocialNetworkApp()
	{
		for (int i = 0; i < totalLikedPages; i++)
		{
			if (Pagelist[i] != nullptr)
				delete Pagelist[i];
		}

		for (int i = 0; i < totalFriends; i++)
		{
			if (Userlist[i] != nullptr)
				delete Userlist[i];
		}
		if(Postlist!=nullptr)
		delete[]Postlist;
	}

	void LoadPages()
	{
		char * buffer = new char[80];
		ifstream fin;
		fin.open("Pages.txt");
		if (fin.is_open())
		{
			fin >> totalPages;
			fin.getline(buffer, 20);		//Extra Commented Lines
			fin.getline(buffer, 80);		//Extra Commented Lines
			fin.getline(buffer, 80);		//Extra Commented Lines

			Pagelist = new Pages *[totalPages];
			for (int i = 0; i < totalPages; i++)
			{
				Pagelist[i] = new Pages();
				Pagelist[i]->ReadPageFromFile(fin);
			}

			delete[]buffer;
			buffer = nullptr;
			fin.close();
		}
		else
		{
			cout << "Unable to Open Pages File\n";
		}
	}
	void LoadUsers()
	{
		char * buffer = new char[150];
		char * ID = new char[10];
		char * Fname = new char[15];
		char * Lname = new char[15];
		ifstream fin;
		fin.open("Users.txt");
		if (fin.is_open())
		{
			fin >> totalUsers;

			fin.getline(buffer, 20);		//Extra Commented Lines
			fin.getline(buffer, 80);		//Extra Commented Lines
			fin.getline(buffer, 150);		//Extra Commented Lines

			Userlist = new Users *[totalUsers];

			for (int i = 0; i < totalUsers; i++)
			{
				char ** FriendList = new char*[10];
				for (int i = 0; i < 10; i++)
				{
					FriendList[i] = new char[10];
				}
				char ** LikedPages = new char*[10];
				for (int i = 0; i < 10; i++)
				{
					LikedPages[i] = new char[10];
				}
				bool flag = false;

				fin >> buffer;
				ID = Helper::GetStringFromBuffer(buffer);
				fin >> buffer;
				Fname = Helper::GetStringFromBuffer(buffer);
				fin >> buffer;
				Lname = Helper::GetStringFromBuffer(buffer);
				for (int j = 0; !flag; j++)
				{
					fin >> buffer;
					if (buffer[0] != '-')
					{
						FriendList[j] = Helper::GetStringFromBuffer(buffer);
						totalFriends++;
					}
					else
						flag = true;
				}
				flag = false;
				for (int j = 0; !flag; j++)
				{
					fin >> buffer;
					if (buffer[0] != '-')
					{
						LikedPages[j] = Helper::GetStringFromBuffer(buffer);
						totalLikedPages++;
					}
					else
						flag = true;
				}
				Userlist[i] = new Users(ID, Fname, Lname, LikedPages, totalLikedPages, totalFriends, FriendList);
			}
			delete[]buffer;
			buffer = nullptr;
			delete[]ID;
			delete[]Fname;
			delete[]Lname;
			totalLikedPages = 0;
			totalFriends = 0;
			fin.close();
		}
		else
		{
			cout << "Unable to Open Users File\n";
		}

	}
	void LoadComments()
	{
		ifstream fin;
		char * buffer = new char[180];
		char * commentID = new char[5];
		char * postID = new char[10];
		char * commentorID = new char[5];
		char * Comnt = new char[70];
		Posts * Post;
		Object * CommentedBy;
		fin.open("Comments.txt");
		if (fin.is_open())
		{
			fin >> totalComments;
			fin.getline(buffer, 50);		//Extra Commented Lines
			fin.getline(buffer, 180);		//Extra Commented Lines
			fin.ignore();
			Comment = new Comments*[totalComments];
			for (int i = 0; i < totalComments; i++)
			{
				fin >> commentID;
				fin >> postID;
				Post = SearchPost(postID);
				fin >> commentorID;
				CommentedBy = Search(commentorID);
				fin.getline(Comnt, 70);
				Comment[i] = new Comments(commentID, Comnt, CommentedBy, Post);
			}
		}
	}
	void LoadPosts()
	{
		ifstream fin;
		char * buffer = new char[200];
		char * postID = new char[10];
		int Day = 0;
		int Month = 0;
		int Year = 0;
		int totalLikes = 0;
		char * Text = new char[100];
		char Liker[10][6];
		Object * PostedBy;
		Object ** LikedBy;
		int activityType;
		char * activityValue = new char[30];
		fin.open("Posts.txt");
		if (fin.is_open())
		{
			fin.getline(buffer, 200);		//Extra Commented Lines
			fin >> totalPosts;
			Postlist = new Posts *[totalPosts];
			for (int i = 0; i < 9; i++)		//Loop for Extra Commented Lines
			{
				fin.getline(buffer, 200);	//Extra Commented Lines
			}
			/*fin.getline(buffer, 200);
			fin.getline(buffer, 200);
			fin.getline(buffer, 200);
			fin.getline(buffer, 200);
			fin.getline(buffer, 200);
			fin.getline(buffer, 200);
			fin.getline(buffer, 200);
			fin.getline(buffer, 200);*/
			for (int i = 0; i < totalPosts; i++)
			{
				fin >> postID;
				fin >> Day;
				fin >> Month;
				fin >> Year;
				fin.ignore();
				fin.getline(Text, 100);
				fin >> activityType;
				if (activityType == 0)
					goto label;
				else
					fin.getline(activityValue, 30);
			label:			fin >> buffer;
				PostedBy = Search(buffer);
				int count = 0, j = 0;
				fin >> Liker[j];
				if (Liker[j] == 0)
				{
					goto label1;
				}
				else
				{
					while (strcmp(Liker[j], "-1") != 0)
					{
						count++;
						j++;
						fin >> Liker[j];
					}
					LikedBy = new Object*[count];
					for (int k = 0; k < count; k++)
					{
						LikedBy[k] = Search(Liker[k]);
						totalLikes++;
					}
				}
			label1:
				Postlist[i] = new Posts(postID, Text, Day, Month, Year, activityType, activityValue, PostedBy, LikedBy, totalLikes);
				fin.ignore();
				fin.getline(buffer, 200);
				totalLikes = 0;
			}
			fin.close();

		}
		else
			cout << "Unable to Open Users File\n";
	}
	Object * Search(char * ID)
	{
		if (ID[0] == 'p')
		{
			SearchPage(ID);
		}
		else if (ID[0] == 'u')
		{
			for (int i = 0; i < totalUsers; i++)
			{
				if (strcmp(Userlist[i]->GetId(), ID) == 0)
				{
					return Userlist[i];
				}
			}
		}
		else
			return 0;
	}

	Posts * SearchPost(char * ID)
	{
		for (int i = 0; i < totalPosts; i++)
		{
			if (strcmp(ID, Postlist[i]->GetId()) == 0)
			{
				return Postlist[i];
			}
		}
		return 0;
	}

	Pages * SearchPage(char * ID)
	{
		for (int i = 0; i < totalPages; i++)
		{
			if (strcmp(Pagelist[i]->GetId(), ID) == 0)
				return Pagelist[i];
		}
	}

	void LoadData()
	{
		LoadPages();
		LoadUsers();
		LoadPosts();
		LoadComments();
	}

	int SetCurrentUser(char * User)
	{
		int index = 0;
		bool flag = false;
		cout << "Command:\tSet Current User " << '"' << User << '"' << endl;
		for (int i = 0; i < 20 && !flag; i++)
		{
			if (strcmp(User, Userlist[i]->GetId()) == 0)
			{
				flag = true;
				index = i;
				cout << Userlist[i]->getUserFname() << " " << Userlist[i]->getUserLname() << " successfully set as Current User\n\n";
			}
		}
		return index;
	}

	void viewLikedPages(int index)
	{
		char ** LikedPages = nullptr;
		LikedPages = Userlist[index]->getLikedPages();
		cout << "Command:\t" << "View Liked Pages\n";
		cout << "----------------------------------------------------------------\n";
		cout << Userlist[index]->getUserFname() << " " << Userlist[index]->getUserLname() << " - Liked Pages\n\n";
		for (int i = 0; i < totalPages-2; i++)
		{
			for (int j = 0; Userlist[i]->getLikedPages(j); j++)
			{
				if (strcmp(LikedPages[i], Pagelist[j]->GetId()) == 0)
				{
					cout << LikedPages[i] << " - " << Pagelist[j]->getTitle() << '\n';
				}
			}
		}
		cout << endl;
	}

	void linkPages()
	{
		for (int i = 0; i < totalUsers; i++)
		{
			int index = 0;
			for (int j = 0; j<10; j++)
			{
				for (int k = 0; k < totalPages; k++)
				{
					if (strcmp(Pagelist[k]->GetId(), Userlist[i]->getLikedPages(j)) == 0)
					{
						Userlist[i]->setPages(Pagelist[k], index);
						index++;
						break;
					}
				}
			}
		}
	}

	void linkFriends()
	{
		for (int i = 0; i < totalUsers; i++)
		{
			int index = 0;
			for (int j = 0; j<10; j++)
			{
				for (int k = 0; k < totalUsers; k++)
				{
					if (strcmp(Userlist[k]->GetId(), Userlist[i]->getFriendList(j)) == 0)			//Link Friends With Users
					{
						Userlist[i]->setFriends(Userlist[k], index);
						index++;
						break;
					}
				}
			}
		}
	}

	void linkPosts()
	{
		Posts ** temp;
		for (int i = 0; i < totalUsers; i++)
		{
			int count = 0, j = 0;
			while (j < totalPosts)
			{
				if (Postlist[j]->getSharedBy() == Userlist[i])
				{
					count++;
				}
				j++;
			}
			if (count > 0)
			{
				temp = new Posts*[count];
				int j = 0, k = 0;
				while (j < totalPosts)
				{
					if (Postlist[j]->getSharedBy() == Userlist[i])
					{
						temp[k] = Postlist[j];
						k++;
					}
					j++;
				}
				Userlist[i]->setPosts(count, temp);
			}
		}
		for (int i = 0; i < totalPages; i++)
		{
			int count = 0;
			for (int j = 0; j < totalPosts; j++)
			{
				if (Postlist[j]->getSharedBy() == Pagelist[i])
				{
					count++;
				}
			}
			if (count > 0)
			{
				temp = new Posts*[count];
				int k = 0;
				for (int j = 0; j < totalPosts; j++)
				{
					if (Postlist[j]->getSharedBy() == Pagelist[i])
					{
						temp[k] = Postlist[j];
						k++;
					}
				}
				Pagelist[i]->setPosts(count, temp);
			}
		}
	}
	void linkComments()
	{
		for (int i = 0; i < totalPosts; i++)
		{
			int j = 0, count = 0;
			while (j < totalComments)
			{
				if (Comment[j]->getPost() == Postlist[i])
					count++;
				j++;
			}
			int k = 0;
			if (count > 0)
			{
				Comments**Coment = new Comments *[count];
				for (int j = 0; j < totalComments; j++)
				{
					if (Comment[j]->getPost() == Postlist[i])
					{
						Coment[k] = Comment[j];
						k++;
					}
				}
				Postlist[i]->setComments(Coment, count);
			}
		}
	}
	void Linker()
	{
		linkPages();
		linkFriends();
		linkPosts();
		linkComments();
	}
	void searchFacebook(char * keyWord)
	{
		cout << "\n----------------------------------------------------------------\n";
		cout << "\nSearch (\"" << keyWord << "\")";

		cout << "\nUsers:\n";
		for (int i = 0; i < totalUsers; i++)
		{
			if (Userlist[i]->Search(keyWord))
			{
				Userlist[i]->ShowSearchResult();
			}
		}
		for (int i = 0; i < totalPages; i++)
		{
			if (Pagelist[i]->Search(keyWord))
			{

				Pagelist[i]->showSearchResults();
			}
		}

		cout << "\nPosts:\n";
		for (int i = 0; i < totalPosts; i++)
		{
			if (Postlist[i]->Search(keyWord))
			{
				Postlist[i]->showSearchResults();
			}
		}
	}
	void showPost(char* buffer)
	{
		cout << "\n----------------------------------------------------------------\n";
		cout << "\nView (" << buffer << ")";
		Posts* temp = SearchPost(buffer);
		if (temp != 0)
		{
			temp->Display();
		}
		else
			cout << "\n No Such Post\n";
	}
	void likePost(char* buffer)
	{
		cout << "\n----------------------------------------------------------------\n";
		cout << "\nLike Post(" << buffer << ")";
		Posts* temp = SearchPost(buffer);
		temp->LikePost(Users::CurrentUser);
	}
	void likersList(char* buffer)
	{
		cout << "\n----------------------------------------------------------------\n";
		cout << "\n(" << buffer << ") - Liked By:\n";
		Posts* temp = SearchPost(buffer);
		temp->ViewLikers();
	}
	void viewPage(char* id)
	{
		cout << "\n----------------------------------------------------------------\n";
		cout << "\nView Page(" << id << ")\n";
		Pages* temp = SearchPage(id);
		temp->PrintTimeline();
	}

	void viewFriendlist(int index)
	{
		char ** Friends = nullptr;
		bool flag = false;
		Friends = Userlist[index]->getFriendList();
		cout << "\n----------------------------------------------------------------\n";
		cout << Userlist[index]->getUserFname() << " " << Userlist[index]->getUserLname() << " - Friend List\n\n";
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < Userlist[0]->getTotalUsers(); j++)
			{
				if (strcmp(Friends[i], Userlist[j]->GetId()) == 0)
				{
					cout << Friends[i] << " - " << Userlist[j]->getUserFname() << " " << Userlist[j]->getUserLname() << '\n';
					break;
				}
			}
		}
		cout << "\n----------------------------------------------------------------\n";
	}


	void postComment(char* postid, char* description)
	{
		cout << "\n----------------------------------------------------------------\n";
		cout << "\nPostComment(" << postid << ", " << description << ")";
		Posts* tempPost = SearchPost(postid);
		if (tempPost != 0) {
			Comments** temp = new Comments*[totalComments + 1];
			for (int i = 0; i < totalComments; i++)
				temp[i] = Comment[i];
			char *Id = Helper::GetStringFromBuffer("c");
			temp[totalComments] = new Comments(Id, description, Users::CurrentUser, tempPost);
			delete[] Comment;
			Comment = temp;
			tempPost->addComments(temp[totalComments]);
			totalComments++;
		}
	}
	void sharePost(char* postid)
	{
		cout << "\n----------------------------------------------------------------\n";
		cout << " Share Post(" << postid << ")";
		Posts* copy = SearchPost(postid);
		Posts** temp = new Posts*[totalPosts + 1];
		char * Id = Helper::GetStringFromBuffer("post");
		for (int i = 0; i < totalPosts; i++)
			temp[i] = Postlist[i];

		temp[totalPosts] = new Posts;
		temp[totalPosts]->SetValues(Id, Date::CurrentDate, copy, Users::CurrentUser);
		delete[] Postlist;
		Postlist = temp;
		Users::CurrentUser->addPost(temp[totalPosts]);
		totalPosts++;
	}

	void run()
	{
		int index = SetCurrentUser("u7");
		Users::CurrentUser = Userlist[index];
		cout << "Command:\t Set Current System Date 15 11 2017\nSystem Date:\t";
		Date::CurrentDate.SetDateDate(15, 11, 2017);
		Date::CurrentDate.PrintDate();
		viewFriendlist(index);
		viewLikedPages(index);
		cout << "\n----------------------------------------------------------------\n";
		cout << "Command:\t Print Homepage";
		Users::CurrentUser->printHomepage(Date::CurrentDate);
		cout << "\n----------------------------------------------------------------\n";
		cout << "Command:\t Print Timeline";
		Users::CurrentUser->printTimeline();
		cout << "\n----------------------------------------------------------------\n";
		cout << "Command:\t View Liked By";
		likersList("post5");
		likePost("post5");
		likersList("post5");
		cout << "\n----------------------------------------------------------------\n";
		cout << "Command:\t Post Comment";
		postComment("post4", "Good Luck for your Result");
		showPost("post4");
		postComment("post8", "Thanks for the wishes");
		showPost("post8");
		cout << "\n----------------------------------------------------------------\n";
		cout << "Command:\t Share Post";
		sharePost("post5");
		Users::CurrentUser->printTimeline();
		cout << "\n----------------------------------------------------------------\n";
		cout << "Command:\t View Page";
		viewPage("p1");
		cout << "\n----------------------------------------------------------------\n";
		cout << "Command:\t Search";
		searchFacebook("Birthday");
		searchFacebook("Ali");
	}


};

void main()
{
	SocialNetworkApp FB;
	FB.LoadData();
	FB.Linker();
	FB.run();

	system("pause");
}