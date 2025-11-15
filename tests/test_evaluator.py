# tests/test_evaluator.py
from src.constants import ATTRIBUTION_TOKEN
from src.evaluator import extract_quotes


class TestExtractQuotes:

    def test_with_attribution_token(self):
        # Test when the generation has a valid quote with ATTRIBUTION_TOKEN
        generation = f'"This is a test quote."{ATTRIBUTION_TOKEN}'
        expected = ["This is a test quote."]
        assert extract_quotes(generation) == expected

    def test_multiple_quotes(self):
        # Test when the generation has multiple quotes with attribution tokens
        generation = f'"This is a test quote."{ATTRIBUTION_TOKEN} "This is another test quote."{ATTRIBUTION_TOKEN}'
        expected = ["This is a test quote.", "This is another test quote."]
        assert extract_quotes(generation) == expected

    def test_without_attribution_token(self):
        # Test when the generation has no ATTRIBUTION_TOKEN
        generation = '"This is a test quote without token."'
        expected = []
        assert extract_quotes(generation) == expected

    def test_attribution_with_no_quotes(self):
        # Test when only part of the format exists
        generation = 'this is a test quote with no quotes {ATTRIBUTION_TOKEN}'
        expected = []
        assert extract_quotes(generation) == expected

    def test_empty_string(self):
        # Test with an empty string input
        generation = ""
        expected = []
        assert extract_quotes(generation) == expected

    def test_no_quotes(self):
        # Test when there are no quotes in the input
        generation = "This text has no quotes."
        expected = []
        assert extract_quotes(generation) == expected
