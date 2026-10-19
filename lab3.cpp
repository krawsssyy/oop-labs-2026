#define _CRT_SECURE_NO_WARNINGS // define line required at the top (!!) of your program, in order to use less secure functions like strcpy, strcat etc..
// needed for visual studio to suppress warnings about functions like strcpy and strcat
#include <iostream>
#include <string.h>

int main()
{
    char* s = new char[256];
    // C-style strings in C++ are ASCII-Z (ASCII zero terminated)
    // that means that every char-array in C++ declared/initialized with the "" syntax ends with the \0 character, which is used by the program to determine where the string ends
    // without it, it cannot determine where the string ends because it holds no other information, such as the length
    // so, for e.g., if we have the string "test", in memory it will look like: 't' 'e' 's' 't' \0

    // for e.g., if we have char x[] = {'t', 'e', 's', 't'}, this one does not end with \0
    // but if we do char x[] = "test", then it does
    std::cout << "Enter string:";
    std::cin.getline(s, 255); // use getline to read a string with spaces, as regular std::cin >> s stops at the first space
    // we give this one 255 to keep one spot open for the character we append with strcat
    // second argument to getline is the maximum length that the string can take, including the ending '\0', so this one reads at most 254 characters

    std::cout << "String 's' is: " << s << std::endl;
    std::cout << "String 's' length: " << strlen(s) << std::endl; // strlen returns the number of characters in the string !without the null terminator!
    // so, for the previous string "test", it will give 4, and not 5
    // !! beware of this, as when we'd like to copy some strings, the actual number of bytes we need is strlen(original) + 1, to account for that 0 character at the end
    char t[] = "X";
    strcat(s, t); // strcat appends the 2nd argument at the end of the 1st one
    // first is called destination, second is source
    // !! beware, strcat by itself does no length checks, it just blindly appends the source to the end of the destination, without ensuring that the destination can handle it
    // prefer the safer variants like strcat_s(destination, maximum_size_of_destination_buffer, source)
    std::cout << "String 's' is: " << s << std::endl;
    std::cout << "String 's' length: " << strlen(s) << std::endl;
    char* u = new char[strlen(s) + 1]; // exactly as said before, when we copy one string into another, we need to ensure that we account for that extra null terminator
    strcpy(u, s); // strcpy copies the 2nd argument (source) into the first one (destination), overwriting it
    // strcpy also copies the ending null terminator, so you don't need to set it manually
    // as with strcat, base strcpy does no size checks, and does not ensure that the destination is large enough to hold the source, so you'll have to ensure that manually!!\
    // prefer the safer variants like strcpy_s(destination, max_size_of_destination, source)
    std::cout << "String 'u' is: " << u << std::endl;
    std::cout << "String 'u' length: " << strlen(u) << std::endl;

    char* v = strtok(s, "XYZ"); // strtok allows us to tokenize a character array
    // that is, it basically allows us to split our array into chunks based on a given delimiter
    // the delimiter can be a string or a single character
    // when the delimiter is a string, ANY of the characters inside will act as delimiters
    // strtok returns the string until the first delimiter match (not-including it)
    // to get more chunks, we have to call strtok multiple times, where each call will return the next delimited token from our string
    // on subsequent calls, the first parameter to strtok becomes NULL, as this function holds an internal state where it already parsed our string from the first call
    // if we want to get all chunks, we call strtok until the return pointer is null
    // beware, pointers returned by strtok need not be deleted, we only delete dynamic memory allocated with new !!!

    // strtok also has a safe variant, strtok_s(source, delimiter, char** context), where we have to initialize a nullptr for the context(char* context = nullptr) and then pass
    // it along for all calls by reference (give the function &context), such that it can more straight-forwardly carry its internal state throughout calls

    // also, strtok consumes the strings, so beware of that
    // it modifies the original string by replacing delimiters with '\0'

    if (v == NULL) {
        std::cout << "No tokens to split by for strtok." << std::endl;
    }
    while (v != NULL) {
        std::cout << "String 'v' is: " << v << std::endl;
        v = strtok(NULL, "XYZ");
    }
    char* w = strstr(u, "XYZ"); // unlike strtok, strstr searches for the ENTIRE substring,
    // not any individual character from it
    // it returns a pointer to where that substring begins
    // on subsequent calls, we still have to give it the string, unlike strtok
    // but as with strtok, the pointer returned by it need not be deleted

    // also, beware, strstr does not consume the string like strtok and does not modify it any way like strtok does
    if (w != NULL) {
        std::cout << "First token from strstr: ";
        for (char* i = u; i < w; i++)
            std::cout << *i;
        std::cout << std::endl << "Rest of the string + delimiter: " << w << std::endl;
    }
    else {
        std::cout << "No tokens to split by for strstr." << std::endl;
    }
    delete[] u;
    u = nullptr;
    delete[] s;
    s = nullptr;

    // lab exercise: Given a sentence in a char*, print out the sentece's words and the number of words.

    char* sentence_strtok = new char[256];
    std::cout << "Enter string for the lab exercise: ";
    std::cin.getline(sentence_strtok, 256);

    char* sentence_strstr = new char[strlen(sentence_strtok) + 1];
    strcpy(sentence_strstr, sentence_strtok);

    // variant 1 - strtok
    std::cout << "strtok variant" << std::endl;
    char* stok = strtok(sentence_strtok, " ");
    int counter = 0;
    std::cout << "The words are: ";
    while (stok != NULL) {
        counter++;
        std::cout << stok << std::endl;
        stok = strtok(NULL, " ");
    }
    // or for(char* stok = strtok(sentence_strtok, " "); stok != NULL; stok = strtok(NULL, " ")) {
    //  counter++;
    //  std::cout << stok << " ";
    // }

    // this is a play on the syntax of FOR
    // FOR(initialization_stage; exit_condition_check; increment_stage)
    // the initialization stage dictates how the loop-variable is initialized (in our case, we loop over our string with strtok, so it makes sense that the pointer we used there is the loop variable)
    // the exit_condition_check tells the loop what is the condition of terminating it, that condition is checked before every iteration, and when it becomes false, the loop ends (i.e. the loop is active while that condition is true) - for us, we loop over the strtok'd string until we still have tokens left (i.e. stok != NULL)
    // the increment_stage tells the loop how to adjust (either increment or decrement) the loop variable for each step, that's done after every iteration of the loop to modify it for the next one, and in our case we get the next token from the string
    std::cout << std::endl << "This sentence has " << counter << " words." << std::endl << std::endl;

    // variant 2 - strstr
    std::cout << "strstr variant" << std::endl;
    char* sstr = strstr(sentence_strstr, " ");
    char* current = sentence_strstr; // we make a copy of our original pointer, because we'll need to modify it in the loop
    // if we do that on the original pointer, we'll modify the address it points
    // for delete[] to work properly, we need to keep the pointer unchanged
    counter = 0; // reset counter for this other variant
    std::cout << "The words are: ";
    while (sstr != NULL) {
        counter++;
        for (char* i = current; i < sstr; i++) // since strstr returns the start of the match, we print the string from our start up until that match, which is the word
            std::cout << *i;
        std::cout << std::endl;
        current = sstr + 1; // we move the new string to start after the match (we add the +1 to jump over the delimiter)
        // if we had a bigger size delimiter, we'd add strlen(delimiter) to jump over it
        sstr = strstr(current, " ");
    } // this loop ends when we no longer have any delimiters
    if (strlen(sentence_strstr) != 0) { // if our initial string is not empty, we print the remainder
        // this also acts as a check, so we don't increment the counter when the string is empty and wrongly print 1
        std::cout << current << std::endl; // print the last token, since it gets left out by that loop
        counter++; // since the loop leaves out the last token, we also need to increment our counter
    }
    std::cout << std::endl << "This sentence has " << counter << " words." << std::endl;

    delete[] sentence_strstr;
    sentence_strstr = nullptr;
    delete[] sentence_strtok;
    sentence_strtok = nullptr;

    return 0;
}


