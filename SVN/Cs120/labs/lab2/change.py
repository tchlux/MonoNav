 # this function returns the number of dollars
 # pre: currency must be real and positive
 # post: output is a real number
def dollar(currency):
    currency = currency * 100
    dollar_var = currency // 100
    return dollar_var

# def test_dollar():
#     print(dollar(1.41),"= 1")

# test_dollar()


 # this function returns the number of quaters
 # pre: currency must be real and positive
 # post: output is a real number
def quarter(currency):
    value_of_quarter = .25
    currency = currency - dollar(currency)
    quarter_var = currency // value_of_quarter
    return quarter_var

# def test_quarter():
#     print(quarter(1.41),"= 1")

# test_quarter()


 # this function returns the number of dimes
 # pre: currency must be real and positive
 # post: output is a real number
def dime(currency):
    value_of_dime = .1
    value_of_quarter = .25
    currency = (currency - (quarter(currency) * value_of_quarter) - (dollar(currency)))
    dime_var = currency // value_of_dime
    return dime_var

# def test_dime():
#     print(dime(1.41),"= 1")
    
# test_dime()


 # this function returns the number of nickels
 # pre: currency must be real and positive
 # post: output is a real number
def nickel(currency):
    value_of_nickel = .05
    value_of_dime = .1
    value_of_quarter = .25
    currency = (currency - (dime(currency) * value_of_dime) - (quarter(currency) * value_of_quarter) - (dollar(currency)))
    nickel_var = currency // value_of_nickel
    return nickel_var

# def test_nickel():
#     print(nickel(1.41),"= 1")

# test_nickel()


 # this function returns the number of pennies
 # pre: currency must be real and positive
 # post: output is a real number
def penny(currency):
    value_of_penny = .01
    value_of_nickel = .05
    value_of_dime = .1
    value_of_quarter = .25
    currency = (currency - (nickel(currency) * value_of_nickel) - (dime(currency) * value_of_dime) - (quarter(currency) * value_of_quarter) - (dollar(currency)))
    penny_var = currency // value_of_penny
    # penny_var = penny_var + 1 #this is to compensate for nasty float values returned
    return penny_var

# def test_penny():
#     print(penny(1.41),"= 1")

# test_penny()

currency = 8.47

print('')
print(dollar(currency),"dollars")
print(quarter(currency),"quarters")
print(dime(currency),"dimes")
print(nickel(currency),"nickels")
print(penny(currency),"pennies")


 # calculates the total number of coins
 # pre: uses the real numbers provided from currency
 # post: the number of coins is real and positive
def total_coins():
    total_coins_var = dollar(currency) + quarter(currency) + dime(currency) + nickel(currency) + penny(currency)
    return total_coins_var

print("")
print("The total number of coins is",total_coins(),"!!!   I think..")
print("")
print("Note that if the dollar amount is one and there is only one penny")
print("then add 1 to the total coin value")
print("")
print("Make it rain in da club.")
print('')
