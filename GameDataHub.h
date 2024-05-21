#pragma once

constexpr std::size_t MAX_USER_NAME = 6;

struct UserData {
	char userName[MAX_USER_NAME];
	int gen;
	int depth;
	int score;
};

struct History {
	int maxScore;
	int numPlayedUsers;
	UserData* history;
};

class GameDataHub {
	bool _requestUpdate;
	
public:


	bool SaveUserData(const UserData& newUserData) {
		return true;
	}

};