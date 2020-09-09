#pragma once
#include <Singleton.h>
#include <string>
#include <unordered_map>

class UserManager : public Bass::Singleton<UserManager>
{
public:
	UserManager();
	virtual ~UserManager();

	bool AddUser(const int& nSocketIndex, const std::string& NickName);
	void RemoveUser(const int& nSocketIndex);
	std::string GetUserNickName(const int& nSocketIndex);

	std::vector<int>& GetConnectedList();

private:
	std::unordered_map<int, std::string> m_mapUserList;	// SocketIndex, NickName
	std::vector<int> m_vecConnectedList;

};

