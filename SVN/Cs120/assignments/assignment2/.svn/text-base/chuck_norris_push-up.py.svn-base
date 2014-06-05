def change_in_earth_position (small_mass, small_mass_movement, large_mass):
# will return large_mass_movement
    large_mass_movement = (small_mass * small_mass_movement) / large_mass
    return large_mass_movement

def compare_to_diameter_of_atom (diameter_of_atom, large_mass_movement):
# will return diameter_comparison_ratio
    diameter_comparison_ratio = (diameter_of_atom / large_mass_movement)
    return diameter_comparison_ratio

def mass_of_smaller_body (small_mass_movement, large_mass, large_mass_movement):
# will return small_mass
    small_mass_movement = micrometer_to_meter(small_mass_movement)
    large_mass_movement = (large_mass_movement - small_mass_movement)
    small_mass = (large_mass * large_mass_movement) / small_mass_movement
    return small_mass

def energy_used (small_mass, small_mass_movement, gravitational_force):
# will return energy_used_in_joules
    energy_used_in_joules = (small_mass * small_mass_movement * gravitational_force)
    return energy_used_in_joules

def compare_to_a_bomb (energy_used_in_joules, joules_in_a_bomb):
# will return bomb_comparison_ratio
    compare_to_a_bomb = (energy_used_in_joules / joules_in_a_bomb)
    return compare_to_a_bomb

def meter_to_nanometer (meter):
    nanometer = meters /  (10 ** -9)
    return nanometer

def nanometer_to_meter (nanometer):
    meter = nanometer / 1000000000
    return meter

def meter_to_micrometer (meter):
    micrometer = meter / (10 ** -6)
    return micrometer

def micrometer_to_meter (micrometer):
    meter = micrometer / 1000000
    return meter

def terajoule_to_joule (terajoule):
    joule = terajoule * 1000000000000
    return joule

# these global variables are simply for testing purposes
# small_mass = 1
# small_mass_movement = 10
# large_mass = 2
# large_mass_movement = 20
# diameter_comparison_ratio = 3
# energy_used_in_joules = 4
# bomb_comparison_ratio = 5

for i in range (2):
    print("")

large_mass = 5.97291 * 10 ** 24
small_mass = 70
small_mass_movement = .2
diameter_of_atom = nanometer_to_meter(.1)
gravitational_force = 9.8
change_in_large_mass_position = change_in_earth_position(small_mass, small_mass_movement, large_mass)
print('')
print('')
print('If Chuck Norris weighed', small_mass,'kilograms and his center of mass moved', small_mass_movement, 'meters')
print(' then the earth would move', change_in_large_mass_position, 'meters away from him when')
print(' he pushed.')
print('')
print('')
print('In that case, the Earth is moving',
 compare_to_diameter_of_atom(diameter_of_atom, change_in_large_mass_position), 'times less than the')
print(' diameter of an atom.')
print('That doesnt sound like the Chuck Norris I know..')
print('')
print('')

small_mass_movement = (micrometer_to_meter(10))
atom_bomb_in_joules = terajoule_to_joule(38000)
small_mass = mass_of_smaller_body(10, large_mass, .2)
energy_used_by_small_mass = energy_used( small_mass, micrometer_to_meter(10), gravitational_force)

print('In order for Chuck to not noticeably move when he pushed, he would')
print(' have to weigh', small_mass, 'kilograms.')
print('')
print('')
print('If Chuck Norris weighed that much then he would have to use', energy_used_by_small_mass)
print(' joules of energy to do a push up!')
print('')
print('')
print('That much energy would be equivalent to', compare_to_a_bomb( energy_used_by_small_mass, terajoule_to_joule(38000)), 'atom bombs!!')
print(' Holy cow!')
print('')

for i in range (2):
    print('')

print("By the way, I think I submitted my final code under the test code")
print(" drop box.  Sorry I just realized now that I had no submission for")
print("the final project!")
