def change_in_earth_position (small_mass, small_mass_movement, large_mass):
# will return large_mass_movement
    large_mass_movement = (small_mass * small_mass_movement) / large_mass
    return large_mass_movement

def compare_to_diameter_of_atom (diameter_of_atom_in_nanometers, large_mass_movement):
# will return diameter_comparison_ratio
    diameter_of_atom = nanometer_to_meter(diameter_of_atom_in_nanometers)
    diameter_comparison_ratio = (diameter_of_atom / large_mass_movement)
    return diameter_comparison_ratio

def mass_of_smaller_body (small_mass_movement, large_mass, large_mass_movement):
# will return small_mass
    large_mass_movement = micrometer_to_meter(large_mass_movement)
    small_mass = (large_mass * large_mass_movement) / small_mass_movement
    return small_mass

def energy_used (small_mass, small_mass_movement, gravitational_force):
# will return energy_used_in_joules
    energy_used_in_joules = (small_mass * small_mass_movement * gravitational_force)
    return energy_used_in_joules

def compare_to_a_bomb (energy_used_in_joules, terajoules_in_a_bomb):
# will return bomb_comparison_ratio
    joules_in_a_bomb = terajoule_to_joule(terajoules_in_a_bomb)
    compare_to_a_bomb = (energy_used_in_joules / joules_in_a_bomb)
    return compare_to_a_bomb

def meter_to_nanometer (meter):
    nanometer = meters * 10 ** -9
    return nanometer

def nanometer_to_meter (nanometers):
    meter = nanometer * 1000000000
    return meter

def meter_to_micrometer (meter):
    micrometer = meter * 10 ** -6
    return micrometer

def micrometer_to_meter (micrometer):
    meter = micrometer * 1000000
    return meter

def terajoule_to_joule (terajoule):
    joule = terajoule / 1000000000000
    return joule

# these global variables are simply for testing purposes
# small_mass = 1
# small_mass_movement = 10
# large_mass = 2
# large_mass_movement = 20
# diameter_comparison_ratio = 3
# energy_used_in_joules = 4
# bomb_comparison_ratio = 5

print('')
change_in_earth_position(70, .2, 5.97291 * 10 ** 24)
print('If Chuck Norris weighed', small_mass,'kilograms and his center of mass moved', small_mass_movement, 'meters')
print(' then the earth would move', large_mass_movement, 'meters away from him when he pushed.')
print('')


print('In that case, the Earth is moving', diameter_comparison_ratio, 'times less than the diameter of an atom.')
print(' that doesnt sound like the Chuck Norris I know..')
print('')
print('In order to not noticeably move himself, Chuck Norris would have to weigh', small_mass)
print(' kilograms.')
print('')
print('If Chuck Norris weighed that much then he would have to use', energy_used_in_joules)
print(' joules of energy to do a push up!')
print('')
print('That much energy would be equivalent to', bomb_comparison_ratio, 'atom bombs!!  Holy cow!')
print('')
