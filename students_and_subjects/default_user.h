#pragma once

#include "IUser.h"

class default_user :
    public IUser
{
public:
    default_user(const std::string&, unsigned int);
    default_user(IUser::users_buffer&&);
    default_user(const IUser&);


public:
    void users_interface_loop() override;
    void set_users_controller(std::shared_ptr<users_controller>) override;

    virtual ~default_user();
private:

};

