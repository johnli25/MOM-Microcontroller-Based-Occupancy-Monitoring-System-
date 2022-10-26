import csv
import sys

hex_dict = [
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
]


def main(query: str):
    # Simple extraction
    with open("mac-vendors-export-2022-10-25.csv", "r", encoding="UTF8") as file:
        csvreader = csv.DictReader(file)
        with open(f"{query}-ouis.txt", "w") as outfile:
            for row in csvreader:
                if query in row["Vendor Name"].lower():
                    prefix = row["Mac Prefix"]
                    outfile.write(f"{prefix}\n")
    
    # Formatted as uints
    with open("mac-vendors-export-2022-10-25.csv", "r", encoding="UTF8") as file:
        csvreader = csv.DictReader(file)
        with open(f"{query}-ouis-uints.txt", "w") as outfile:
            for row in csvreader:
                if query in row["Vendor Name"].lower():
                    prefix = row["Mac Prefix"]
                    prefix_bytes = prefix.split(":")
                    prefix_in_int = "{"
                    for i, byte in enumerate(prefix_bytes):
                        hex_to_int = 0
                        for j, char in enumerate(byte):
                            if j == 0:
                                hex_to_int += hex_dict.index(char) * 16
                            else:
                                hex_to_int += hex_dict.index(char)
                        prefix_in_int += str(hex_to_int)
                        if i < 2:
                            prefix_in_int += ","
                    prefix_in_int += "}"
                    outfile.write(f"{prefix_in_int}\n")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 get_ouis.py company_to_search")
    else:
        main(sys.argv[1].lower())
