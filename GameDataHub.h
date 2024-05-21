#pragma once

constexpr std::size_t MAX_USER_NAME = 6;
constexpr std::size_t FILE_NAME_MAX_SIZE = 256;

struct UserData {
	wchar_t userName[MAX_USER_NAME];
	int playerBlessIndex;
	int gen;
	int depth;
	int score;
};

struct PlayHistory {
	int maxScore;
	int numPlayedUsers;
	std::vector<UserData> userHistory;
};

struct FetchData {
	int maxScore;
	int numPlayedUsers;
	UserData prevUser;
};

class GameDataHub {
	wchar_t _filedir[FILE_NAME_MAX_SIZE];

	bool _requestUpdate;
	PlayHistory _playHistory;
	UserData _currUser;
public:
//////////// FILE STREAMS ////////////////////////////////
	void LoadHistoryFromFile(const wchar_t* filename) {
		wcsncpy_s(_filedir, filename, FILE_NAME_MAX_SIZE);

		std::wifstream wifile(filename);
		if (!wifile)
			throw std::exception("Hub: Can't open file!");
		
		bool firstline{ true };
		std::wstring wline;
		while (std::getline(wifile, wline)) {
			if (firstline) {
				std::wistringstream wss(wline);
				std::wstring wtoken;
				std::getline(wss, wtoken, L',');
				_playHistory.maxScore = _wtoi(wtoken.c_str());
				
				std::getline(wss, wtoken, L',');
				_playHistory.numPlayedUsers = _wtoi(wtoken.c_str());

				firstline = false;
				continue;
			} 

			UserData user;
			std::wistringstream wss(wline);
			std::wstring wtoken;
			std::getline(wss, wtoken, L',');
			wcsncpy_s(user.userName, wtoken.c_str(), FILE_NAME_MAX_SIZE);
			
			std::getline(wss, wtoken, L',');
			user.playerBlessIndex = _wtoi(wtoken.c_str());
			
			std::getline(wss, wtoken, L',');
			user.gen = _wtoi(wtoken.c_str());
			
			std::getline(wss, wtoken, L',');
			user.depth = _wtoi(wtoken.c_str());
			
			std::getline(wss, wtoken, L',');
			user.score = _wtoi(wtoken.c_str());

			_playHistory.userHistory.push_back(user);
		}
	}

	void SaveHistoryToFile() {
		std::wofstream wofile(_filedir, std::ios::trunc);
		if (!wofile) 
			throw std::exception("Hub: Can't open file!");

		wofile << _playHistory.maxScore << ','
			<< _playHistory.numPlayedUsers << std::endl;
		for (const auto& user : _playHistory.userHistory) {
			std::wstring wline;
			std::wostringstream woss(wline);

			wofile << user.userName << ','
				<< user.playerBlessIndex << ','
				<< user.gen << ','
				<< user.depth << ','
				<< user.score << std::endl;
		}
	}
//////////////////////////////////////////////////////////

	void Init() {
		__InitPlayHistory();
		__ResetCurrentUser();
	}

public:
	void DispatchCurrentUserData() {
		// Update Play History
		_playHistory.maxScore =
			(_playHistory.maxScore < _currUser.score) * _currUser.score +
			(_playHistory.maxScore >= _currUser.score) * _playHistory.maxScore;
		_playHistory.numPlayedUsers += 1;
		_playHistory.userHistory.push_back(_currUser);

		// Empty the current user.
		__ResetCurrentUser();

		_requestUpdate = true;
	}

	FetchData FetchUpdatedUserData() {
		if (_requestUpdate)
			throw std::exception("There is no fetchable data!");

		_requestUpdate = false;
		return {
			_playHistory.maxScore,
			_playHistory.numPlayedUsers,
			_playHistory.userHistory.back()
		};
	}

	// Getters
	int GetMaxScore() {
		return _playHistory.maxScore;
	}

	int GetCurrentGeneration() {
		return _playHistory.numPlayedUsers + 33;
	}

	UserData GetPreviousUser() {
		return _playHistory.userHistory.back();
	}

	// Current User Data
	void SetCurrentUserName(const wchar_t* name) {
		wcsncpy_s(_currUser.userName, name, FILE_NAME_MAX_SIZE);
	}

	void SetCurrentUserBlessIndex(int blessIndex) {
		_currUser.playerBlessIndex = blessIndex;
	}

	void SetCurrentUserDepth(int depth) {
		_currUser.depth = depth;
	}

	void SetCurrentUserScore(int score) {
		_currUser.score = score;
	}

	int GetCurrentUserBlessIndex() {
		return _currUser.playerBlessIndex;
	}

	UserData GetCurrentUser() {
		return _currUser;
	}

private:
	void __InitPlayHistory() {
		// Find max score
		int max = -1;
		int count = 0;
		for (const auto& userData : _playHistory.userHistory) {
			max = (userData.score > max) * userData.score
				+ (userData.score <= max) * max;
			++count;
		}
		_playHistory.maxScore = max;
		_playHistory.numPlayedUsers = count;
	}

	void __ResetCurrentUser() {
		_currUser.userName[0] = L'\n';
		_currUser.playerBlessIndex = -1;
		_currUser.gen = GetCurrentGeneration();
		_currUser.depth = -1;
		_currUser.score = -1;
	}
};