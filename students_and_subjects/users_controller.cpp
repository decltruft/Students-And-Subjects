#include "users_controller.h"


users_controller::users_controller()
{
	_download_from_file_and_creat_list();
}

void users_controller::show_users_list() const
{
	const size_t count = 61;
	print_symbol('=', count);
	std::cout << std::endl;

	size_t _width = 9;

	std::wcout << "|№" << " |    Никнейм    |     Хеш-пароля     | Роль | Разрешение |  " << std::endl;

	print_symbol('=', count);
	std::cout << std::endl;
	size_t index = 0;


	for (const auto& it : _users)
	{
		std::cout << '|' << index + 1;
		print_symbol(' ', 2 - std::to_string(index).size());
		std::cout << '|' << it->get_username();
		print_symbol(' ', 15 - it->get_username().size());
		std::cout << '|' << it->get_password_hash();
		print_symbol(' ', 20 - std::to_string(it->get_password_hash()).size());
		std::cout << "|  " << it->get_role() << "   |";
		std::cout << "     " << it->is_activated() << "      |\n";

		print_symbol('-', count);
		std::cout << std::endl;

		++index;
	}
}

bool users_controller::add_new_users_account(IUser& new_user)
{
	auto result = std::find_if(_users.begin(), _users.end(), [&new_user](const std::unique_ptr<IUser>& u)
		{return u->get_username() == new_user.get_username(); });

	if (result != _users.end())
		return false;

	_users.push_back(std::make_unique<default_user>(new_user.get_username(), new_user.get_password_hash()));
	return true;
}

bool users_controller::remove_users_account(const std::string& uname)
{
	auto result = std::find_if(_users.begin(), _users.end(), [&uname](const std::unique_ptr<IUser>& u)
		{return u->get_username() == uname; });

	if (*result == nullptr)
		return false;

	_users.erase(result);
	return true;
}

bool users_controller::is_user_exist(const std::string& username) const
{
	auto result = std::find_if(_users.begin(), _users.end(), [&username](const std::unique_ptr<IUser>& u) 
		{ return u->get_username() == username; });

	if (result == _users.end())
		return false;
	else
		return true;
}

bool users_controller::is_correct_password(const std::string& username, const unsigned int hash) const
{
	auto result = std::find_if(_users.begin(), _users.end(), [&username](const std::unique_ptr<IUser>& u)
		{ return u->get_username() == username; });

	if ((*result)->get_password_hash() != hash)
		return false;
	else
		return true;
}

unsigned short users_controller::get_users_role(const std::string& uname) const
{
	auto result = std::find_if(_users.begin(), _users.end(), [&uname](const std::unique_ptr<IUser>& u)
		{return u->get_username() == uname; });
	
	if (result == _users.end())
		return 0;
	else if ((*result)->get_role() == 0)
		return 0;
	else
		return 1;
}

std::vector<std::unique_ptr<IUser>>::iterator users_controller::get_user(const std::string& uname)
{
	return std::find_if(_users.begin(), _users.end(), [&uname](const std::unique_ptr<IUser>& u)
		{return u->get_username() == uname; });
}

bool users_controller::change_users_nickname(const std::string& uname, const std::string& new_username)
{
	auto result = std::find_if(_users.begin(), _users.end(), [&uname](const std::unique_ptr<IUser>& u)
		{return u->get_username() == uname; });

	if (result == _users.end())
		return false;

	(*result)->set_username(new_username);
	return true;
}

bool users_controller::change_users_password(const std::string& uname, const std::string& new_pass)
{
	auto result = std::find_if(_users.begin(), _users.end(), [&uname](const std::unique_ptr<IUser>& u)
		{return u->get_username() == uname; });

	if (result == _users.end())
		return false;

	(*result)->set_password(new_pass);

	return true;
}

bool users_controller::change_users_role(const std::string& uname, unsigned short new_role)
{
	auto result = std::find_if(_users.begin(), _users.end(), [&uname](const std::unique_ptr<IUser>& u)
		{return u->get_username() == uname; });

	if (result == _users.end())
		return false;

	(*result)->set_role(new_role);
	return true;
}

bool users_controller::change_users_access(const std::string& uname, bool new_access)
{
	auto result = std::find_if(_users.begin(), _users.end(), [&uname](const std::unique_ptr<IUser>& u) 
		{return u->get_username() == uname; });
	
	if(result == _users.end())
		return false;

	(*result)->set_activation(new_access);
	return true;
}

void users_controller::sorting_users_by_nickname()
{
	std::sort(_users.begin(), _users.end(), [](const std::unique_ptr<IUser>& u1, const std::unique_ptr<IUser>& u2) 
		{ return u1->get_username() < u2->get_username(); });
}

void users_controller::sorting_users_by_role()
{
	std::sort(_users.begin(), _users.end(), [](const std::unique_ptr<IUser>& u1, const std::unique_ptr<IUser>& u2) 
		{ return u1->get_role() > u2->get_role(); });
}

void users_controller::sorting_users_by_activation()
{
	std::sort(_users.begin(), _users.end(), [](const std::unique_ptr<IUser>& u1, const std::unique_ptr<IUser>& u2) 
		{ return u1->is_activated() > u2->is_activated(); });
}


users_controller::~users_controller()
{
	_upload_to_file();
}

void users_controller::_download_from_file_and_creat_list()
{
	std::ifstream users_info_file(_FILENAME);
	if (!users_info_file.is_open())
	{
		std::string exception_message = "Your file" + _FILENAME + "has not been opened";
		throw std::exception(exception_message.c_str());
	}

	IUser::users_buffer buffer;

	while (users_info_file >> buffer._username >> buffer._password_hash >> buffer._role >> buffer._is_activated)
	{
		if (buffer._role == 1)
			_users.emplace_back(std::move(std::make_unique<administrator>(std::move(buffer))));
		else
			_users.emplace_back(std::move(std::make_unique<default_user>(std::move(buffer))));
	}
}

void users_controller::_upload_to_file()
{
	std::ofstream users_info_file("new_1.txt");
	if (!users_info_file.is_open())
	{
		std::string exception_message = "Your file" + _FILENAME + "has not been opened";
		throw std::exception(exception_message.c_str());
	}

	for (auto& it : _users)
		users_info_file << it->get_username() << ' ' << it->get_password_hash() <<
		' ' << it->get_role() << ' ' << it->is_activated() << std::endl;

	users_info_file.close();
	std::remove(_FILENAME.c_str());
	std::rename("new_1.txt", _FILENAME.c_str());
}

void users_controller::print_symbol(char symb, int count) const
{
	for (int i{ 0 }; i < count; ++i)
		std::cout << symb;
}

administrator::~administrator()
{

}

administrator::administrator(IUser::users_buffer&& buff)
	: IUser(std::forward<IUser::users_buffer&&>(buff)), _controller(nullptr)
{
}

administrator::administrator(const IUser& other) : 
	IUser(other)
{
}

void administrator::set_users_controller(std::shared_ptr<users_controller> users_c)
{
	_controller = users_c;
}

void administrator::users_interface_loop()
{
	if (!this->is_activated())
	{
		std::cout << "Ваш аккаунт не активирован! Попросите администратора активировать его!\n";
		return;
	}

	char choice;
	std::wstring f_name, name, sname, gr_name, new_fname, new_name, new_sname, new_grname;
	std::string nickname, new_nickname, new_password;
	unsigned short new_role;
	bool new_activation, eng, mathm, prog, phys, db;
	double avr_GPA;

	MAIN_MENU:
	system("pause");
	system("cls");

	std::cout << "1.Режим пользователя\n2.Панель администратора\n3.Выйти\n\nВаш выбор: ";
	std::cin >> choice;
	
	if (choice == '1')
	{
		do
		{
			USERS_MENU:
			system("pause");
			system("cls");

			std::cin.get();
			std::cout << "1.Просмотра списка учащихся\n2.Просмотр списка факультативов\n3.Сортировка учащихся\n4.Индивидуальное задание\n5.Вернуться назад\n\nВаш выбор: ";
			std::cin >> choice;

			switch (choice)
			{
			case '1':
				system("pause");
				system("cls");

				this->get_students_list()->show_list();

				system("pause");
				system("cls");
				break;

			case '2':
				system("pause");
				system("cls");

				this->get_subjects_list()->show();

				system("pause");
				system("cls");
				break;

			case '3':
			SORT_MENU:
				system("pause");
				system("cls");

				std::cout << "1.Сортировка по фамилии\n2.Сортировка по имени группы\n3.Сортировка по среднему баллу\n4.Вернуться назад\n" <<
					"\n\nВаш выбор: ";
				std::cin >> choice;

				switch (choice)
				{
				case '1':
					system("pause");
					system("cls");

					this->get_students_list()->sort_by_family_name();
					this->get_students_list()->show_list();

					break;

				case '2':
					system("pause");
					system("cls");

					this->get_students_list()->sort_by_group_name();
					this->get_students_list()->show_list();

					break;

				case '3':
					system("pause");
					system("cls");

					this->get_students_list()->sort_by_average_GPA();
					this->get_students_list()->show_list();

					break;

				case '4':
					goto USERS_MENU;
					break;

				default:
					break;
				}

				system("pause");
				system("cls");
				break;

			case '4':
				this->get_subjects_list()->personal_task_to_show_after_sorting();

				system("pause");
				system("cls");
				break;
			
			case '5':
				goto MAIN_MENU;
				break;

			default:
				break;
			}
		} while (choice != 'q');
	}
	else if (choice == '2')
	{
		do
		{
			ADMIN_MENU:
			system("pause");
			system("cls");

			std::cin.get();
			std::cout << "1.Работа со списком пользователей\n2.Работа со списком занятий и учащихся\n3.Назад\n\nВаш выбор: ";
			std::cin >> choice;

			switch (choice)
			{
			case '1':
				ADMIN_MODE:
				system("pause");
				system("cls");

				_controller->show_users_list();

				std::cin.get();
				std::cout << "1.Изменить никнейм\n2.Изменить пароль\n3.Изменить роль\n4.Заблокировать/разблокировать\n" <<
					"5.Сортировать пользователей\n6.Удалить пользователя\n7.Вернуться назад\n\nВаш выбор: ";
				std::cin >> choice;

				system("pause");
				system("cls");

				switch (choice)
				{
				case '1':
					std::cin.get();
					
					std::cout << "Введите старый никнейм: ";
					std::getline(std::cin, nickname);

					std::cout << "Введите новый никнейм: ";
					std::getline(std::cin, new_nickname);

					if (!_controller->change_users_nickname(nickname, new_nickname))
						std::cout << "Операция не удалась!\n";
					else
						std::cout << "Никнейм изменен!\n";

					break;

				case '2':
					std::cin.get();

					std::cout << "Введите никнейм: ";
					std::getline(std::cin, nickname);

					std::cout << "Введите новый пароль: ";
					std::getline(std::cin, new_password);

					if (!_controller->change_users_password(nickname, new_password))
						std::cout << "Операция не удалась!\n";
					else
						std::cout << "Пароль изменен!\n";

					break;

				case '3':
					std::cin.get();

					std::cout << "Введите никнейм: ";
					std::getline(std::cin, nickname);

					std::cout << "Введите новую роль (0 - юзер либо 1 - админ): ";
					std::cin >> new_role;
					std::cin.get();

					if (!_controller->change_users_role(nickname, new_role))
						std::cout << "Операция не удалась!\n";
					else
						std::cout << "Роль изменена!\n";

					break;

				case '4':
					std::cin.get();

					std::cout << "Введите никнейм: ";
					std::getline(std::cin, nickname);

					std::cout << "Введите пользовательский доступ (0 - заблокирован 1 - разблокирован): ";
					std::cin >> new_activation;
					std::cin.get();

					if (!_controller->change_users_access(nickname, new_activation))
						std::cout << "Операция не удалась!\n";
					else
						std::cout << "Доступ изменен!\n";

					break;

				case '5':
					std::cin.get();

					std::cout << "1.Сортировка по никнейму\n2.Сортировка по роли\n3.Сортировка по разрешению доступа\n4.Вернуться назад\n\nВаш выбор: ";
					std::cin >> choice;

					switch (choice)
					{
					case '1':
						_controller->sorting_users_by_nickname();
						_controller->show_users_list();

						break;

					case '2':
						_controller->sorting_users_by_role();
						_controller->show_users_list();

						break;

					case '3':
						_controller->sorting_users_by_activation();
						_controller->show_users_list();

						break;

					case '4': 
						goto ADMIN_MODE;

					default:
						break;
					}

					break;

				case '6':
					std::cin.get();

					std::cout << "Введите никнейм удаляемого пользователя: ";
					std::getline(std::cin, nickname);

					if (nickname == this->get_username())
					{
						std::cout << "Вы не можете удалить свой аккаунт!\n";
					}
					else
					{
						if(!_controller->remove_users_account(nickname))
							std::cout << "Операция не удалась!\n";
						else
							std::cout << "Аккаунт удален!\n";
					}

					break;
				
				case '7':
					goto ADMIN_MENU;
					break;

				default:
					break;
				}

				system("pause");
				system("cls");
				break;

			case '2':
				USERS_MODE:
				system("pause");
				system("cls");

				std::cin.get();
				this->get_students_list()->show_list();

				std::cout << "1.Добавить студента\n2.Удалить студента\n3.Изменить фамилию\n4.Изменить имя\n5.Изменить отчество\n6.Изменить группу\n" <<
					"7.Изменить средний балл\n8.Изменить участие в факультативах\n9.Вернуться назад\n\nВаш выбор:  ";
				std::cin >> choice;

				system("pause");
				system("cls");

				switch (choice)
				{
				case '1':
					std::cin.get();

					

					break;

				case '2':
					std::cin.get();

					std::cout << "Введите фамилию: ";
					std::getline(std::wcin, f_name);

					std::cout << "Введите имя: ";
					std::getline(std::wcin, name);

					std::cout << "Введите отчество: ";
					std::getline(std::wcin, sname);

					if (!this->get_subjects_list()->remove_the_student(student(f_name, name, sname)))
						std::cout << "Указанного студента не существует\n";
					else
						std::cout << "Студент удален!\n";

					this->get_students_list()->remove_the_student(student(f_name, name, sname));
					system("pause");
					system("cls");
					break;
				
				case '3':
					std::cin.get();

					std::cout << "Введите фамилию: ";
					std::getline(std::wcin, f_name);

					std::cout << "Введите имя: ";
					std::getline(std::wcin, name);

					std::cout << "Введите отчество: ";
					std::getline(std::wcin, sname);

					std::cout << "Введите новую фамилию: ";
					std::getline(std::wcin, new_fname);

					if(!this->get_subjects_list()->change_students_family_name(student(f_name, name, sname), new_fname))
						std::cout << "Указанного студента не существует\n";
					else
						std::cout << "Фамилия изменена!\n";

					this->get_students_list()->change_students_family_name(student(f_name, name, sname), new_fname);
					system("pause");
					system("cls");
					break;

				case '4':
					std::cin.get();

					std::cout << "Введите фамилию: ";
					std::getline(std::wcin, f_name);

					std::cout << "Введите имя: ";
					std::getline(std::wcin, name);

					std::cout << "Введите отчество: ";
					std::getline(std::wcin, sname);

					std::cout << "Введите новое имя: ";
					std::getline(std::wcin, new_name);

					if (!this->get_subjects_list()->change_students_name(student(f_name, name, sname), new_name))
						std::cout << "Указанного студента не существует\n";
					else
						std::cout << "Имя изменено!\n";

					this->get_students_list()->change_students_name(student(f_name, name, sname), new_name);
					system("pause");
					system("cls");
					break;
				
				case '5':
					std::cin.get();

					std::cout << "Введите фамилию: ";
					std::getline(std::wcin, f_name);

					std::cout << "Введите имя: ";
					std::getline(std::wcin, name);

					std::cout << "Введите отчество: ";
					std::getline(std::wcin, sname);

					std::cout << "Введите новое отчество: ";
					std::getline(std::wcin, new_sname);

					if (!this->get_subjects_list()->change_students_surname(student(f_name, name, sname), new_sname))
						std::cout << "Указанного студента не существует\n";
					else
						std::cout << "Отчество изменено!\n";

					this->get_students_list()->change_students_surname(student(f_name, name, sname), new_sname);
					system("pause");
					system("cls");
					break;
				
				case '6':
					std::cin.get();

					std::cout << "Введите фамилию: ";
					std::getline(std::wcin, f_name);

					std::cout << "Введите имя: ";
					std::getline(std::wcin, name);

					std::cout << "Введите отчество: ";
					std::getline(std::wcin, sname);

					std::cout << "Введите новый номер группы: ";
					std::getline(std::wcin, new_grname);

					if (!this->get_subjects_list()->change_students_group_name(student(f_name, name, sname), new_grname))
						std::cout << "Указанного студента не существует\n";
					else
						std::cout << "Группа изменена!\n";

					this->get_students_list()->change_students_group_name(student(f_name, name, sname), new_grname);
					system("pause");
					system("cls");
					break;

				case '7':
					std::cin.get();

					std::cout << "Введите фамилию: ";
					std::getline(std::wcin, f_name);

					std::cout << "Введите имя: ";
					std::getline(std::wcin, name);

					std::cout << "Введите отчество: ";
					std::getline(std::wcin, sname);

					std::cout << "Введите новый средний балл: ";
					std::cin >> avr_GPA;

					if (!this->get_subjects_list()->change_students_average_GPA(student(f_name, name, sname), avr_GPA))
						std::cout << "Указанного студента не существует\n";
					else
						std::cout << "Группа изменена!\n";

					this->get_students_list()->change_students_average_GPA(student(f_name, name, sname), avr_GPA);
					system("pause");
					system("cls");
					break;
				
				case '8':
					std::cin.get();

					std::cout << "1.Английский\n2.Математика\n3.Программирование\n4.Физика\n5.Базы данных\n\nВаш выбор:  ";
					std::cin >> choice;



					switch (choice)
					{
					case '1':
						std::cin.get();

						std::cout << "Введите фамилию: ";
						std::getline(std::wcin, f_name);

						std::cout << "Введите имя: ";
						std::getline(std::wcin, name);

						std::cout << "Введите отчество: ";
						std::getline(std::wcin, sname);

						std::cout << "Введите новую запись на английский: ";
						std::cin >> eng;

						if (!this->get_subjects_list()->change_students_is_english(student(f_name, name, sname), eng))
							std::cout << "Указанного студента не существует\n";
						else
							std::cout << "Запись изменена!\n";

						this->get_students_list()->change_students_is_english(student(f_name, name, sname),eng);
						break;

					case '2':
						std::cin.get();

						std::cout << "Введите фамилию: ";
						std::getline(std::wcin, f_name);

						std::cout << "Введите имя: ";
						std::getline(std::wcin, name);

						std::cout << "Введите отчество: ";
						std::getline(std::wcin, sname);

						std::cout << "Введите новую запись на математику: ";
						std::cin >> mathm;

						if (!this->get_subjects_list()->change_students_is_math(student(f_name, name, sname), mathm))
							std::cout << "Указанного студента не существует\n";
						else
							std::cout << "Запись изменена!\n";

						this->get_students_list()->change_students_is_math(student(f_name, name, sname), mathm);
						break;

					case '3':
						std::cin.get();

						std::cout << "Введите фамилию: ";
						std::getline(std::wcin, f_name);

						std::cout << "Введите имя: ";
						std::getline(std::wcin, name);

						std::cout << "Введите отчество: ";
						std::getline(std::wcin, sname);

						std::cout << "Введите новую запись на английский: ";
						std::cin >> prog;

						if (!this->get_subjects_list()->change_students_is_programming(student(f_name, name, sname), prog))
							std::cout << "Указанного студента не существует\n";
						else
							std::cout << "Запись изменена!\n";

						this->get_students_list()->change_students_is_programming(student(f_name, name, sname), prog);
						break;

					case '4':
						std::cin.get();

						std::cout << "Введите фамилию: ";
						std::getline(std::wcin, f_name);

						std::cout << "Введите имя: ";
						std::getline(std::wcin, name);

						std::cout << "Введите отчество: ";
						std::getline(std::wcin, sname);

						std::cout << "Введите новую запись на английский: ";
						std::cin >> phys;

						if (!this->get_subjects_list()->change_students_is_physic(student(f_name, name, sname), phys))
							std::cout << "Указанного студента не существует\n";
						else
							std::cout << "Запись изменена!\n";

						this->get_students_list()->change_students_is_physic(student(f_name, name, sname), phys);
						break;

					case '5':
						std::cin.get();

						std::cout << "Введите фамилию: ";
						std::getline(std::wcin, f_name);

						std::cout << "Введите имя: ";
						std::getline(std::wcin, name);

						std::cout << "Введите отчество: ";
						std::getline(std::wcin, sname);

						std::cout << "Введите новую запись на английский: ";
						std::cin >> db;

						if (!this->get_subjects_list()->change_students_is_databases(student(f_name, name, sname), db))
							std::cout << "Указанного студента не существует\n";
						else
							std::cout << "Запись изменена!\n";

						this->get_students_list()->change_students_is_databases(student(f_name, name, sname), db);
						break;

					case '9':
						goto ADMIN_MENU;
						break;

					default:
						break;
					}

					system("pause");
					system("cls");
					break;


				default:
					break;
				}

				system("pause");
				system("cls");
				break;

			case '3':
				goto MAIN_MENU;

			default:
				break;
			}
		} while (choice != 'q');
	}
}
