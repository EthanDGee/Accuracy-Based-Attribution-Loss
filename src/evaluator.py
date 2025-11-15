import math
import re
from src.constants import ATTRIBUTION_TOKEN, EPSILON
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
    """
    Finds the closest matching sequence for the input `quote` within the
    `source` string, based on the allowable Levenshtein distance ratio.

    The method calculates the maximum Levenshtein distance allowed
    based on the given `max_dist_ratio` and the `quote` length. It then searches
    for substrings in the `source` that are close to the `quote`, and
    determines the best match based on the least Levenshtein distance.

    :param quote: The target string to search for in the source.
    :type quote: str
    :param source: The string in which to search for the closest match of the
                   `quote`.
    :type source: str
    :param max_dist_ratio: Defines the maximum allowed Levenshtein distance
                           between the `quote` and potential matches as a ratio
                           of the `quote` length. Must be a float between 0
                           and 1.
    :type max_dist_ratio: float
    :return: The closest match object representing the portion of the `source`
             that matches the `quote` within the allowable distance ratio.
             If no match is found, returns None.
    :rtype: Match or None
    """
    max_l_dist = int(len(quote) * max_dist_ratio)

    matches = find_near_matches(quote, source, max_l_dist=max_l_dist)

    best_match = None
    for match in matches:
        if best_match is None or match.dist < best_match.dist:
            best_match = match

    return best_match


def evaluate_accuracy(generation: str, source: str, max_dist_ratio: float = 0.2):
    """
    Evaluate the accuracy of a generation by comparing extracted references with their closest
    matches in the source, using a maximum distance ratio constraint.

    :param generation: Generated text containing references to compare with the source.
    :param source: Original text source to compare references against.
    :param max_dist_ratio: Maximum allowable ratio of distance for a match to be considered valid.
        Defaults to 0.2.
    :return: Total loss value computed by summing the logarithmic distance distribution
        of the closest matches for each reference.
    :rtype: float
    """
    references = _extract_references(generation)

    # having a total loss could potentially lead to the number of attributions decreasing as training progress
    total_loss = 0.0
    for reference in references:
        max_dist = max_dist_ratio * len(reference)
        distance = _find_closest_quote(reference, source, max_dist_ratio)

        # if the quote can't be found give it the maximumum penalty
        if distance is None:
            distance = max_dist
        else:
            distance = distance.dist

        # this punishes the result exponentially in reference to the ratio of max distance
        total_loss += -math.log(1 - (distance / (max_dist + EPSILON)))  # epsilon to avoid divide by zero

    return total_loss
