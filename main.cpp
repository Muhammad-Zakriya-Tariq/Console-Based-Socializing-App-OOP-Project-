#include <iostream>
#include <fstream>
using namespace std;

template <class T>
void DeallocateMatrix(T** t, int num) {
	for (int i = 0; i < num; i++)
		if (t[i])
			delete[] t[i];

	if (t)
		delete[] t;
}
class Post;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PROTOTYPES OF CLASSES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Helper {
public:
	static int String_Length(const char* = NULL);
	static char* Get_String_From_Buffer(ifstream&);
	static char* Get_String_With_Space_From_Buffer(ifstream&);
	static char* Copy_String(const char* = NULL);
	static char* Concatenate(const char* = NULL, const char* = NULL);
	static char* Concatenate_without_space(const char* = NULL, const char* = NULL);
	static char* NumToString(int = 0);
	static bool Compare_String(const char* = NULL, const char* = NULL);
	static bool IsSubStr(const char* = NULL, const char* = NULL);
};

class Date {
private:
	int day, month, year;
public:
	static Date system_Date;
	Date(const int = 1, const int = 1, const int = 2000);
	void Print();
	bool Compare(const Date&);
	void set_value(int = 1, int = 1, int = 2000);
};

Date Date::system_Date;

class Object {
private:
	char* ID, * name;
public:
	Object();
	virtual ~Object();
	virtual void Print();
	virtual void set_value(char* = NULL, char* = NULL);
	virtual void Set_post(Post* p) {}
	char* Get_ID() { return ID; } //Gets ID
	char* Get_name() { return name; } //Gets name
};

class Comment : public Object {
private:
	Object* commentor;
public:
	Comment();
	void set_value(char* = NULL, char* = NULL, Object* = NULL);
	void Print();
	Object* Get_Commentor() { return commentor; }//return who commented on post
};

class Post : public Object {
private:
	int num_of_likes, num_of_comments;
	Comment** comments;
	Object** liked_by;
	Date post_date;
protected:
	Object* shared_by;
public:
	Post();
	virtual ~Post();
	virtual void LoadData(ifstream&);
	void PrintLike();
	void PrintComment();
	virtual void Print();
	void Show_Post();
	void Set_like_by(Object* = NULL);
	void Set_comments(Comment* = NULL);
	void set_values(Object* = NULL);
	Date Get_Date() { return post_date; }
};

class Activity : public Post {
private:
	int activity_type;
	char* data;
	static const char* activities[];
public:
	Activity();
	~Activity();
	void LoadData(ifstream&);
	void Print();
};

const char* Activity::activities[] = { "Feeling", "Thinking about", "Making", "Celebrating" };

class Page : public Object {
private:
	int num_of_posts;
	Post** posts;
public:
	Page();
	~Page();
	void LoadData(ifstream&);
	void Show_all_posts();
	void Set_post(Post*);
	void Show_posts();
};

class User : public Object {
private:
	int num_of_friends, num_of_liked_pages, num_of_posts;
	User** friends;
	Page** liked_pages;
	Post** posts;
public:
	User();
	~User();
	void LoadData(ifstream&);
	void set_values(int = 0, int = 0);
	void Set_Friend(User* = NULL);
	void Set_page(Page* = NULL);
	void Set_post(Post*);
	void View_Friends();
	void View_Pages();
	void Show_all_posts();
	void Show_posts();
	void Home_page();
};

class SocialNetworkApp {
private:
	User** users;
	Page** pages;
	Post** posts;
	Comment** comments;
	int total_users, total_pages, total_posts, total_comments;
	User* current_user;
public:
	SocialNetworkApp();
	~SocialNetworkApp();
	void Load_Data_From_File_Pages(ifstream&);
	void Load_Data_From_File_Users(ifstream&);
	void Load_Data_From_File_Posts(ifstream&);
	void Load_Data_From_File_Comments(ifstream&);
	void Associate_Friends(char*** = NULL, const int* = NULL);
	void Associate_Pages(char*** = NULL, const int* = NULL);
	Object* Search_Object_By_ID(const char*);

	void Set_Current_User(const char*);
	void View_Friends();
	void Home_page();
	void View_timeline();
	void view_liked_by(const char* = NULL);
	void View_Liked_Pages();
	void view_post(const char* = NULL);
	void view_page(const char* = NULL);
	void New_comment(const char* = NULL, const char* = NULL);
	void New_like(const char* = NULL);
	void Search(const char* = NULL);

	void Run();
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DRIVER FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main()
{
	SocialNetworkApp FaceBook;
	FaceBook.Run();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~HELPER CLASS FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//returns the string length of a string
int Helper::String_Length(const char* str) {
	if (str == NULL)
		return 0;

	int length = 0;
	for (; str[length] != '\0'; length++);
	return length;
}

//gets a string from file and returns the string with minimum space needed
char* Helper::Get_String_From_Buffer(ifstream& fin) {
	char* temp = new char[20];
	fin >> temp;

	int length = String_Length(temp);
	char* str = new char[length + 1];

	for (int i = 0; i < length; i++)
		str[i] = temp[i];

	str[length] = '\0';

	delete[] temp;
	return str;
}

//gets a string from file with spaces and returns the string with minimum space needed
char* Helper::Get_String_With_Space_From_Buffer(ifstream& fin) {
	char* temp = new char[160];
	fin.getline(temp, 160, '\n');

	int length = String_Length(temp);
	char* str = new char[length + 1];

	for (int i = 0; i < length; i++)
		str[i] = temp[i];

	str[length] = '\0';

	delete[] temp;
	return str;
}

//makes a deep copy and returns the copy
char* Helper::Copy_String(const char* temp) {
	if (temp == NULL)
		return NULL;

	int length = String_Length(temp);

	char* str = new char[length + 1];

	for (int i = 0; i < length; i++)
		str[i] = temp[i];

	str[length] = '\0';
	return str;
}

//Concatenates two strings with a space
char* Helper::Concatenate(const char* str1, const char* str2) {
	if (str1 == NULL && str2 == NULL)
		return NULL;
	else if (str1 == NULL)
		return Helper::Copy_String(str2);
	else if (str2 == NULL)
		return Helper::Copy_String(str1);

	int size1 = Helper::String_Length(str1);
	int size2 = Helper::String_Length(str2);

	char* str = new char[size1 + size2 + 2];
	int j = 0;

	for (int i = 0; str1[i] != '\0'; i++, j++)
		str[j] = str1[i];
	str[j++] = ' ';

	for (int i = 0; str2[i] != '\0'; i++, j++)
		str[j] = str2[i];
	str[size1 + size2 + 1] = '\0';

	return str;
}

//Concatenates two strings without a space
char* Helper::Concatenate_without_space(const char* str1, const char* str2) {
	if (str1 == NULL && str2 == NULL)
		return NULL;
	else if (str1 == NULL)
		return Helper::Copy_String(str2);
	else if (str2 == NULL)
		return Helper::Copy_String(str1);

	int size1 = Helper::String_Length(str1);
	int size2 = Helper::String_Length(str2);

	char* str = new char[size1 + size2 + 1];
	int j = 0;

	for (int i = 0; str1[i] != '\0'; i++, j++)
		str[j] = str1[i];

	for (int i = 0; str2[i] != '\0'; i++, j++)
		str[j] = str2[i];
	str[size1 + size2] = '\0';

	return str;
}

//turns int to string
char* Helper::NumToString(int num) {
	int temp = num, count = 0;

	do {
		temp /= 10;
		count++;
	} while (temp > 0);
	
	char* result = new char[count + 1];

	for (int i = count - 1; i >= 0; i--) {
		result[i] = (num % 10) + '0';
		num /= 10;
	}
	result[count] = '\0';

	return result;
}

//checks if two strings are equal
bool Helper::Compare_String(const char* str1, const char* str2) {
	if (str1 == NULL && str2 == NULL)
		return true;
	else if (str1 == NULL || str2 == NULL)
		return false;

	int length = String_Length(str1), temp = String_Length(str2);

	if (length != temp)
		return false;

	for (int i = 0; i < length; i++)
		if (str1[i] != str2[i])
			return false;

	return true;
}

//checks if sub string str1 is present in str2
bool Helper::IsSubStr(const char* str1, const char* str2) {
	int size1 = Helper::String_Length(str1);
	int size2 = Helper::String_Length(str2);

	if (size1 > size2)
		return false;

	for (int i = 0; i <= size2 - size1; i++)
		if (str2[i] == str1[0]) {
			bool result = true;
			for (int j = 1; j < size1 && result; j++)
				if (str2[i + j] != str1[j])
					result = false;

			if (result)
				return true;
		}

	return false;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DATE CLASS FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//default constructor
Date::Date(const int _day, const int _month, const int _year) :day(_day), month(_month), year(_year) {}

//print function
void Date::Print() {
	cout << day << "/" << month << "/" << year;
}

//compares Date and see if its equal to or one less then current date
bool Date::Compare(const Date& d) {
	if (year == d.year)
		if (month == d.month)
			if (day == d.day || day == d.day + 1)
				return true;
	return false;
}

void Date::set_value(int _day, int _month, int _year) {
	day = _day;
	month = _month;
	year = _year;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~OBJECT CLASS FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//constructor
Object::Object() {
	ID = NULL;
	name = NULL;
}

//destructor
Object::~Object() {
	if (ID)
		delete[] ID;

	if (name)
		delete[] name;
}

//prints ID and name
void Object::Print() {
	if (ID) cout << ID;
	cout << " - ";
	if (name) cout << name;
	cout << endl;
}

//sets values
void Object::set_value(char* _ID, char* _name) {
	ID = _ID;
	name = _name;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~COMMENT CLASS FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//default constructor
Comment::Comment() {
	commentor = NULL;
}

//sets values
void Comment::set_value(char* _ID, char* _text, Object* _commentor) {
	Object::set_value(_ID, _text);
	commentor = _commentor;
}

//prints text
void Comment::Print() {
	if (commentor)
		cout << commentor->Get_name();
	cout << " wrote: ";
	if (Get_name())
		cout << Get_name();
	cout << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~POST CLASS FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//default constructor
Post::Post() {
	num_of_likes = num_of_comments = 0;

	comments =  NULL;

	liked_by =  NULL;

	shared_by = NULL;
}

//destructor
Post::~Post() {
	if (comments)
		DeallocateMatrix(comments, num_of_comments);

	if (liked_by)
		delete[] liked_by;
}

//prints names of pages/users who liked the post
void Post::PrintLike() {
	if (!liked_by)
		return;

	cout << "\nPost Liked By:\n";
	for (int i = 0; i < num_of_likes; i++)
		liked_by[i]->Print();
}

//prints comments of pages/users who commented on the post
void Post::PrintComment() {
	if (!comments)
		return;

	for (int i = 0; i < num_of_comments; i++) {
		cout << "\t\t";
		comments[i]->Print();
	}
}

//loads data from file
void Post::LoadData(ifstream& fin) {
	char* _ID = Helper::Get_String_From_Buffer(fin);

	int day, month, year;
	fin >> day >> month >> year;
	post_date.set_value(day, month, year);

	fin.ignore();
	char* _text = Helper::Get_String_With_Space_From_Buffer(fin);

	set_value(_ID, _text);
}

//prints sharer name along with title
void Post::Print() {
	cout << "--- ";
	if (shared_by)
		cout << shared_by->Get_name();
	cout << " shared '";
	if (Get_name())
		cout << Get_name();
	cout << "'....(";
	post_date.Print();
	cout << ")" << endl;
}

//shows post with commenmts
void Post::Show_Post() {
	Print();
	PrintComment();
}

//Association to users/pages who can like
void Post::Set_like_by(Object* obj) {
	if (obj == NULL)
		return;

	if (liked_by == NULL) {
		liked_by = new Object * [10];
		for (int i = 0; i < 10; i++)
			liked_by[i] = NULL;
	}

	for (int i = 0; i < 10; i++)
		if (liked_by[i] == NULL) {
			if (liked_by[i] == obj)
				return;

			liked_by[i] = obj;
			num_of_likes++;
			return;
		}
}

//Associates comments to a post
void Post::Set_comments(Comment* com) {
	if (com == NULL)
		return;

	if (comments == NULL) {
		comments = new Comment * [10];
		for (int i = 0; i < 10; i++)
			comments[i] = NULL;
	}

	for (int i = 0; i < 10; i++)
		if (comments[i] == NULL) {
			if (comments[i] == com)
				return;

			comments[i] = com;
			num_of_comments++;
			return;
		}
}

//sets values
void Post::set_values( Object* _sharer) {
	shared_by = _sharer;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Activity CLASS FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//default constructor
Activity::Activity() {
	data = NULL;
	activity_type = 0;
}

//deconstructor
Activity::~Activity() {
	if (data)
		delete[] data;
}

//loads data from file
void Activity::LoadData(ifstream& fin) {
	Post::LoadData(fin);

	fin >> activity_type;
	fin.ignore();
	char* activity_text = Helper::Get_String_With_Space_From_Buffer(fin);

	data = Helper::Concatenate(activities[activity_type - 1], activity_text);
	delete[] activity_text;
}

//prints sharer name along with title and activity
void Activity::Print() {
	cout << "--- ";
	if (shared_by)
		cout << shared_by->Get_name();
	cout << " is ";
	if (data)
		cout << data;
	cout << endl;
	if (Get_name())
		cout << "\t" << Get_name();
	cout << "'....(";
	Get_Date().Print();
	cout << ")" << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PAGE CLASS FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//default constructor
Page::Page() {
	num_of_posts = 0;
	posts = NULL;
}

//deconstructor
Page::~Page() {
	if (posts)
		DeallocateMatrix(posts, num_of_posts);
}

//loads data from file
void Page::LoadData(ifstream& fin) {
	char* _ID = Helper::Get_String_From_Buffer(fin);
	fin.ignore();
	char* _name = Helper::Get_String_With_Space_From_Buffer(fin);
	
	set_value(_ID, _name);
}

//shows all posts
void Page::Show_all_posts() {
	for (int i = 0; i < num_of_posts; i++)
		if (posts[i]) {
			posts[i]->Show_Post();
			cout << endl << endl;
		}
}
//shows post which match date
void Page::Show_posts() {
	for (int i = 0; i < num_of_posts; i++)
		if (posts[i])
			if (Date::system_Date.Compare(posts[i]->Get_Date())) {
				posts[i]->Show_Post();
				cout << endl << endl;
			}
}

//associates post with page
void Page::Set_post(Post* tempPost) {
	if (tempPost == NULL)
		return;

	if (posts == NULL) {
		posts = new Post * [10];
		for (int i = 0; i < 10; i++)
			posts[i] = NULL;
	}

	for (int i = 0; i < 10; i++)
		if (posts[i] == NULL) {
			if (posts[i] == tempPost)
				return;

			posts[i] = tempPost;
			num_of_posts++;
			return;
		}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~USER CLASS FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//User class default constructor
User::User() {
	friends = NULL;
	liked_pages = NULL;

	num_of_friends = num_of_liked_pages = num_of_posts = 0;

	posts = NULL;
}

//User class default deconstructor
User::~User() {
	if (friends)
		delete[] friends;

	if (liked_pages)
		delete[] liked_pages;

	if (posts)
		DeallocateMatrix(posts, num_of_posts);
}

//loads data from file
void User::LoadData(ifstream& fin) {
	char* _ID = Helper::Get_String_From_Buffer(fin);
	char* f_name = Helper::Get_String_From_Buffer(fin);
	char* l_name = Helper::Get_String_From_Buffer(fin);

	set_value(_ID, Helper::Concatenate(f_name, l_name));

	delete[] f_name;
	delete[] l_name;
}

//loads data from file
void User::set_values(int NOF, int NOP) {

	num_of_friends = NOF;
	if (NOF > 0) {
		friends = new User * [NOF];
		for (int i = 0; i < NOF; i++)
			friends[i] = NULL;
	}

	num_of_liked_pages = NOP;
	if (NOP > 0) {
		liked_pages = new Page * [NOP];
		for (int i = 0; i < NOP; i++)
			liked_pages[i] = NULL;
	}
}

//sets friend
void User::Set_Friend(User* tempUser) {
	if (friends == NULL || tempUser == NULL)
		return;

	for (int i = 0; i < num_of_friends; i++)
		if (friends[i] == NULL) {
			if (friends[i] == tempUser)
				return;

			friends[i] = tempUser;
			return;
		}
}

//sets liked pages
void User::Set_page(Page* tempPage) {
	if (liked_pages == NULL || tempPage == NULL)
		return;

	for (int i = 0; i < num_of_liked_pages; i++)
		if (liked_pages[i] == NULL) {
			if (liked_pages[i] == tempPage)
				return;

			liked_pages[i] = tempPage;
			return;
		}
}

//associates post with user
void User::Set_post(Post* tempPost) {
	if (tempPost == NULL)
		return;
	
	if (posts == NULL) {
		posts = new Post * [10];
		for (int i = 0; i < 10; i++)
			posts[i] = NULL;
	}

	for (int i = 0; i < 10; i++)
		if (posts[i] == NULL) {
			if (posts[i] == tempPost)
				return;

			posts[i] = tempPost;
			num_of_posts++;
			return;
		}
}

//prints list of friends
void User::View_Friends() {
	if (friends == NULL)
		return;

	cout << Get_name() << " - Friend List\n\n";

	for (int i = 0; i < num_of_friends; i++)
		friends[i]->Print();
}

//prints list of liked pages
void User::View_Pages() {
	if (liked_pages == NULL)
		return;

	cout << Get_name() << " - Liked Pages\n\n";

	for (int i = 0; i < num_of_liked_pages; i++)
		liked_pages[i]->Print();
}

//shows all posts associated with user
void User::Show_all_posts() {
	for (int i = 0; i < num_of_posts; i++)
		if (posts[i]) {
			posts[i]->Show_Post();
			cout << endl << endl;
		}
}
//shows post which match date
void User::Show_posts() {
	for (int i = 0; i < num_of_posts; i++)
		if (posts[i])
			if (Date::system_Date.Compare(posts[i]->Get_Date())) {
				posts[i]->Show_Post();
				cout << endl << endl;
			}
}

//shows a users a home page
void User::Home_page() {
	cout << Get_name() << " - Home Page\n\n";

	if (friends)
		for (int i = 0; i < num_of_friends; i++)
			friends[i]->Show_posts();

	if (liked_pages)
		for (int i = 0; i < num_of_liked_pages; i++)
			liked_pages[i]->Show_posts();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SOCIAL NETWORK APP CLASS FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//default constructor for Social network app class
SocialNetworkApp::SocialNetworkApp() {
	users = NULL;
	pages = NULL;
	posts = NULL;
	comments = NULL;
	current_user = NULL;
	total_users = total_pages = total_posts = total_comments = 0;
}

//default deconstructor for social network app class
SocialNetworkApp::~SocialNetworkApp() {
	if (users)
		DeallocateMatrix(users, total_users);

	if (pages)
		DeallocateMatrix(pages, total_pages);

	if (comments)
		delete[] comments;

	if (posts)
		delete[] posts;
}

//associate Users with their friends
void SocialNetworkApp::Associate_Friends(char*** tempF, const int* NOF) {
	if (tempF == NULL || NOF == NULL || users == NULL)
		return;

	for (int i = 0; i < total_users; i++)
		for (int j = 0; j < NOF[i]; j++)
			users[i]->Set_Friend((User*)Search_Object_By_ID(tempF[i][j]));
}

//associates Users with their liked pages
void SocialNetworkApp::Associate_Pages(char*** tempP, const int* NOP) {
	if (tempP == NULL || NOP == NULL || pages == NULL)
		return;

	for (int i = 0; i < total_users; i++)
		for (int j = 0; j < NOP[i]; j++)
			users[i]->Set_page((Page*)Search_Object_By_ID(tempP[i][j]));
}

//loads data of pages
void SocialNetworkApp::Load_Data_From_File_Pages(ifstream& fin) {
	fin.open("SocialNetworkPages.txt");

	if (!fin)
		return;

	fin >> total_pages;

	if (total_pages < 1)
		return;

	pages = new Page * [total_pages];

	for (int i = 0; i < total_pages; i++) {
		pages[i] = new Page;
		pages[i]->LoadData(fin);
	}

	fin.close();
}

//loads data of users and associates user with other users
void SocialNetworkApp::Load_Data_From_File_Users(ifstream& fin) {
	fin.open("SocialNetworkUsers.txt");

	if (!fin)
		return;

	fin >> total_users;

	if (total_users < 1)
		return;

	users = new User * [total_users];

	char*** tempF = new char** [total_users];
	int* numF = new int[total_users];

	char*** tempP = new char** [total_users];
	int* numP = new int[total_users];

	char * temp = NULL;

	for (int i = 0; i < total_users; i++) {
		users[i] = new User;
		numF[i] = numP[i] = 0;

		tempF[i] = new char* [10];
		tempP[i] = new char* [10];

		users[i]->LoadData(fin);

		do {
			temp = Helper::Get_String_From_Buffer(fin);
			if (!Helper::Compare_String(temp, "-1"))
				tempF[i][numF[i]++] = temp;
		} while (!Helper::Compare_String(temp, "-1"));
		delete[] temp;

		do {
			temp = Helper::Get_String_From_Buffer(fin);
			if (!Helper::Compare_String(temp, "-1"))
				tempP[i][numP[i]++] = temp;
		} while (!Helper::Compare_String(temp, "-1"));
		delete[] temp;

		users[i]->set_values(numF[i], numP[i]);
	}
	fin.close();

	Associate_Friends(tempF, numF);
	Associate_Pages(tempP, numP);

	for (int i = 0; i < total_users; i++) {
		DeallocateMatrix(tempF[i], numF[i]);
		DeallocateMatrix(tempP[i], numP[i]);
	}

	delete[] tempF;
	delete[] numF;
	delete[] tempP;
	delete[] numP;
}

//loads data of posts
void SocialNetworkApp::Load_Data_From_File_Posts(ifstream& fin) {
	fin.open("SocialNetworkPosts.txt");

	if (!fin)
		return;

	fin >> total_posts;

	if (total_posts < 1)
		return;

	posts = new Post * [total_posts];
	int post_type, activity_type = 0;
	char* objID, * tempID;
	Object* temp;

	for (int i = 0; i < total_posts; i++) {
		fin >> post_type;
		if (post_type == 1)
			posts[i] = new Post;
		else if (post_type == 2)
			posts[i] = new Activity;

		posts[i]->LoadData(fin);

		tempID = Helper::Get_String_From_Buffer(fin);
		temp = Search_Object_By_ID(tempID);

		if (temp) {
			temp->Set_post(posts[i]);
			posts[i]->set_values(temp);
		}

		objID = Helper::Get_String_From_Buffer(fin);
		while (!Helper::Compare_String(objID, "-1")) {
			temp = Search_Object_By_ID(objID);
			if (temp)
				posts[i]->Set_like_by(temp);
			
			delete[] objID;
			objID = Helper::Get_String_From_Buffer(fin);
		}

		delete[] objID;
		delete[] tempID;
	}

	fin.close();
}

//loads data of comments
void SocialNetworkApp::Load_Data_From_File_Comments(ifstream& fin) {
	fin.open("SocialNetworkComments.txt");

	if (!fin)
		return;

	fin >> total_comments;

	if (total_comments < 1)
		return;

	comments = new Comment * [total_comments];
	char* ID, * text, * tempID;
	Post* temp;
	Object* sharer;

	for (int i = 0; i < total_comments; i++) {
		comments[i] = new Comment;

		ID = Helper::Get_String_From_Buffer(fin);
		tempID = Helper::Get_String_From_Buffer(fin);
		temp = dynamic_cast<Post*>(Search_Object_By_ID(tempID));
		delete[] tempID;

		tempID = Helper::Get_String_From_Buffer(fin);
		sharer = Search_Object_By_ID(tempID);
		delete[] tempID;

		fin.ignore();
		text = Helper::Get_String_With_Space_From_Buffer(fin);

		comments[i]->set_value(ID, text, sharer);
		if (temp)
			temp->Set_comments(comments[i]);
	}

	fin.close();
}

//searchs then sends Object pointer
Object* SocialNetworkApp::Search_Object_By_ID(const char* ID) {
	if (ID[0] == 'u')
		for (int i = 0; i < total_users && users; i++)
			if (Helper::Compare_String(users[i]->Get_ID(), ID))
				return users[i];

	if (ID[0] == 'p' && ID[1] != 'o')
		for (int i = 0; i < total_pages && pages; i++)
			if (Helper::Compare_String(pages[i]->Get_ID(), ID))
				return pages[i];

	if (ID[0] == 'p' && ID[1] == 'o')
		for (int i = 0; i < total_posts && posts; i++)
			if (Helper::Compare_String(posts[i]->Get_ID(), ID))
				return posts[i];

	return NULL;
}

//sets current user if user is found
void SocialNetworkApp::Set_Current_User(const char* str) {
	current_user = dynamic_cast<User*>(Search_Object_By_ID(str));

	if (current_user)
		cout << endl << current_user->Get_name() << " successfully set as Current User\n";
	else
		cout << "\nUser not found setting to NULL\n";
}

//See current list of friends of current user
void SocialNetworkApp::View_Friends() {
	if (current_user)
		current_user->View_Friends();
}

//see current list of liked pages of current user
void SocialNetworkApp::View_Liked_Pages() {
	if (current_user)
		current_user->View_Pages();
}

//sees users/pages post of the last 24 hours
void SocialNetworkApp::Home_page() {
	if (current_user)
		current_user->Home_page();
}

//sees all user post
void SocialNetworkApp::View_timeline() {
	if (current_user) {
		cout << current_user->Get_name() << " -Timeline\n\n";
		current_user->Show_all_posts();
	}
}

//shows likes on pages
void SocialNetworkApp::view_liked_by(const char* postID) {
	Post* tempPost = dynamic_cast<Post*>(Search_Object_By_ID(postID));

	if (tempPost)
		tempPost->PrintLike();
}

//shows post with comments
void SocialNetworkApp::view_post(const char* postID) {
	Post* tempPost = dynamic_cast<Post*>(Search_Object_By_ID(postID));

	if (tempPost)
		tempPost->Show_Post();
}

//adds new comment to a post
void SocialNetworkApp::New_comment(const char* postID, const char* text) {
	Post* tempPost = dynamic_cast<Post*>(Search_Object_By_ID(postID));

	if (!tempPost || !current_user)
		return;

	Comment* temp = new Comment;
	char* numStr = Helper::NumToString(++total_comments);
	char* _ID = Helper::Concatenate_without_space("c", numStr);
	delete[] numStr;

	temp->set_value(_ID , Helper::Copy_String(text), current_user);
	tempPost->Set_comments(temp);
}

//adds a new like to a post
void SocialNetworkApp::New_like(const char* postID) {
	Post* tempPost = dynamic_cast<Post*>(Search_Object_By_ID(postID));

	if (tempPost)
		tempPost->Set_like_by(current_user);
}

//searches for a specific keyword
void SocialNetworkApp::Search(const char* search_text) {
	int  count = 0;
	for (int i = 0; i < total_users; i++)
		if (Helper::IsSubStr(search_text, users[i]->Get_name())) {
			if (count == 0)
				cout << "\nUsers:\n";

			cout << "---";
			users[i]->Print();
			cout << endl;
			count++;
		}

	count = 0;
	for (int i = 0; i < total_posts; i++)
		if (Helper::IsSubStr(search_text, posts[i]->Get_name())) {
			if (count == 0)
				cout << "\nPosts:\n";

			cout << "---" << posts[i]->Get_ID();
			posts[i]->Print();
			cout << endl;
			count++;
		}

	count = 0;
	for (int i = 0; i < total_pages; i++)
		if (Helper::IsSubStr(search_text, pages[i]->Get_name())) {
			if (count == 0)
				cout << "\nPages:\n";

			cout << "---";
			pages[i]->Print();
			cout << endl;
			count++;
		}
}

//shows a page and their posts
void SocialNetworkApp::view_page(const char* pageID) {
	Page* tempPost = dynamic_cast<Page*>(Search_Object_By_ID(pageID));

	if (!tempPost)
		return;

	cout << tempPost->Get_name() << endl;
	tempPost->Show_all_posts();
}

//Driver Code
void SocialNetworkApp::Run() {
	ifstream fin;
	Load_Data_From_File_Pages(fin);
	Load_Data_From_File_Users(fin);
	Load_Data_From_File_Posts(fin);
	Load_Data_From_File_Comments(fin);

	cout << "Command:\t\tSet current user 'u7'\n";
	Set_Current_User("u7");

	cout << "\nCommand:\t\tSet current System Date 15 11 2017";
	Date::system_Date.set_value(15, 11, 2017);
	cout << "\nSystem Date:\t\t ";
	Date::system_Date.Print();
	cout << endl;

	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << "\nCommand:\t\tView Friend List\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	View_Friends();

	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << "\nCommand:\t\tView Liked Pages\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	View_Liked_Pages();

	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << "\nCommand:\t\tView Home\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	Home_page();

	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << "\nCommand:\t\tView Timeline\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	View_timeline();

	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << "\nCommand:\t\t ViewLikedList(post5)\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	view_liked_by("post5");

	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << "\nCommand:\t\t LikePost(post5)\n";
	cout << "\nCommand:\t\t ViewLikedList(post5)\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	New_like("post5");
	view_liked_by("post5");

	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << "\nCommand:\t\t PostComment(post4, Good Luck for your Result)\n";
	cout << "Command:\t\t ViewPost(post4)\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	New_comment("post4", "Good Luck for your Result");
	view_post("post4");

	cout << "\n-------------------------------------------------------------------------------------------------------------\n";

	cout << "\nCommand:\t\t PostComment(post8, Thanks for the wishes)\n";
	cout << "Command:\t\t ViewPost(post8)\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	New_comment("post8", "Thanks for the wishes");
	view_post("post8");

	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << "\nCommand:\t\t ViewPage(p1)\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	view_page("p1");

	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << "\nCommand:\t\t Search('Birthday')\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	Search("Birthday");

	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << "\nCommand:\t\t Search('Ali')\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	Search("Ali");
}