#include "subjects_list.h"

subjects_list::subjects_list(const students_list& stud_l)
{
	_subjects.reserve(5);

	subject english(L"**ÀÍÃËÈÉÑÊÈÉ ßÇÛÊ**");
	subject math(L"**ÌÀÒÅÌÀÒÈÊÀ**");
	subject programming(L"**ÏĞÎÃĞÀÌÌÈĞÎÂÀÍÈÅ**");
	subject physical(L"**ÔÈÇÈÊÀ**");
	subject databases(L"**ÁÀÇÛ ÄÀÍÍÛÕ**");

	for (size_t index{ 0 }; index < stud_l.get_count_of_students(); ++index)
	{
		if (stud_l[index].is_English())
			english.add_new_student(stud_l[index]);
		if (stud_l[index].is_Math())
			math.add_new_student(stud_l[index]);
		if (stud_l[index].is_Programming())
			programming.add_new_student(stud_l[index]);
		if (stud_l[index].is_Physical())
			physical.add_new_student(stud_l[index]);
		if (stud_l[index].is_DataBases())
			databases.add_new_student(stud_l[index]);
	}

	_subjects.push_back(std::move(english));
	_subjects.push_back(std::move(math));
	_subjects.push_back(std::move(programming));
	_subjects.push_back(std::move(physical));
	_subjects.push_back(std::move(databases));
}

bool subjects_list::add_new_student(const student& stud)
{
	bool is_exist = false;
	bool is_complete = false;

	for (size_t index{0}; index < count_of_subjects; ++index)
	{
		switch(index)
		{
		case ENGLISH:
			if (stud.is_English())
				is_complete = _subjects[ENGLISH].add_new_student(stud);
			break;

		case MATH:
			if (stud.is_Math())
				is_complete = _subjects[MATH].add_new_student(stud);
			break;
		
		case PROGRAMMING:
			if (stud.is_Programming())
				is_complete = _subjects[PROGRAMMING].add_new_student(stud);
			break;

		case PHYSICAL:
			if (stud.is_Physical())
				is_complete = _subjects[PHYSICAL].add_new_student(stud);
			break;

		case DATABASES:
			if (stud.is_DataBases())
				is_complete = _subjects[DATABASES].add_new_student(stud);
			break;

		default:
			break;
		}

		if (is_complete && !is_exist)
			is_exist = true;
	}
	return is_exist;
}

bool subjects_list::remove_the_student(const student& stud)
{
	bool is_exist = false;
	bool is_find = false;

	for (std::vector<subject>::iterator it = _subjects.begin(); it != _subjects.end(); ++it)
	{
		is_find = it->remove_the_student(stud);

		if (is_find && !is_exist)
			is_exist = true;
	}
	return is_exist;
}

bool subjects_list::change_students_family_name(const student& stud, const std::wstring& new_fn)
{
	bool is_exist = false;
	bool is_find = false;

	for (std::vector<subject>::iterator it = _subjects.begin(); it != _subjects.end(); ++it)
	{
		is_find = it->change_students_family_name(stud, new_fn);

		if (is_find && !is_exist)
			is_exist = true;
	}
	return is_exist;
}

bool subjects_list::change_students_name(const student& stud, const std::wstring& new_n)
{
	bool is_exist = false;
	bool is_find = false;

	for (std::vector<subject>::iterator it = _subjects.begin(); it != _subjects.end(); ++it)
	{
		is_find = it->change_students_name(stud, new_n);

		if (is_find && !is_exist)
			is_exist = true;
	}
	return is_exist;
}

bool subjects_list::change_students_surname(const student& stud, const std::wstring& new_sn)
{
	bool is_exist = false;
	bool is_find = false;

	for (std::vector<subject>::iterator it = _subjects.begin(); it != _subjects.end(); ++it)
	{
		is_find = it->change_students_surname(stud, new_sn);

		if (is_find && !is_exist)
			is_exist = true;
	}
	return is_exist;
}

bool subjects_list::change_students_group_name(const student& stud, const std::wstring& new_gn)
{
	bool is_exist = false;
	bool is_find = false;

	for (std::vector<subject>::iterator it = _subjects.begin(); it != _subjects.end(); ++it)
	{
		is_find = it->change_students_group_name(stud, new_gn);

		if (is_find && !is_exist)
			is_exist = true;
	}
	return is_exist;
}

bool subjects_list::change_students_average_GPA(const student& stud, const double new_GPA)
{
	bool is_exist = false;
	bool is_find = false;

	for (std::vector<subject>::iterator it = _subjects.begin(); it != _subjects.end(); ++it)
	{
		is_find = it->change_students_average_GPA(stud, new_GPA);

		if (is_find && !is_exist)
			is_exist = true;
	}
	return is_exist;
}

bool subjects_list::change_students_is_english(const student& stud, const bool new_eng)	// ÂÀÆÍÎ: ïåğåäàâàòü ñşäà è âî âñåõ ïîõîæèå ìåòîäû ÏÎËÍÓŞ êîïèş ñòóäåíòà, à íå òîëüêî ÔÈÎ
{
	bool is_changed = false;

	for (size_t index{ 0 }; index < count_of_subjects; ++index)
	{
		if ((_subjects[ENGLISH].is_exist(stud)) && (new_eng == false))
		{
			_subjects[ENGLISH].remove_the_student(stud);
			is_changed = true;
		}
		else if (!(_subjects[ENGLISH].is_exist(stud)) && (new_eng == true))
		{
			_subjects[ENGLISH].add_new_student(stud);
			is_changed = true;
		}
		else if(_subjects[index].is_exist(stud))
		{
			_subjects[index].change_students_is_english(stud, new_eng);
			is_changed = true;
		}
	}

	return is_changed;
}

bool subjects_list::change_students_is_math(const student& stud, const bool new_math)
{
	bool is_changed = false;

	for (size_t index{ 0 }; index < count_of_subjects; ++index)
	{
		if ((_subjects[MATH].is_exist(stud)) && (new_math == false))
		{
			_subjects[MATH].remove_the_student(stud);
			is_changed = true;
		}
		else if (!(_subjects[MATH].is_exist(stud)) && (new_math == true))
		{
			_subjects[MATH].add_new_student(stud);
			is_changed = true;
		}
		else if (_subjects[index].is_exist(stud))
		{
			_subjects[index].change_students_is_math(stud, new_math);
			is_changed = true;
		}
	}

	return is_changed;
}

bool subjects_list::change_students_is_programming(const student& stud, const bool new_prog)
{
	bool is_changed = false;

	for (size_t index{ 0 }; index < count_of_subjects; ++index)
	{
		if ((_subjects[PROGRAMMING].is_exist(stud)) && (new_prog == false))
		{
			_subjects[PROGRAMMING].remove_the_student(stud);
			is_changed = true;
		}
		else if (!(_subjects[PROGRAMMING].is_exist(stud)) && (new_prog == true))
		{
			_subjects[PROGRAMMING].add_new_student(stud);
			is_changed = true;
		}
		else if (_subjects[index].is_exist(stud))
		{
			_subjects[index].change_students_is_programming(stud, new_prog);
			is_changed = true;
		}
	}

	return is_changed;
}

bool subjects_list::change_students_is_physic(const student& stud, const bool new_phys)
{
	bool is_changed = false;

	for (size_t index{ 0 }; index < count_of_subjects; ++index)
	{
		if ((_subjects[PHYSICAL].is_exist(stud)) && (new_phys == false))
		{
			_subjects[PHYSICAL].remove_the_student(stud);
			is_changed = true;
		}
		else if (!(_subjects[PHYSICAL].is_exist(stud)) && (new_phys == true))
		{
			_subjects[PHYSICAL].add_new_student(stud);
			is_changed = true;
		}
		else if (_subjects[index].is_exist(stud))
		{
			_subjects[index].change_students_is_physic(stud, new_phys);
			is_changed = true;
		}
	}

	return is_changed;
}

bool subjects_list::change_students_is_databases(const student& stud, const bool new_db)
{
	bool is_changed = false;

	for (size_t index{ 0 }; index < count_of_subjects; ++index)
	{
		if ((_subjects[DATABASES].is_exist(stud)) && (new_db == false))
		{
			_subjects[DATABASES].remove_the_student(stud);
			is_changed = true;
		}
		else if (!(_subjects[DATABASES].is_exist(stud)) && (new_db == true))
		{
			_subjects[DATABASES].add_new_student(stud);
			is_changed = true;
		}
		else if (_subjects[index].is_exist(stud))
		{
			_subjects[index].change_students_is_databases(stud, new_db);
			is_changed = true;
		}
	}

	return is_changed;
}

void subjects_list::show() const
{
	for (size_t index{ 0 }; index < count_of_subjects; ++index)
	{
		switch (index)
		{
		case ENGLISH:
			std::wcout << "\t\t\t\t\t**ÀÍÃËÈÉÑÊÈÉ ßÇÛÊ**\n";
			break;
		case MATH:
			std::wcout << "\t\t\t\t\t**ÌÀÒÅÌÀÒÈÊÀ**\n";
			break;
		case PROGRAMMING:
			std::wcout << "\t\t\t\t\t**ÏĞÎÃĞÀÌÌÈĞÎÂÀÍÈÅ**\n";
			break;
		case PHYSICAL:
			std::wcout << "\t\t\t\t\t**ÔÈÇÈÊÀ**\n";
			break;
		case DATABASES:
			std::wcout << "\t\t\t\t\t**ÁÀÇÛ ÄÀÍÍÛÕ**\n";
			break;
		default:
			break;
		}
		_subjects[index].show();
		std::cout << "\n\n";
	}
}

void subjects_list::personal_task_to_show_after_sorting()
{
	std::vector<subject> subjects_buffer = _subjects;
	std::sort(subjects_buffer.begin(), subjects_buffer.end(), [](const subject& subj_1, const subject& subj_2)
		{return subj_1.get_count_of_students() > subj_2.get_count_of_students(); });

	std::wcout << "\t\t\t\t***ÔÀÊÓËÜÒÀÒÈÂÛ Â ÏÎĞßÄÊÅ ÓÁÛÂÀÍÈß ÏÎÏÓËßĞÍÎÑÒÈ***\n\n\n";
	for (size_t index{ 0 }; index < count_of_subjects; ++index)
	{
		if(subjects_buffer[index].get_subject_name() == L"**ÀÍÃËÈÉÑÊÈÉ ßÇÛÊ**")
			std::wcout << "\t\t\t\t\t**ÀÍÃËÈÉÑÊÈÉ ßÇÛÊ**\n";
		else if (subjects_buffer[index].get_subject_name() == L"**ÌÀÒÅÌÀÒÈÊÀ**")
			std::wcout << "\t\t\t\t\t**ÌÀÒÅÌÀÒÈÊÀ**\n";
		else if (subjects_buffer[index].get_subject_name() == L"**ÏĞÎÃĞÀÌÌÈĞÎÂÀÍÈÅ**")
			std::wcout << "\t\t\t\t\t**ÏĞÎÃĞÀÌÌÈĞÎÂÀÍÈÅ**\n";
		else if (subjects_buffer[index].get_subject_name() == L"**ÔÈÇÈÊÀ**")
			std::wcout << "\t\t\t\t\t**ÔÈÇÈÊÀ**\n";
		else 
			std::wcout << "\t\t\t\t\t**ÁÀÇÛ ÄÀÍÍÛÕ**\n";

		subjects_buffer[index].show();
		std::cout << "\n\n";
	}

}
