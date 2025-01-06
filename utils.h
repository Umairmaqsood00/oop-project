#pragma once
#include<iostream>
#include<cstring>
#include<string>
#include<fstream>
using namespace std;
const int MAX = 5;

class login {

	string name;
	string password;

public:

	login(string e, string p) {
		name = e;
		password = p;
	}

	string getname() const {
		return name;
	}

	string getpassword() const {
		return password;
	}
};

class personalinfo {

	string s;
	string b;
	string n;
	string* friends = new string[10];

public:
	void setname(string n) {
		s = n;
	}

	void setbio(string bi) {
		b = bi;
	}

	string getname() const {
		return s;
	}

	string getbio() const {
		return b;
	}

	void getnotification(string s) {
		n = s;
	}

	string seenotifications() const {
		return n;
	}

string* getfriends() const {
		return friends;
	}
};

class Comments 
{
	string name;
	string text;
	string likes;

public:
	Comments() : name(""), text(""){}
	Comments(string n, string t) :name(n), text(t) {}

	string getname() const {
		return name;
	}

	string gettext() const {
		return text;
	}
	
        string getlikes() const {
		return likes;
	}
	void setname(string n) {
		name = n;
	}

	void setlikesusers(string s) {
		likes = s;
	}

	void settext(string t) {
		text = t;
	}

	void display() const {
		//cout << "liked by : " << getlikes() << endl;
		cout << "commented by : " << getname() << " : " << gettext() << endl;
	}
};

class Posts 
{
	Comments** comments;
	int likes;
	string likedusers;
	string* post;
	int count;

public:

	Posts() :count(0), likes(0) 
	{
		comments = new Comments * [5];
		post = new string[10];
		for (int i = 0; i < 5; i++) {
			comments[i] = nullptr;
		}
	}

	void create(string t) 
	{

		post[count++] = t;
	}

	int getlike() const 
	{
		return likes;
	}

	void setlikes(int l)
	{
		likes = l;
	}

	void setlikeduser(string s) 
	{
		likedusers = s;
	}

	string getlikedusers() const 
	{
		return likedusers;
	}

	void addlikes() {
		likes++;
	}
	
	string newpost() const {
		return post[count-1];
	}
	string getpost(int index) const {

		return post[index];

	}
};


class pages {
	string post;

public:

	pages() {
		post = "";
	}
	string getpage() const {
		return post;
	}

	void addpage(string t) {
		post = t;
	}
};

class user {

	login** lg = new login * [3];
	personalinfo** pl = new personalinfo * [3] {nullptr};
	Posts** posts = new Posts * [10] {nullptr};
	Comments** com = new Comments * [5] {nullptr};
	pages** p = new pages * [5] {nullptr};
	string name;
	string password;
	int currentuser = 0;
	int friendcount = 0; 
	int count = 0;

public:

	user() {
	}

	user(string n, string p) :name(n), password(p) {

	}

	bool compare() {
		string s, p;
		bool flag = 0;
		ifstream f("data.txt");
		for (int i = 0; i < 3; i++) {
			getline(f, s);
			getline(f, p);
			lg[i] = new login(s, p);

			if (name == lg[i]->getname() && password == lg[i]->getpassword()) {
				currentuser = i;
				return true;
			}
		}
		return false;
	}
	void getinfo() {
		string s, b, fr;
		ifstream f("info.txt");

		for (int i = 0; i <= currentuser; i++) {
			getline(f, s);
			getline(f, b);
			getline(f, fr);
		}

		if (pl[currentuser] == nullptr) {
			pl[currentuser] = new personalinfo();
		}

		pl[currentuser]->setname(s);
		pl[currentuser]->setbio(b);

		cout << "My name is: " << pl[currentuser]->getname() << endl;
		cout << "Bio: " << pl[currentuser]->getbio() << endl;
		cout << "Friends: " << endl;

		string* friends = pl[currentuser]->getfriends();

		int pos = 0;
		while ((pos = fr.find(',')) != string::npos) {
			friends[friendcount++] = fr.substr(0, pos);
			cout << "- " << fr.substr(0, pos) << endl;
			fr.erase(0, pos + 1);
		}

		friends[friendcount++] = fr;
		cout << "- " << fr << endl;
		cout << "total number of friends are : " << friendcount << endl;

		char choice;
		cout << "Press A if you want to add someone :";
		cin >> choice;

		if(choice == 'A') {
			if (friendcount < 5) { 
				string newFriend;
				cout << "Enter name: ";
				cin.ignore();
				getline(cin, newFriend);

				bool alreadyFriend = false;
				for (int i = 0; i < friendcount; i++) {
					if (friends[i] == newFriend) {
						cout << newFriend << " is already your friend." << endl;
						alreadyFriend = true;
						break;
					}
				}

				if (!alreadyFriend) {
					
					cout << "Friend request successfully sent to " << newFriend << "." << endl;
				}
			}
			else {
				cout << "Your friend list is full." << endl;
			}
		}

		cout << "Press A if you want to see pending friend request :";
		cin >> choice;
		if (choice == 'A') {
	
			string arr[5] = {"Saad Mansoor","Changez Khan","Usama Bin laden","Adolf Hitler","Asim Munir"};
			
			cout << "These are your friend requests : " << endl;

			for (int i = 0; i < 5; i++) {
				cout << arr[i] << endl;
			}
			char c1;
			cout << "Do you want to add anyone : " << endl;
			cin.ignore();
			cin >> c1;
			if (c1 == 'Y') {
				if (friendcount < 5) {
					int id;
					cout << "enter which one you want to add : " << endl;
					cin >> id;
					
					friends[friendcount] = arr[id];
					friendcount++;
					cout << arr[id] << " has become your friend : " << endl;
					
				}
				else {
					cout << "you cannot add anyone as your friend list is complete : " << endl;
					cout << friendcount << endl;
				}
			}
		
			cout << "total number of friends are : " << friendcount << endl;

		}
	}

	void viewpost() {

		ifstream f("timeline.txt");
		
		string s;
		string n;
		int postCount = 0;

		if (posts[currentuser] == nullptr) {
			posts[currentuser] = new Posts();
		}

		bool flag = false;
		while (getline(f, s) && postCount < 5) {
			if (s == name) {
				flag = true;
				break;
			}
		}

		if (flag) {

			while (getline(f, s) && postCount < 5) {
				posts[currentuser]->create(s);
				postCount++;

			}
		}

		cout << "Available Posts:" << endl;

		for (int i = 0; i < postCount; i++) {

			cout << posts[currentuser]->getpost(i) << endl;

		}
		int id;
		cout << "Enter which post you want to see: ";
		cin >> id;

		if (id < 1 || id > postCount) {
			cout << "Invalid post ID." << endl;
			return;
		}

		ifstream l("likecom.txt");
		string likes;
		bool flag2 = 0, check;
		int c1 = 0;
		while (getline(l, likes)) {
			if (likes == name) {
				flag2 = true;
				break;
			}
		}

		if (flag2) {
			while (getline(l, likes)) {
				if (likes.find("Post") != string::npos) {
					c1++;

					if (c1 == id) {
						check = true;
						break;
					}
				}
			}
		}

		if (check) {
			cout << "liked by : ";
			while (getline(l, likes)) {
				if (likes.find("Post") != string::npos) {
					break;
				}
				posts[currentuser]->setlikeduser(likes);
				cout << posts[currentuser]->getlikedusers() << endl;
			}
		}
		ifstream c("comment.txt");

		string owner, text;
		int currentPost = 0;
		bool commentsFound = false, flag1 = false;

		while (getline(c, s)) {
			if (s == name) {
				flag1 = true;
				break;
			}
		}

		if (flag1) {
			while (getline(c, s)) {
				if (s.find("Post") != string::npos) {
					currentPost++;

					if (currentPost == id) {
						commentsFound = true;
						break;
					}
				}
			}
		}


		if (commentsFound) {
			cout << "Comments for Post " << id << ":" << endl;

			while (getline(c, owner) && getline(c, text)) {
				if (owner.find("Post") != string::npos) {
					break;
				}

				if (com[currentuser] == nullptr) {
					com[currentuser] = new Comments();
				}

				if (owner.empty() || text.empty()) {
					break;
				}
				else {
					com[currentuser]->setname(owner);
					com[currentuser]->settext(text);
					//com[currentuser]->setlikesusers(likes);
					com[currentuser]->display();
				}
			}
		}

		char c3;
		cout << "Press A if you want to create a new post : " << endl;
		cin >> c3;

		if (c3 == 'A') {
			if (postCount < MAX) {
				postCount++;
				string g;
				cout << "What do you want to post : " << endl;
				cin.ignore();
				getline(cin, g);
				posts[currentuser]->create(g);
				cout << "Just know you posted :" << posts[currentuser]->newpost() << endl;
				ofstream of("timeline.txt",ios::app);
				of << endl;
				of << "        New posts : " << endl;
				of << posts[currentuser]->newpost() << endl;
			}
			else {
				cout << "your post limit is complete : " << endl;
			}
		}
	}

	void viewpages() {
		ifstream f("comment.txt");
		bool flag1 = false,flag=false;
		string s;

		while (getline(f, s)) {
			if (s.find("Pages") != string::npos) {
						flag1 = true;
						break;
					
			}
		}

		if (flag1) {
			while (getline(f, s)) {
				if (s == name) {
					flag = true;
					break;
				}
			}
		}


		if (flag) {
			while (getline(f, s) && count<5) {
				if (s.find("Pages") != string::npos) {
					break;
				}
				cout << s << endl;
				count++;
			}
		}
	}

	void viewnotification() {
		ifstream n("info.txt");
		string notification;
		bool foundNotifications = false;

		while (getline(n, notification)) {
			if (notification == "Notifications") {
				foundNotifications = true;
				break;
			}
		}

		if (!foundNotifications) {
			cout << "No notifications section found in the file." << endl;
			return;
		}

		bool userFound = false;
		while (getline(n, notification)) {
			if (notification == name) {
				userFound = true;
				break;
			}
		}

		if (!userFound) {
			cout << "No notifications for user: " << name << endl;
			return;
		}

		string allNotifications = "";
		while (getline(n, notification)) {
			if (notification.empty() || notification.find("Notifications") != string::npos) {
				break;
			}
			allNotifications += notification + "\n";
		}

		if (pl[currentuser] == nullptr) {
			pl[currentuser] = new personalinfo();
		}
		pl[currentuser]->getnotification(allNotifications);

		cout << "Notifications for " << name << ":" << endl;
		cout << pl[currentuser]->seenotifications();
	}

	void feed() {
		ifstream of("feed.txt");
		string *feed=new string[100];
		bool flag = false;
		int c = 0;

		while (getline(of, feed[c])) {
			if (feed[c] == name) {
				
				//c++;
				flag = true;
				break;
			}
			
		}

		if (flag) {
			while (getline(of, feed[c])) {
				if (feed[c].empty()) {
					break;
				}
				else {

					cout << feed[c] << endl;
					c++;
				}

			}
		}
		char c4;
		cout << "Do you want to share your opinion : ";
		cin >> c4;
		if (c4 == 'A') {
			int id;
			cout << "enter which post you want to see : " << endl;
			cin >> id;
			cout << feed[id-1] << endl;
			cout << "press A to like the post :";
			cin >> c4;
			
				if (c4 == 'A') {
					cout << "You Liked the post " << endl;
				}
				cout << "press B to comment the post : ";
				cin >> c4;
				 if (c4 == 'B') {
					string s;
					cout << "enter your comment : " << endl;
					cin.ignore();
					getline(cin, s);
					cout <<  name << " commented : " << s << endl;
				}
		}

	}

	void pagesinformation() {
		ifstream f("comment.txt");
		string s;
		bool flag = false,flag1=false;
		int post = 0;
		
		while (getline(f, s)) {
			if (s == "Pages information :") {
				
				flag = true;
				break;
			}
		}

		if (flag) {
			while (getline(f, s)) {
				if (s == name) {
					flag1 = true;
					break;
				}
			}
		}

		if (flag1) {
			
			while (getline(f, s)) {
				if (s.empty()) {
					break;
				}

				if (p[currentuser] == nullptr) {
					p[currentuser] = new pages();
				}

				p[currentuser]->addpage(s);
				post++;
				cout << p[currentuser]->getpage() << endl;
			}
		}
		
	}

	void viewmessages() {
		ifstream in("messages.txt");

		string* messages = new string[100];
		int messageCount = 0;
		bool foundUserMessages = false;

		cout << "Messages:" << endl;

		while (getline(in, messages[messageCount])) {
			
			if (messages[messageCount] == name) {
				foundUserMessages = true;
				while (getline(in, messages[messageCount])) {
					if (messages[messageCount].empty()) {
						
						break;
					}
					messageCount++;
					cout << messageCount << ": " << messages[messageCount - 1] << endl;
				}
				break; 
			}
		}

		if (!foundUserMessages || messageCount == 0) {
			cout << "No messages found for user: " << name << endl;
			delete[] messages;
			return;
		}

		cout << "Total messages: " << messageCount << endl;

		int messageIndex = 0;
		cout << "Enter the no of the messages you want to reply to (0 to cancel): ";
		cin >> messageIndex;

		if (messageIndex < 1 || messageIndex > messageCount) {
			cout << "Invalid selection Exiting." << endl;
			delete[] messages;
			return;
		}

		string selectedMessage = messages[messageIndex - 1];
		cout << "You selected: " << selectedMessage << endl;

		cin.ignore(); 
		string reply;
		cout << "Enter your reply: ";
		getline(cin, reply);

		sendmessages(selectedMessage, reply);

		delete[] messages;
		in.close();
	}

		void sendmessages(const string& selectedMessage, const string& reply) {
			ofstream of("messages.txt", ios::app);
			
				of << endl;
				of << "                    Replies : " << endl;
				of << "Reply to: " << selectedMessage << endl;
				of << "My reply is: " << reply << endl;

				cout << "Message sent successfully." << endl;
			
			of.close();
		}

};

class app : public user {
	string name;
	string password;

public:
	app() {
		cout << "enter username : " << endl;
		getline(cin, name);
		cout << "enter password : " << endl;
		getline(cin, password);

		user u(name, password);
		while (!u.compare()) {
			cout << "wrong username or password : " << endl;

			cout << "enter username : " << endl;
			getline(cin, name);

			cout << "enter password : " << endl;
			getline(cin, password);
			u = user(name, password);
		}



		cout << "login successfully" << endl;

		int choice;
		do {

			cout << "press 1 for personal information : " << endl;
			cout << "press 2 for timeline : " << endl;
			cout << "press 3 to view pages you have liked : " << endl;
			cout << "press 4 to see notification bar : " << endl;
			cout << "press 5 to see user feed : " << endl;
			cout << "press 6 to view pages information : " << endl;
			cout << "press 7 to view messages : " << endl;
			cin >> choice;

			if (choice == 1) {
				cout << "                                                  Personal Information   " << endl;
				cout << endl;
				u.getinfo();
			}

			else if (choice == 2) {
				cout << "                                                  My Feed   " << endl;
				cout << endl;
				u.viewpost();

			}

			else if (choice == 3) {
				cout << "                                                  Pages   " << endl;
				cout << endl;
				u.viewpages();

			}
			else if (choice == 4) {
				cout << "                                                  Notification Bar   " << endl;
				cout << endl;
				u.viewnotification();
			}

			else if (choice == 5) {
				cout << "                                                  Timeline   " << endl;
				cout << endl;
				u.feed();
			}

			else if (choice == 6) {
				cout << "                                                  Pages Information  " << endl;
				cout << endl;
				u.pagesinformation();
			}
			else if (choice == 7) {
				cout << "                                                  Messanger   " << endl;
				cout << endl;
				u.viewmessages();
				
				//u.sendmessages(s);
			}
		} 
		while (choice != 8);

	}
};
