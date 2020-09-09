#include "UserManager.h"
#include <LogManager.h>

UserManager::UserManager()
{
}

UserManager::~UserManager()
{
	m_mapUserList.clear();
}

bool UserManager::AddUser(const int& nSocketIndex, const std::string& NickName)
{
	using namespace Bass;
	if (m_mapUserList.end() != m_mapUserList.find(nSocketIndex))
	{
		LogManager::GetInstance().Warning(L"Socket(%d) Already Added In UserManager", nSocketIndex);
		return false;
	}

	m_mapUserList.insert_or_assign(nSocketIndex, NickName);
	m_vecConnectedList.push_back(nSocketIndex);
	return true;
}

void UserManager::RemoveUser(const int& nSocketIndex)
{
	if (m_mapUserList.end() != m_mapUserList.find(nSocketIndex))
	{
		for (auto it = m_vecConnectedList.begin(); it != m_vecConnectedList.end(); ++it)
		{
			if (*it == nSocketIndex)
			{
				m_vecConnectedList.erase(it);
				break;
			}
		}

		m_mapUserList.erase(nSocketIndex);
	}
}

std::string UserManager::GetUserNickName(const int& nSocketIndex)
{
	auto it = m_mapUserList.find(nSocketIndex);
	if (it != m_mapUserList.end())
		return it->second;
	return std::string();
}

std::vector<int>& UserManager::GetConnectedList()
{
	return m_vecConnectedList;
}
