#include "FilmsRepository.h"

#define YEAR "year"
#define LENGTH "length"
#define NAME "name"
#define SUMMARY "summary"
#define PRICE "price"
#define DIRECTOR "director"
#define FILM_ID "film_id"
#define HEADER "#. Film Id | Film Name | Film Length | Film Price | Rate | Production Year | Film Director"
#define DOT '.'
#define LINE " | "
#define DOT_S ". "
#define RECOM_HEADER "#. Film Id | Film Name | Film Length | Film Director"
#define RECOMMENDATION "Recommendation Film"
#define MIN_YEAR "min_year"
#define MAX_YEAR "max_year"
#define MIN_RATE "min_rate"
#define ONE 1
#define START 0
#define EMPTY 0
#define NUM_START 48
#define NUM_END 57
#define NOT_RATED -1
#define ZERO 0
#define NOT_ALLOWED -1
#define NOT_EXISTING -1
#define CHECKED 1
#define NOT_CHECKED 0
#define FOUR_TIMES 4

FilmsRepository* FilmsRepository::main_repository;

FilmsRepository::FilmsRepository()
{
	last_id = ONE;
}

FilmsRepository* FilmsRepository::get_films_rep()
{
	if(!main_repository)
	{
		main_repository = new FilmsRepository();
	}
	return main_repository;
}

std::vector<Film*> FilmsRepository::get_films()
{
	return films;
}

Film* FilmsRepository::get_film(int film_id)
{
	for(int i = START; i < films.size(); i++)
	{
		if(film_id == films[i]->get_id())
		{
			return films[i];
		}
	}
}

int FilmsRepository::add_film(std::map<std::string, std::string> informations, int publisher_id)
{
	films.push_back(new Film(id_generator(), string_adjust(informations[NAME])
		, num_adjust(informations[YEAR]), num_adjust(informations[LENGTH])
		, num_adjust(informations[PRICE]), string_adjust(informations[SUMMARY])
		, string_adjust(informations[DIRECTOR]), publisher_id));
	recom_table_expand(last_id);
	last_id++;
	return last_id - ONE;
}

void FilmsRepository::recom_table_expand(int curr_id)
{
	for (int i = 0; i < recom_table.size(); ++i)
	{
		recom_table[i].push_back(0);
	}
	std::vector<int> temp (recom_table.size() + 1, 0);
	recom_table.push_back(temp);
}

void FilmsRepository::edit_film(std::map<std::string, std::string> informations)
{
	int f_id = num_adjust(informations[FILM_ID]);
	for(int i = START; i < films.size(); i++)
	{
		if(f_id == films[i]->get_id())
		{
			films[i]->change_information(informations);
			return;
		}
	}
}

void FilmsRepository::delete_film(std::string film_id)
{
	int f_id = num_adjust(film_id);
	for(int i = START; i < films.size(); i++)
	{
		if(f_id == films[i]->get_id())
		{
			films[i]->sell_out();
			return;
		}
	}
}

void FilmsRepository::print_film_by_ids(std::map<std::string, std::string> informations, std::vector<int> films_id)
{
	int num_list = ONE;
	std::cout << HEADER << std::endl;
	for(int i = START; i < films.size(); i++)
	{
		if(name_check(informations[NAME], films[i]->get_name()) 
			&& rate_check(informations[MIN_RATE], films[i]->get_rate()) 
			&& year_check(informations[MIN_YEAR], informations[MAX_YEAR], films[i]->get_year()) 
			&& price_check(informations[PRICE], films[i]->get_price()) 
			&& director_check(informations[NAME], films[i]->get_director())
			&& films[i]->sell_status())
		{
			for(int j = START; j < films_id.size(); j++)
			{
				if(films[i]->get_id() == films_id[j])
				{
					std::cout << num_list << DOT_S << films[i]->get_id() << LINE 
						<< films[i]->get_name() << LINE << films[i]->get_length() << LINE 
						<< films[i]->get_price() << LINE << films[i]->get_rate() << LINE 
						<< films[i]->get_year() << LINE << films[i]->get_director() << std::endl;
					num_list++;
				}
			}

		}
	}
}

void FilmsRepository::print_films(std::map<std::string, std::string> informations)
{
	int num_list = ONE;
	std::cout << HEADER << std::endl;
	for(int i = START; i < films.size(); i++)
	{
		if(name_check(informations[NAME], films[i]->get_name()) 
			&& rate_check(informations[MIN_RATE], films[i]->get_rate()) 
			&& year_check(informations[MIN_YEAR], informations[MAX_YEAR], films[i]->get_year()) 
			&& price_check(informations[PRICE], films[i]->get_price()) 
			&& director_check(informations[NAME], films[i]->get_director())
			&& films[i]->sell_status())
		{
					std::cout << num_list << DOT_S << films[i]->get_id() << LINE 
						<< films[i]->get_name() << LINE << films[i]->get_length() << LINE 
						<< films[i]->get_price() << LINE << films[i]->get_rate() << LINE 
						<< films[i]->get_year() << LINE << films[i]->get_director() << std::endl;
					num_list++;
		}
	}
}

void FilmsRepository::print_film(std::string film_id, std::vector<int> purchased_id)
{
	int f_id = num_adjust(film_id);
	for(int i = START; i < films.size(); i++)
	{
		if(films[i]->get_id() == f_id && films[i]->sell_status())
		{
			std::cout << "Details of Film " << films[i]->get_name() << std::endl
				<< "Id = " << films[i]->get_id() << std::endl
				<< "Director = " << films[i]->get_director() << std::endl
				<< "Length = " << films[i]->get_length() << std::endl
				<< "Year = " << films[i]->get_year() << std::endl
				<< "Summary = " << films[i]->get_summary() << std::endl
				<< "Rate = " << films[i]->get_rate() << std::endl
				<< "Price = " << films[i]->get_price() << std::endl << std::endl
				<< "Comments" << std::endl;
			films[i]->print_comments();
			std::cout << std::endl << RECOMMENDATION << std::endl;
			//recommendation_print(films[i]->get_id(), purchased_id);
			return;
		}
	}
	throw NotFound();
}

std::vector<Film*> FilmsRepository::get_film_recommendation(int film_id, std::vector<int> purchased_id)
{
	std::vector<Film*> recom_films;
	std::cout << RECOM_HEADER << std::endl;
	int checked = NOT_CHECKED;
	std::vector<int> mutal_seens;
	for(int i = START; i < films.size(); i++)
	{
		for(int j = START; j < purchased_id.size(); j++)
		{
			if(films[i]->get_id() == purchased_id[j])
			{
				mutal_seens.push_back(NOT_ALLOWED);
				checked = CHECKED;
				break;
			}
		}
		if((films[i]->get_id() == film_id || !films[i]->sell_status()) && checked == NOT_CHECKED)
			mutal_seens.push_back(NOT_ALLOWED);
		else if(checked == NOT_CHECKED)
		{
			mutal_seens.push_back(recom_table[film_id - 1][i]);
		}
		checked = NOT_CHECKED;
	}
	for(int n = START; n < FOUR_TIMES; n++)
	{
		int recommend_num = ONE, max_num = START;
		int max = NOT_EXISTING;
		for(int i = START; i < films.size(); i++)
		{
			if((max < recom_table[film_id - 1][i]) && (mutal_seens[i] != NOT_ALLOWED))
			{
				max = recom_table[film_id - 1][i];
				max_num = i;
			}
		}
		if(max != NOT_EXISTING)
		{
			mutal_seens[max_num] = NOT_ALLOWED;
			recom_films.push_back(films[max_num]);
		}
		recommend_num++;
	}
	return recom_films;
}

void FilmsRepository::rate_film(int film_id, std::string s_rate, int last_rate)
{
	for(int i = START; i < films.size(); i++)
	{
		if(films[i]->get_id() == film_id)
		{
			if(films[i]->get_rated_num() == ZERO)
			{
				films[i]->set_rate(num_adjust(s_rate));
				films[i]->increase_rated_num();
			}
			else
			{
				if(last_rate == NOT_RATED)
				{
					films[i]->add_rate(num_adjust(s_rate));
				}
				else
				{
					films[i]->update_rate(num_adjust(s_rate), last_rate);
				}
			}
			return;
		}
	}

}

void FilmsRepository::comment_film(int film_id, std::string content, int commenter_id)
{
	for(int i = START; i < films.size(); i++)
	{
		if(films[i]->get_id() == film_id)
		{
			films[i]->add_comment(content, commenter_id);
		}
	}
}

int FilmsRepository::reply_to_comment(int film_id, std::string comment_id, std::string content)
{
	for(int i = START; i < films.size(); i++)
	{
		if(films[i]->get_id() == film_id)
		{
			return films[i]->add_reply(num_adjust(comment_id), content);
		}
	}
}

void FilmsRepository::delete_comment(int film_id, std::string comment_id)
{
	for(int i = START; i < films.size(); i++)
	{
		if(films[i]->get_id() == film_id)
		{
			films[i]->erase_comment(num_adjust(comment_id));
		}
	}
}

int FilmsRepository::find_film_pub(std::string film_id)
{
	int f_id = num_adjust(film_id);
	for(int i = START; i < films.size(); i++)
	{
		if(f_id == films[i]->get_id() && films[i]->sell_status())
			return films[i]->get_pub_id();
	}
	throw NotFound();
}

int FilmsRepository::find_film_price(std::string film_id)
{
	int f_id = num_adjust(film_id);
	for(int i = START; i < films.size(); i++)
	{
		if(f_id == films[i]->get_id() && films[i]->sell_status())
			return films[i]->get_price();
	}
	throw NotFound();
}

double FilmsRepository::find_film_rate(std::string film_id)
{
	int f_id = num_adjust(film_id);
	for(int i = START; i < films.size(); i++)
	{
		if(f_id == films[i]->get_id() && films[i]->sell_status())
			return films[i]->get_rate();
	}
	throw NotFound();
}

std::string FilmsRepository::find_film_name(std::string film_id)
{
	int f_id = num_adjust(film_id);
	for(int i = START; i < films.size(); i++)
	{
		if(f_id == films[i]->get_id() && films[i]->sell_status())
			return films[i]->get_name();
	}
	throw NotFound();
}

int FilmsRepository::id_generator()
{
	return last_id;
}

int FilmsRepository::num_adjust(std::string num)
{
	for(int i = START; i < num.size(); i++)
	{
		if(num[i] > NUM_END || num[i] < NUM_START)
			throw Server::Exception("Type of data you entered is not right.");
	}
	return stoi(num);
}

std::string FilmsRepository::string_adjust(std::string str)
{
	return str;
}

bool FilmsRepository::name_check(std::string s_name, std::string name)
{
	if(s_name.size() == EMPTY)
		return true;
	for(int i = START; i < s_name.size(); i++)
	{
		for (int j = i; j < name.size(); j++)
			if(s_name.substr(i, j - i - ONE) == name)
				return true;
	}
	return false;
}

bool FilmsRepository::rate_check(std::string s_rate, double rate)
{
	if(s_rate.size() == EMPTY)
		return true;
	for(int i = START; i < s_rate.size(); i++)
	{
		if((s_rate[i] > NUM_END || s_rate[i] < NUM_START) && !(s_rate[i] == DOT))
			throw BadRequest();
	}
	if(stod(s_rate) <= rate)
		return true;
	return false;
}

bool FilmsRepository::year_check(std::string min_year, std::string max_year, int year)
{
	if(min_year.size() == EMPTY && max_year.size() == EMPTY)
		return true;
	for(int i = START; i < min_year.size(); i++)
	{
		if(min_year[i] > NUM_END || min_year[i] < NUM_START)
			throw BadRequest();
	}
	for(int i = START; i < max_year.size(); i++)
	{
		if(max_year[i] > NUM_END || max_year[i] < NUM_START)
			throw BadRequest();
	}
	if(min_year.size() != EMPTY && max_year.size() != EMPTY)
		if(year >= stoi(min_year) && year <= stoi(max_year))
			return true;
	else if(min_year.size() == EMPTY)
		if(year <= stoi(max_year))
			return true;
	else
		if(year >= stoi(min_year))
			return true;
	return false;

}

bool FilmsRepository::price_check(std::string s_price, int price)
{
	if(s_price.size() == EMPTY)
		return true;
	for(int i = START; i < s_price.size(); i++)
	{
		if(s_price[i] > NUM_END || s_price[i] < NUM_START)
			throw Server::Exception("Renter the price.");
	}
	if(stod(s_price) >= price)
		return true;
	return false;
}

bool FilmsRepository::director_check(std::string s_director, std::string director)
{
	if(s_director.size() == EMPTY)
		return true;
	for(int i = START; i < s_director.size(); i++)
	{
		for (int j = i; j < director.size(); j++)
			if(s_director.substr(i, j - i - ONE) == director)
				return true;
	}
	return false;
}

int FilmsRepository::get_film_num()
{
	return (last_id - 1);
}

void FilmsRepository::update_recom_table(int film_id, std::vector<int> mutals)
{
	for (int i = 0; i < films.size(); ++i)
	{
		recom_table[film_id - 1][i] = mutals[i];
		recom_table[i][film_id - 1] = mutals[i];
	}

}