cars_and_mileage = input("Make and mileage of cars seperated by commas: ")

# this function converts the input into a list
# pre: cars_and_mileage
# post: cars_and_mileage_list form
def input_make_and_mileage_return_list(cars_and_mileage):
    cars_and_mileage_list = cars_and_mileage.split(',')
    return cars_and_mileage_list


# this function returns the highest mileage of them all in the land
# pre: cars_and_mileage list
# post: who is the fairest of them all?? ME no really, returns the highest mileage (aka the "fairest of them all")
def highest_mileage_return(cars_and_mileage):
    cars_and_mileage_list = input_make_and_mileage_return_list(cars_and_mileage)
    cars_and_mileage_list.sort()
    number_of_terms = len(cars_and_mileage_list)
    number_of_mileages = number_of_terms // 2
    highest_mileage = cars_and_mileage_list[number_of_mileages - 1]
    return highest_mileage


# this function prints a list of the highest mileage cars
# pre: the list of cars and mileages
# post: spongebob squarepants, and the highest mileage cars
def print_best_economy_cars(cars_and_mileage):
    (highest_mileage) = highest_mileage_return(cars_and_mileage) 
    print("the highest mileage: ", highest_mileage)
    list_of_best_economy_cars = []
    cars_and_mileage_list = input_make_and_mileage_return_list(cars_and_mileage)
    counter = -2
    for item in cars_and_mileage_list:
        counter += 1
        if item == highest_mileage:
            
            list_of_best_economy_cars.append(cars_and_mileage_list[counter])
    print("list of high mileage cars ", list_of_best_economy_cars)
    print(' who lives in a pineapple under the sea???')
    for i in range (50):
        print('SPONGEBOB SQUAREPANTS')


print_best_economy_cars(cars_and_mileage)
