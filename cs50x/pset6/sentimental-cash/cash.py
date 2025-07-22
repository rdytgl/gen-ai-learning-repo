from cs50 import get_float

while True:
    change = get_float("Change: ")
    if change >= 0:
        break

# convert change into cents
cents = round(change * 100)  # to avoic floating point issues, we round

coins = 0

coins += cents // 25
cents = cents % 25

coins += cents // 10
cents = cents % 10

coins += cents // 5
cents = cents % 5

coins += cents // 1
cents = cents % 1

print(coins)
