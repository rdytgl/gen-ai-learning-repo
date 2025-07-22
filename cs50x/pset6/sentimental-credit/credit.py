from cs50 import get_int
import re


def main():
    while True:
        try:
            card_number = get_int("What is your credit card number? ")
            if card_number > 0:
                break
        except ValueError:

            pass
    if cc_valid(card_number):
        print(cc_type(card_number))
    else:
        print("INVALID")


def cc_valid(cc_no):
    digits = [int(d) for d in str(cc_no)]
    total = 0
    # reverse the order of digits to make checksum easier
    digits.reverse()

    for i, digit in enumerate(digits):
        if i % 2 == 1:
            doubled = digit * 2
            total += sum(int(d) for d in str(doubled))
        else:
            total += digit

    return total % 10 == 0


def cc_type(cc_no):
    num = str(cc_no)

    if re.fullmatch(r"3[47][0-9]{13}", num):
        return "AMEX"
    elif re.fullmatch(r"5[1-5][0-9]{14}", num):
        return "MASTERCARD"
    elif re.fullmatch(r"4[0-9]{12}([0-9]{3})?", num):
        return "VISA"
    else:
        return "INVALID"


if __name__ == "__main__":
    main()
