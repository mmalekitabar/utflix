#include "FilmsRepository.h"

FilmsRepository::FilmsRepository()
{
	last_id = 1;
}

int FilmsRepository::add_film(std::map<std::string, std::string> informations, int publisher_id)
{
	films.push_back(new Film(id_generator(), string_adjust(informations["name"])
		, num_adjust(informations["year"]), num_adjust(informations["length"])
		, num_adjust(informations["price"]), string_adjust(informations["summary"])
		, string_adjust(informations["director"]), publisher_id));
	last_id++;
	return last_id - 1;
}

void FilmsRepository::edit_film(std::map<std::string, std::string> informations)
{
	int f_id = num_adjust(informations["film_id"]);
	for(int i = 0; i < films.size(); i++)
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
	for(int i = 0; i < films.size(); i++)
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
	int num_list = 1;
	std::cout << "#. Film Id | Film Name | Film Length | Film Price | Rate | Production Year | Film Director" << std::endl;
	for(int i = 0; i < films.size(); i++)
	{
		if(name_check(informations["name"], films[i]->get_name()) 
			&& rate_check(informations["min_rate"], films[i]->get_rate()) 
			&& year_check(informations["min_year"], informations["max_year"], films[i]->get_year()) 
			&& price_check(informations["price"], films[i]->get_price()) 
			&& director_check(informations["name"], films[i]->get_director())
			&& films[i]->sell_status())
		{
			for(int j = 0; j < films_id.size(); j++)
			{
				if(films[i]->get_id() == films_id[j])
				{
					std::cout << num_list << ". " << films[i]->get_id() << " | " 
						<< films[i]->get_name() << " | " << films[i]->get_length() << " | " 
						<< films[i]->get_price() << " | " << films[i]->get_rate() << " | " 
						<< films[i]->get_year() << " | " << films[i]->get_director() << std::endl;
					num_list++;
				}
			}

		}
	}
}


void FilmsRepository::print_films(std::map<std::string, std::string> informations)
{
	int num_list = 1;
	std::cout << "#. Film Id | Film Name | Film Length | Film Price | Rate | Production Year | Film Director" << std::endl;
	for(int i = 0; i < films.size(); i++)
	{
		if(name_check(informations["name"], films[i]->get_name()) 
			&& rate_check(informations["min_rate"], films[i]->get_rate()) 
			&& year_check(informations["min_year"], informations["max_year"], films[i]->get_year()) 
			&& price_check(informations["price"], films[i]->get_price()) 
			&& director_check(informations["name"], films[i]->get_director())
			&& films[i]->sell_status())
		{
					std::cout << num_list << ". " << films[i]->get_id() << " | " 
						<< films[i]->get_name() << " | " << films[i]->get_length() << " | " 
						<< films[i]->get_price() << " | " << films[i]->get_rate() << " | " 
						<< films[i]->get_year() << " | " << films[i]->get_director() << std::endl;
					num_list++;
		}
	}
}


void FilmsRepository::print_film(std::string film_id, std::vector<int> purchased_id)
{
	int f_id = num_adjust(film_id);
	for(int i = 0; i < films.size(); i++)
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
			std::cout << std::endl << "Recommendation Film" << std::endl;
			recommendation_print(films[i]->get_id(), purchased_id);
			return;
		}
	}
	throw NotFound();
}

void FilmsRepository::recommendation_print(int film_id, std::vector<int> purchased_id)
{
	std::cout << "#. Film Id | Film Name | Film Length | Film Director" << std::endl;
	int checked = 0;
	std::vector<double> rates;
	for(int i = 0; i < films.size(); i++)
	{
		for(int j = 0; j < purchased_id.size(); j++)
		{
			if(films[i]->get_id() == purchased_id[j])
			{
				rates.push_back(-1);
				checked = 1;
				break;
			}
		}
		if((films[i]->get_id() == film_id || !films[i]->sell_status()) && checked == 0)
			rates.push_back(-1);
		else if(checked == 0)
		{
			rates.push_back(films[i]->get_rate());
		}
		checked = 0;
	}
	for(int n = 0; n < 4; n++)
	{
		int recommend_num = 1, max_num = -1;
		double max = -1;
		for(int i = 0; i < films.size(); i++)
		{
			if(max < films[i]->get_rate() && rates[i] != -1)
			{
				max = films[i]->get_rate();
				max_num = i;
			}
		}
		if(max != -1)
		{
		rates[max_num] = -1;
		std::cout << recommend_num << ". " << films[max_num]->get_id() << " | " 
			<< films[max_num]->get_name() << " | " << films[max_num]->get_length() 
			<< " | " << films[max_num]->get_director() << std::endl;
		}
	}
}

void FilmsRepository::rate_film(int film_id, std::string s_rate, int last_rate)
{
	for(int i = 0; i < films.size(); i++)
	{
		if(films[i]->get_id() == film_id)
		{
			if(films[i]->get_rated_num() == 0)
			{
				films[i]->set_rate(num_adjust(s_rate));
				films[i]->increase_rated_num();
			}
			else
			{
				if(last_rate == -1)
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

void FilmsRepository::comment_film(int film_id, std::string content)
{
	for(int i = 0; i < films.size(); i++)
	{
		if(films[i]->get_id() == film_id)
		{
			films[i]->add_comment(content);
		}
	}
}

void FilmsRepository::reply_to_comment(int film_id, std::string comment_id, std::string content)
{
	for(int i = 0; i < films.size(); i++)
	{
		if(films[i]->get_id() == film_id)
		{
			films[i]->add_reply(num_adjust(comment_id), content);
		}
	}
}

void FilmsRepository::delete_comment(int film_id, std::string comment_id)
{
	for(int i = 0; i < films.size(); i++)
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
	for(int i = 0; i < films.size(); i++)
	{
		if(f_id == films[i]->get_id() && films[i]->sell_status())
			return films[i]->get_pub_id();
	}
	throw NotFound();
}

int FilmsRepository::find_film_price(std::string film_id)
{
	int f_id = num_adjust(film_id);
	for(int i = 0; i < films.size(); i++)
	{
		if(f_id == films[i]->get_id() && films[i]->sell_status())
			return films[i]->get_price();
	}
	throw NotFound();
}

int FilmsRepository::id_generator()
{
	return last_id;
}


int FilmsRepository::num_adjust(std::string num)
{
	if(num.size() == 0)
		throw BadRequest();
	for(int i = 0; i < num.size(); i++)
	{
		if(num[i] > 57 || num[i] < 48)
			throw BadRequest();
	}
	return stoi(num);
}

std::string FilmsRepository::string_adjust(std::string str)
{
	if(str.size() == 0)
		throw BadRequest();
	return str;
}

bool FilmsRepository::name_check(std::string s_name, std::string name)
{
	if(s_name.size() == 0)
		return true;
	for(int i = 0; i < s_name.size(); i++)
	{
		for (int j = i; j < name.size(); j++)
			if(s_name.substr(i, j - i - 1) == name)
				return true;
	}
	return false;
}
bool FilmsRepository::rate_check(std::string s_rate, double rate)
{
	if(s_rate.size() == 0)
		return true;
	for(int i = 0; i < s_rate.size(); i++)
	{
		if((s_rate[i] > 57 || s_rate[i] < 48) && !(s_rate[i] == '.'))
			throw BadRequest();
	}
	if(stod(s_rate) <= rate)
		return true;
	return false;
}
bool FilmsRepository::year_check(std::string min_year, std::string max_year, int year)
{
	if(min_year.size() == 0 && max_year.size() == 0)
		return true;
	for(int i = 0; i < min_year.size(); i++)
	{
		if(min_year[i] > 57 || min_year[i] < 48)
			throw BadRequest();
	}
	for(int i = 0; i < max_year.size(); i++)
	{
		if(max_year[i] > 57 || max_year[i] < 48)
			throw BadRequest();
	}
	if(min_year.size() != 0 && max_year.size() != 0)
		if(year >= stoi(min_year) && year <= stoi(max_year))
			return true;
	else if(min_year.size() == 0)
		if(year <= stoi(max_year))
			return true;
	else
		if(year >= stoi(min_year))
			return true;
	return false;

}
bool FilmsRepository::price_check(std::string s_price, int price)
{
	if(s_price.size() == 0)
		return true;
	for(int i = 0; i < s_price.size(); i++)
	{
		if(s_price[i] > 57 || s_price[i] < 48)
			throw BadRequest();
	}
	if(stod(s_price) >= price)
		return true;
	return false;
}
bool FilmsRepository::director_check(std::string s_director, std::string director)
{
	if(s_director.size() == 0)
		return true;
	for(int i = 0; i < s_director.size(); i++)
	{
		for (int j = i; j < director.size(); j++)
			if(s_director.substr(i, j - i - 1) == director)
				return true;
	}
	return false;
}