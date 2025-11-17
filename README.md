# Accuracy-Based-Attribution-Loss

With the modern focus on RAG based systems that leverage AI based systems to accelerate the workflow by poroviing relevant responses based on user submitted content there has been a clear focus on preventing hallucations in cited content. The current approach to increase alignment is by fine tuning models on example datasets. Acquring these datasets is an incredibly time intensive process and requires a large amount of human work. These datasets are often very unexpansive and as a result can introduce bias as in order to provide accurate results a wide variety of domains to be represented in the example text. Trying to allieaviate these concerns I propose an automated method of determining accuracy by comparing the final generation to the source text. This allows for a far wider amount of texts to be represented while allowing for a broader text corpora to be easily trained on.

## types of loss function

### Quote Accuracy

The first proposed loss function to improve accuracy works by extracting citations in a generated response marked by an attribution token, and fuzzily searching for the quoted text in the source document. This "fuzzy search" is based on lehvenstien distance calculation from quotes to source text with an arbirtray theshold hyperparameter set. Due to the fact that lehvenstien distance is a mere count of the number of additions and deletions required translate text into the souce text the theshold is set to be a percentage of total tokens replaced.

The calcautaltion for accuracy of a given reference $r$ with a token count of $c$, a source text c a distance theshold of $t$,  and min_dist returing the minimal distance of search results of a source document.
references =_extract_references(generation)
$$
m = t * c \\



d= \begin{cases} \text{m}, & \text{mindist}(r, s)\text{ is nil}\\
\text{\text{mindist}(r, s)\\}, & \text{otherwise} \end{cases}\\ 
L(r, s) = - \log(1 - \frac{d}{m + \epsilon})  
$$

This places an exponentiall decay in the difference between quoted text and the ouput text. While giving an a massive penaly on hallucinated text. 

### Local Alignment
