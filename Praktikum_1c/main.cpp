#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "List.h"
#include "tweet.h"
using namespace std;

int main(void)
{
	List<tweet> Tweets;
	string Text;
	
	Tweets.format("Tweet\n--->\n", "\n", "\n--->\n");
	while (true)
	{
		cout << "\nNachricht: ";
        //cin >> Text;
        char tmpText[140];
        cin.getline(tmpText, 140);
        Text = tmpText;
		if (Text == "quit") break;
		Tweets.InsertFront(tweet(Text));

		cout << Tweets;
	}

	return 0;
}
