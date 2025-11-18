# Accuracy-Based-Attribution-Loss

With the modern focus on RAG based systems that leverage AI based systems to accelerate the workflow by poroviing relevant responses based on user submitted content there has been a clear focus on preventing hallucations in cited content. The current approach to increase alignment is by fine tuning models on example datasets. Acquring these datasets is an incredibly time intensive process and requires a large amount of human work. These datasets are often very unexpansive and as a result can introduce bias as in order to provide accurate results a wide variety of domains to be represented in the example text. Trying to allieaviate these concerns I propose an automated method of determining accuracy by comparing the final generation to the source text. This allows for a far wider amount of texts to be represented while allowing for a broader text corpora to be easily trained on.

## types of loss function

### Quote Accuracy

The first proposed loss function to improve accuracy works by extracting citations in a generated response marked by an attribution token, and fuzzily searching for the quoted text in the source document. This "fuzzy search" is based on Levenshtein distance calculation from quotes to source text with an arbirtray theshold hyperparameter set. Due to the fact that Levenshtein distance is a mere count of the number of additions and deletions required translate text into the souce text the theshold is set to be a percentage of total tokens replaced.

The calcutaltion for accuracy of a given referrnce $r$ with a token count of $c$, a source text c a distance theshold of $t$,  and min_dist returing the minimal distance of search results of a source document.
references =_extract_references(generation)
$$
m = t * c \\

d= \begin{cases} \text{m}, & \text{mindist}(r, s)\text{ is nil}\\
\text{\text{mindist}(r, s)\\}, & \text{otherwise} \end{cases}\\
L(r, s) = - \log(1 - \frac{d}{m + \epsilon})  
$$

This places an exponentiall decay in the difference between quoted text and the ouput text. While giving an a massive penaly on hallucinated text.

### Local Alignment

Another key focus has been the cases where quoted text is not used accurately within the generated content. Trying to ensure allignment with source text to maintain accurate responses while maintating genereal flexibility in the final output. One way to do this is to measure the reliance on the quoted text in generated output. This method relies purely on the quoted text as it exists to focus on alighnemtn to ensure accurate quote usage.

To do this we can compare embedding vector of the $n$ many tokens of the sorrounding text with the quotes.The use of only the local sorrounding tokens is intentional as many generations use a variety of sources, and citations in the final output so localizatin restricts this to maintain overall generalization quality while still measuring alignment.

For a quote embedding $q$ and sorrounding texts embeddings $s$ the loss is as follows.

$$
L(q,s) = \log(\frac{s \times 1}{|s| * ||q||})
$$

This punished the models by how orthogonal it is to the wuotted text ensuring proper alignment.
