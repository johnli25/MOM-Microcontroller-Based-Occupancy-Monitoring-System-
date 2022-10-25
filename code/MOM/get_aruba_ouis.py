import csv

with open('oui.csv', 'r', encoding='UTF8') as file:
    csvreader = csv.DictReader(file)
    with open('aruba-ouis.txt', 'w') as outfile:
        for row in csvreader:
            if 'aruba' in row['Organization Name'].lower():
                outfile.write(f'{row["Assignment"]}\n')
