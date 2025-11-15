import re
from src.constants import ATTRIBUTION_TOKEN



def extract_quotes(generation: str) -> str:
    """
    Extract text between quotes that have been marked by an ATTRIBUTION_TOKEN

    Args:
        generation (str): Input text containing attributed content

    Returns:
        str: Extracted quote text marked by ATTRIBUTION_TOKEN, or empty string if not found
    """
    if not generation:
        return ""

    pattern = f"\".*\"{ATTRIBUTION_TOKEN}"
    match = re.search(pattern, generation)

    if match:

        return match.group(1).strip()
    return ""

