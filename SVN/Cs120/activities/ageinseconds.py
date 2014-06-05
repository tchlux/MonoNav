# todays_date = 7
# todays_month = 9
# birthday_month = 10
# birthday = 18
average_in_days_in_month = 365 / 12
# age_in_years = 18
# age_in_days = 365 * age_in_years + (birthday_month - todays_month - 1)*(average_days_in_month) + (average_days_in_month - todays_date)
hours_in_day = 24
minutes_in_day = hours_in_day * 60
seconds_in_day = minutes_in_day * 60
# my_age = age_in_days * hours_in_day * seconds_in_day

# print("My age in seconds is my_age")


def convert_years_to_seconds(years):
    seconds_in_year = seconds_in_day * 365
    return seconds_in_year
