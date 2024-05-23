#pragma once

constexpr std::size_t MAX_USER_NAME = 6;
constexpr std::size_t FILE_NAME_MAX_SIZE = 256;

struct UserData {
	wchar_t userName[MAX_USER_NAME+1];	// null ternimated wchar string
	int playerBlessIndex;
	int gen;
	int depth;
	int score;
};

struct PlayHistory {
	int maxScoreUserIndex;
	int numPlayedUsers;
	std::vector<UserData> userHistory;
};

struct FetchData {
	int numPlayedUsers;
	UserData maxScoreUser;
	UserData prevUser;
	UserData currUser;
};

class GameDataHub {
	wchar_t _filedir[FILE_NAME_MAX_SIZE];

	bool _requestUpdate;
	PlayHistory _hist{ -1, 0 };
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
			std::wistringstream wss(wline);
			std::wstring wtoken;

			if (firstline) {
				std::getline(wss, wtoken, L',');
				_hist.maxScoreUserIndex = _wtoi(wtoken.c_str());
				
				std::getline(wss, wtoken, L',');
				_hist.numPlayedUsers = _wtoi(wtoken.c_str());

				firstline = false;
				continue;
			} 

			UserData user;
			std::getline(wss, wtoken, L',');
			wcsncpy_s(user.userName, wtoken.c_str(), MAX_USER_NAME);
			
			std::getline(wss, wtoken, L',');
			user.playerBlessIndex = _wtoi(wtoken.c_str());
			
			std::getline(wss, wtoken, L',');
			user.gen = _wtoi(wtoken.c_str());
			
			std::getline(wss, wtoken, L',');
			user.depth = _wtoi(wtoken.c_str());
			
			std::getline(wss, wtoken, L',');
			user.score = _wtoi(wtoken.c_str());

			_hist.userHistory.push_back(user);
		}
	}

	void SaveHistoryToFile() {
		std::wofstream wofile(_filedir, std::ios::trunc);
		if (!wofile) 
			throw std::exception("Hub: Can't open file!");

		wofile << _hist.maxScoreUserIndex << ','
			<< _hist.numPlayedUsers << std::endl;
		for (const auto& user : _hist.userHistory) {
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

public:
	/**
	 * @brief 현재 가지고 있는 유저 대이타를 스트럭화 해서 유저 히스토리에 푸쉬합니다.
	 */
	void DispatchCurrentUserData() {
		int maxScore = 0;
		if (_hist.maxScoreUserIndex == -1)
		{
			maxScore = 100;
		}
		else
			maxScore = _hist.userHistory[_hist.maxScoreUserIndex].score;

		// Update Play History
		_hist.maxScoreUserIndex =
			(maxScore < _currUser.score) * _hist.userHistory.size() +
			(maxScore >= _currUser.score) * _hist.maxScoreUserIndex;
		_hist.numPlayedUsers += 1;

		// Push the current user data
		_hist.userHistory.push_back(_currUser);

		// Empty the current user.
		__ResetCurrentUser();

		// Notify that the update is required.
		_requestUpdate = true;
	}

	/**
	 * @brief 업데이트 된 중요 유저 데이터들을 가져옵니다. 중요 유저 데이터란,
	 * 가장 높은 점수를 얻은 유저, 가장 최근에 플레이한 유저, 현재 유저를 의미합니다.
	 * @return FetchData
	 */
	FetchData FetchUpdatedUserData() {
		if (_requestUpdate)
			throw std::exception("There is no fetchable data!");

		_requestUpdate = false;
		return {
			_hist.numPlayedUsers,
			_hist.userHistory[_hist.maxScoreUserIndex],
			_hist.userHistory.back(),
			_currUser
		};
	}

	/**
	 * @brief 엔트리 씬에서 씬 데이터의 업데이트가 필요한지 확인합니다.
	 * @return 
	 */
	bool NeedUpdate() {
		return _requestUpdate;
	}

	// Getters
	int GetMaxScore() {
		if (_hist.userHistory.empty())
			return 100;
		return _hist.userHistory[_hist.maxScoreUserIndex].score;
	}

	UserData GetMaxScoreUser() {
		if (_hist.userHistory.empty())
			return { L"None", -1, -1, -1, 100 };
		return _hist.userHistory[_hist.maxScoreUserIndex];
	}

	int GetCurrentGeneration() {
		return _hist.numPlayedUsers + 33;
	}

	UserData GetPreviousUser() {
		if (_hist.userHistory.empty())
			return { L"None", -1, -1, -1, 60 };
		return _hist.userHistory.back();
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

	void __ResetCurrentUser() {
		_currUser.userName[0] = L'\n';
		_currUser.playerBlessIndex = -1;
		_currUser.gen = GetCurrentGeneration();
		_currUser.depth = -1;
		_currUser.score = -1;
	}
};