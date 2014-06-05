
def input_list():
    string = input('A comma seperated list of numbers pretay pleeze:')
    list_of_numbers = string.split(",")
    list_of_numbers = [int(string) for string in list_of_numbers]
    (sd , list_mean) = standard_deviation(list_of_numbers)
    print('Mean of list:' , list_mean)
    print('Standard deviation of list' , sd)

def standard_deviation(list_of_numbers):
    length_of_list = len(list_of_numbers)
    sum_of_list = 0
    list_mean = (sum(list_of_numbers) / length_of_list)
    list_of_numerators = [((list_of_numbers[i] - list_mean) ** 2) for i in range(length_of_list)]
    sum_of_numerators = sum(list_of_numerators)
    sd = ((sum_of_numerators) / (length_of_list - 1)) ** (1/2)
    return (sd, list_mean)

#input_list()


def process_epa_list():
    string_of_epa_list = input()
    epa_list = string_of_epa_list.split(",")
    list_of_numbers = [epa_list[i] for i in range (2,len(epa_list),3)]
    minimum = min(list_of_numbers)
    man_with_min = (epa_list.index(minimum) - 2)
    print('Manufacturer: ', epa_list[man_with_min])
    return minimum


print(process_epa_list())
