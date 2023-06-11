#pragma once

#include "default_user.h"

class administrator;

class users_controller
{
public:
    users_controller();

    void show_users_list() const;

public:
    bool add_new_users_account(IUser&);
    bool remove_users_account(const std::string&);

    bool is_user_exist(const std::string&) const;
    bool is_correct_password(const std::string&, const unsigned int) const;
    unsigned short get_users_role(const std::string&) const;
    std::vector<std::unique_ptr<IUser>>::iterator get_user(const std::string&);

    bool change_users_nickname(const std::string&, const std::string&);
    bool change_users_password(const std::string&, const std::string&);
    bool change_users_role(const std::string&, unsigned short);
    bool change_users_access(const std::string&, bool);

    void sorting_users_by_nickname();
    void sorting_users_by_role();
    void sorting_users_by_activation();

public:

    ~users_controller();

private:
    const std::string _FILENAME = "users_info.txt";

    std::vector<std::unique_ptr<IUser>> _users;

    void _download_from_file_and_creat_list();
    void _upload_to_file();

    void print_symbol(char, int) const;
};



class administrator :
    public IUser
{
public:
    administrator(IUser::users_buffer&&);
    administrator(const IUser&);

    void set_users_controller(std::shared_ptr<users_controller>);

public:
    void users_interface_loop() override;

public:
    virtual ~administrator();

private:
    std::shared_ptr<users_controller> _controller;

};
