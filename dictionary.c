/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include "dictionary.h"

#define HASH_SIZE 26

bool dictLoaded = false;
node atoz[HASH_SIZE];
unsigned int wordsInDict = 0;
FILE* dict;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
	char first = tolower(word[0]);
    int hash_index = first - 'a';
    node* traverser = &atoz[hash_index];
    
    while (true) {
    	if (traverser->next == NULL)
    		break;
    	else {
    		traverser = traverser->next;
    		if (strcasecmp(word, traverser->dictWord) == 0)
    			return true;
    	}
   	}
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    dict = fopen(dictionary, "r");
    
    if (dict != NULL) {
    	
    	dictLoaded = true;
    	
    	for (int i = 0; i < HASH_SIZE; i++)
    		atoz[i].next = NULL;
    	
    	while(!feof(dict)) {
    		node* newWord = malloc(sizeof(node));
    		if (fscanf(dict, "%s", newWord->dictWord) == 1) {	
				wordsInDict++;
				for (int i = 'a'; i <= 'z'; i++) {
					if ((newWord->dictWord)[0] == i) {
						if (atoz[i - 'a'].next == NULL) {
							newWord->next = NULL;
							atoz[i - 'a'].next = newWord;
							break;
						} else {
							newWord->next = atoz[i - 'a'].next;
							atoz[i - 'a'].next = newWord;
							break;
						}
					}	
				}
			} else
				free(newWord);			
    	}
    	return true;
    }
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (dictLoaded)
    	return wordsInDict;
    	
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    if (dictLoaded) {
    	for (int i = 0; i < HASH_SIZE; i++) {
    		node* traverser = &atoz[i];
    		traverser = traverser->next;
    		while (traverser != NULL) {
    			node* temp = traverser;
    			traverser = traverser->next;
    			free(temp);
    		}
    	}
    	fclose(dict);
    	return true;
    }
    return false;
}
