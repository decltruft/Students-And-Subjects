#include "default_user.h"


default_user::default_user(const std::string& username, unsigned int hash)
	: IUser(username, hash)
{
}

default_user::default_user(IUser::users_buffer&& buff)
	: IUser(std::forward<IUser::users_buffer&&>(buff))
{

}

default_user::default_user(const IUser& other) :
	IUser(other)
{

}

void default_user::users_interface_loop()
{
	if (!this->is_activated())
	{
		std::cout << "��� ������� �� �����������! ��������� �������������� ������������ ���!\n";
		return;
	}

	char choice;
	do
	{
	USERS_MENU:
		system("pause");
		system("cls");

		std::cin.get();
		std::cout << "1.��������� ������ ��������\n2.�������� ������ �������������\n3.���������� ��������\n4.�������������� �������\n5.��������� �����\n\n��� �����: ";
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

			std::cout << "1.���������� �� �������\n2.���������� �� ����� ������\n3.���������� �� �������� �����\n4.��������� �����\n" <<
				"\n\n��� �����: ";
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

		default:
			break;
		}
	} while (choice != 'q');
}

void default_user::set_users_controller(std::shared_ptr<users_controller>)
{

}

default_user::~default_user()
{

}
