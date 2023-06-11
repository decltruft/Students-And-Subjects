#include <Windows.h>

#include "users_controller.h"

// ПАРОЛЬ ОТ АККАУНТА admin - admin228
// ПАРОЛЬ ОТ АККАУНТА random_user - qwerty123

void show_head();
void PROGRAMMING_LOOP_FUNCTION();

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    PROGRAMMING_LOOP_FUNCTION();

    system("pause");
    return 0;
}

void PROGRAMMING_LOOP_FUNCTION()
{
    show_head();

    std::shared_ptr<students_list> list_of_students = std::make_shared<students_list>();
    std::shared_ptr<subjects_list> list_of_subjects = std::make_shared<subjects_list>(*list_of_students);
    std::shared_ptr<users_controller> list_of_users = std::make_shared<users_controller>();

    std::unique_ptr<IUser> user;

    std::string nickname, password;

    char choice;
    std::cout << "Нет аккаунта? Хотите зарегистрироваться? (y/n): ";
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        std::string new_username, new_password, repeating_password;

        std::cin.get();
        std::cout << "Имя нового пользователя: ";
        std::getline(std::cin, new_username);

        std::cout << "Пароль нового пользователя: ";
        std::getline(std::cin, new_password);
        std::cout << "Повторите пароль: ";
        std::getline(std::cin, repeating_password);

        if (new_password == repeating_password)
        {
            default_user new_user(new_username, IUser::Hash(new_password));
            if (!list_of_users->add_new_users_account(new_user))
                std::cout << "Пользователь с таким именем уже существует!\n";
        }

    }

    std::cin.get();
    std::cout << "Введите имя пользователя: ";
    std::getline(std::cin, nickname);
    std::cout << "Введите пароль: ";
    std::getline(std::cin, password);

    if (!list_of_users->is_user_exist(nickname))
    {
        std::cout << "Данный пользователь не зарегистрирован в системе!\n";
        return;
    }
    else if (!list_of_users->is_correct_password(nickname, IUser::Hash(password)))
    {
        std::cout << "Неверный пароль пользователя!\n";
        return;
    }

    if (list_of_users->get_users_role(nickname) == 0)
        user = std::make_unique<default_user>(**(list_of_users->get_user(nickname)));
    else
        user = std::make_unique<administrator>(**(list_of_users->get_user(nickname)));
   
    user->set_set_users_lists(list_of_subjects, list_of_students);
    user->set_users_controller(list_of_users);

    system("pause");
    system("cls");

    user->users_interface_loop();
}

void show_head()     
{
    time_t now;
    std::tm nowLocal;

    now = time(NULL);
    localtime_s(&nowLocal, &now);

    std::cout << "=======================================================================================================================" << std::endl;
    std::cout << "\t\t\t\t\t      " << nowLocal.tm_mday << '.' << nowLocal.tm_mon + 1 << '.' << nowLocal.tm_year + 1900 << std::endl;
    std::cout << "\t\t\t\t\t\t" << nowLocal.tm_hour << ':' << nowLocal.tm_min << std::endl;
    std::cout << "=======================================================================================================================\n";
    std::cout << "\t\t\t\tРазработал: Нестюк Сергей Олегович, гр. 213871\n\t\t\t\t\tРуководитель: Рыбак Виктор Александрович\n\t\t\t\t\t\t© 2023" << std::endl;
    std::cout << "=======================================================================================================================\n\n\n";
}
