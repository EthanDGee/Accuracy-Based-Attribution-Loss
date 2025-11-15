# tests/test_evaluator.py
from src.constants import ATTRIBUTION_TOKEN
from src.evaluator import _extract_references, evaluate_accuracy, _find_closest_quote


class TestFindClosestQuote:

    def test_exact_match(self):
        # Test when the quote exactly matches a portion of the source
        quote = "This is a quote."
        source = "Some text before. This is a quote. Some text after."
        max_dist_ratio = 0.2
        match = _find_closest_quote(quote, source, max_dist_ratio)
        assert match is not None
        assert match.matched == quote
        assert match.dist == 0

    def test_no_match(self):
        # Test when the quote has no match in the source
        quote = "This quote does not exist."
        source = "Completely unrelated text."
        max_dist_ratio = 0.2
        match = _find_closest_quote(quote, source, max_dist_ratio)
        assert match is None


class TestEvaluateAccuracy:

    def test_evaluate_accuracy_with_perfect_match(self):
        # Test when all references have exact matches in the source
        generation = f'"This is a test quote."{ATTRIBUTION_TOKEN}'
        source = "This is a test quote."
        loss = evaluate_accuracy(generation, source)
        assert loss == 0.0

    def test_evaluate_accuracy_with_no_match(self):
        # Test when there are no matches in the source
        generation = f'"This is a test quote."{ATTRIBUTION_TOKEN}'
        source = "Completely unrelated text."
        loss = evaluate_accuracy(generation, source)
        assert loss > 0.0

    def test_evaluate_accuracy_with_partial_matches(self):
        # Test when references have partial matches in the source
        generation = f'"This is a simple quote."{ATTRIBUTION_TOKEN} "Another test."{ATTRIBUTION_TOKEN}'
        source = "This is a similar quote. This is not another test."
        loss = evaluate_accuracy(generation, source)
        assert loss > 0.0  # Ensure there is some loss due to partial matching


class TestExtractQuotes:

    def test_with_attribution_token(self):
        # Test when the generation has a valid quote with ATTRIBUTION_TOKEN
        generation = f'"This is a test quote."{ATTRIBUTION_TOKEN}'
        expected = ["This is a test quote."]
        assert _extract_references(generation) == expected

    def test_multiple_quotes(self):
        # Test when the generation has multiple quotes with attribution tokens
        generation = f'"This is a test quote."{ATTRIBUTION_TOKEN} "This is another test quote."{ATTRIBUTION_TOKEN}'
        expected = ["This is a test quote.", "This is another test quote."]
        assert _extract_references(generation) == expected

    def test_without_attribution_token(self):
        # Test when the generation has no ATTRIBUTION_TOKEN
        generation = '"This is a test quote without token."'
        expected = []
        assert _extract_references(generation) == expected

    def test_attribution_with_no_quotes(self):
        # Test when only part of the format exists
        generation = 'this is a test quote with no quotes {ATTRIBUTION_TOKEN}'
        expected = []
        assert _extract_references(generation) == expected

    def test_empty_string(self):
        # Test with an empty string input
        generation = ""
        expected = []
        assert _extract_references(generation) == expected

    def test_no_quotes(self):
        # Test when there are no quotes in the input
        generation = "This text has no quotes."
        expected = []
        assert _extract_references(generation) == expected
