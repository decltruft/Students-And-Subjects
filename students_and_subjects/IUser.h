#pragma once

#include <iostream>

#include "students_list.h"
#include "subjects_list.h"

class users_controller;

class IUser
{
public:
	struct users_buffer
	{
		std::string		_username = " ";
		unsigned		_password_hash = 0;
		unsigned short _role = 0;
		bool		   _is_activated = false;
	};

	static unsigned Hash(const std::string&);

public:
	IUser(const std::string&, unsigned int);
	IUser(users_buffer&&);
	IUser(const IUser&);

public:
	virtual void users_interface_loop() = 0;
	virtual void set_users_controller(std::shared_ptr<users_controller>) = 0;
	void		 set_set_users_lists(std::shared_ptr<subjects_list> subj_l = nullptr, std::shared_ptr<students_list> stud_l = nullptr);

	friend std::ostream& operator<<(std::ostream&, const IUser&);

public:
	void set_username(const std::string&);
	void set_password(const std::string&);
	void set_role(unsigned);
	void set_activation(bool);

	std::shared_ptr<students_list> get_students_list();
	std::shared_ptr<subjects_list> get_subjects_list();

	std::string    get_username() const;
	unsigned       get_password_hash() const;
	unsigned short get_role() const;
	bool           is_activated() const;

public:
	virtual ~IUser();

private:
	std::string		_username;
	unsigned		_password_hash;
	unsigned short _role;
	bool		   _is_activated;

	std::shared_ptr<students_list> _students_list;
	std::shared_ptr<subjects_list> _subjects_list;
};

