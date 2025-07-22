import string


def main():
    while True:
        try:
            txt = input("Text: ")
            if len(txt) > 0:
                break
        except ValueError:
            pass

    sentences = count_sentences(txt)
    words = count_words(txt)
    letters = count_letters(txt)

    L = (letters / words) * 100
    S = (sentences / words) * 100

    index = (0.0588 * L) - (0.296 * S) - 15.8

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


def count_sentences(text):
    endings = ("!", ".", "?")
    sentence_count = 0
    for i in text:
        if i in endings:
            sentence_count += 1
    return sentence_count


def count_words(text):
    word_count = len(text.split())
    return word_count


def count_letters(text):
    text = text.lower()
    letter_count = 0
    for i in text:
        if i in string.ascii_lowercase:
            letter_count += 1
    return letter_count


if __name__ == "__main__":
    main()
