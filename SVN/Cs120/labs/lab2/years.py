 # it calculates the number of years to the star
 # pre: distance & speed must be real positive numbers
 # post: outputs the years as a real positive number
def calculate_years_to_star(distance, speed_mph):
    light_year_miles = 5.878 * (10 ** 12)
    hours_in_day = 24
    days_in_year = 365
    miles = distance * light_year_miles
    hours_to_star = miles / speed_mph
    years = hours_to_star / hours_in_day / days_in_year
    return years



# def test_calculate_years_to_star():
#     print(calculate_years_to_star(1, 100), "= 6710045")

# test_calculate_years_to_star()

distance = 1
speed_mph = 100
print('')
print("The number of years it would take to get to the star is")
print(calculate_years_to_star(distance, speed_mph),"  I think..")
print('')
print("If you go any farther, you might hit the sun! Son.")
print('')
