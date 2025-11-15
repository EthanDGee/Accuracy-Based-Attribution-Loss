import re
from src.constants import ATTRIBUTION_TOKEN
from fuzzysearch import find_near_matches


def _extract_references(generation: str) -> list[str]:
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


def _find_closest_quote(quote: str, source: str, max_dist_ratio: float):
    max_l_dist = len(quote) * max_dist_ratio

    matches = find_near_matches(quote, source, max_l_dist=max_l_dist)

    best_match = None
    for match in matches:
        if best_match is None or match.dist < best_match.dist:
            best_match = match

    return best_match

