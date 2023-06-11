#include "IUser.h"

IUser::~IUser()
{
	
}

unsigned IUser::Hash(const std::string& input)
{
	unsigned int Init = 124564352;
	unsigned int Magic = 5674356;
	unsigned int Hash = Init;
	for (size_t i(0); i < input.length(); ++i)
	{
			Hash = Hash ^ (input[i]);
			Hash = Hash * Magic;
	}
		return Hash;
}

IUser::IUser(const std::string& uname, unsigned int hash)
	: _username(uname), _password_hash(hash), _role(0), _is_activated(0)
{
}

IUser::IUser(users_buffer&& buff) :
	_username(buff._username), _password_hash(buff._password_hash), _role(buff._role), _is_activated(buff._is_activated),
	_subjects_list(nullptr), _students_list(nullptr)
{

}

IUser::IUser(const IUser& other) :
	_username(other._username), _password_hash(other._password_hash), _is_activated(other._is_activated), _role(other._role),
	_students_list(nullptr), _subjects_list(nullptr)
{
}

void IUser::set_set_users_lists(std::shared_ptr<subjects_list> subj_l, std::shared_ptr<students_list> stud_l)
{
	_subjects_list = subj_l;
	_students_list = stud_l;
}

std::ostream& operator<<(std::ostream& os, const IUser& user)
{
	os << user._username << ' ' << user._password_hash << ' '
		<< user._role << ' ' << user._is_activated << std::endl;

	return os;
}

void IUser::set_username(const std::string& new_name)
{
	_username = new_name;
}

void IUser::set_password(const std::string& new_password)
{
	_password_hash = Hash(new_password);
}

void IUser::set_role(unsigned new_role)
{
	_role = new_role;
}

void IUser::set_activation(bool new_activation)
{
	_is_activated = new_activation;
}

std::shared_ptr<students_list> IUser::get_students_list()
{
	return _students_list;
}

std::shared_ptr<subjects_list> IUser::get_subjects_list()
{
	return _subjects_list;
}

std::string IUser::get_username() const
{
	return _username;
}

unsigned IUser::get_password_hash() const
{
	return _password_hash;
}

unsigned short IUser::get_role() const
{
	return _role;
}

bool IUser::is_activated() const
{
	return _is_activated;
}
