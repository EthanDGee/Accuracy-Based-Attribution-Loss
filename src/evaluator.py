import re
from src.constants import ATTRIBUTION_TOKEN


def extract_quotes(generation: str) -> list[str]:
    """
    Extract text between quotes that have been marked by an ATTRIBUTION_TOKEN

    Args:
        generation (str): Input text containing attributed content

    Returns:
        list[str]: List of extracted quote texts marked by ATTRIBUTION_TOKEN, or empty list if none found
    """

    quotes: list[str] = []

    # loop through all the quotes in the text.
    for match in re.finditer(r'"(.*?)"', generation):
        start, end = match.span()
        quote_text = match.group(1)

        # check if the quote is followed by ATTRIBUTION_TOKEN
        after = generation[end: end + len(ATTRIBUTION_TOKEN)]
        if after == ATTRIBUTION_TOKEN:
            quotes.append(quote_text)

    return quotes
